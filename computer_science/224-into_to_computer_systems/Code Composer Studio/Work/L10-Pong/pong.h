//	pong.h	08/07/2013
#ifndef PONG_H_
#define PONG_H_
//*******************************************************************************
//
//                            MSP430F2274
//                  .-----------------------------.
//            SW1-->|P1.0^                    P2.0|<->LCD_DB0
//            SW2-->|P1.1^                    P2.1|<->LCD_DB1
//            SW3-->|P1.2^                    P2.2|<->LCD_DB2
//            SW4-->|P1.3^                    P2.3|<->LCD_DB3
//       ADXL_INT-->|P1.4                     P2.4|<->LCD_DB4
//        AUX INT-->|P1.5                     P2.5|<->LCD_DB5
//        SERVO_1<--|P1.6 (TA1)               P2.6|<->LCD_DB6
//        SERVO_2<--|P1.7 (TA2)               P2.7|<->LCD_DB7
//                  |                             |
//         LCD_A0<--|P3.0                     P4.0|-->LED_1 (Green)
//        i2c_SDA<->|P3.1 (UCB0SDA)     (TB1) P4.1|-->LED_2 (Orange) / SERVO_3
//        i2c_SCL<--|P3.2 (UCB0SCL)     (TB2) P4.2|-->LED_3 (Yellow) / SERVO_4
//         LCD_RW<--|P3.3                     P4.3|-->LED_4 (Red)
//   TX/LED_5 (G)<--|P3.4 (UCA0TXD)     (TB1) P4.4|-->LCD_BL
//             RX-->|P3.5 (UCA0RXD)     (TB2) P4.5|-->SPEAKER
//           RPOT-->|P3.6 (A6)          (A15) P4.6|-->LED 6 (R)
//           LPOT-->|P3.7 (A7)                P4.7|-->LCD_E
//                  '-----------------------------'
//
//******************************************************************************
// system equates
//
#define myCLOCK			12000000		// 12 Mhz clock
#define	WDT_CTL			WDT_MDLY_32		// WD configuration (SMCLK, ~32 ms)
#define WDT_CPI			32000			// WDT Clocks Per Interrupt (@1 Mhz)
#define	WDT_1SEC_CNT	myCLOCK/WDT_CPI	// WDT counts/second
#define twoSec			2*WDT_1SEC_CNT;
#define WDT_CLK			32000				// 32 Khz WD clock (@1 Mhz
#define	WDT_CPS			myCLOCK/WDT_CLK

//------------------------------------------------------------------------------
// pong equates
//
#define WDT_ADC		WDT_CPS/10		// 100 ms

#define BEEP_COUNT		myCLOCK/3000
#define BEEP_COUNT1		(myCLOCK/300)
#define BEEP_COUNT2		(myCLOCK/468)
#define BEEP_COUNT3		(myCLOCK/348)
#define BEEP_COUNT4		(myCLOCK/548)
#define BEEP_COUNT5		(myCLOCK/700)
#define BALL_SPEED		32000
#define POT_THRESHHOLD	1

#define BEEP TBCCR0 = BEEP_COUNT; TBCCR2 = BEEP_COUNT >> 1; TB0_tone_on = 20;
#define BEEP1 TBCCR0 = BEEP_COUNT1; TBCCR2 = BEEP_COUNT1 >> 1; TB0_tone_on = 40;
#define BEEP2 TBCCR0 = BEEP_COUNT2; TBCCR2 = BEEP_COUNT2 >> 1; TB0_tone_on = 100;
#define BEEP3 TBCCR0 = BEEP_COUNT3; TBCCR2 = BEEP_COUNT3 >> 1; TB0_tone_on = 80;
#define BEEP4 TBCCR0 = BEEP_COUNT4; TBCCR2 = BEEP_COUNT4 >> 1; TB0_tone_on = 100;
#define BEEP5 TBCCR0 = BEEP_COUNT5; TBCCR2 = BEEP_COUNT5 >> 1; TB0_tone_on = 100;
#define BEEP6 TBCCR0 = BEEP_COUNT4; TBCCR2 = BEEP_COUNT4 >> 1; TB0_tone_on = 120;

//------------------------------------------------------------------------------
// pong structs
//
typedef struct					// ball struct
{
	int x;						// horizontal position
	int y;						// vertical position
	int old_x;					// previous horizontal position
	int old_y;					// previous vertical position
} BALL;

typedef struct					// paddle struct
{
	int channel;				// ADC id
	int potValue;				// last ADC value
	int x;						// horizontal position
	int y;						// vertical position
	int old_y;					// previous vertical position
} PADDLE;

//------------------------------------------------------------------------------
// pong prototypes
//
BALL* new_ball(int x, int y);
void delete_ball(BALL* ball);
int drawBall(BALL* ball);
PADDLE* new_paddle(int channel, int x);
void delete_paddle(PADDLE* paddle);
int drawPaddle(PADDLE* myPaddle);

int MOVE_BALL_event(BALL* ball, short xx, short yy, uint16 val);
void ADC_READ_event(PADDLE* paddle);

#endif /*PONG_H_*/
