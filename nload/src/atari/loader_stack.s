        .export clear_menu
        .export load_setup
        .export load_init
        .export dosiov
        .export load_close
        .export bindcb
        .export clodcb
        .export stadcb

        .include "atari.inc"

.segment "LSTACK"

clear_menu:    
    	lda     #0
    	ldx     #0
    	ldy     #$b8
cloop:	sta     $0700,x
    	inx
    	bne     cloop
    	inc     cloop+2  ; increasing HI-byte of the clearing address
    	dey
    	bne     cloop
	    RTS

load_setup:
        LDA     #$C0
        STA     RUNAD
        LDA     #$E4
        STA     RUNAD+1
        RTS

load_init:
        LDA     #$C0
        STA     INITAD
        LDA     #$E4
        STA     INITAD+1
        RTS

dosiov:
        STA     dodcbl+1
        STY     dodcbl+2
        LDY     #$0B
dodcbl: LDA     $FFFF,Y
        STA     DCB,Y
        DEY
        BPL     dodcbl

SIOVDST:
        JSR     SIOV
        LDY     DSTATS
        TYA
        RTS

load_close:
        LDA     #<clodcb
        LDY     #>clodcb
        JMP     dosiov

stadcb:
        .BYTE   $71         ; DDEVIC
        .BYTE   $01         ; DUNIT
        .BYTE   'S'         ; DCOMND
        .BYTE   $40         ; DSTATS
        .BYTE   <DVSTAT     ; DBUFL
        .BYTE   >DVSTAT     ; DBUFH
        .BYTE   $0F         ; DTIMLO
        .BYTE   $00         ; DRESVD
        .BYTE   $04         ; DBYTL
        .BYTE   $00         ; DBYTH
        .BYTE   $00         ; DAUX1
        .BYTE   $00         ; DAUX2

clodcb:
        .BYTE   $71         ; DDEVIC
        .BYTE   $01         ; DUNIT
        .BYTE   'C'         ; DCOMND
        .BYTE   $00         ; DSTATS
        .BYTE   $00         ; DBUFL
        .BYTE   $00         ; DBUFH
        .BYTE   $0F         ; DTIMLO
        .BYTE   $00         ; DRESVD
        .BYTE   $00         ; DBYTL
        .BYTE   $00         ; DBYTH
        .BYTE   $00         ; DAUX1
        .BYTE   $00         ; DAUX2

bindcb:
        .BYTE   $71         ; DDEVIC
        .BYTE   $01         ; DUNIT
        .BYTE   'R'         ; DCOMND
        .BYTE   $40         ; DSTATS
        .BYTE   $FF         ; DBUFL
        .BYTE   $FF         ; DBUFH
        .BYTE   $0F         ; DTIMLO
        .BYTE   $00         ; DRESVD
        .BYTE   $FF         ; DBYTL
        .BYTE   $FF         ; DBYTH
        .BYTE   $FF         ; DAUX1
        .BYTE   $FF         ; DAUX2
