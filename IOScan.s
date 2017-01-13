/*******************************************************************************
File name       : IO.s
Description     : Assembly language function to interact with hardware
Author          :     
Created         : 
Revision History

*******************************************************************************/

  MODULE        WK_6    /* The module name */
  PUBLIC ioscan         /* Make function name visible to linker               */


  SECTION `.rodata`:CONST:REORDER:NOROOT(2)
  DATA

// Find the base address for each port in the datasheet (or reference manual)
PORTA           equ 0x40020000
PORTC           equ 0x40020800    

// These are the registers in the GPIO that we will be dealing with
// Find the offsets from the base address in the reference manual.
IDR              equ   0x10  
BSRRL            equ   0x18  
BSRRH            equ   0x1A

PORTA_BSRRL      equ     PORTA + BSRRL  ; low half of the register for ODR
PORTA_BSRRH      equ     PORTA + BSRRH  ; high half of the register for ODR

PORTC_IDR       equ     PORTC + IDR ;; for reading button state
INPUT_MASK      equ     0x00002000

  /* Tells the linker the section name : memory type : fragment (align)       */
  SECTION `.text`:CODE:NOROOT(2) 
  THUMB                 /* Mode control directive                             */

/*******************************************************************************
Function Name   : ioscan
Description     : Scans the user button, and lights the LED if pressed.
C Prototype     : void ioscan(void)
                :
Parameters      :
Return value    : None
Registers Used  :
              R0: Scratch
              R1: Scratch
              R2: PORTC_IDR
              R3: PORTA_BSRR low or high                       
*******************************************************************************/

ioscan:
        ldr     r2, =PORTC_IDR    ;; Load PORTC_IDR into R1
        ldr     r0, [r2]          ;; Load contents of PORTC_IDR into R0
        ldr     r1, =INPUT_MASK   ;; Load INPUT_MASK into R1
        
        ldr     r3, =PORTA_BSRRL        
        cmp     r0, r1
        ite     eq
        moveq   r0, #0x200000  ;; 0x20 << 0x10 (32d << 16d)
        movne   r0, #0x20 
        
        str   r0, [r3]  ;; set pos 5 in high or low half of the register
        bx     lr
        
 END
