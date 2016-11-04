;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;	BENJAMIN THOMPSON
; 	CS 124 SECTION 1
;	THIS IS MY WORK
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section
            .retainrefs                     ; Additionally retain any sections
                                            ; that have references to current
                                            ; section
GLED		.equ	0x40
RLED		.equ	0x01

ONESEC		.equ	10						; 10 for 1 sec delay
TENSEC		.equ	100						; 100 for 10 sec delay
SIX			.equ	6						; 6 for loop
FIVESEC		.equ	50						; 50 for 5 sec delay
FIFTHSEC	.equ	2						; 2 for 1/5 sec delay
TWENTY		.equ	20						; 20 for loop
TENTH		.equ	36500					; 1/10 sec delay
;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

			mov.b	#0x41,&P1DIR			;initialize output

;-------------------------------------------------------------------------------
						;Main Loop

;-------------------------------------------------------------------------------
loop:		bis.b	#GLED,&P1OUT			;Turn on GREEN LED
			bic.b	#RLED,&P1OUT			;Turn off red LED

		 	mov.w	#FIVESEC,r14			; assign 50 to r14
			call	#delay					; call 1/10 sec delay // for 5 seconds

			mov.w	#SIX,r13				; assign 6 to r13
sixtimes:	xor.b	#GLED,&P1OUT			; toggle green LED
			mov.w	#ONESEC,r14				; move 10 to r14
			call	#delay					; call 1/10 sec delay // for 1 second
			sub.w	#1,r13
				jne	sixtimes				; repeat 6 times

			mov.w	#TWENTY,r13				; assign 20 to r13
			mov.w	#FIFTHSEC,r14			; assign 2 to r14
twentyx:	xor.b	#GLED,&P1OUT			; toggle green led
			call	#delay					; call 1/10 sec delay // for 1/5 second
			sub.w	#1,r13
				jne	twentyx					; repeat 20 times

			bic.b	#GLED,&P1OUT			; turn green led off
			bis.b	#RLED,&P1OUT			; turn red led on

			mov.w	#TENSEC,r14				; assign 100 to r13
			call	#delay					; call 1/10 sec delay // for 10 seconds

			jmp		loop					; return to main loop

;------------------------------------------------------------------------------
						;Subroutine // delay as per requested (1/10 sec * r14)

;------------------------------------------------------------------------------
delay:		push	r14						; push r14 on the stack
			push	r13						; push r13 on the stack

delay0:		mov.w	#TENTH,r13				; 1/10 second delay
delay1:		sub.w	#1,r13					; subtract 1 from r13
				jne	delay1
			sub.w	#1, r14					; delay requested from main loop
				jne	delay0
			pop		r13						; pop r13 off the stack
			pop		r14						; pop r14 off the stack
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
