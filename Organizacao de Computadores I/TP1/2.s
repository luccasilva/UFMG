ADDI x15, x0, 1
BLE x10, x15, FALSE
ADDI x16, x0, 2

LOOP:
BGE x16, x10, TRUE
REM x14, x10, x16
BEQ x14, x0, FALSE
ADDI x16, x16, 1
JAL x0, LOOP

TRUE:
ADDI x10, x0, 1
JAL x0, END

FALSE:
ADDI x10, x0, 0
JAL x0, END

END: