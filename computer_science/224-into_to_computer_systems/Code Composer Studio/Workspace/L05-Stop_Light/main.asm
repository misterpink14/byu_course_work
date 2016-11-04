;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section
            .retainrefs                     ; Additionally retain any sections
                                            ; that have references to current
                                            ; section

GLED		.equ	0x40					; Green LED
RLED		.equ	0x01					; Red LED

SEC1		.equ	10						;
TEN			.equ	100						;
SIX			.equ	6						;
FIVESEC		.equ	50						;
FIFTH	.equ	2						;
TWENTY		.equ	20						;
TENTHSEC	.equ	37878					; 1/10 sec delay
;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

;-------------------------------------------------------------------------------
                                            ; Main loop here
;-------------------------------------------------------------------------------
loop:		bis.b	#GLED,&P1OUT			; Turn on GREEN LED
			bic.b	#RLED,&P1OUT			; Turn off red LED



delayfive:  mov.w	#FIVESEC,r14			; set r14 to 50 // delay 5 second

fivesec:	call	#delay					; call subroutine

			sub.w	#1,r14					; 50 times
				jnz	fivesec

			mov.w	#SIX,r13				;move 6 to r13
repeatsix:	xor.b	#GLED,&P1OUT			;toggle green LED

			mov.w	#ONE,r14				;move 10 to r14
onesec:
			call	#delay					;delay 1 sec
			sub.w	#1,r14
				jnz	onesec
			sub.w	#1,r13
				jnz	repeatsix					;repeat 6 times

			mov.w	#TWENTY,r13
			mov.w	#FIFTH,r14

			call	#toggle
;repeattwen:	xor.b	#GLED,&P1OUT

;fifthsec:	sub.w	#1,r14
;			call	#delay
;				jnz	fifthsec
;			sub.w	#1,r13
;				jne	repeattwen

redon:		bic.b	#GLED,&P1OUT
			bis.b	#RLED,&P1OUT


			mov.w	#TEN,r13
tensec:		call	#delay
			sub.w	#1,r13
				jne	tensec


			jmp		loop

toggle:		push	r13
toggle1:	sub.w	#1,r13
			call	#delay
				jne	toggle1

delay:		push	r14
			mov.w	#TENTHSEC,r14
delay1:		sub.w	#1,r14
				jne	delay1

			pop		r14
			ret

;-------------------------------------------------------------------------------
;           Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect 	.stack

;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
