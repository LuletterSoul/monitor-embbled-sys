;***************************************************
;*The function for interrupt
;***************************************************

        AREA	INTFUN, CODE, READONLY

        EXPORT   INTS_OFF
        EXPORT   INTS_ON


INTS_OFF
   mrs   r0, cpsr          ; current CSR
   mov   r1, r0            ; make a copy for masking
   orr   r1, r1, #0xC0     ; mask off int bits
   msr   CPSR_cxsf, r1     ; disable ints (IRQ and FIQ)
   and   r0, r0, #0x80     ; return FIQ bit from original CSR
   mov   pc,lr             ; return


INTS_ON
   mrs   r0, cpsr          ; current CSR
   bic   r0, r0, #0xC0     ; mask on ints
   msr   CPSR_cxsf, r0     ; enable ints (IRQ and FIQ)
   mov   pc,lr             ; return

  END