.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
  .long MAGIC
  .long FLAGS
  .long CHECKSUM


.section .text
.extern kMain
.extern callConstructors
.global loader

loader:
  mov $k_stack, %esp

  call callConstructors

  push %eax
  push %ebx
  call kMain

_stop:
  cli
  hlt
  jmp _stop

.section  .bss
.space 2*1024*1024; # 2 MiB
k_stack:
