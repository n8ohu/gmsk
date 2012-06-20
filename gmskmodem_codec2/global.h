/* global.h */


// global data + defines, some other vars

// version 20111202: initial release

/*
 *      Copyright (C) 2011 by Kristoff Bonne, ON1ARF
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; version 2 of the License.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 */


// DEFINEs
// GLOBAL PARAMETERS

// common for sender and receiver
#define PARSECLIRETMSGSIZE 600			// maximum size of return message of parsecli
#define ISALRETMSGSIZE 160 // maximum size of return message of input_sal
#define INITALSARETMSGSIZE 160

#define PERIOD 960 // 20 ms of audio at 48Khz sampling
#define RATE 48000
#define FOREVER 1

// defines for receiver
#define MAXNOISEREJECT 45000	// maximum noise samples (amplitude > noise amplitude)
										// that may be ignored 
#define BITERRORSSTARTSYN 2	// number of biterrors accepted in "START" syn pattern
										// note, this is a "penalty".
										// 2 means either 1 bit wrong

                              // margin above what level a received audio-sample is concidered noise
#define MAXAUDIOLEVEL_MARGIN 1.4
#define DISABLE_AUDIOLEVELCHECK 1 // set to "1" to disable audio level check, else set to "0"



// defines for sender
#define BUFFERSIZE_AUDIO 240000 // 5 seconds  
#define BUFFERSIZE_BITS 48000 // 10 seconds

#define AUDIOMINBUFFER 4800

#define DEFAULT_SILENCEBEGIN 2 // 2 seconds silence at beginning
#define DEFAULT_SILENCEEND 1 // 1 seconds silence at beginning

#define ALSACAPTURENONBLOCK 1 // 0=blocked alsa capture, 1 = unblocked alsa read
#define ALSAPLAYBACKNONBLOCK 0 // 0=blocked alsa playback, 1 = unblocked alsa read
#define ALSAMAXERRORCOUNT 100 // stop after 100 invalid errors


// global data structure definition for RECEIVER
typedef struct {
	char *buffer[256];
	int buffersize[256];
	int audioaverage[256];
	int fileend[256];
	int sending[256];
	int pntr_capture, pntr_process;
	FILE * filein;
	char * fnamein;
	snd_pcm_t *handle;
	snd_pcm_uframes_t frames;
	char * fnameout;
	int outtostdout;
	char * udpout_host;
	int udpout_port;
	int dumpstream;
	int dumpaverage;
	int stereo;
	int ipv4only;
	int ipv6only;
	uint16_t syncpattern;
	int syncsize;
	int sendmarker;
	int recformat; // 0=undef, 1=dvtool, 2=dstar stream, 10=raw, 20=codec2
	int disable;

	// data only used when ALSA is possible
	#ifdef _USEALSA
		int fileorcapture; // 0 = capture, 1 = file
		char * capturedevice;
	#endif
} r_globaldatastr;

// global data structure itself
r_globaldatastr r_global;


// global data structure definition for SENDER
typedef struct {
	// audio and bit queues
	int16_t buffer_audio[BUFFERSIZE_AUDIO];
	unsigned char buffer_bits[BUFFERSIZE_BITS];
	unsigned char buffer_bits_mask[BUFFERSIZE_BITS];
	char octetorderinvert[BUFFERSIZE_BITS];
	int ptr_a_fillup; int ptr_a_read; // audio
	int ptr_b_fillup; int ptr_b_read; // bits

	// flags if the queues are empty or not
	int waiting_bits;
	int waiting_audio;

	// file in
	char * fnamein;
	int infromstdin;

	// TCP or UDP in
	int tcpport;
	int udpport;

	// output
	int fileoralsa;

	// file out
	char * fnameout;

	// only used when ALSA is possible
	#ifdef _USEALSA
		// ALSA
		char * alsaname;
		snd_pcm_t *alsahandle;
		snd_pcm_uframes_t alsaframes;
		int alsastate;

		// PTT switching        
		char * pttcsdevice;
		char * ptttxdevice;
		char * pttlockfile;
		int ptton;
		int ptt_invert;
	#endif

	// flags from CLI options to application
	int sync;
	int zap;
	int silencebegin;
	int silenceend;

	// disabled
	int disable;

} s_globaldatastr;

// global data structure itself
s_globaldatastr s_global;


// global data structure definition COMMON for both sender and receiver
typedef struct {
	// flags from CLI options to application
	int verboselevel;

	// common options
	int audioinvert; // 0=none, 1=rx, 2=tx, 3=both
	int format; // 0=undef, 1=dvtool, 2=dstar stream, 10=raw, 20=codec2
	int rawinvert;

	// DV system
	int dvsystem; // 0=undef, 1=d-star, 2=codec2

	// communication between sender and receiver to avoid starting to send when receiving a stream
	int sending;
	int receiving;
} g_globaldatastr;

// global data structure itself
g_globaldatastr g_global;


// COMBINED datastructure
// Used when functions need information from multiple
// global structures

// only used as pointer structure
typedef struct {
	r_globaldatastr *p_r_global; // global data receiver
	s_globaldatastr *p_s_global; // global data sender
	g_globaldatastr *p_g_global; // global data for both sender and receiver
} c_globaldatastr;

// structure itself
c_globaldatastr c_global; 


// END GLOBAL STRUCTURES


// FIXED D-STAR PATTERNS
// beginning syncronisation pattern:
// 128 bit pattern containing "1010..." (twice as much as required by specs)
// followed by 15 bit frame syncronisation pattern "1110110 01010000"

// as the frame sync pattern is only 15 bits and not a full 2 octets, the
// final "0" of the bit syn pattern is located in the MSB of the 2 last octets

unsigned char dstar_startsync_pattern[]= {0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x76, 0x50};


unsigned char codec2_startsync_pattern[]= {0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
0x55, 0x55, 0x05, 0x67};




// some other stuff
unsigned char bit2octet[]={ 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

uint16_t size2mask[]= {0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF};

unsigned char invertbits[]= {
 0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
 0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
 0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
 0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
 0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
 0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
 0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
 0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
 0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
 0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
 0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
 0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
 0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
 0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
 0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
 0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF };




