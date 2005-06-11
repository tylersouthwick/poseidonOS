
#ifndef __COFF_H
#define __COFF_H

#define COFF_MAGIC 0x14C

#define COFF_RELFLG 0x001
#define COFF_EXEC 0x002
#define COFF_LNNO 0x004
#define COFF_LSYMS 0x008
#define COFF_AR32WR 0x0100

#define COFF_HAS_RELOCATION_INFO(a) ((int)a & COFF_RELFLG)
#define COFF_IS_EXECUTIBLE(a) ((int)a & COFF_EXEC)
#define COFF_HAS_LINE_NUMBERS(a) ((int)a & COFF_LNNO)
#define COFF_NO_LOCAL_SYMS(a) ((int)a & COFF_LSYMS)
#define COFF_LITTLE_ENDIAN(a) ((int)a & COFF_AR32WR)

typedef struct {
	unsigned short f_magic;
	unsigned short f_nscns;
	unsigned long f_timedat;
	unsigned long f_symptr;
	unsigned long f_nsyms;
	unsigned short f_opthdr;
	unsigned short f_flags;
}  FILHDR;

typedef struct {
	char s_name[8];
	unsigned long s_paddr;
	unsigned long s_vaddr;
	unsigned long s_size;
	unsigned long s_scnptr;
	unsigned long s_relptr;
	unsigned long s_lnnoptr;
	unsigned short s_nreloc;
	unsigned short s_nlnno;
	unsigned long s_flags;
} SCNHDR;

#endif

