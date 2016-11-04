//	pong.c	08/08/2013
//******************************************************************************
//  Pong
//
//		THIS IS MY WORK
//			BENJAMIN THOMPSON
//			Section 1
//
//  Description:
//
//	Write a C program to play a 2-player game of Pong, a two-dimensional sports
//	game which simulates table tennis. Use the potentiometers to control the
//	paddles moving vertically on each side of the screen. The paddles and walls
//	reflect a ball back and forth at the correct speed and reflection angle.
//	A point is scored when one side fails to return the ball to the other side.
//	Show the score in real time on the LCD display.
//
//	Divide the paddle into segments to change the ball's angle of return.
//	For example, the center segments return the ball a 90° angle in relation to
//	the paddle, while the outer segments return the ball at smaller angles.
//	Make the ball accelerate the more it is returned back and forth between
//	paddles; missing the ball resets the speed.
//
//  Author:		Paul Roper, Brigham Young University
//  Revisions:	March 2010	Original code, split into files
//              08/05/2013	updated
//			08/08/2013	dx,dy signed values
//
//  Built with Code Composer Studio Version: 5.3.0.00090
//*******************************************************************************
//******************************************************************************
//
#include "msp430x22x4.h"
#include <stdlib.h>
#include <math.h>
#include "RBX430-1.h"
#include "RBX430_lcd.h"
#include "pong.h"

//------------------------------------------------------------------------------
// add service routine events here (bit additive):
#define MOVE_BALL		0x0001
#define ADC_READ		0x0002
#define SCORE			0x0004
#define NEW_GAME		0x0008
#define HIST			0x0010

//------------------------------------------------------------------------------
//   constants
#define myCLOCK			12000000		// 12 Mhz clock
#define	WDT_CTL			WDT_MDLY_32		// WD configuration (SMCLK, ~32 ms)
#define WDT_CPI			32000			// WDT Clocks Per Interrupt (@1 Mhz)
#define	WDT_1SEC_CNT	myCLOCK/WDT_CPI	// WDT counts/second
#define LCD_DELAY		50

//------------------------------------------------------------------------------
// pong global variables
volatile uint16 WDT_cps_cnt;			// watchdog counters
volatile uint16 WDT_adc_cnt;

volatile uint16 TB0_tone_on;			// PWM tones

volatile uint16 sys_event;				// pending events
volatile int16 dx, dy;					// ball delta change
volatile uint16 WDT_Sec_Cnt;			// WDT second counter

extern const uint16 pong_image[];		// 2 paddle image
extern const uint8 one[];
extern const uint8 two[];
extern const uint8 three[];
extern const uint8 go[];
short sc = 3;

int sec = WDT_1SEC_CNT;
int speed = BALL_SPEED;
short leftScore = 0;
short rightScore = 0;
short leftTotal = 0;
short rightTotal = 0;
unsigned short rally = 0;
unsigned short r = 0;
unsigned short ace = 0;

void win(int player);
void endGame();
void addScore();
void resetScore();
void mBall(BALL* ball, PADDLE* rightPaddle, PADDLE* leftPaddle);
void info();
//------------------------------------------------------------------------------
//
void main(void)
{


	// 	MSP430 Clock - Set DCO to 12 MHz:
	ERROR2(RBX430_init(_12MHZ));			// init board
	ERROR2(lcd_init());						// init LCD
	ERROR2(ADC_init());						// init ADC


	// configure watchdog
	WDTCTL = WDT_CTL;

	WDT_cps_cnt = WDT_CPS;
	// Set Watchdog interval
	WDT_Sec_Cnt = WDT_1SEC_CNT;				// set WD 1 second counter
	IE1 |= WDTIE;							// enable WDT interrupt
	WDT_adc_cnt = 0;

	// configure TimerA to move the ball
	TAR = 0;								// reset timer
	TACCR0 = 0;								// interrupt rate
	TACTL = TASSEL_2|ID_3|MC_1|TAIE;		// SMCLK/8, up mode, interrupt enable

	// configure TimerB h/w PWM for speaker
	P4SEL |= 0x20;							// P4.5 TB2 output
	TBR = 0;								// reset timer B
	TBCTL = TBSSEL_2 | ID_0 | MC_1;			// SMCLK, /1, UP (no interrupts)
	TBCCTL2 = OUTMOD_3;						// TB2 = set/reset

	__bis_SR_register(GIE);					// enable interrupts

	lcd_clear();							// clear LCD
	lcd_backlight(ON);						// turn on LCD
	lcd_wordImage(pong_image, 25, 35, 1);
	lcd_mode(LCD_2X_FONT);					// turn 2x font on
	lcd_cursor(20, 30);						// set display coordinates
	printf("P O N G");
	lcd_mode(~LCD_2X_FONT);					// turn 2x font off
	lcd_cursor(30, 5);
	printf("PRESS SWITCH 1");

	while (((P1IN & 0x0f) ^ 0x0f) != 1);			// wait for a switch


	lcd_clear();
	lcd_bitImage(three, 25, 35, 1);
	while(sec != 0);

	lcd_clear();
	lcd_bitImage(two, 25, 35, 1);
	while(sec != 0);

	lcd_clear();
	lcd_bitImage(one, 25, 35, 1);
	while(sec != 0);

	lcd_clear();
	lcd_bitImage(go, 25, 35, 1);
	while(sec != 0);
	lcd_clear();
	lcd_mode(LCD_2X_FONT);
	sc = 0;

	//-----------------------------------------------------------
	//	play forever
	while (1)
	{

		BALL* ball;							// game ball object
		PADDLE* rightPaddle;				// right paddle object
		PADDLE* leftPaddle;			// right paddle object

		lcd_volume(345);					// **increase as necessary*

		// manufacture and draw ball
		lcd_rectangle(0, 158, 162, 2, 1);
		lcd_rectangle(0, 0, 162, 2, 1);
		lcd_rectangle(79, 0, 3, 160, 1);

		ball = new_ball(80, 80);
		drawBall(ball);

		leftPaddle = new_paddle(LEFT_POT, 0);
		drawPaddle(leftPaddle);

		// manufacture and draw paddle
		rightPaddle = new_paddle(RIGHT_POT, 157);
		drawPaddle(rightPaddle);


		dx = rand() % 2 ? -1 : 1;			// delta x
		dy = rand() % 2 ? -1 : 1;			// delta y
		WDT_adc_cnt = 1;					// start sampling the paddles
		TACCR0 = speed;				        // interrupt rate
		sys_event = 0;						// no events pending
		lcd_mode(LCD_2X_FONT);

		//-----------------------------------------------------------
		//	event service routine loop
		//-----------------------------------------------------------
		while (1)
		{
			// disable interrupts while checking sys_event
			_disable_interrupts();

			// if event pending, enable interrupts
			if (sys_event) _enable_interrupt();

			// else enable interrupts and goto sleep
			else __bis_SR_register(LPM0_bits | GIE);

			//-------------------------------------------------------
			//	I'm AWAKE!!!  What needs service?
			if (sys_event & MOVE_BALL)				// timer A event
			{
				sys_event &= ~MOVE_BALL;			// clear TimerA event
				mBall(ball, rightPaddle, leftPaddle);
			}
			else if (sys_event & ADC_READ)			// read ADC event
			{
				sys_event &= ~ADC_READ;				// clear ADC event
				ADC_READ_event(rightPaddle);		// process new
				ADC_READ_event(leftPaddle);
			}
			else if (sys_event & SCORE)
			{
				sys_event &= ~SCORE;
				free(ball);
				addScore();
				ball = new_ball(80, 80);
				drawBall(ball);
			}
			else if (sys_event & NEW_GAME)
			{
				sys_event &= ~NEW_GAME;
				endGame();
				resetScore();
				free(ball);
				free(rightPaddle);
				free(leftPaddle);
				break;
			}
			else if (sys_event & HIST)
			{
				int delay = (WDT_1SEC_CNT/2);
				while(--delay);
				info();
				drawPaddle(rightPaddle);		// process new
				drawPaddle(leftPaddle);
				while(sec != 0);
				sys_event &= ~HIST;
			}
			else									// ????
			{
				ERROR2(10);							// unrecognized event
			}
		}
	}
} // end main

void win (int player)
{
	lcd_mode(~LCD_2X_FONT);
	lcd_cursor(player, 65);						// set display coordinates
	printf("You WIN!");
	lcd_mode(LCD_2X_FONT);
	BEEP3;
	while(--WDT_cps_cnt != 0);
	BEEP2;
	while(--WDT_cps_cnt != 0);
	BEEP3;
	while(--WDT_cps_cnt != 0);
	BEEP4;
	while(--WDT_cps_cnt != 0);
	BEEP5;
	while(--WDT_cps_cnt != 0);
	BEEP6;
	while(--WDT_cps_cnt != 0);
	lcd_clear();
	lcd_mode(LCD_2X_FONT);
	return;
}

void addScore()
{
	if(sc == 1)
	{
		sc = 0;
		rightScore++;
		lcd_cursor(65, 140);						// set display coordinates
		printf("%d", leftScore);
		lcd_cursor(86, 140);						// set display coordinates
		printf("%d", rightScore);
	}
	else if(sc == 2)
	{
		sc = 0;
		leftScore++;
		lcd_cursor(65, 140);						// set display coordinates
		printf("%d", leftScore);
		lcd_cursor(86, 140);						// set display coordinates
		printf("%d", rightScore);
	}
	speed = BALL_SPEED;
	if(r > rally)
	{
		rally = r;
	}
	r = 0;
}

void endGame()
{
	if(leftScore == 5)
	{
		win(10);
	}
	if(rightScore == 5)
	{
		win(90);
	}
}

void mBall(BALL* ball, PADDLE* rightPaddle, PADDLE* leftPaddle)
{
	if(((ball->x) == 153) && ((abs((ball->y) - (rightPaddle->y)) <= 8)))
	{
		if(abs((ball->y) - (rightPaddle->y)) <= 1)
			dy = MOVE_BALL_event(ball, 8, 8, 0);		// update ball position
		else if(abs((ball->y) - (rightPaddle->y)) <= 5)
			dy = MOVE_BALL_event(ball, 8, 8, 1);
		else
			dy = MOVE_BALL_event(ball, 8, 8, 2);
		r++;
	}
	else if (((ball->x) == 7) && (abs((leftPaddle->y) - (ball->y)) <= 8))
	{
		if(abs((ball->y) - (leftPaddle->y)) <= 1)
			dy = MOVE_BALL_event(ball, 8, 8, 0);	// update ball position
		else if(abs((ball->y) - (leftPaddle->y)) <= 5)
			dy = MOVE_BALL_event(ball, 8, 8, 1);
		else
			dy = MOVE_BALL_event(ball, 8, 8, 2);
		r++;
	}
	else
	{
		if (ball->x == -3)
		{
			sc = 2;
			if(r < 2)
				ace++;
		}
		else if (ball->x == 162)
		{
			sc = 1;
			if(r < 2)
				ace++;
		}
		else
			dy = MOVE_BALL_event(ball, -3, 8, dy);
	}
}

void resetScore()
{
	rightScore = 0;
	leftScore = 0;
	rightTotal++;
	leftTotal++;
}

void update()
{
	lcd_rectangle(79, 0, 3, 160, 1);	// keep middle rect
	lcd_cursor(65, 140);						// set display coordinates
	printf("%d", leftScore);
	lcd_cursor(86, 140);						// set display coordinates
	printf("%d", rightScore);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Timer A1 interrupt service routine
//
#pragma vector = TIMERA1_VECTOR
__interrupt void TIMERA1_ISR(void)
{
	TACTL &= ~TAIFG;					// acknowledge interrupt

	TACCR0 = speed;				// adjust ball speed
	sys_event |= MOVE_BALL;				// signal move ball event
	__bic_SR_register_on_exit(LPM0_bits);
	return;
} // end TIMERA1_VECTOR

void info()
{
	sc = 3;
	while(sec != 0);
	lcd_clear();
	lcd_cursor(0, 16);						// set display coordinates
	printf("Left\nWins\n%d", leftTotal);
	lcd_rectangle(1, 30, 20, leftTotal*4, 1);

	lcd_cursor(25, 16);						// set display coordinates
	printf("Right");
	lcd_cursor(25, 8);
	printf("Wins");
	lcd_cursor(25, 0);
	printf("%d", rightTotal);
	lcd_rectangle(26, 30, 20, rightTotal*4, 1);

	lcd_cursor(56, 16);						// set display coordinates
	printf("Longest");
	lcd_cursor(56, 8);
	printf("Rally");
	lcd_cursor(56, 0);
	printf("%d", rally);
	lcd_rectangle(57, 30, 20, rally*4, 1);

	lcd_cursor(99, 16);						// set display coordinates
	printf("Ace");
	lcd_cursor(99, 8);
	printf("Count");
	lcd_cursor(96, 0);
	printf("%d", ace);
	lcd_rectangle(97, 30, 20, ace*4, 1);

	lcd_cursor(130, 16);						// set display coordinates
	printf("Total");
	lcd_cursor(130, 8);
	printf("Games");
	lcd_cursor(130, 0);
	printf("%d", (leftTotal + rightTotal));
	lcd_rectangle(131, 30, 20, (leftTotal + rightTotal)*4, 1);

	while(((P1IN & 0x0f) ^ 0x0f) != SW_2);
	lcd_clear();
	lcd_mode(LCD_2X_FONT);
	lcd_rectangle(0, 158, 162, 2, 1);
	lcd_rectangle(0, 0, 162, 2, 1);
	lcd_rectangle(79, 0, 3, 160, 1);
	P1IN = 0x0f;
	sc = 0;
}


//------------------------------------------------------------------------------
//	Watchdog Timer ISR
//
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	if (--WDT_cps_cnt == 0)				// 1 second?
	{
		LED_GREEN_TOGGLE;				// toggle green LED
		WDT_cps_cnt = WDT_CPS;			// freset counter
	}
	// decrement tone counter - turn off tone when 0
	if (TB0_tone_on && (--TB0_tone_on == 0)) TBCCR0 = 0;

	// decrement adc event counter - signal to read adc
	if (WDT_adc_cnt && (--WDT_adc_cnt == 0))
	{
		WDT_adc_cnt = WDT_ADC;
		sys_event |= ADC_READ;			// signal ADC event
	}
	if(sec == 0){
		sec = WDT_1SEC_CNT;
		if(sc == 0)
			lcd_rectangle(79, 0, 3, 160, 1);	// keep middle rect
	}

	if(((P1IN & 0x0f) ^ 0x0f) == 2)
		sys_event |= HIST;

	if((sec == (WDT_1SEC_CNT/2)) && (sc == 0))
	{
		update();
		if (speed >= (BALL_SPEED/5))
			speed *= .9;
	}

	if((sc == 1) || (sc == 2))
	{
		sys_event |= SCORE;
	}
	sec--;
	if ((leftScore == 5) || (rightScore == 5))
		sys_event |= NEW_GAME;

	// wake up processor if there are any events pending
	if (sys_event) __bic_SR_register_on_exit(LPM0_bits);
	return;
} // end WDT_ISR



//------------------------------------------------------------------------------
// un-initialized MSP430F2274 interrupt vectors
#pragma vector=PORT1_VECTOR,PORT2_VECTOR,TIMER0_A0_VECTOR,NMI_VECTOR,	\
		USCIAB0RX_VECTOR,USCIAB0TX_VECTOR,TIMERB0_VECTOR,TIMERB1_VECTOR
__interrupt void ISR_trap(void)
{
	ERROR2(SYS_ERR_ISR);				// unrecognized event
	WDTCTL = 0;							// Write to WDT with a wrong password
}
