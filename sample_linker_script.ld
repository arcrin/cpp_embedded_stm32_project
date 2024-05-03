MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K
  RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 40K
}

SECTIONS
{
  .text : {
    *(.text) /* Place all text (code) sections here */
    *(.rodata) /* Read-only data */
  } > FLASH

  .data : {
    *(.data) /* Initialized data */
    . = ALIGN(4);
  } > RAM AT > FLASH

  .bss : {
    *(.bss) /* Uninitialized data */
    . = ALIGN(4);
  } > RAM

  /* Stack and heap are often setup by startup code instead of linker script in many environments */
}
