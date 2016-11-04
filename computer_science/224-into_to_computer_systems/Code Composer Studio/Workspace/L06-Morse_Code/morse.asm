;*******************************************************************************
;     Project:  morse.asm
;      Author:  Benjamin J Thompson

;			THIS IS MY OWN CODE
;
; Description:  Outputs a message in Morse Code using a LED and a transducer
;               (speaker).  The watchdog is configured as an interval timer.
;               The watchdog interrupt service routine (ISR) toggles the green
;               LED every second and pulse width modulates (PWM) the speaker
;               such that a tone is produced.
;
;******************************************************************************
;                            MSP430F2274
;                  .-----------------------------.
;            SW1-->|P1.0^                    P2.0|<->LCD_DB0
;            SW2-->|P1.1^                    P2.1|<->LCD_DB1
;            SW3-->|P1.2^                    P2.2|<->LCD_DB2
;            SW4-->|P1.3^                    P2.3|<->LCD_DB3
;       ADXL_INT-->|P1.4                     P2.4|<->LCD_DB4
;        AUX INT-->|P1.5                     P2.5|<->LCD_DB5
;        SERVO_1<--|P1.6 (TA1)               P2.6|<->LCD_DB6
;        SERVO_2<--|P1.7 (TA2)               P2.7|<->LCD_DB7
;                  |                             |
;         LCD_A0<--|P3.0                     P4.0|-->LED_1 (Green)
;        i2c_SDA<->|P3.1 (UCB0SDA)     (TB1) P4.1|-->LED_2 (Orange) / SERVO_3
;        i2c_SCL<--|P3.2 (UCB0SCL)     (TB2) P4.2|-->LED_3 (Yellow) / SERVO_4
;         LCD_RW<--|P3.3                     P4.3|-->LED_4 (Red)
;   TX/LED_5 (G)<--|P3.4 (UCA0TXD)     (TB1) P4.4|-->LCD_BL
;             RX-->|P3.5 (UCA0RXD)     (TB2) P4.5|-->SPEAKER
;           RPOT-->|P3.6 (A6)          (A15) P4.6|-->LED 6 (R)
;           LPOT-->|P3.7 (A7)                P4.7|-->LCD_E
;                  '-----------------------------'
;******************************************************************************
; System equates --------------------------------------------------------------
            .cdecls C,"msp430.h"            ; include c header
myCLOCK     .equ    1200000                 ; 1.2 Mhz clock
WDT_CTL     .equ    WDT_MDLY_0_5            ; WD conf: Timer, SMCLK, 0.5 ms
WDT_CPI     .equ    500                     ; WDT Clocks Per Interrupt (@1 Mhz)
WDT_IPS     .equ    myCLOCK/WDT_CPI         ; WDT Interrupts Per Second
STACK       .equ    0x0600                  ; top of stack


; External references ---------------------------------------------------------
            .ref    numbers                 ; codes for 0-9
            .ref    letters                 ; codes for A-Z
            .ref    DOT,DASH,END

;  numbers--->N0$--->DASH,DASH,DASH,DASH,DASH,END      ; 0
;             N1$--->DOT,DASH,DASH,DASH,DASH,END       ; 1
;             ...
;             N9$--->DASH,DASH,DASH,DASH,DOT,END       ; 9
;
;  letters--->A$---->DOT,DASH,END                      ; A
;             B$---->DASH,DOT,DOT,DOT,END              ; B
;             ...
;             Z$---->DASH,DASH,DOT,DOT,END             ; Z

;	Morse code is composed of dashes and dots, or phonetically, "dits" and
;    "dahs".  There is no symbol for a space in Morse, though there are rules
;    when writing them.

;	1. One dash is equal to three dots
;	2. The space between parts of the letter is equal to one dot
;	3. The space between two letters is equal to three dots
;	4. The space between two words is equal to seven dots.

;	5 WPM = 60 sec / (5 * 50) elements = 240 milliseconds per element.
;	element = (WDT_IPS * 6 / WPM) / 5

;	Morse Code equates
ELEMENT     .equ    WDT_IPS*240/1000
                            
; Global variables ------------------------------------------------------------
            .bss    beep_cnt,2              ; beeper flag
            .bss    delay_cnt,2             ; delay flag
          	.bss    debounce_cnt,2        ; debounce count
          	.bss	second, 2

; Program section -------------------------------------------------------------
            .text                           ; program section
message:    .string "HELLO CS 142 WORLD"	; message
            .byte   0
            .align  2                       ; align on word boundary

RESET:      mov.w   #STACK,SP               ; initialize stack pointer
            mov.w   #WDT_CTL,&WDTCTL        ; set WD timer interval
            mov.b   #WDTIE,&IE1             ; enable WDT interrupt
            bis.b   #0x60,&P4DIR            ; set P4.5/P3.5 as output (speaker/red LED)
            bis.b	#0x40,&P4DIR
            clr.w   &beep_cnt               ; clear counters
            clr.w   &delay_cnt
            bis.w   #GIE,SR                 ; enable interrupts
            bic.b   #0x0f,&P1SEL          ; RBX430-1 push buttons
            bic.b   #0x0f,&P1DIR          ; Configure P1.0-3 as Inputs
            bis.b   #0x0f,&P1OUT          ; pull-ups
            bis.b   #0x0f,&P1IES          ; h to l
            bis.b   #0x0f,&P1REN          ; enable pull-ups
            bis.b   #0x0f,&P1IE           ; enable switch interrupts
            bis.b	#0x10,&P3DIR
            mov.w 	#WDT_IPS, second

start:		mov.w	#message, r4			; point to message

loop2:		mov.b	@r4+,r5					; get character
			cmp.b	#END, r5				; end of char?
			   jeq	empty					; y
			cmp.b	#' ',r5					; is the char a space?
			   jeq	space					; y
			mov.w	#'9',r9					; for numloop (compare numbers)
numloop:	cmp.b	r9, r5					; check for a numerical value
			   jeq	num						; if number, move to num
			dec.w	r9						; the next numerical value to check
			   jne	numloop					; restart until 0
			sub.w	#'A',r5					; to find the morse code for that letter
			add.w	r5,r5					; make word index
			mov.w	letters(r5),r6			; point to letter codes

run:		mov.b	@r6+,r7					; get DOT, DASH, END
			cmp.b	#END,r7					; END?
			   jeq	empty					; y
			cmp.b	#DOT,r7					; DOT?
			  jeq 	dot						; y
			cmp.b 	#DASH, r7				; Dash?
			  jeq	dash					; y

			jmp 	loop2					; shouldn't get here ever

num:		sub.w	#'0',r5					; find morse code for that number
			add.w	r5,r5					; word index
			mov.w	numbers(r5),r6			; point to letter codes
				jmp run						; run morse code

space: 		mov.w	#ELEMENT*7,r15			; seven element delay
			call	#delay
			   jmp	loop2

empty:		mov.w	#ELEMENT*3,r15			; three element delay
			call	#delay
			   jmp	loop2

dot:		push 	r15
			mov.w 	#ELEMENT, r15			; output dot
			call	#beep
			mov.w	#ELEMENT, r15			; one element delay
			call	#delay
			pop		r15
			jmp run

dash:		mov.w   #ELEMENT*3,r15          ; output DASH
            call    #beep
            mov.w   #ELEMENT,r15            ; delay 1 element
            call    #delay
            jmp run

; beep (r15) ticks subroutine -------------------------------------------------
beep:       mov.w   r15,&beep_cnt           ; start beep


beep02:		bis.b   #0x40,&P4DIR
			tst.w   &beep_cnt               ; beep finished?
              jne   beep02                  ; n
            bic.b	#0x40,&P4DIR
            ret                             ; y

; delay (r15) ticks subroutine ------------------------------------------------
delay:      mov.w   r15,&delay_cnt          ; start delay

delay02:    tst.w   &delay_cnt              ; delay done?
              jne   delay02                 ; n
            ret                             ; y

DEBOUNCE   .equ    20
P1_ISR:    bic.b   #0x0f,&P1IFG          ; acknowledge (put hands down)
           mov.w   #DEBOUNCE,debounce_cnt ; reset debounce count
           reti

; Watchdog Timer ISR ----------------------------------------------------------
WDT_ISR:    tst.w   &beep_cnt               ; beep on?
              jeq   WDT_02                  ; n
            dec.w   &beep_cnt               ; y, decrement count
            xor.b   #0x60,&P4OUT            ; beep using 50% PWM

WDT_02:     tst.w   &delay_cnt              ; delay?
              jeq   WDT_04                  ; n
            dec.w   &delay_cnt              ; y, decrement count

WDT_04:		tst.w   &debounce_cnt            ; debouncing?
             jeq    WDT_09                   ; n
            dec.w   &debounce_cnt            ; y, decrement count, done?
             jne    WDT_09                   ; n
            push    r15                      ; y
            mov.b   &P1IN,r15                ; read switches
            and.b   #0x0f,r15
            xor.b   #0x0f,r15                ; any switches?
             jeq    WDT_08	               ; n
            cmp.w	#0x01,r15
             jne	WDT_08
WDT_06:		xor.b	#0x20,&P4DIR
WDT_08:		pop		r15

WDT_09:
			dec.w	second
				jnz	WDT_10
			xor.w	#0x10,&P3DIR
			mov.w 	#WDT_IPS, second


WDT_10:
			reti                            ; return from interrupt

; Interrupt Vectors -----------------------------------------------------------
			.sect	".int02"
			.word	P1_ISR

            .sect   ".int10"                ; Watchdog Vector
            .word   WDT_ISR                 ; Watchdog ISR

            .sect   ".reset"                ; PUC Vector
            .word   RESET                   ; RESET ISR
            .end
