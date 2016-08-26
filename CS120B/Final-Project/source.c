
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h> // used for rand


#include "C:\Users\Jeremy\Desktop\New folder (4)\bit.h"
#include "C:\Users\Jeremy\Desktop\New folder (4)\timer.h"
#include "C:\Users\Jeremy\Desktop\New folder (4)\io.c"
#include "C:\Users\Jeremy\Desktop\New folder (4)\keypad.h"

unsigned short obstacle1 = 16;
unsigned short obstacle2 = 25;
unsigned short obstacle3 = 0;
unsigned char clearseventenn = 0;
unsigned short obstacle4 = 0;
unsigned char arr1[4] = {12, 13, 14, 15};
unsigned char arr2[3] = {22, 23, 24};
unsigned char arr3[4] = {28, 29, 30, 31};
unsigned char arr4[3] = {10, 11, 12};
unsigned char arr[4] = {10, 11, 26, 27};
unsigned char playerpos = 2;
unsigned char playerpos2 = 16;
unsigned char pause1,x,y,z,i, a, counter2, filler, delaytimer, holderperiod = 0;
unsigned char countertotal = 2;
unsigned char gunvalue = 1;
unsigned long counter = 0; // needs to hold huge variable i guess
unsigned char holder = 0; // holds the menu
unsigned char spotholder = 2; // tracks the top spot
unsigned char spotholder2 = 18; //tracks the bottom spot
unsigned char spotholder3 = 2; // track the top spot for right / left movement
unsigned char spotholder4 = 18; // track the bootom spot for right / left down movement
unsigned char onetimechecker = 0; // another one time checker that gets turned to one to only allow clear screen once
unsigned char gunz = 0; // this will track the position of the pew pew shooter
unsigned char anothertimechecker = 0; // basis off the reset to display the *
unsigned short playerperiod = 0;
unsigned short realtskperiod = 0;
unsigned char roundone, roundtwo = 0;
unsigned short displayperiod = 0;
unsigned short displaycnt = 80;
unsigned short scorecounter, y2 = 0;
unsigned char playertwochecker = 0;
unsigned char gunmotion = 0;
unsigned char obstacle4motion = 0;
 long score = 0; // its the score duh
enum States0{wait,up,down,right, left, reset, pause, gun} State0;
void keypad(){
	switch(State0){
		case wait:
		counter++;
		delaytimer++;

		LCD_Cursor(17);
		LCD_Cursor(' ');
		if (playertwochecker == 1) {
			if (z == 'A') {
				playerpos2 = 16;
				y2 = 0;
				State0 = up;
			}
			else if (z == 'B') {
				playerpos2 = 32;
				y2 = 0;
				State0 = down;
			}
			else if (z == 'C') {
				if (obstacle4motion == 1) {
					LCD_Cursor(obstacle4);
					LCD_WriteData(' ');
				}

				if (playerpos2 == 16) {
					obstacle4 = 12;
				}
				if (playerpos2 == 32) {
					obstacle4 = 27;
				}

				obstacle4motion = 1;
			}
		}
		if (anothertimechecker == 1 && pause1 != 3) {
			LCD_Cursor(playerpos);
			LCD_WriteData('*');
			anothertimechecker = 0;
		}

		if(z == '\0'){
			State0 = wait;
		}

		if ((obstacle1 < 1 && roundone == 0) || (obstacle1 < 17 && roundone == 1)) {
			State0 = reset;

		}

		else if (z == '8'){
			if (playerpos >= 2 && playerpos <= 7) {
			playerpos = playerpos + 16;
			y = 0;
			State0 = down;
			}
		}

		else if (z == '6'){
				if ((playerpos >= 2 && playerpos < 7) || (playerpos >= 18 && playerpos < 23)) {
 				playerpos++;
				spotholder++;
				spotholder2++;
				y = 0;
				State0 = right;
				}
		}

		else if (z == '4'){
				if ((playerpos > 2 && playerpos <= 7) || (playerpos > 18 && playerpos <= 23)) {
				playerpos--;
				spotholder--;
				spotholder2--;
				y = 0;
				State0 = left;
				}
		}


		else if(z == '2'){
			if (playerpos >= 18 && playerpos <= 23) {
			playerpos = playerpos - 16;
			y = 0;
			State0 = up;
			}
		}

		else if (z == '5') { // in charge of firing the pew pew
			if (gunmotion == 1) {
				LCD_Cursor(gunz);
				LCD_WriteData(' ');
			}
			gunz = playerpos + 1;
			State0 = gun;
			gunvalue = 0;
			gunmotion = 1;

		}
		else if(z == '0'){
			if(pause1 == 0){
				pause1 = 1;
			}
			else if(pause1 == 1){
				pause1 = 0;
			}
			else if(pause1 == 3){
				PORTB = 0x00;
				gunz = 50;
				pause1 = 0;
				x = 0;
				y = 0;
				counter = 0;
				counter2 = 0;
				spotholder = 2;
				gunvalue = 0;
				delaytimer = 0;
				spotholder2 = 18;
				playerperiod = 0;
				realtskperiod = 0;
				displayperiod = 0;
				if (playertwochecker == 1) {
					playerpos2 = 16;
					obstacle4 = 0;
				}
				displaycnt = 100;
				roundone = rand() % 2;
				if (roundone == 0) {
					obstacle1 = 16;
					obstacle2 = 22;
					obstacle3 = rand() % (15 + 1 - 12) + 12;
				}
				else if (roundone == 1) {
					obstacle1 = 32;
					obstacle2 = 8;
					obstacle3 = rand() % (24 + 1 - 21) + 21;
				}
				playerpos = 2;
				LCD_ClearScreen();
			}
			else{}
			State0 = pause;
		}
		else{State0 = wait;}
		break;

		case up:
		if(z == '2'){
			State0 = up;
		}
		else{
			State0 = wait;
		}
		break;

		case down:
		if(z == '8'){
			State0 = down;
		}
		else{
			State0 = wait;
		}
		break;

		case right:
		if(z == '6'){
			State0 = right;
		}
		else{
			State0 = wait;
		}
		break;

		case gun:
			State0 = wait;
		break;

		case left:
		if(z == '4'){
			State0 = left;
		}
		else{
			State0 = wait;
		}
		break;

		case pause:
		if(z == '0'){
			State0 = pause;
		}
		else{
			State0 = wait;
		}
		break;

		case reset:
		// Need to reset the player position to put them in an neverending game until they die
		// Must take into consideration where they are before ending
		PORTB++;
		counter = 0;
		gunz = 33;
		gunvalue = 0;
		counter2 = 0; // used for random generator
		countertotal = 16; // used for reset
		spotholder = spotholder; // used for right and left
		delaytimer = 0; // ? might incorporate as a delay if needed
		spotholder2 = spotholder2;
		LCD_ClearScreen();
		roundone = rand() % 2;
		if (playertwochecker == 1) {
			playerpos2 = playerpos2;
			obstacle4 = 0;
		}
		if (roundone == 0) {
			obstacle1 = 16;
			obstacle2 = 22;
			obstacle3 = rand() % (15 + 1 - 12) + 12;
		}
		else if (roundone == 1) {
			obstacle1 = 32;
			obstacle2 = 8; // essentially "randomly" generates objects the obstacle2 are much closer to user able to kill them very easily
			obstacle3 = rand() % (24 + 1 - 21) + 21;
		}
		playerpos = playerpos;
		anothertimechecker = 1;
		State0 = wait;
		break;
	}
}

enum States3{Waitfor} State3;

void menu() {
	switch(State3) {
		case Waitfor:
			if (holder == 0) {
				LCD_ClearScreen();
				LCD_DisplayString(1,"Press * for 1P  Press # for 2P");
				counter2++;
				if (z == '*') {
					holder = 1;
					srand(counter2);
					i = rand() % 5;
					a = rand() % 4;
					LCD_ClearScreen();
				}
				if (z == '#') {
					playertwochecker = 1;
					holder = 1;
					srand(counter2);
					i = rand() % 5;
					a = rand() % 4;
					LCD_ClearScreen();
				}
			}

			break;
	}
}

enum States{DEC} State;
void realtsk(){
	switch(State){
		case DEC:
		if(pause1 == 0){
			LCD_Cursor(17);
			LCD_WriteData(' ');
			if (roundone == 0) {
				obstacle1--;
			}
			else if (roundone == 1) {
				if (obstacle1 > 16) {
					obstacle1--;
				}
			}

			if (roundone == 0) {
				if (obstacle2 > 16)
				obstacle2--;
			}
			else if (roundone == 1) {
				obstacle2--;
			}

			scorecounter++;

			obstacle3--;
			if (obstacle3 == 1) {
				obstacle3 = 0;
			}

			if (playertwochecker == 1) {
				obstacle4--;
				if (obstacle4 == 1) {
					obstacle4 = 0;
				}

			}
			if (gunvalue == 0) {
				gunz++;

				if (gunz == 16) {
					gunz = 0;
				}
				else if (gunz == 32) {
					gunz = 0;
				}

			}

			countertotal--; // used to track when to reset
			if(obstacle1 == playerpos || obstacle2 == playerpos || obstacle3 == playerpos
			|| obstacle1 + 1 == playerpos || obstacle2 + 1 == playerpos || obstacle3 + 1 == playerpos
			|| obstacle4 == playerpos || obstacle4 + 1 == playerpos){
				LCD_Cursor(playerpos + 1);
				LCD_WriteData('<');
				LCD_Cursor(playerpos - 1);
				LCD_WriteData('>');
				LCD_Cursor(playerpos);
				LCD_WriteData('X');
				LCD_Cursor(0);
				delay_ms(2000);
				LCD_Cursor(playerpos + 1);
				LCD_WriteData('X');
				LCD_Cursor(playerpos - 1);
				LCD_WriteData('X');
				LCD_Cursor(0);
				delay_ms(2000);
				pause1 = 3;

			}
			if (gunz == obstacle3 || (gunz - 1) == obstacle3) {
				gunvalue = 1;
			}
			else if (gunz == obstacle4 || (gunz - 1) == obstacle4) {
				obstacle4motion = 0;
				gunvalue = 2;
			}
		}
		LCD_Cursor(17);
		LCD_WriteData(' ');
		break;


	}
}
enum States2{wait0} State2;
void displaytsk(){
	switch(State2){
		case wait0:
		if(pause1 == 0){
			LCD_Cursor(17);
			LCD_WriteData(' ');
			LCD_Cursor(obstacle1 + 1);
			LCD_WriteData(' ');
			LCD_Cursor(obstacle1);
			LCD_WriteData('<');

			LCD_Cursor(obstacle2 + 1);
			LCD_WriteData(' ');
			LCD_Cursor(obstacle2);
			LCD_WriteData('<');

			LCD_Cursor(obstacle3 + 1);
			LCD_WriteData(' ');
			LCD_Cursor(obstacle3);
			LCD_WriteData('#');

			if (playertwochecker == 1) {
			LCD_Cursor(obstacle4 + 1);
			LCD_WriteData(' ');
			LCD_Cursor(obstacle4);
			LCD_WriteData('#');
			}

			if (gunvalue != 1) {

				LCD_Cursor(gunz - 1);
				LCD_WriteData(' ');
				LCD_Cursor(gunz);
				LCD_WriteData('-');

				if (playerpos < 15) {
					LCD_Cursor(spotholder);
					LCD_WriteData('*');
				}
				else if (playerpos > 17) {
					LCD_Cursor(spotholder2);
					LCD_WriteData('*');
				}
			}

			if (gunvalue == 1) {
				LCD_Cursor(gunz - 1);
				LCD_WriteData(' ');
				LCD_Cursor(gunz);
				LCD_WriteData(' ');
				LCD_Cursor(obstacle3);
				LCD_WriteData(' ');
				if (playerpos < 15) {
					LCD_Cursor(spotholder);
					LCD_WriteData('*');
				}
				else if (playerpos > 17) {
					LCD_Cursor(spotholder2);
					LCD_WriteData('*');
				}
				gunvalue = 0;
				gunz = 33;
				obstacle3 = 500;
				gunmotion = 0;
			}
			if (gunvalue == 2) {
				LCD_Cursor(gunz - 1);
				LCD_WriteData(' ');
				LCD_Cursor(gunz);
				LCD_WriteData(' ');
				LCD_Cursor(obstacle4);
				LCD_WriteData(' ');
				if (playerpos < 15) {
					LCD_Cursor(spotholder);
					LCD_WriteData('*');
				}
				else if (playerpos > 17) {
					LCD_Cursor(spotholder2);
					LCD_WriteData('*');
				}
				gunvalue = 0;
				gunz = 33;
				obstacle4 = 500;
				gunmotion = 0;

			}


			/*
			if (playerpos == obstacle2 && y == 0) {
				LCD_Cursor(spotholder);
				LCD_WriteData('*');
				LCD_Cursor(spotholder2);
				LCD_WriteData(' ');

				y = 1;
			}
			*/
			if (playerpos == obstacle1 && y == 0) {
				LCD_Cursor(spotholder);
				LCD_WriteData('*');
				LCD_Cursor(spotholder2);
				LCD_WriteData(' ');

				y = 1;
			}

			if(obstacle2 == 1){
				LCD_Cursor(1);
				LCD_WriteData(' ');
			}

			if(obstacle1 == 1){
				LCD_Cursor(1);
				LCD_WriteData(' ');
			}

			if(obstacle4 == 1){
				LCD_Cursor(1);
				LCD_WriteData(' ');
			}

			if(obstacle4 == 17){
				LCD_Cursor(17);
				LCD_WriteData(' ');
			}


			if(obstacle3 == 17){
				LCD_Cursor(17);
				LCD_WriteData(' ');
				obstacle3 = 0;
			}

			if(obstacle3 == 16){
				LCD_Cursor(16);
				LCD_WriteData(' ');
			}

			if(gunz == 16){
				LCD_Cursor(16);
				LCD_WriteData(' ');
			}

			if(gunz == 16){
				LCD_Cursor(16);
				LCD_WriteData(' ');
			}

			if(gunz == 32){
				LCD_Cursor(32);
				LCD_WriteData(' ');
			}

			if(gunz == 32){
				LCD_Cursor(32);
				LCD_WriteData(' ');
			}

			if(obstacle2 == 17){
				LCD_Cursor(17);
				LCD_WriteData(' ');
			}

			if(obstacle1 == 17){
				LCD_Cursor(17);
				LCD_WriteData(' ');
			}


			if(obstacle2 == 16){
				LCD_Cursor(16);
				LCD_WriteData(' ');
			}

			if(obstacle1 == 16){
				LCD_Cursor(16);
				LCD_WriteData(' ');
			}
			if (playertwochecker == 1) {
				if (playerpos2 == 16) {
					LCD_Cursor(16);
					LCD_WriteData('!');
					LCD_Cursor(32);
					LCD_WriteData(' ');
				}
				if (playerpos2 == 32) {
					LCD_Cursor(32);
					LCD_WriteData('!');
					LCD_Cursor(16);
					LCD_WriteData(' ');
				}
			}
			if(playerpos < 15 && y == 0){
				LCD_Cursor(1);
				LCD_WriteData(' ');
				LCD_Cursor(17);
				LCD_WriteData(' ');
				LCD_Cursor(spotholder);
				LCD_WriteData('*');
				LCD_Cursor(spotholder2);
				LCD_WriteData(' ');
				LCD_Cursor(spotholder - 1);
				LCD_WriteData(' ');
				LCD_Cursor(spotholder + 1);
				LCD_WriteData(' ');
				playerpos = spotholder;
				y = 1;
			}
			else if(playerpos > 17 && y == 0){
				LCD_Cursor(1);
				LCD_WriteData(' ');
				LCD_Cursor(17);
				LCD_WriteData(' ');
				LCD_Cursor(spotholder2);
				LCD_WriteData('*');
				LCD_Cursor(spotholder);
				LCD_WriteData(' ');
				LCD_Cursor(spotholder2 - 1);
				LCD_WriteData(' ');
				LCD_Cursor(spotholder2 + 1);
				LCD_WriteData(' ');
				playerpos = spotholder2;
				y = 1;
			}

		}
		else if(pause1 == 3 && x == 0){
			x = 1;
			LCD_ClearScreen();
			LCD_DisplayString(1,"    YOU DEAD        Score: ");
			LCD_Cursor(28);

			unsigned char score1 = 0;
			score1 = scorecounter / 1000;
			scorecounter = scorecounter - score1 * 1000;
			unsigned char score2 = 0;
			score2 = scorecounter / 100;
			unsigned char score3 = 0;
			scorecounter = scorecounter - score2 * 100;
			score3 = scorecounter / 10;
			unsigned char score4 = 0;
			scorecounter = scorecounter - score3 * 10;
			score4 = scorecounter;
			if(score1 != 0){
				   LCD_WriteData(score1 + '0');
			}
			if(score2 != 0){
				  LCD_WriteData(score2 + '0');
			 }
			if(score3 != 0){
				LCD_WriteData(score3 + '0');
			}
			if(score4 != 0){
				LCD_WriteData(score4 + '0');
			}
			counter2++;
		}
		LCD_Cursor(17);
		LCD_WriteData(' ');
		break;
	}
}

int main()
{
	// Set Data Direction Registers
	// Buttons PORTA[0-7], set AVR PORTA to pull down logic
	DDRA = 0xF0; PORTA = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;// LCD data lines
	DDRD = 0xFF; PORTD = 0x00;

	PORTB = 0x00;

	// Set the timer and turn it on

	TimerSet(10);
	TimerOn();
	LCD_init();
	LCD_ClearScreen();

	State0 = wait;
	State = DEC;
	State2 = wait0;
	LCD_Cursor(2);
	srand(1);
	i = rand() % 2;
	obstacle1 = i;
	while(1){
		z = GetKeypadKey();

		if (z == 'D') { // MUST DO A SOFT RESET IN MAIN
			holder = 0;
			PORTB = 0x00;
			playertwochecker = 0;
			gunz = 50;
			pause1 = 0;
			x = 0;
			y = 0;
			counter = 0;
			counter2 = 0;
			spotholder = 2;
			scorecounter = 0;
			gunvalue = 0;
			delaytimer = 0;
			spotholder2 = 18;
			playerperiod = 0;
			realtskperiod = 0;
			displayperiod = 0;
			displaycnt = 100;
			roundone = rand() % 2;
			if (roundone == 0) {
				obstacle1 = 16;
				obstacle2 = 22;
				obstacle3 = rand() % (15 + 1 - 12) + 12;
			}
			else if (roundone == 1) {
				obstacle1 = 32;
				obstacle2 = 8;
				obstacle3 = rand() % (24 + 1 - 21) + 21;
			}
			playerpos = 2;
			LCD_ClearScreen();
		}

		if (holderperiod == 10 && holder == 0) {
			menu();
			holderperiod = 0;
		}
		else {
			holderperiod++;
		}

			i = rand() % 5;

		if(playerperiod == 10){
			if (holder != 0) { // preemptive check against all other functions running at the start menu
				// this prevents anything from really happening user can only press 5 to start game
			keypad();
			}
			playerperiod = 0;
		}
		else{
			playerperiod++;
		}
		if(realtskperiod == displaycnt){
			if (holder != 0) {
			realtsk();
			}
			realtskperiod = 0;
			if (displaycnt > 18 && holder != 0) {
				displaycnt = displaycnt - 2;
			}
		}
		else{
			realtskperiod++;
		}
		if(displayperiod == 10){
			if (holder != 0) {
			displaytsk();
			}
			displayperiod = 0;
		}
		else{
			++displayperiod;
		}
		while(!TimerFlag){}
		TimerFlag = 0;
		LCD_Cursor(0);

		if (clearseventenn == 5) {
		LCD_Cursor(1);
		LCD_WriteData(' ');
		LCD_Cursor(17);
		LCD_WriteData(' ');
		}
		clearseventenn++;


	}

	// Error: Program should not exit!
	return 0;
}
