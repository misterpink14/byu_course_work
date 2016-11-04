//	pongEvents.c	08/08/2013
//******************************************************************************
//******************************************************************************
//	ALL THESE FUNCTIONS REQUIRE REWORK!
//******************************************************************************
//******************************************************************************
//
#include "msp430x22x4.h"
#include <stdlib.h>
#include "RBX430-1.h"
#include "RBX430_lcd.h"
#include "pong.h"

extern volatile int16 dx, dy;
extern volatile uint16 TB0_tone_on;
extern volatile uint16 sys_event;		// pending events

BALL myBall;							// **replace with malloc'd struct**
PADDLE myPaddle;						// **replace with malloc'd struct**

//------------------------------------------------------------------------------
//	ball factory (fix by malloc'ing ball struct)
//
BALL* new_ball(int x, int y)
{
	// initialize ball values
	myBall.x = x;						// set horizontal position
	myBall.y = y;						// set vertical position
	myBall.old_x = myBall.x;			// set old values
	myBall.old_y = myBall.y;
	return &myBall;
} // end init_ball


//------------------------------------------------------------------------------
//	paddle factory (fix by malloc'ing paddle struct)
//
PADDLE* new_paddle(int channel, int x)
{
	myPaddle.channel = channel;			// ADC input channel
	myPaddle.x = x;						// horizontal paddle position
	myPaddle.y = ADC_read(channel) >> 2;
	myPaddle.old_y = 0;
	return &myPaddle;					// return pointer to paddle
} // end init_ball


//------------------------------------------------------------------------------
//	ADC event - paddle potentiometer and draw paddle (fix)
//
void ADC_READ_event(PADDLE* paddle)
{
	int pot = ADC_read(paddle->channel);	// sample potentiometer

	// check for paddle position change
	if ((abs(pot - paddle->potValue) > POT_THRESHHOLD))
	{
		paddle->potValue = pot;			// save old value
		paddle->y = pot >> 3;			// update paddle position (fix)
		drawPaddle(paddle);				// draw paddle
	}
	return;
} // end ADC_READ_event


//------------------------------------------------------------------------------
//	TimerA event - move ball (fix)
//
void MOVE_BALL_event(BALL* ball)
{
	ball->x += dx;						// increment x coordinate
	ball->y += dy;						// update y coordinate
	if ((ball->y > HD_Y_MAX-6) || (ball->y < 2))
	{
		dy = -dy;
	}
	drawBall(ball);						// ok, draw ball in new position

	if ((ball->x < 5) || (ball->x > HD_X_MAX-11))
	{
		dx = -dx;						// reverse ball direction
		BEEP;
	}
	return;
} // end MOVE_BALL_event
