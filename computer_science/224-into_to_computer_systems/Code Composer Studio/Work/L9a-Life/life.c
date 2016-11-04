//	life.c	07/29/2013
//******************************************************************************
//  The Game of Life
//
//	THIS IS MY OWN WORK
//			BENJAMIN THOMPSON
//			SECTION 1
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
#define myCLOCK			16000000		// 1.2 Mhz clock
#define	WDT_CTL			WDT_MDLY_32		// WD configuration (SMCLK, ~32 ms)
#define WDT_CPI			32000			// WDT Clocks Per Interrupt (@1 Mhz)
#define	WDT_1SEC_CNT	myCLOCK/WDT_CPI	// WDT counts/second

// global variables ------------------------------------------------------------
volatile uint16 WDT_Sec_Cnt;			// WDT second counter
volatile uint8 seconds;					// # of seconds

uint8 life[NUM_ROWS][NUM_COLS/8];		// 80 x 80 life grid
uint8 life_pr[NUM_COLS/8];				// previous row
uint8 life_cr[NUM_COLS/8];				// current row
uint8 life_nr[NUM_COLS/8];				// next row

//------------------------------------------------------------------------------
// main ------------------------------------------------------------------------
void main(void)
{
	RBX430_init(_16MHZ);					// init board
	ERROR2(lcd_init());						// init LCD

	// configure Watchdog
	WDTCTL = WDT_CTL;						// Set Watchdog interval
	WDT_Sec_Cnt = WDT_1SEC_CNT;				// set WD 1 second counter
	IE1 |= WDTIE;							// enable WDT interrupt

	lcd_clear();							// clear LCD
	lcd_backlight(ON);						// turn on LCD backlight

	__bis_SR_register(GIE);					// enable interrupts

	// output splash screen & wait for switch
	lcd_wordImage(life_image, (159-126)/2, 50, 1);
	lcd_mode(LCD_PROPORTIONAL | LCD_2X_FONT);
	lcd_cursor(10, 20);
	printf("Press Any Key");
	lcd_mode(0);

	while (1)								// new pattern seed
	{
		// load initial seed patterns
		unsigned short switches;
		while (1){
			if (switches = (P1IN & 0x0f) ^ 0x0f){break;}
		}
		while (1)							// successive generations
		{
			uint16 generation = 0;			// generation counter
			WDT_Sec_Cnt = WDT_1SEC_CNT;		// set WD 1 second counter
			seconds = 0;					// clear second counter

			init_life(switches);

			while(1)// successive generations
			{
				memset(life_pr,0, 10*sizeof(uint8));
				memcpy(life_cr,life[NUM_ROWS-2], 10*sizeof(uint8));
				memcpy(life_nr,life[NUM_ROWS-3], 10*sizeof(uint8));

				unsigned short row;
				for(row = NUM_ROWS-2; row ; --row)
				{
					unsigned short col;
					for(col = NUM_COLS-2; col; --col)
					{
						const short THREE = 3;
						unsigned short ALIVE_count = cell_value(life_pr, (col-1)) + cell_value(life_pr, (col)) + cell_value(life_pr, (col+1))
								+ cell_value(life_cr, (col-1)) + cell_value(life_cr, (col+1))
								+ cell_value(life_nr, (col-1)) + cell_value(life_nr, col) + cell_value(life_nr, (col+1));
						if(cell_value(life_cr, col) == 1)
						{
							if((ALIVE_count != 2) && (ALIVE_count != THREE))
							{
								cell_death(row, col);
							}
						}
						else
						{
							if(ALIVE_count == THREE)
							{
								cell_birth(row, col);
							}
						}
					}
					memcpy(life_pr,life_cr, 10*sizeof(uint8));
					memcpy(life_cr,life_nr, 10*sizeof(uint8));
					memcpy(life_nr,life[row-2], 10*sizeof(uint8));
				}
				LED_RED_TOGGLE;
				if (switches = (P1IN & 0x0f) ^ 0x0f){break;}
				lcd_cursor(2, 1);
				printf("%d/%d", ++generation, seconds);
				lcd_cursor(144,1);
				printf("%2d", (generation/seconds));
				LED_RED_TOGGLE;
				if (seconds == 100){
					while (1){
 						if (switches = (P1IN & 0x0f) ^ 0x0f){break;}
					}
					break;
				}
			}
		}
	}
} // end main()

void draw_rle_pattern(int row, int col, const uint8* object)
{
	int number = 0;
	const uint8* ptr = object;

	for(;*ptr != 16; ptr++)
	{
		if(*ptr != 'y'){ continue;}
		ptr += 4;
		while((*ptr >= '0') && (*ptr <= '9'))
			number = number * 10 + (*ptr++ - '0');
		break;
	}
	row += number;
	short i = 0;
	for(;*ptr != '!'; ptr++)
	{

		number = 0;
		while((*ptr >= '0') && (*ptr <= '9'))
			number = number * 10 + (*ptr++ - '0');
		if(number == 0){
			number = 1;
		}
		number += i;
		if(*ptr == 'b'){
			for(; i < number; i++){
			cell_death(row, (col+i));
			}
			continue;
		}
		else if(*ptr == 'o'){
			for(; i < number; i++){
				cell_birth(row, (col+i));
			}
			continue;
		}
		else if(*ptr == '$'){
			for(; i < number; i++){
				row--;
			}
			i = 0;
		}
	}
}

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

void init_life(unsigned short switches)
{
	memset(life,0, 800*sizeof(uint8));
	if (switches == LIFE){
		lcd_clear();
		//memset(life_pr,0, 10*sizeof(uint8));
		draw_rle_pattern(65, 30, gosper_glider_gun);
		draw_rle_pattern(60, 5, pulsar);
		draw_rle_pattern(4, 7, beacon_maker);
		draw_rle_pattern(4, 30, hexapole);
		draw_rle_pattern(4, 40, hexapole);
		draw_rle_pattern(4, 50, hexapole);
		draw_rle_pattern(4, 60, hexapole);
		draw_rle_pattern(15, 65, loafer);

		return;
	}
	else if(switches == BIRD){
		lcd_clear();
		//memset(life_pr,0, 10*sizeof(uint8));
		draw_rle_pattern(60, 5, pulsar);            // sun
		draw_rle_pattern(31, 2, bird);              // bird
		draw_rle_pattern(40, 20, hwss);             // bigger bird
		draw_rle_pattern(11, 29, glider);           // blows bird apart
		draw_rle_pattern(65, 65, loafer);
		short i;
		for (i = 2; i < 78; i += 3)                 // draw ground
		{
		   draw_rle_pattern(7, i, block);           // block
		}

		return;
	}
	else if(switches == BOMB){
		lcd_clear();
		//memset(life_pr,0, 10*sizeof(uint8));
		draw_rle_pattern(65, 10, gosper_glider_gun);
		draw_rle_pattern(40, 10, lwss);             // LWSS

		draw_rle_pattern(20, 10, pulsar);           // pulsar
		draw_rle_pattern(20, 35, pulsar);           // pulsar
		draw_rle_pattern(20, 60, pulsar);           // pulsar

		draw_rle_pattern(10, 10, block);            // block
		draw_rle_pattern(10, 18, beehive);          // beehive
		draw_rle_pattern(10, 26, loaf);             // loaf
		draw_rle_pattern(10, 34, boat);             // boat
		draw_rle_pattern(10, 42, toad);             // toad
		draw_rle_pattern(10, 50, beacon);           // beacon
		draw_rle_pattern(10, 58, blinker);          // blinker
		draw_rle_pattern(10, 66, by_flop);          // by_flop
		return;
	}
	else{
		lcd_clear();
		//memset(life_pr,0, 10*sizeof(uint8));
		draw_rle_pattern(66, 5, gosper_glider_gun);
		draw_rle_pattern(32, 4, blinker_puffer);
		draw_rle_pattern(4, 5, gosper_glider_gun2);
	}
	return;
}

