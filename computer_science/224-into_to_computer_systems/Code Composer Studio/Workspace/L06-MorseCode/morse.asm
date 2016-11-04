;			.title	"morse.asm"
;*******************************************************************************
;     Project:  morse.asm
;      Author:  Student Code
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

; Program section -------------------------------------------------------------
            .text                           ; program section
message:    .string "PARIS"                 ; PARIS message
            .byte   0
            .align  2                       ; align on word boundary

RESET:      mov.w   #STACK,SP               ; initialize stack pointer
            mov.w   #WDT_CTL,&WDTCTL        ; set WD timer interval
            mov.b   #WDTIE,&IE1             ; enable WDT interrupt
            bis.b   #0x20,&P4DIR            ; set P4.5 as output (speaker)
            clr.w   &beep_cnt               ; clear counters
            clr.w   &delay_cnt
            bis.w   #GIE,SR                 ; enable interrupts

; output 'A' in morse code (DOT, DASH, space)
loop:       mov.w   #ELEMENT,r15            ; output DOT
            call    #beep
            mov.w   #ELEMENT,r15            ; delay 1 element
            call    #delay

            mov.w   #ELEMENT*3,r15          ; output DASH
            call    #beep
            mov.w   #ELEMENT,r15            ; delay 1 element
            call    #delay

            mov.w   #ELEMENT*7,r15          ; output space
            call    #delay                  ; delay
            jmp     loop                    ; repeat

; beep (r15) ticks subroutine -------------------------------------------------
beep:       mov.w   r15,&beep_cnt           ; start beep

beep02:     tst.w   &beep_cnt               ; beep finished?
              jne   beep02                  ; n
            ret                             ; y

; delay (r15) ticks subroutine ------------------------------------------------
delay:      mov.w   r15,&delay_cnt          ; start delay

delay02:    tst.w   &delay_cnt              ; delay done?
              jne   delay02                 ; n
            ret                             ; y

; Watchdog Timer ISR ----------------------------------------------------------
WDT_ISR:    tst.w   &beep_cnt               ; beep on?
              jeq   WDT_02                  ; n
            dec.w   &beep_cnt               ; y, decrement count
            xor.b   #0x20,&P4OUT            ; beep using 50% PWM

WDT_02:     tst.w   &delay_cnt              ; delay?
              jeq   WDT_10                  ; n
            dec.w   &delay_cnt              ; y, decrement count

WDT_10:     reti                            ; return from interrupt

; Interrupt Vectors -----------------------------------------------------------
            .sect   ".int10"                ; Watchdog Vector
            .word   WDT_ISR                 ; Watchdog ISR

            .sect   ".reset"                ; PUC Vector
            .word   RESET                   ; RESET ISR
            .end
