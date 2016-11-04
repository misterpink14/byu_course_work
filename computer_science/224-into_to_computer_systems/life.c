//	life.c	07/29/2013
//******************************************************************************
//  The Game of Life
//
//  Lab Description:
//
//  The universe of the Game of Life is an infinite two-dimensional orthogonal
//  grid of square cells, each of which is in one of two states, alive or dead.
//  With each new generation, every cell interacts with its eight neighbors,
//  which are the cells horizontally, vertically, or diagonally adjacent
//  according to the following rules:
//
//  1. A live cell stays alive (survives) if it has 2 or 3 live neighbors,
//     otherwise it dies.
//  2. A dead cell comes to life (birth) if it has exactly 3 live neighbors,
//     otherwise it stays dead.
//
//  An initial set of patterns constitutes the seed of the simulation. Each
//  successive generation is created by applying the above rules simultaneously
//  to every cell in the current generation (ie. births and deaths occur
//  simultaneously.)  See http://en.wikipedia.org/wiki/Conway's_Game_of_Life
//
//  Author:		Paul Roper, Brigham Young University
//  Revisions:	June 2013	Original code
//              07/12/2013	life_pr, life_cr, life_nr added
//              07/23/2013	generations/seconds added
//              07/29/2013	100 second club check
//
//  Built with Code Composer Studio Version: 5.3.0.00090
//******************************************************************************
//  Lab hints:
//
//  The life grid (uint8 life[80][10]) is an 80 row x 80 column bit array.  A 0
//  bit is a dead cell while a 1 bit is a live cell.  The outer cells are always
//  dead.  A boolean cell value is referenced by:
//
//         life[row][col >> 3] & (0x01 << (col % 8))
//
//  Each life cell maps to a 2x2 lcd pixel.
//
//                    00       01       02           07       08      09
//  life[79][0-9]  00000000 00000000 00000000 ... 00000000 00000000 00000000
//  life[78][0-9]  0xxxxxxx xxxxxxxx xxxxxxxx ... xxxxxxxx xxxxxxxx xxxxxxx0
//  life[77][0-9]  0xxxxxxx xxxxxxxx xxxxxxxx ... xxxxxxxx xxxxxxxx xxxxxxx0
//                 ...
//  life[02][0-9]  0xxxxxxx xxxxxxxx xxxxxxxx ... xxxxxxxx xxxxxxxx xxxxxxx0
//  life[01][0-9]  0xxxxxxx xxxxxxxx xxxxxxxx ... xxxxxxxx xxxxxxxx xxxxxxx0
//  life[00][0-9]  00000000 00000000 00000000 ... 00000000 00000000 00000000
//
//  The next generation can be made directly in the life array if the previous
//  cell values are held in the life_pr (previous row), life_cr (current row),
//  and life_nr (next row) arrays and used to count cell neighbors.
//
//  life_pr[0-9]  0xxxxxxx xxxxxxxx xxxxxxxx ... xxxxxxxx xxxxxxxx xxxxxxx0
//  life_cr[0-9]  0xxxxxxx xxxxxxxx xxxxxxxx ... xxxxxxxx xxxxxxxx xxxxxxx0
//  life_nr[0-9]  0xxxxxxx xxxxxxxx xxxxxxxx ... xxxxxxxx xxxxxxxx xxxxxxx0
//
//  Begin each new row by moving life_cr values to life_pr, life_nr values to
//  life_cr, and loading life_nr with the row-1 life values.  Then for each
//  column, use these saved values in life_pr, life_cr, and life_nr to
//  calculate the number of cell neighbors of the current row and make changes
//  directly in the life array.
//
//  life_pr[0-9] = life_cr[0-9]
//  life_cr[0-9] = life_nr[0-9]
//  life_nr[0-9] = life[row-1][0-9]
//
//******************************************************************************
//******************************************************************************
// includes --------------------------------------------------------------------
#include "msp430x22x4.h"
#include <stdlib.h>
#include <string.h>
#include "RBX430-1.h"
#include "RBX430_lcd.h"
#include "life.h"

// defined constants -----------------------------------------------------------
#define myCLOCK			1200000			// 1.2 Mhz clock
#define	WDT_CTL			WDT_MDLY_32		// WD configuration (SMCLK, ~32 ms)
#define WDT_CPI			32000			// WDT Clocks Per Interrupt (@1 Mhz)
#define	WDT_1SEC_CNT	myCLOCK/WDT_CPI	// WDT counts/second

// global variables ------------------------------------------------------------
volatile uint16 WDT_Sec_Cnt;			// WDT second counter
volatile uint16 seconds;				// # of seconds

uint8 life[NUM_ROWS][NUM_COLS/8];		// 80 x 80 life grid
uint8 life_pr[NUM_COLS/8];				// previous row
uint8 life_cr[NUM_COLS/8];				// current row
uint8 life_nr[NUM_COLS/8];				// next row

//------------------------------------------------------------------------------
// main ------------------------------------------------------------------------
void main(void)
{
	RBX430_init(_1MHZ);					// init board
	ERROR2(lcd_init());					// init LCD

	// configure Watchdog
	WDTCTL = WDT_CTL;					// Set Watchdog interval
	WDT_Sec_Cnt = WDT_1SEC_CNT;			// set WD 1 second counter
	IE1 |= WDTIE;						// enable WDT interrupt

	lcd_clear();						// clear LCD
	lcd_backlight(ON);					// turn on LCD backlight
	lcd_rectangle(0, 0, NUM_COLS*2, NUM_ROWS*2, 1);	// draw border

	__bis_SR_register(GIE);				// enable interrupts

	// output splash screen & wait for switch
	lcd_wordImage(life_image, (159-126)/2, 50, 1);
	lcd_mode(LCD_PROPORTIONAL | LCD_2X_FONT);
	lcd_cursor(10, 20);
	printf("Press Any Key");
	lcd_mode(0);
	while (1) if ((P1IN & 0x0f) ^ 0x0f) break;

	while (1)							// new pattern seed
	{
		// load initial seed patterns
		uint16 generation = 0;			// generation counter
		uint8 pen  = BIRTH;				// temp variable
		WDT_Sec_Cnt = WDT_1SEC_CNT;		// set WD 1 second counter
		seconds = 0;					// clear second counter

		while (1)						// successive generations
		{
			uint16 row, col;
			// for each live row (78 down to 1)
			for (row = NUM_ROWS-2; row; --row)
			{
				// for each live column (78 down to 1)
				for (col = NUM_COLS-2; col; --col)
				{
					if (pen == BIRTH)
					{
						cell_birth(row, col);
					}
					else
					{
						cell_death(row, col);
					}
				}
			}
			lcd_wordImage(life_image, (159-126)/2, 50, (BIRTH == pen) ? 3 : 1);
			lcd_cursor(4, 1);			// output life generation
			printf("%d/%d", ++generation, seconds);
			if (seconds == 100) while (1);
			pen = (pen == BIRTH) ? DEATH : BIRTH;
		}
	}
} // end main()


//------------------------------------------------------------------------------
// Watchdog Timer ISR ----------------------------------------------------------
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	if (--WDT_Sec_Cnt == 0)
	{
		WDT_Sec_Cnt = WDT_1SEC_CNT;		// reset counter
		++seconds;						// up seconds counter
		LED_GREEN_TOGGLE;				// toggle green LED
	}
} // end WDT_ISR(void)
