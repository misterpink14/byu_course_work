;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file

			.ref	letters

			.bss	PWM_cnt, 2
			.bss	delay_cnt, 2

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory
;-------------------------------------------------------------------------------
message:	.string	"HelloWorld"
			.byte	0
			.align	2

start:		mov.w	#0x0300, SP				; initialize SP
			mov.w	#WDT_MDLY_0_5,&WDTCTL	; WDT interval = .05 ms
			mov.b	#WDTIE,&IE1				; enable WDT interrupt
			bis.b	#0x06,&P1DIR			; P4.5 output (speaker)
			mov.w	#0x02,&P1OUT
			bis.w	#GIE,SR

loop:		mov.w	#message, r4

loop2:		mov.b	@r4+,r5
			cmp.b	#0, r5
			   jeq	loop
			cmp.b	#' ',r5
			   jeq	loop8
			sub.w	#'A',r5
			add.w	r5,r5
			mov.w	letters(r5),r6

loop4:		mov.b	@r6,r7
			cmp.b	#0,r7
			   jeq	loop8
			cmp.b	#1,r7
			   jne 	loop6
			call #dot
			   jmp	loop4

loop6:		call	#dash
			   jmp loop4

loop8:		mov.w	#400,r15
			call	#delay
			   jmp	loop2

dot:		push 	r15
			mov.w 	#400, r15
			call	#beep
			mov.w	#400, r15
			call	#delay

dash:		mov.w   #ELEMENT*3,r15          ; output DASH
            call    #beep
            mov.w   #ELEMENT,r15            ; delay 1 element
            call    #delay


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
            sub.w   #1,&beep_cnt            ; y, decrement count
            xor.b   #0x20,&P4OUT            ; beep using 50% PWM

WDT_02:     tst.w   &delay_cnt              ; delay?
              jeq   WDT_10                  ; n
            sub.w   #1,&delay_cnt           ; y, decrement count

WDT_10:     reti                            ; return from interrupt

; Interrupt Vectors -----------------------------------------------------------
            .sect   ".int10"                ; Watchdog Vector
            .word   WDT_ISR                 ; Watchdog ISR
