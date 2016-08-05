/* Partner	1	Jeremy Pang	&	E-mail: jpang007@ucr.edu
 
 * Partner	2	Andy Long	&	E-mail: along010@ucr.edu
 
 * Lab	Section: 221
 
 * Assignment:	Lab	5	Exercise	4
 
 * Exercise	Description:	[optional	- include	for	your	own	benefit]
 
 * SM that also is linked to a LCD screen is an extension of button stopping game
 
 * I	acknowledge	all	content	contained	herein,	excluding
 
 *	template	or	example	code,	is	my	own	original	work.
 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "C:\Users\student\Documents\Atmel Studio\6.2\GccApplication3\GccApplication3\io.c"
enum States { START,STATE0, STATE1, WAIT,WAIT2,WAIT3,WAIT4} State;
volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.
// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks
unsigned char a = 0x00;
unsigned char counter = 0;
unsigned char counter2 = 5;
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

void tsk() {
	
	switch(State) {   // Transitions
		case START:  // Initial transition
		if(~PINA & 0x01){
			State = WAIT;
		}
		else{
			State = START;
		}
		break;
		
		case WAIT:
		if(~PINA & 0x01) {
			State = WAIT;
		}
		else {
			State = STATE1;
		}
		break;
		
		case WAIT3:
		if(~PINA & 0x01) {
			State = WAIT4;
		}
		else {
			State = WAIT3;
		}
		break;
		
		case WAIT4:
		if(~PINA & 0x01){
			State = WAIT4;
		}
		else{
			State = STATE1;
		}
		break;
		
		case STATE1:
		PORTB = a;
		LCD_Cursor(1);
		LCD_WriteData(counter2 + '0');
		if (!(~PINA & 0x01) && a == 0x00) {
			a = 0x01;
			counter = 1;
			State = STATE1;
		}
		else if (!(~PINA & 0x01) && a == 0x01) {
			a = 0x02;
			counter = 2;
			State = STATE1;
		}
		else if (!(~PINA & 0x01) && a == 0x02) {
			a = 0x04;
			counter = 3;
			State = STATE1;
		}
		else if (!(~PINA & 0x01) && a == 0x04) {
			a = 0x01;
			counter = 4;
			State = STATE1;
		}
		else {
			State = WAIT2;
		}
		break; // Transitions
		
		case WAIT2:
		if (~PINA & 01) {
			State = WAIT2;
			if(counter == 3) {
				counter2++;
				if (counter2 == 9) {
					LCD_DisplayString(1 ,"Winner!!");
				}
			}
			else{
				if(counter2 > 0){
				counter2--;
				}
			}			
		}
		else{

			State = WAIT3;
		}
	}
}

void main()
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00; // Init port B to 0s
	DDRD = 0xFF; PORTD = 0x00;
	TimerSet(10);
	TimerOn();

	unsigned char tmpB = 0x00;
	LCD_Cursor(1);
	LCD_WriteData(5 + '0');
	while(1) {
		// User code (i.e. synchSM calls)
		tsk();
		while (!TimerFlag); // Wait 1 sec
		TimerFlag = 0;
		// Note: For the above a better style would use a synchSM with TickSM()
		// This example just illustrates the use of the ISR and flag
	}
}
