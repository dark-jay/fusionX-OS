#ifndef __GDT_H
#define __GDT_H

#include "libc/types.h"
#include "libc/libc.h"

#define IDTSIZE		0xFF	/* maximum number of descriptors in the table */
#define GDTSIZE		0xFF	/* maximum number of descriptors in the table */

#define IDTBASE		0x00000000	/* physical address of the idt, it must be this location */
#define GDTBASE		0x00000800	/* physical address of the gdt, it must be this location */

// gdt registry structure
struct gdtr {
  uint16_t limit;
  uint32_t base;
} __attribute__ ((packed));

// segment descriptors structure
struct gdtdesc {
  uint16_t lim0_15;
  uint16_t base0_15;
  uint8_t base16_23;
  uint8_t acces;
  uint8_t lim16_19:4;
  uint8_t other:4;
  uint8_t base24_31;
} __attribute__ ((packed));

struct tss {
	uint16_t previous_task, __previous_task_unused;
	uint32_t esp0;
	uint16_t ss0, __ss0_unused;
	uint32_t esp1;
	uint16_t ss1, __ss1_unused;
	uint32_t esp2;
	uint16_t ss2, __ss2_unused;
	uint32_t cr3;
	uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	uint16_t es, __es_unused;
	uint16_t cs, __cs_unused;
	uint16_t ss, __ss_unused;
	uint16_t ds, __ds_unused;
	uint16_t fs, __fs_unused;
	uint16_t gs, __gs_unused;
	uint16_t ldt_selector, __ldt_sel_unused;
	uint16_t debug_flag, io_map;
} __attribute__ ((packed));

extern "C" {
	void init_gdtdesc(uint32_t, uint32_t, uint8_t, uint8_t, struct gdtdesc *);
	void init_gdt(void);
}

#endif
