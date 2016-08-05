/*
 * GccApplication1.c
 *
 * Created: 8/4/2016 1:08:21 PM
 *  Author: student
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
//unsigned arr2[26] = {1,2,3,2,1,1,1,2,2,2,1,1,1,1,2,3,2,1,1,1,1,2,2,1,2,3};
 double arr[30] = {440.00,392.00,349.63,392.00,440.00,440.00,444.000,0,392.00,392.00,392.00,0,444.00,532.25,532.25,0,
	 440.00,392.00,349.63,392.00,440.00,440.00,440.00,440.00,392.00,392.00,440.00,392.00,349.63,0};
unsigned char cnt = 0;


volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmershould clear to 0.
// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks
void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s
	// AVR output compare register OCR1A.
	OCR1A = 125; // Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt
	//Initialize avr counter
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds
	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}
void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}
void TimerISR() {
	TimerFlag = 1;
}
// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		// prevents OCR3A from underflowing, using prescaler 64
		// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}
void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}
void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}
unsigned char yo = 0;

enum States { START,WAIT, WAIT2, PLAY} State;
void tsk() {
	switch (State) {
		case START:
			State = WAIT;
		break;
		
		case WAIT: 
	
			if(~PINA & 0x01 && yo == 0){
				PWM_on();
				set_PWM(arr[0]);
				cnt++;	
				yo = 1;
				State = WAIT2;
			}
			else if(yo == 1){
				State = PLAY;
			}
			else {
				State = WAIT;
			}
		break;
		
		case WAIT2:
		if(~PINA & 0x01){
			State = WAIT2; 
		}
		else {
		 State = WAIT;
		}
		break;
		
		case PLAY:
		if(cnt == 30){
			PWM_off();
			cnt = 0;
			yo = 0;
			State = WAIT;
		}
		else {
			set_PWM(arr[cnt]);
			cnt++;
			State = WAIT;
		}
		break;
	}
}
int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerOn();
	TimerSet(200);
	PWM_on();
	
	State = START; 
	
    while(1)
    {

		tsk();
		while (!TimerFlag); // Wait 1 sec
		TimerFlag = 0;
       //TODO:: Please write your application code 
    }
}
