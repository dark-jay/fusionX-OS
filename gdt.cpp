#include "gdt.h"

// taking array of gdtdesc because i need linear memory
gdtdesc 	gdtdesc_var[GDTSIZE];		/* GDT */
gdtr 		gdtr_var;				/* GDTR */
tss     default_tss;

// initialize a segment descriptor in gdt or ldt
void init_gdtdesc(uint32_t base, uint32_t limit, uint8_t acces, uint8_t other, struct gdtdesc *desc)
{
	desc->lim0_15 = (limit & 0xffff);
	desc->base0_15 = (base & 0xffff);
	desc->base16_23 = (base & 0xff0000) >> 16;
	desc->acces = acces;
	desc->lim16_19 = (limit & 0xf0000) >> 16;
	desc->other = (other & 0xf);
	desc->base24_31 = (base & 0xff000000) >> 24;
	return;
}

// this function will initialize the gdt
void init_gdt(void)
{

	default_tss.debug_flag = 0x00;
	default_tss.io_map = 0x00;
	default_tss.esp0 = 0x1FFF0;
	default_tss.ss0 = 0x18; /* load task register or LTR here is 0x18  */

	/* initialize gdt segments */
	init_gdtdesc(0x0, 0x0, 0x0, 0x0, &gdtdesc_var[0]); // null segment descriptor
	init_gdtdesc(0x0, 0xFFFFF, 0x9B, 0x0D, &gdtdesc_var[1]);	/* code */
	init_gdtdesc(0x0, 0xFFFFF, 0x93, 0x0D, &gdtdesc_var[2]);	/* data */
	init_gdtdesc(0x0, 0x0, 0x97, 0x0D, &gdtdesc_var[3]);		/* stack */

	init_gdtdesc(0x0, 0xFFFFF, 0xFF, 0x0D, &gdtdesc_var[4]);	/* ucode */
	init_gdtdesc(0x0, 0xFFFFF, 0xF3, 0x0D, &gdtdesc_var[5]);	/* udata */
	init_gdtdesc(0x0, 0x0, 0xF7, 0x0D, &gdtdesc_var[6]);		/* ustack */

	init_gdtdesc((uint32_t) & default_tss, 0x67, 0xE9, 0x00, &gdtdesc_var[7]);	/* descripteur de tss */

	// initialize the gdtr structure
	gdtr_var.limit = GDTSIZE * 8;
	gdtr_var.base = GDTBASE;

	// copy the gdtr to its memory area
	memcpy((char *) gdtr_var.base, (char *) gdtdesc_var, gdtr_var.limit);

	// load the gdtr registry with the lgdt instruction
	asm("lgdtl (gdtr_var)");

	// load selectors into segment registers
  // 0x10 is pointing at the new data selector
  // 0x08 is pointing at the new code selector
	asm("   movw $0x10, %ax	\n \
            movw %ax, %ds	\n \
            movw %ax, %es	\n \
            movw %ax, %fs	\n \
            movw %ax, %gs	\n \
            ljmp $0x08, $next	\n \
            next:		\n");

}
