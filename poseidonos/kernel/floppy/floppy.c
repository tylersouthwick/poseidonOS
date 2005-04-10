#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <devices.h>
#include <irq.h>
#include <dma.h>

/***********************************************************
 * floppy.c
 * 
 * Creates an abstraction to read blocks from a floppy disk
 * controller.  Most of this code came from GazOS (which can
 * be found at http://gazos.sourceforge.net).  In later versions
 * of this program, there will be a rewrite from scratch, but
 * this will work at present.
 * 
 * License: GPL (see readme or the GPL website)
 * *********************************************************/

void temp_sleep(int mill);
#define FLOPPY_SLEEP_TIME 5
#define SLEEP(a) temp_sleep(a)

/***************************global floppy variables*************************/
static volatile bool floppy_done = false;
static bool floppy_dchange = false;
static bool floppy_motor = false;
static int floppy_mtick = 0;
static volatile int floppy_timeout = 0;
static unsigned char floppy_status[7] = {0};
static unsigned char floppy_statsz = 0;
static unsigned char floppy_sr0 = 0;
static unsigned char floppy_track = 0xff;
static drive_geometry floppy_geometry = {DG144_HEADS, DG144_TRACKS, DG144_SPT};

extern unsigned long *floppy_dma_address;
extern int timer_count;
/*************************end global floppy variables***********************/

/*******************************************************************************
 * void floppy_init()
 * 
 * This is where the floppy driver is initilized and where the floppy device(s)
 * are registered with the system.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	November 27, 2004
 * *****************************************************************************/
void floppy_init()
{
	process_t *floppy_timer_process;
	int floppy_count = 0;
	unsigned char c;
	unsigned char a;
	unsigned char b;
	
	#ifdef FLOPPY_SHOW_TYPE
	char *drive_type[6] = {
		"no floppy drive",
		"360kb 5.25in floppy drive",
		"1.2mb 5.25in floppy drive",
		"720kb 3.5in",
		"1.44mb 3.5in",
		"2.88mb 3.5in"
	};
	#endif
	
	outportb(0x70, 0x10);
	INPORTB(c, 0x71);
	
	a = c >> 4; // get the high nibble
	b = c & 0xF; // get the low nibble by ANDing out the high nibble
	
	if (a > 0)
	{
		floppy_count++;
		device_register("fd0", DEV_FLOPPY, DEV_FLOPPY_0, 0,0 );
	}
	
	if (b > 0)
	{
		floppy_count++;
		device_register("fd1", DEV_FLOPPY, DEV_FLOPPY_1, 0,0 );
	}
	
#ifdef DEBUG_FLOPPY_1
	kprint("Found ");
	put_int(floppy_count, 10);
	kprint(" floppy drive(s)\n");
#endif
	
	idt_interrupt_add(0x26, floppy_isr, 0);
	irq_umask(IRQ_6);
	floppy_timer_process = multitasking_process_new(floppy_timer, "floppy timer", PRIORITY_LOW);
	multitasking_process_add(floppy_timer_process);


#ifdef DEBUG_FLOPPY
	kprint("resetting floppy...");
#endif

	floppy_reset();

#ifdef DEBUG_FLOPPY
	kprint("done\n");
#endif
}

/*******************************************************************************
 * void floppy_sendbyte(int byte)
 * 
 * This is a wrapper to send a byte to the floppy controller.  This comes from
 * the Intel docs.
 * 
 * Parameters:
 * 	1) int byte
 * 		This is the byte that is to be sent to the FDC
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
void floppy_sendbyte(int byte)
{
	volatile int msr;
	int tmo;
	
	for(tmo = 0; tmo < 128; tmo++)
	{
		INPORTB(msr, FDC_MSR);
		if ((msr & 0xC0) == 0x80)
		{
			outportb(FDC_DATA, byte);
			return;
		}
		INPORTB(msr, 0x80);
	}
}

/*******************************************************************************
 * int floppy_getbyte()
 * 
 * This is a wrapper to get a byte from the floppy controller.  This comes from
 * the Intel docs.
 * 
 * Return Value:
 * 	This returns the byte that is read from the FDC
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
int floppy_getbyte()
{
	volatile int msr;
	int tmo;
	
	for (tmo = 0; tmo < 128; tmo ++)
	{
		INPORTB(msr, FDC_MSR);
		if ((msr & 0xD0) == 0xD0)
		{
			INPORTB(msr, FDC_DATA);
			return msr;
		}
		INPORTB(msr, 0x80);
	}
	
	return -1;	/*timeout*/
}

/*******************************************************************************
 * void floppy_timer()
 * 
 * This is a timer that is installed into the system and checks for floppy
 * timeouts.  It should be disabled whenever the FDC is not in use.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
 
void floppy_timer()
{
	while(1)
	{
		if (floppy_timeout)
			--floppy_timeout;
		
		if (floppy_mtick > 0)
			--floppy_mtick;
		else if (!floppy_mtick && (floppy_motor == true))
		{
			outportb(FDC_DOR, 0x0C);
			floppy_motor = false;
		}
		
		sleep(1);	//sleep a little
	}
}

/*******************************************************************************
 * void floppy_irq()
 * 
 * This is the C implementation of the floppy IRQ handler.  It is called from
 * the floppy ISR handler (in floppy.asm).  This could eventually be moved into
 * the ISR (there is only one line).  All this does is set a variable to true
 * saying that the irq fired.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
void floppy_irq()
{
	floppy_done = true;
}

/*******************************************************************************
 * bool floppy_wait(bool sensei)
 * 
 * This waits until either the irq had been fired or there has been a floppy
 * timeout.  At that time, it will send a sense interrupt message to the FDC,
 * allowing the floppy to send another irq.
 * 
 * Parameters:
 * 	1) bool sensei
 * 		This is a flag that defines whether or not the CMD_SENSEI command is
 * 		sent to the FDC.
 * 
 * Return value:
 * 	Returns whether or not there was a timeout
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
bool floppy_wait(bool sensei)
{
	floppy_timeout = 5;
	
	while((floppy_done==false) && floppy_timeout);

	floppy_statsz = 0;
	
	while ((floppy_statsz < 7) && (inportb(FDC_MSR) & (1<<4)))
		floppy_status[floppy_statsz++] = floppy_getbyte();
	
	if (sensei == true)
	{
		//if set, then we send a "sense interrupt status" command to the fdc
		floppy_sendbyte(CMD_SENSEI);
		floppy_sr0 = floppy_getbyte();
		floppy_track = floppy_getbyte();
	}
	
	floppy_done = false;
	
	if (!floppy_timeout)
	{
		/*timeout*/
		if (inportb(FDC_DIR) & 0x80)
			floppy_dchange = true;
		return false;
	} else 
		return true;
}

/*******************************************************************************
 * void floppy_reset()
 * 
 * This resets the floppy (duh!) into a known condition.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
void floppy_reset()
{
	outportb(FDC_DOR, 0);
	
	floppy_mtick = 0;
	floppy_motor = false;
	
	/*disable interrupt*/
	outportb(FDC_DRS, 0);
	
	/*reenable interrupts*/
	outportb(FDC_DOR, 0x0C);
	
	/*the reset triggered an interrupt, wait for it to be handled*/
	floppy_done = true;
#ifdef DEBUG_FLOPPY
	kprint("\nwaiting for floppy...");
#endif

	floppy_wait(true);

#ifdef DEBUG_FLOPPY
	kprint("done\n");
#endif
	
	/*specify driv timings*/
	floppy_sendbyte(CMD_SPECIFY);
	floppy_sendbyte(0xDF);
	floppy_sendbyte(0x02);
	
	/*clear the "disk change" status */
#ifdef DEBUG_FLOPPY
	kprint("floppy is seeking...");
#endif

	floppy_seek(1);

#ifdef DEBUG_FLOPPY
	kprint("done\n");
#endif
	
#ifdef DEBUG_FLOPPY
	kprint("floppy is being calibrated...");
#endif

	floppy_recalibrate();

#ifdef DEBUG_FLOPPY
	kprint("done\n");
#endif
	
	floppy_dchange = false;
}

/*******************************************************************************
 * bool floppy_diskchange()
 * 
 * This in itself does nothing.  Just gives the value of floppy_dchange.
 * 
 * Return value:
 * 	This returns whether or not the flooppy disk has changed.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
bool floppy_diskchange()
{
	return floppy_dchange;
}

/*******************************************************************************
 * void floppy_motor_start()
 * 
 * This starts the motor.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
void floppy_motor_start()
{
	if (floppy_motor == false)
	{
		floppy_mtick = -1;
		outportb(FDC_DOR, 0x1C);
		SLEEP(FLOPPY_SLEEP_TIME);
		floppy_motor = true;
	}
}

/*******************************************************************************
 * void floppy_motor_stop()
 * 
 * This stop the motor.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
void floppy_motor_stop()
{
	if (floppy_motor == true)
		floppy_mtick = 13500;
}

/*******************************************************************************
 * void floppy_recalibrate()
 * 
 * This recalibrates the FDC.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
void floppy_recalibrate()
{
	/*turn the motor on*/
	floppy_motor_start();
	
	/*send command bytes*/
	floppy_sendbyte(CMD_RECAL);
	floppy_sendbyte(0);
	
	/*wait until seek if finished*/
	floppy_wait(true);
	
	/*turn the motor off*/
	floppy_motor_stop();
}

/*******************************************************************************
 * void floppy_seek(int track)
 * 
 * This causes the floppy head to seek to the given track so that data can either
 * be written or read from it.
 * 
 * Parameters:
 * 	1) int track
 * 		This is the track that we want to seek to.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
bool floppy_seek(int track)
{
	///check to see if we've already seeked to 'track'
	if (floppy_track == track)
		return true;
	
	///send command bytes
	floppy_sendbyte(CMD_SEEK);
	floppy_sendbyte(0);
	floppy_sendbyte(track);
	
	///wait until seek is finished
	if (!floppy_wait(true))
		return false;		///timeout
	
	///wait for the head to settle
	SLEEP(FLOPPY_SLEEP_TIME);
	
	///make sure that seek worked
	if ((floppy_sr0 != 0x20) || (floppy_track != track))
		return false;
	else
		return true;
}

/*******************************************************************************
 * bool floppy_log_disk(drive_geometry *g)
 * 
 * This checks the drive geometry.  This should be called after every disk change
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
bool floppy_log_disk(drive_geometry *g)
{
	///get the floppy drive into a known condition
	floppy_reset();
	
	///assume that the disk is 1.6MB and try to read block #21 on first track
	floppy_geometry.heads = DG168_HEADS;
	floppy_geometry.tracks = DG168_TRACKS;
	floppy_geometry.spt = DG168_SPT;
	
	if (floppy_block_read(20, NULL, 1))
	{
		///this disk is 1.68MB
		if (g)
		{
			g->heads = floppy_geometry.heads;
			g->tracks = floppy_geometry.tracks;
			g->spt = floppy_geometry.spt;
		}
		return true;
	}
	
	///this disk is not 1.68MB
	///it might be a 1.44MB disk- we'll try reading block #18 on the first track
	floppy_geometry.heads = DG144_HEADS;
	floppy_geometry.tracks = DG144_TRACKS;
	floppy_geometry.spt = DG144_SPT;
	
	if (floppy_block_read(17, NULL, 1))
	{
		if (g)
		{
			g->heads = floppy_geometry.heads;
			g->tracks = floppy_geometry.tracks;
			g->spt = floppy_geometry.spt;
		}
		return true;
	}
	
	///if it reaches this point, then the floppy isn't a 1.68MB disk
	///or a 1.44MB disk.  We don't support it.
	
	return false;
}

/*******************************************************************************
 * void floppy_block2hts(int block, int *head, int *track, int *sector)
 * 
 * This converts the block into its respective head, track and sector, depending
 * on what the current geometry is.
 * 
 * Parameters:
 * 	1) int *head
 * 	2) int *track
 * 	3) int *sector
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
void floppy_block2hts(int block, int *head, int *track, int *sector)
{
	*head = (block % (floppy_geometry.spt * floppy_geometry.heads)) / (floppy_geometry.spt);
	*track = block / (floppy_geometry.spt * floppy_geometry.heads);
	*sector = block % floppy_geometry.spt + 1;
}

/*bool floppy_format_track(unsigned char track, drive_geometry *g)
{
	
}*/

/*******************************************************************************
 * bool floppy_rw(int block, unsigned char *blockbuff, 
 * 					unsigned char read, unsigned long nosectors)
 * 
 * Since the read and write to a floppy disk is not that much different.  Most of
 * the code is the same.  The only difference is dependent on what the 'read' 
 * variable is set as.
 * 
 * Parameters:
 * 	1) int block
 * 		This is the block that we want to read.
 * 	2) unsigned char *blockbuff
 * 		This is the buffer that we want it read into or written out to.  The size 
 * 		of this buffer should be 512 * nosectors, as each sector read in is 512 
 * 		bytes
 * 	3) unsigned char read
 * 		Are we going to read or write to this block.
 * 	4) unsigned long nosectors
 * 		The number of sectors that we want to be read in.
 * 
 * Return value:
 * 	This returns where or not the read/write was successfull.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
bool floppy_rw(int block, unsigned char *blockbuff, unsigned char read, unsigned long nosectors)
{
	int head;
	int track;
	int sector;
	int tries;
	int copycount=0;
	unsigned char *p_track_buffer = (unsigned char*)floppy_dma_address;
	unsigned char *p_block_buffer = blockbuff;
	
	///convert logical address into physical address
	floppy_block2hts(block , &head, &track, &sector);
	
	///start the floppy motor
	floppy_motor_start();
	
	if (!read && blockbuff)
	{
		///copy data from the data buffer into the track buffer
		for (copycount=0; copycount<(nosectors*512); copycount++)
		{
			*p_track_buffer = *p_block_buffer;
			p_block_buffer++;
			p_track_buffer++;
		}
	}
	
	for (tries = 0; tries < 3; tries++)
	{
		///check for disk change
		if (inportb(FDC_DIR) & 0x80)
		{
			floppy_dchange = true;
			floppy_seek(1);
			floppy_recalibrate();
			floppy_motor_stop();
			kprint("FDC: Disk change detected. Trying again.\n");
			return floppy_rw(block, blockbuff, read, nosectors);
		}
		
		///move head to the right track
		if (!floppy_seek(track))
		{
			floppy_motor_stop();
			kprint("FDC: Seek error\n");
			return false;
		}
		
		///program data rate (500Kb/s)
		outportb(FDC_CCR, 0);
		
		///send command
		if (read)
		{
			dma_xfer(2, (unsigned long)floppy_dma_address, nosectors*512, false);
			floppy_sendbyte(CMD_READ);
		} else {
			dma_xfer(2, (unsigned long)floppy_dma_address, nosectors*512, true);
			floppy_sendbyte(CMD_WRITE);
		}
		
		floppy_sendbyte(head << 2);
		floppy_sendbyte(track);
		floppy_sendbyte(head);
		floppy_sendbyte(sector);
		floppy_sendbyte(2);
		floppy_sendbyte(floppy_geometry.spt);
		
		if (floppy_geometry.spt == DG144_SPT)
			floppy_sendbyte(DG144_GAP3RW);
		else
			floppy_sendbyte(DG168_GAP3RW);
		
		floppy_sendbyte(0xff);
		
		///wait for commmand completion
		if (!floppy_wait(true))
		{
			kprint("Timed out, trying operation again after rest\n");
			floppy_reset();
			return floppy_rw(block, blockbuff, read, nosectors);
		}
		
		///let's see if the transfer worked
		if ((floppy_status[0] & 0xC0) == 0) break;
		
		///it didn't work.  try again
		floppy_recalibrate();
	}
	
	floppy_motor_stop();
	
	if (read && blockbuff)
	{
		///copy data from track buffer into data buffer
		p_block_buffer = blockbuff;
		p_track_buffer = (unsigned char *)floppy_dma_address;
		for (copycount = 0; copycount <(nosectors*512); copycount++)
		{
			*p_block_buffer = *p_track_buffer;
			p_block_buffer++;
			p_track_buffer++;
		}
	}
	
	return (tries != 3);
}

/*******************************************************************************
 * bool floppy_block_read(int block, unsigned char *blockbuff,
 * 							unsigned long nosectors)
 * 
 * This reads data from a floppy disk starting at 'block' and reads 'nosectors'
 * number of blocks.
 * 
 * Parameters:
 * 	1) int block
 * 		The starting sector to read
 * 	2) unsigned char *blockbuff
 * 		The buffer to be read into
 * 	3) unsigned long nosectors
 * 		How many sectors do we want to read in?
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
bool floppy_block_read(int block, unsigned char *blockbuff, unsigned long nosectors)
{
	int track=0;
	int sector=0;
	int head=0;
	int track2=0;
	int result=0;
	int loop=0;
	
	floppy_block2hts(block, &head, &track, &sector);
	floppy_block2hts(block+nosectors, &head, &track2, &sector);
	
	if (track != track2)
	{
		for (loop=0; loop<nosectors; loop++)
			result = floppy_rw(block+loop, blockbuff+(loop*512), true, 1);
		return result;
	}
	return floppy_rw(block, blockbuff, true, nosectors);
}
/*******************************************************************************
 * bool floppy_block_write(int block, unsigned char *blockbuff, 
 * 							unsigned long nosectors)
 * 
 * This writes the contents of 'blockbuff' onto a floppy disk, starting at 'block'
 * and going for 'nosectors'
 * 
 * Parameters:
 * 	1) int block
 * 		The starting sector to write to
 * 	2) unsigned char *blockbuff
 * 		The buffer to read from when writing
 * 
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 31, 2004
 * *****************************************************************************/
bool floppy_block_write(int block, unsigned char *blockbuff, unsigned long nosectors)
{
	return floppy_rw(block, blockbuff, false, nosectors);
}
