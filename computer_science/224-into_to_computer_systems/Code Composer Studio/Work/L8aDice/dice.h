// defined constants -----------------------------------------------------------
#define myCLOCK			8000000			// 1.2 Mhz clock
#define	WDT_CTL			WDT_MDLY_8		// WD configuration (Timer, SMCLK, ~32 ms)
#define WDT_CPI			1000			// WDT Clocks Per Interrupt (@1 Mhz)
#define	WDT_1SEC_CNT	myCLOCK/WDT_CPI/8	// WDT counts/second (32 ms)

#define BEEP			2000			// beep frequency
#define BEEP_CNT		8				// beep duration
#define BEEP1			myCLOCK/1468/12*10			// beep frequency
#define BEEP2			myCLOCK/1648/12*10			// beep frequency
#define BEEP3			myCLOCK/1746/12*10			// beep frequency
#define BEEP4			myCLOCK/1950/12*10			// beep frequency

// external/internal prototypes ------------------------------------------------
extern int rand16(void);				// get random #
extern int random(int, int);

void WDT_sleep(int delay);			// WDT sleep routine
void doTone(uint16 tone, uint16 time);	// output tone
void drawDie(uint8 die, uint8* old_die, int16 x, int16 y);
int get_switch(int);
