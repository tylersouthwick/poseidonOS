#include <ktypes.h>
#include <screen.h>
#include <gdt.h>
#include <multitasking.h>

extern void gdt_asm_init();
extern tss_t * system_tss;

void gdt_init() {
#ifdef USE_DYNAMIC_GDT
	struct gdt_descriptor *gdt = kmalloc(sizeof(struct gdt_descriptor) * 7);
	tss_t *tss = system_tss;
	int i = 0;

	/*null segment*/
	memset(gdt, 0, sizeof(struct gdt_descriptor));
	i++;

	/*kernel code segment*/
	//gdt_add_descriptor(&gdt[i], 0, 0xFFFF, 1, 1, 1, 0, 0, GDT_TYPE_CODE_EXECUTE_ONLY);
	i++;

	/*kernel code segment*/
	i++;

	/*kernel code segment*/
	i++;

	/*kernel code segment*/
	i++;

	/*kernel code segment*/
	gdt[i].limit = sizeof(tss_t);
	gdt[i].base015 =(int)&tss;
	gdt[i].base1623=(int)&tss >>16;
	gdt[i].access =0x89;//0x80+0x9
	gdt[i].granularity=0;
	gdt[i].base2431=(int)&tss>>24;
	
#endif
	gdt_asm_init();
}
