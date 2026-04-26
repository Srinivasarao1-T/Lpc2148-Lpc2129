SET PATH=C:\KeilARM\ARM\BIN40\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\Program Files\Flash Magic;C:\Program Files\Flash Magic_8051;C:\Program Files\Flash Magic_ARM;;C:\PROGRA~1\FLASHM~1;C:\PROGRA~1\FLASHM~2
SET ARMCC41INC=C:\KeilARM\ARM\RV31\INC
SET ARMCC41LIB=C:\KeilARM\ARM\RV31\LIB
SET CPU_TYPE=LPC2129
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00000000
"C:\KeilARM\ARM\BIN40\ArmAsm" --Via "startup._ia"
"C:\KeilARM\ARM\BIN40\ArmCC" --Via "mux.__i"
"C:\KeilARM\ARM\BIN40\ArmLink" --Via "mux.lnp"
C:\KeilARM\ARM\BIN40\fromelf.exe "mux.axf" --i32combined --output "mux.hex"
