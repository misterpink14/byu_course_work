       .title  "simon.asm"
;*******************************************************************************
;  Project:  simon.asm
;  Author:   Benjamin Thompson, Adam Jenkins

;	 	This is OUR code

;
;  Description: A MSP430 assembly language program that plays the game of Simon.
;
;    1. Each round of the game starts by the LEDs flashing several times.
;    2. The colored LEDs (along with the associated tones) then flash one at
;       a time in a random sequence.
;    3. The push button switches are sampled and compared with the original
;       sequence of colors/tones.
;    4. The sampling the switches continues until the end of the sequence is
;       successfully reached or a mistake is made.
;    5. Some congratulatory tune is played if the sequence is correct or some
;       raspberry sound is output if a mistake is made.
;    6. If the complete sequence is successfully reproduced, the game is
;       repeated with one additional color/tone added to the sequence.
;       Otherwise, the game starts over with the default number of colors/tones.
;
;  Requirements:
;	Timer_B output (TB2) is used for hardware PWM of the transducer (buzzer).
;	Subroutines in at least one assembly and one C file are used by your program.
;	ALL subroutines must be correctly implemented using Callee-Save protocol.
;
;  Bonus:
;
;      -Port 1 interrupts are used to detect a depressed switch.
;	  -Use LCD to display round, score, highest score, and lowest score.
;	  -Turn on LCD backlight with any activity.
;	  -Turn off LCD backlight after 5 seconds of inactivity.
;
;*******************************************************************************
;   constants and equates
;
        .cdecls C,LIST,"msp430x22x4.h"
;
;*******************************************************************************
;
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
;
;******************************************************************************
;    Define some LED macros

    .asg "bis.b    #0x01,&P4OUT",LED1_ON
    .asg "bic.b    #0x01,&P4OUT",LED1_OFF

    .asg "bis.b    #0x02,&P4OUT",LED2_ON
    .asg "bic.b    #0x02,&P4OUT",LED2_OFF

    .asg "bis.b    #0x04,&P4OUT",LED3_ON
    .asg "bic.b    #0x04,&P4OUT",LED3_OFF

    .asg "bis.b    #0x08,&P4OUT",LED4_ON
    .asg "bic.b    #0x08,&P4OUT",LED4_OFF

myCLOCK .equ    8000000                 ; 8 Mhz clock
WDT_CTL .equ    WDT_MDLY_32             ; WD configuration (Timer, SMCLK, 32 ms)
WDT_CPI .equ    32000                   ; WDT Clocks Per Interrupt (@1 Mhz)
WDT_IPS .equ    myCLOCK/WDT_CPI         ; WDT Interrupts Per Second
STACK   .equ    0x0600                  ; top of stack
TD	.equ	1000000/440/2/2*587/440	; D tone
TG	.equ	1000000/440/2*392/440	; GTone
TA	.equ	1000000/440/2/2
TA2	.equ	1000000/440/2
ATONE	.equ	myCLOCK/TA	; A tone
DTONE	.equ	myCLOCK/TD
GTONE	.equ	myCLOCK/TG
A2TONE	.equ	myCLOCK/TA2
LOTONE	.equ	myCLOCK/90


TONE    .equ    2000                   ; buzzer tone
DELAY   .equ    160                      ; delay count

DEBOUNCE	.equ	5000

GLED	.equ	0x01
OLED	.equ	0x02
YLED	.equ	0x04
RLED	.equ	0x08
ALED	.equ	0x0f

SCORE	.equ	0x04
RSC	.equ	0x01

FIVES	.equ	WDT_IPS*5

;*******************************************************************************
;       RAM section
;
        .bss    WDTSecCnt,2             ; watchdog counts/second
        .bss    WDT_delay,2             ; watchdog delay counter

;*******************************************************************************
;	Reference other files

		.ref	RBX430_init
		.ref	rand16
		.ref	RBX430_H_
		.ref	setrandSeed


;*******************************************************************************
;       ROM section
;
        .text                           ; code Section

reset:  mov.w   #STACK,SP               ; Initialize stack pointer
     	mov.w	#0,r13
        mov.w	#0x01,r12
        call	#RBX430_init	; initialize 430 device.

;       Set Watchdog interval
        mov.w   #WDT_CTL,&WDTCTL        ; Set Watchdog interrupt interval
        mov.w   #WDT_IPS,WDTSecCnt
        mov.b   #WDTIE,&IE1             ; Enable WDT interrupt

;       enable buzzer to use Timer B PWM
        clr.w   &TBR                    ; Timer B SMCLK, /1, up mode
        mov.w   #TBSSEL_2|ID_0|MC_1,&TBCTL
        mov.w   #OUTMOD_3,&TBCCTL2      ; output mode = set/reset
       	bis.b  #0x30,&P4DIR             ; P4.5 output (buzzer)
       	bis.b  #0x20,&P4SEL             ; select alternate output (TB2) for P4.5
       	bic.b	#0x10,&P4OUT

;       enable interrupts
        bis.w   #GIE,SR                 ; enable interrupts

start:	mov.w   #4,r15
mov.w	#ATONE,r14
loop0:	add.w	#ATONE/2,r14	; Intro sound
mov.w	r14,r12
        and.w   #0x0fff,r12
        add.w   #TONE,r12	; set the tone
        call    #LEDs                   ; turn on an LED
        call    #toneON                 ; turn on tone
        call    #delay2                  ; delay
        dec.w	r15
          jne   loop0
        call    #toneOFF                ; turn off tone
bic.b #ALED,&P4OUT
loop02:	mov.w	#4,r15
call	#delay
loop01:
push	r12
mov.w	#A2TONE,r12
 	bis.b	#ALED, &P4OUT
 	call    #toneON                 ; turn on tone
        call    #delay3                  ; delay
        call    #toneOFF                ; turn off tone
        bic.b	#ALED, &P4OUT
        call	#delay3
        dec	r15
          jne	loop01
        pop	r12


call	#delay
call	#delay

;*******************************************************************************
;	The Game!

startgame:
mov.w	r13,r12
call	#setrandSeed
call	#rand16
mov.w	#0x05,r5	; Use r5 to keep score
nextstage:
call	#challenge
continuegame:
;	mov.w	#DEBOUNCE,r11
;short:	sub.w	#1,r11
;	jnz	short
call	#getSwitch
call	#checkres
cmp.b	#0,r10
jeq	lose
add.w	#1,r6	; Use r6 to record responses
cmp.w	r5,r6	; has player finished current sequence?
jeq	charge	; yes? send to win sequence
jmp	continuegame	; no? wait for next response


lose:
push	r9
push	r12
mov.w	#1,r6
mov.w	#RLED,r4
mov.w	#LOTONE,r12
call	#toneON
lose2:	bis.w	r4,&P4OUT
mov.w	#0xffff,r9
lose1:	dec.w	r9
jne lose1
rra.w	r4
jnz	lose2
bic.b	#0x0f,&P4OUT
call	#delay
call	#toneOFF
pop	r12
pop	r9
jmp	loop02	; Start game over

charge:
add.w	#1,r5	; add one to score
call	#cout1
;	call #delay3
call	#cout2
;	call #delay3
call	#cout3
;	call #delay3
call	#cout4
call #delay2
call	#cout3
;	call #delay3
call	#out4
call #delay
jmp	nextstage	; add one to current sequence


challenge:
push	r9
push	r12
push	r5
ch1:	sub.w	#1,r5
tst.w	r5
jeq	endchallenge
mov.w	r12,r9
and.w	#0x0001,r9

cmp.b	#0x01,r9
jeq	ch2
mov.w	r12,r9
rrc.w	r9
and.w	#0x0001,r9
cmp.b	#0x01,r9
jeq	ch3
call	#out1
rrc.w	r12
rrc.w	r12
jmp	ch1
ch3:
call	#out2
rrc.w	r12
rrc.w	r12
jmp	ch1

ch2:	mov.w	r12,r9
rrc.w	r9
and.w	#0x0001,r9
cmp.b	#0x01,r9
jeq	ch4
call	#out3
rrc.w	r12
rrc.w	r12
jmp	ch1
ch4:
call	#out4
rrc.w	r12
rrc.w	r12
jmp	ch1


endchallenge:
mov.w	#1,r6	; reset response counter
pop	r5
pop	r12
pop	r9
ret


out1:
push	r12
bis.b	#GLED,&P4OUT
mov.w	#ATONE,r12
        call    #toneON                 ; turn on tone
        call    #delay                  ; delay
        call    #toneOFF                ; turn off tone
bic.b	#GLED,&P4OUT
pop	r12
ret

out2:
push	r12
bis.b	#OLED,&P4OUT
mov.w	#DTONE,r12
        call    #toneON                 ; turn on tone
        call    #delay                  ; delay
        call    #toneOFF                ; turn off tone
bic.b	#OLED,&P4OUT
pop	r12
ret

out3:
push	r12
bis.b	#YLED,&P4OUT
mov.w	#GTONE,r12
        call    #toneON                 ; turn on tone
        call    #delay                  ; delay
        call    #toneOFF                ; turn off tone
bic.b	#YLED,&P4OUT
pop	r12
ret

out4:
push	r12
bis.b	#RLED,&P4OUT
mov.w	#A2TONE,r12
        call    #toneON                 ; turn on tone
        call    #delay                  ; delay
        call    #toneOFF                ; turn off tone
bic.b	#RLED,&P4OUT
pop	r12
ret


cout1:
push	r12
bis.b	#GLED,&P4OUT
mov.w	#ATONE,r12
        call    #toneON                 ; turn on tone
        call    #delay3                 ; delay
        call    #toneOFF                ; turn off tone
bic.b	#GLED,&P4OUT
pop	r12
ret

cout2:
push	r12
bis.b	#OLED,&P4OUT
mov.w	#DTONE,r12
        call    #toneON                 ; turn on tone
        call    #delay3                 ; delay
        call    #toneOFF                ; turn off tone
bic.b	#OLED,&P4OUT
pop	r12
ret

cout3:
push	r12
bis.b	#YLED,&P4OUT
mov.w	#GTONE,r12
        call    #toneON                 ; turn on tone
        call    #delay3                 ; delay
        call    #toneOFF                ; turn off tone
bic.b	#YLED,&P4OUT
pop	r12
ret

cout4:
push	r12
bis.b	#RLED,&P4OUT
mov.w	#A2TONE,r12
        call    #toneON                 ; turn on tone
        call    #delay3                 ; delay
        call    #toneOFF                ; turn off tone
bic.b	#RLED,&P4OUT
pop	r12
ret

;*******************************************************************************
;       delay
;
delay:
mov.w   #DELAY,WDT_delay        ; set WD delay counter
        bis.w   #LPM0,SR                ; goto sleep
        ret                             ; I'm awake - return

delay2:
mov.w   #DELAY/3,WDT_delay        ; set WD delay counter
        bis.w   #LPM0,SR                ; goto sleep
        ret

delay3:
mov.w   #DELAY/6,WDT_delay        ; set WD delay counter
        bis.w   #LPM0,SR                ; goto sleep
        ret



;*******************************************************************************
;       get switch subroutine
;
getSwitch:                              ; get switch subroutine

        mov.b   &P1IN,r4                ; wait for a switch
        and.b   #0x0f,r4
        xor.b   #0x0f,r4                ; any switch depressed?
          jeq   getSwitch               ; n

bis.b	#0x10,&P4OUT	;Turn on LCD background
mov.w	#FIVES, r14
press1:	cmp.b	#0x01,r4
jne	press2
call	#switch1

press2:	cmp.b	#0x02,r4
jne	press3
call	#switch2

press3:	cmp.b	#0x04,r4
jne	press4
call	#switch3

press4:	cmp.b	#0x08,r4
jne	endgetsw
call	#switch4

endgetsw:	ret                             ; y, return


;*******************************************************************************
;	Switch functions

switch1:
mov.w	#0,r8
call	#out1
ret

switch2:
mov.w	#2,r8
call	#out2
ret

switch3:
mov.w	#1,r8
call	#out3
ret

switch4:
mov.w	#0x03,r8
call	#out4
ret

;*******************************************************************************
;	Check response

checkres:
push	r12
push	r9
push	r6
sub.w	#1,r6
test:
cmp.b	#0,r6
jeq contcheck
sub.w	#1,r6
rrc.w	r12
rrc.w	r12
jmp	test

contcheck:
pop	r6
mov.w	r12,r9
and.w	#0x0003,r9
cmp.w	r8,r9
jeq	true
mov.w	#0,r10
pop	r9
pop	r12
ret

true:
mov.w	#0x01,r10
pop	r9
pop	r12
ret

;*******************************************************************************
;    enable/disable tone
;
toneON:
        push    r12
        rra.w   r12                     ; tone / 2
        mov.w   r12,&TBCCR2             ; use TBCCR2 as 50% duty cycle
        pop     r12
        mov.w   r12,&TBCCR0             ; start clock
        ret

toneOFF:
        mov.w   #0,&TBCCR0              ; Timer B off
        ret

LEDs:	push	r12
        bic.b   #0x0f,&P4OUT            ; turn off LED's
        and.w	#0x0f,r12
        bis.b	r12,&P4OUT
        pop	r12
        ret

;******************************************************************************
;DEBOUNCE	.equ	20
;P1_ISR:
;	bic.b

;*******************************************************************************
;       Interrupt Service Routines
;
WDT_ISR:                                ; Watchdog Timer ISR
dec.w	r13
        cmp.w   #0,WDT_delay            ; delaying?
          jeq   WDT_02                  ; n
        dec.w   WDT_delay               ; y, wake-up processor?
          jne   WDT_02                  ; n
        bic.w   #LPM0,0(SP)             ; y, clear low-power bits for reti

WDT_02:
        dec.w   WDTSecCnt               ; decrement counter, 0?
          jne   WDT_03                  ; n
        mov.w   #WDT_IPS, WDTSecCnt     ; y, re-initialize counter
        xor.b   #0x40,&P4OUT            ; toggle P4.6

WDT_03:
dec.w	r14
jnz	WDT_04
bic.b	#0x10,&P4OUT

WDT_04: reti                            ; return from interrupt


;*******************************************************************************
;       Interrupt vector sections

        .sect   ".int10"                ; WDT vector section
        .word   WDT_ISR                 ; address of WDT ISR

        .sect   ".reset"                ; reset vector section
        .word   reset                   ; address of reset
        .end
