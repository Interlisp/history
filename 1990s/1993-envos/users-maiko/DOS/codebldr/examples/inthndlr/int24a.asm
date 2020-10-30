             PAGE ,132
             .386
;*=============================================================================
;* Intel 386/486 C Code Builder(TM) Kit
;* Copyright 1991 Intel Corporation.  All Rights Reserved.
;*-----------------------------------------------------------------------------
;*   INT24A.ASM
;*
;*   An example int 24h (critical error) interrupt routine & sample program.
;*
;* The following commands can be used to create an .OBJ file:
;*    MASM 5.1:   masm /I..\..\inc int24a.asm;
;*    MASM 6.0:   ml /c /Zm /I..\..\inc int24a.asm
;*    Phar Lap:   386asm int24a.asm -i ..\..\inc\
;*    TASM 2.x:   tasm /i..\..\inc int23a.asm
;*
;*   The .OBJ file may then be used to create an .REX and an .EXE file by:
;*      icc -N int24a.obj
;*
;*   Two internal extender service calls are performed within this file.  The
;*   calls are made by placing a request number in AH, an argument in AL, and
;*   calling the routine whose address is given in the 'GDA_SERV' field of the
;*   GDA.
;******************************************************************************
CODE            SEGMENT para public USE32 'CODE'
                ASSUME  cs:CODE,ds:CODE,es:CODE


;******************************************************************************
;*   Include files
;******************************************************************************
        include extender.ah             ;global data area ('GDA_SERV' addr)
        include stk.ah                  ;contains STK image defines


;******************************************************************************
;*   Sample program's data
;******************************************************************************
drv_nrdy_flag   DB      0               ;drive-not-ready flag (set by int24)
filename        DB      'A:\nothere.not',0
gda_ptr DD      0                       ;address of gda

msg1    DB      0dh,0ah,'*** Critical Error Intercept Test ***',0dh,0ah
        DB      'A critical error will be caused by trying to read drive A'
        DB      0dh,0ah
        DB      'when it is not ready.',0dh,0ah,0dh,0ah
        DB      'Press any key after ensuring that drive A is empty.'
        DB      0dh,0ah,0dh,0ah
MSG1_LEN EQU    $-msg1

msg2    DB      'The critical error handler has detected a "drive not ready"'
        DB      0dh,0ah
        DB      'condition, but has suppressed the display of "Abort, Retry, '
        DB      'Fail?".'
        DB      0dh,0ah,0dh,0ah
        DB      'Press any key after inserting a disk into drive A.'
        DB      0dh,0ah,0dh,0ah
MSG2_LEN EQU    $-msg2

msg3    DB      'The drive was ready, there must be a formatted disk in A.'
        DB      0dh,0ah
        DB      'This concludes the test.',0dh,0ah
MSG3_LEN EQU    $-msg3




;******************************************************************************
;*   test_int24
;*
;*   A sample program which sets the int 24h (critical error) vector to the
;*   example interrupt routine, then causes a critical error (drive not ready).
;*   Rather than displaying DOS's "Abort, Retry, Fail?" message, the example
;*   handler allows this test program to display it's own message concerning
;*   the drive not ready error.
;*
;*   Input:
;*      edx     -       Address of the GDA.  (Note:  If this program were to be
;*                      linked with a C module, requiring the C startup code to
;*                      execute first, the gda pointer would not be in edx, but
;*                      it could be retrieved from the global variable '_gda'.)
;******************************************************************************
test_int24:

;******************************************************************************
;*   Hook int 24h interrupt handler into "high interrupt" table
;******************************************************************************
        mov     gda_ptr,edx             ;save ptr to gda
        call    int24_init              ;initialize int 24h interrupt handler

;******************************************************************************
;*   Display test's sign-on message
;******************************************************************************
        mov     ah,40h                  ;write to device
        mov     ebx,1                   ;stdout's fixed handle
        mov     ecx,MSG1_LEN            ;size of msg to display
        mov     edx,OFFSET msg1         ;addr of msg to display
        int     21h                     ;"Make sure drive A is empty"

;******************************************************************************
;*   Try to read disk in drive A
;******************************************************************************
try_again:
        mov     ah,7                    ;wait for key press before continuing
        int     21h

        mov     drv_nrdy_flag,0         ;reset drive-not-ready flag

        mov     ah,3dh                  ;open file DOS func #
        mov     al,0                    ;open for reading
        mov     edx,OFFSET filename
        int     21h                     ;try to open file on A: drive

        cmp     drv_nrdy_flag,0         ;was drive ready?
        je      ready_now               ;yes, done trying

;******************************************************************************
;*   Critical error occurred showing drive A not ready; display msg & try again
;******************************************************************************
        mov     ah,40h                  ;write to device
        mov     ebx,1                   ;stdout's fixed handle
        mov     ecx,MSG2_LEN            ;size of msg to display
        mov     edx,OFFSET msg2         ;addr of msg to display
        int     21h                     ;"Put a disk in drive A"

        jmp     SHORT try_again         ;try to read drive A again

ready_now:
;******************************************************************************
;*   Display message to notify test is complete
;******************************************************************************
        mov     ah,40h                  ;write to device
        mov     ebx,1                   ;stdout's fixed handle
        mov     ecx,MSG3_LEN            ;size of msg to display
        mov     edx,OFFSET msg3         ;addr of msg to display
        int     21h                     ;"Disk was in drive A - test complete"

;******************************************************************************
;*   Unhook int 24h handler & terminate the program
;******************************************************************************
        mov     edx,gda_ptr             ;restore ptr to gda
        call    int24_term              ;terminate int 24h interrupt handler

        mov     ax,4c00h                ;terminate (4c) with ret code = 0
        int     21h





;******************************************************************************
;*   All code below belongs to the int 24h interrupt handler template:
;******************************************************************************



;******************************************************************************
;*   Local data area used by interrupt handler routines
;******************************************************************************
int_gda_ptr     DD      0               ;address of gda
old_int24       DD      0               ;address of previous int 24h handler



;******************************************************************************
;*   int24_init
;*
;*   Performs initialization for int 24h handler.  First, a service is call
;*   is performed to retrieve the current int 24h handler address, if any.
;*   This address is saved for use by the new handler (to chain to the cur-
;*   rent handler).  The second service call sets the new int 24h interrupt
;*   handler to be the current routine.
;*
;*   The service calls could be replaced with similar calls to '_dos_getvect()'
;*   and '_dos_setvect()' if this code were linked with the C library.  In
;*   that case, the GDA address would not be needed.
;*
;*   Input:
;*      edx - gda address.
;*
;*   Output:
;*      edx preserved.  Other registers volatile.
;******************************************************************************
int24_init:
        mov     int_gda_ptr,edx         ;save ptr to gda

;******************************************************************************
;*   Install int 24h (Critical error) interrupt handler
;******************************************************************************
        mov     ah,35h                  ;GET interrupt handler addr
        mov     al,24h                  ;interrupt # to get
        call    [edx].GDA_SERV          ;returns current handler addr in ebx
        mov     old_int24,ebx           ;save existing handler addr, if any

        xor     eax, eax                ;clear hi bit (set = no V86 ints)
        mov     ah,25h                  ;SET interrupt handler addr
        mov     al,24h                  ;interrupt # to set
        lea     edx,int24               ;get address of our int 24h handler
        mov     ebx,int_gda_ptr         ;get ptr to gda
        call    [ebx].GDA_SERV          ;call service routine to set int addr

;******************************************************************************
;*   Exit 'int24_init'
;******************************************************************************
        mov     edx,int_gda_ptr         ;restore ptr to gda before returning
        ret




;******************************************************************************
;*   int24
;*
;*   Int 24h (Critical error) interrupt handler.
;*
;*   This routine is called before control is given to the DOS (real mode) int
;*   24h interrupt handler.
;*
;*   As written, this routine checks the error code in edi to check for 1
;*   specific critical error (drive not ready).  If this was not the error
;*   which caused the interrupt, control is passed to DOS's critical error
;*   handler for processing.  If the error is "drive not ready", a flag is
;*   set to notify the sample test program that this error has occurred.  (Note
;*   that the test program will also receive back from the INT call a '3' in al
;*   with the carry flag set, indicating "Path not found".  This does not
;*   always indicate that the drive was not ready, however.)  Another flag is
;*   set ('_STK_NOINT') to bypass calling the DOS critical error handler.
;*
;*   Input:
;*      ebp     - Address of STK image to be sent to the Virtual 86 interrupt
;*                   handler.  To return a flag value to the interrupted pro-
;*                   cess (if '_STK_NOINT' is set), modify STK_FLG through ebp.
;*      ebx     - Address of STK image showing status at time of interrupt.
;*                   If the interrupted process is a Virtual 86 process, ebx
;*                   will be the same as ebp.  To set a return value in a
;*                   register (if '_STK_NOINT' is set), modify the appropriate
;*                   register (e.g., 'STK_EBX', etc.) through ebx.  The modi-
;*                   fied register value will be returned to the interrupted
;*                   process.
;*                   Note:  Flag changes must be made using ebp - see above.
;*      stk_edi - Critical error code.
;*
;*   Output:
;*      All registers must be preserved.
;******************************************************************************
int24:
        push    eax                     ;save all used regs

;******************************************************************************
;*   Determine if critical error is the one we're interested in
;******************************************************************************
        mov     eax,[ebp].stk_edi       ;get edi to be sent to DOS int 24h
        and     eax,0fh                 ;isolate lowest nibble of edi
        cmp     eax,2                   ;drive-not-ready critical error?
        jne     done_int24              ;if not, we'll pass error to DOS hndlr

;******************************************************************************
;*   Critical error is drive-not-ready; process it
;******************************************************************************
        mov     drv_nrdy_flag,1         ;set drive-not-ready flag for test pgm
        or      [ebp].stk_opts,_STK_NOINT ;don't call DOS (V86) int handler

;******************************************************************************
;*   Done; chain to previous int 24h interrupt routine, if any
;******************************************************************************
done_int24:
        pop     eax

        cmp     old_int24,0             ;was there an "old" int24 handler?
        jne     goto_old_int24          ;if so, continue with old routine
        ret
goto_old_int24:
        jmp     [old_int24]             ;continue int 24 processing



;******************************************************************************
;*   int24_term
;*
;*   Performs cleanup for the int 24h handler.  A service call is made to
;*   restore the handler that was current before the new handler was
;*   installed.
;*
;*   Input:
;*      edx - gda address.
;*
;*   Output:
;*      edx preserved.  Other registers volatile.
;******************************************************************************
int24_term:
        mov     int_gda_ptr,edx         ;save ptr to gda

;******************************************************************************
;*   Remove int 24h handler by replacing with previous handler
;******************************************************************************
        mov     ah,25h                  ;SET interrupt handler addr
        mov     al,24h                  ;interrupt # to set
        mov     edx,old_int24           ;get address of old int 24h handler
        mov     ebx,int_gda_ptr         ;get ptr to gda
        call    [ebx].GDA_SERV          ;call service routine to set int addr

;******************************************************************************
;*   Exit 'int24_term'
;******************************************************************************
        mov     edx,int_gda_ptr         ;restore ptr to gda before returning
        ret


CODE    ENDS
        end     test_int24


