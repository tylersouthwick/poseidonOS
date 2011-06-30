#ifndef DEV_FLOPPY_H
#define DEV_FLOPPY_H

/**********************************************************************************************
 * floppy.h
 * 
 * Notes:
 *	a lot of the floppy code is modeled after GazOS - some of it is even a copy of that code.
 *	In later versions of PoseidonOS, the floppy code will be rewritten from scratch, but, at
 *	the moment, it will be based on the GazOS code.
 ********************************************************************************************/

#include <ktypes.h>

/*****************************************definitions****************************************/
/* drive geometries */
#define DG144_HEADS       2     /* heads per drive (1.44M) */
#define DG144_TRACKS     80     /* number of tracks (1.44M) */
#define DG144_SPT        18     /* sectors per track (1.44M) */
#define DG144_GAP3FMT  0x54     /* gap3 while formatting (1.44M) */
#define DG144_GAP3RW   0x1b     /* gap3 while reading/writing (1.44M) */

#define DG168_HEADS       2     /* heads per drive (1.68M) */
#define DG168_TRACKS     80     /* number of tracks (1.68M) */
#define DG168_SPT        21     /* sectors per track (1.68M) */
#define DG168_GAP3FMT  0x0c     /* gap3 while formatting (1.68M) */
#define DG168_GAP3RW   0x1c     /* gap3 while reading/writing (1.68M) */

/* IO ports */
#define FDC_DOR  (0x3f2)   /* Digital Output Register */
#define FDC_MSR  (0x3f4)   /* Main Status Register (input) */
#define FDC_DRS  (0x3f4)   /* Data Rate Select Register (output) */
#define FDC_DATA (0x3f5)   /* Data Register */
#define FDC_DIR  (0x3f7)   /* Digital Input Register (input) */
#define FDC_CCR  (0x3f7)   /* Configuration Control Register (output) */

/* command bytes (these are 765 commands + options such as MFM, etc) */
#define CMD_SPECIFY (0x03)  /* specify drive timings */
#define CMD_WRITE   (0xc5)  /* write data (+ MT,MFM) */
#define CMD_READ    (0xe6)  /* read data (+ MT,MFM,SK) */
#define CMD_RECAL   (0x07)  /* recalibrate */
#define CMD_SENSEI  (0x08)  /* sense interrupt status */
#define CMD_FORMAT  (0x4d)  /* format track (+ MFM) */
#define CMD_SEEK    (0x0f)  /* seek track */
#define CMD_VERSION (0x10)  /* FDC version */
/***************************************end definitions**************************************/

/*****************************************structures*****************************************/
/* drive geometry */
typedef struct drive_geometry {
   unsigned char heads;
   unsigned char tracks;
   unsigned char spt;     /* sectors per track */
} drive_geometry;
/***************************************end structures***************************************/

/******************************************prototypes****************************************/
void floppy_init(void);
void floppy_sendbyte(int);
int floppy_getbyte(void);
void floppy_irq(void);
void floppy_isr(void);
void floppy_timer(void);
bool floppy_wait(bool);
void floppy_reset(void);
bool floppy_diskchange(void);
void floppy_motor_start(void);
void floppy_motor_stop(void);
void floppy_recalibrate(void);
bool floppy_seek(int);
bool flooppy_log_disk(drive_geometry *);
void floppy_block2hts(int, int *, int *, int *);
bool floppy_format_track(unsigned char, drive_geometry *);
bool floppy_rw(int, unsigned char *, unsigned char, unsigned long);
bool floppy_block_read(unsigned int block, void *blockbuff, unsigned int nosectors);
bool floppy_block_write(unsigned int block, void *blockbuff, unsigned int nosectors);
/***************************************end prototypes*****************************************/

#endif
