#ifndef EXEC_ELF_H
#define EXEC_ELF_H

typedef unsigned char uint8_t;
typedef signed char s8;
typedef unsigned short uint16_t;
typedef signed short s16;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned long long u64;
typedef signed long long s64;

typedef uint32_t elf32_Addr;
typedef uint16_t elf32_Half;
typedef uint32_t elf32_Off;
typedef int32_t elf32_Sword;
typedef uint32_t elf32_Word;


//elf file header
struct elf32_header {
  uint8_t identifier[16];    //identification bytes
  elf32_Half type;           //elf object type
  elf32_Half machine;        //target machine type
  elf32_Word version;        //file verison
  elf32_Addr entry;          //program entry point
  elf32_Off ph_offset;       //first program header offset
  elf32_Off sho_offset;      //first section header offset
  elf32_Word flags;          //object file flags
  elf32_Half eh_size;        //size of the elf header
  elf32_Half phentsize;      //program header entry size
  elf32_Half phnum;          //number of program header entries
  elf32_Half shentsize;      //size of section header entries
  elf32_Half shnum;          //number of section header entries
  elf32_Half section_header_string_idx;  //index in section header of section name string table
} __attribute__ ((packed));

//elf section header
struct elf_section_header {
  elf32_Word name;           //index into string table for the name
  elf32_Word type;           //header type
  elf32_Word flags;          //header flags
  elf32_Addr address;        //header address
  elf32_Off offset;          //header offset in file
  elf32_Word size;           //header size
  elf32_Word link;           //a link to another relevant section
  elf32_Word info;           //header info
  elf32_Word address_align;  //alignment for address
  elf32_Word entry_size;     //size of entries in this section (ie symbol table)
} __attribute__ ((packed));

//a symbol in a symbol table
struct elf_symbol {
  elf32_Word name;
  elf32_Addr value;
  elf32_Word size;
  uint8_t info;
  uint8_t other;
  elf32_Half index;          //symbol header index
} __attribute__ ((packed));

//relcation entry without and addend
struct elf_relocation {
  elf32_Addr offset;
  elf32_Word info;
} __attribute__ ((packed));

struct elf_relocation_addend {
  elf32_Addr offset;
  elf32_Word info;
  elf32_Sword addend;
} __attribute__ ((packed));

struct elf32_program_header {
  elf32_Word type;
  elf32_Off offset;
  elf32_Addr virtual_address;
  elf32_Addr physical_address;
  elf32_Word file_size;            //size of this section in the file
  elf32_Word mem_size;             //size of this section in memory
  elf32_Word flags;
  elf32_Word align;
} __attribute__ ((packed));

struct elf32_dynamic_section {
  elf32_Sword tag;
  union {
    elf32_Word value;
    elf32_Addr pointer;
  } un;
} __attribute__ ((packed));


/*
 * Defines
 */

//file types
#define ELF_TYPE_NONE    0
#define ELF_TYPE_REL     1
#define ELF_TYPE_EXEC    2
#define ELF_TYPE_DYNAMIC 3
#define ELF_TYPE_CORE    4
#define ELF_TYPE_LOPROC  0xff00
#define ELF_TYPE_HIPROC  0xffff

//machine types (architectures)
#define ELF_MACHINE_NONE   0
#define ELF_MACHINE_M32    1
#define ELF_MACHINE_SPARC  2
#define ELF_MACHINE_386    3
#define ELF_MACHINE_68K    4
#define ELF_MACHINE_88K    5
#define ELF_MACHINE_860    7
#define ELF_MACHINE_MIPS   8

//version entries
#define ELF_VERSION_NONE    0
#define ELF_VERSION_CURRENT 1

//offsets into e_ident
// offsets into e_ident
#define EI_MAG0     0
#define EI_MAG1     1
#define EI_MAG2     2
#define EI_MAG3     3
#define EI_CLASS    4
#define EI_DATA     5
#define EI_VERSION  6
#define EI_PAD      7
#define EI_NIDENT   16 // number of bytes in the e_ident array

// program classes
#define ELFCLASSNONE    0
#define ELFCLASS32      1
#define ELFCLASS64      2 // invalid in this OS (no 64-bit support), here for future expansion

// data encoding (ie, endianness)
#define ELFDATANONE     0
#define ELFDATALSB      1
#define ELFDATAMSB      2

// special section indexes
#define SHN_UNDEF       0
#define SHN_LOPRESERVE  0xff00
#define SHN_LOPROC      0xff00
#define SHN_HIPROC      0xff1f
#define SHN_ABS         0xfff1
#define SHN_COMMON      0xfff2
#define SHN_HIRESERVE   0xffff

// section types
#define SHT_NULL        0
#define SHT_PROGBITS    1
#define SHT_SYMTAB      2
#define SHT_STRTAB      3
#define SHT_RELA        4
#define SHT_HASH        5
#define SHT_DYNAMIC     6
#define SHT_NOTE        7
#define SHT_NOBITS      8
#define SHT_REL         9
#define SHT_SHLIB       10
#define SHT_DYNSYM      11
#define SHT_LOPROC      0x70000000
#define SHT_HIPROC      0x7fffffff
#define SHT_LOUSER      0x80000000
#define SHT_HIUSER      0xffffffff

// section header flags
#define SHF_WRITE       0x1
#define SHF_ALLOC       0x2
#define SHF_EXECINSTR   0x4
#define SHF_MASKPROC    0xf0000000

// symbol table
#define STN_UNDEF       0

// symbol bindings
#define STB_LOCAL       0
#define STB_GLOBAL      1
#define STB_WEAK        2
#define STB_LOPROC      13
#define STB_HIPROC      15

// symbol types
#define STT_NOTYPE      0
#define STT_OBJECT      1
#define STT_FUNC        2
#define STT_SECTION     3
#define STT_FILE        4
#define STT_LOPROC      13
#define STT_HIPROC      15

// relocation types
#define R_386_NONE      0
#define R_386_32        1
#define R_386_PC32      2
#define R_386_GOT32     3
#define R_386_PLT32     4
#define R_386_COPY      5
#define R_386_GLOB_DAT  6
#define R_386_JMP_SLOT  7
#define R_386_RELATIVE  8
#define R_386_GOTOFF    9
#define R_386_GOTPC     10

// program header types
#define PT_NULL         0
#define PT_LOAD         1
#define PT_DYNAMIC      2
#define PT_INTERP       3
#define PT_NOTE         4
#define PT_SHLIB        5
#define PT_PHDR         6
#define PT_LOPROC       0x70000000
#define PT_HIPROC       0x7fffffff

// program header flags
#define PF_X            (1 << 0) // exectuable
#define PF_W            (1 << 1) // writable
#define PF_R            (1 << 2) // readable

// dynamic section tags
/*                            d_un    exectuable  shared object */
#define DT_NULL         0 //  ignored mandatory   mandatory
#define DT_NEEDED       1 //  d_val   optional    optional
#define DT_PLTRELSZ     2 //  d_val   optional    optional
#define DT_PLTGOT       3 //  d_ptr   optional    optional
#define DT_HASH         4 //  d_ptr   mandatory   mandatory
#define DT_STRTAB       5 //  d_ptr   mandatory   mandatory
#define DT_SYMTAB       6 //  d_ptr   mandatory   mandatory
#define DT_RELA         7 //  d_ptr   mandatory   optional
#define DT_RELASZ       8 //  d_val   mandatory   optional
#define DT_RELAENT      9 //  d_val   mandatory   optional
#define DT_STRSZ        10 // d_val   mandatory   mandatory
#define DT_SYMENT       11 // d_val   mandatory   mandatory
#define DT_INIT         12 // d_ptr   optional    optional
#define DT_FINI         13 // d_ptr   optional    optional
#define DT_SONAME       14 // d_val   ignored     optional
#define DT_RPATH        15 // d_val   optional    ignored
#define DT_SYMBOLIC     16 // ignored ignored     optional
#define DT_REL          17 // d_ptr   mandatory   optional
#define DT_RELSZ        18 // d_val   mandatory   optional
#define DT_RELENT       19 // d_val   mandatory   optional
#define DT_PLTREL       20 // d_val   optional    optional
#define DT_DEBUG        21 // d_ptr   optional    ignored
#define DT_TEXTREL      22 // ignored optional    optional
#define DT_JMPREL       23 // d_ptr   optional    optional
#define DT_LOPROC       0x70000000
#define DT_HIPROC       0x7fffffff

// macros for individual file sections and performing actions with them
#define STRING(image, offset) ((char *)(&((image)->ei_strtab[(offset)])))
#define SYMNAME(image, sym) STRING(image, (sym)->st_name)
#define SYMBOL(image, num) ((struct elf32_Sym *)&(image)->ei_symtab[num])
#define HASHTABSIZE(image) ((image)->ei_symhash[0])
#define HASHBUCKETS(image) ((unsigned int *)&(image)->ei_symhash[2])
#define HASHCHAINS(image) ((unsigned int *)&(image)->ei_symhash[2+HASHTABSIZE(image)])

// macros for relocation tables
#define ELF32_R_SYM(i)		((i)>>8)
#define ELF32_R_TYPE(i)		((unsigned char)(i))
#define ELF32_R_INFO(s,t)	(((s)<<8)+(unsigned char)(t))

// macros for symbols
#define ELF32_ST_BIND(i)	((i)>>4)
#define ELF32_ST_TYPE(i)	((i)&0xf)
#define ELF32_ST_INFO(b,t)	(((b)<<4)+((t)&0xf))

// Prototypes

// loads an ELF binary (type: 1 = kmod, 0 = static) - a wrapper for the above two functions
int32_t LoadElf( uint32_t kcr3, uint32_t base, uint32_t type, uint32_t taskflags, uint32_t newcr3_override, const char* modnm, char** argv );

#include "exec.h"

int elf_parse(char *filename, struct exec *e);

#endif
