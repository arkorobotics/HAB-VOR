/*
 *   Authors: Arko
 *   		  Based on 'vortrack' - Copyright (c) 2014 Thierry Leconte (f4dwv)
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <signal.h>
#include <getopt.h>
#include <math.h>
#include <complex.h>
#include "vornav.h"


// RTL USB Variables and Functions
int initRtl(int dev_index, int fr);
int runRtlVorTracker(int fr);
int cancelRtlVorTracker(void);
int devid = 0;
int ppm = 0;
int gain = 0;
int verbose = 0;
int interval=2;
int freq;

// Program Functions
static void sighandler(int signum);

// Prints program usage information
static void usage(void)
{
	fprintf(stderr, "vor-nav by Arko \n\n");
	fprintf(stderr, "vortrack by Thierry Leconte \n\n");
	fprintf(stderr, "Usage: vortrack [-g gain] [-l interval ] [-p ppm] [-r device] frequency in MHz\n\n");
	fprintf(stderr, " -g gain :\t\t\tgain in tenth of db (ie : 500 = 50 db)\n");
	fprintf(stderr, " -p ppm :\t\t\tppm freq shift\n");
	fprintf(stderr, " -r n :\t\t\trtl device number\n");
	fprintf(stderr, " -l interval :\t\t\ttime between two measurements\n");
	exit(1);
}

// Main
int main(int argc, char **argv)
{
	// Process program arguement inputs
	int c;
	struct sigaction sigact;

	while ((c = getopt(argc, argv, "vg:l:p:r:h")) != EOF) {
		switch ((char)c) {
		case 'v':
			verbose = 1;
			break;
		case 'l':
			interval = atoi(optarg);
			break;
		case 'g':
			gain = atoi(optarg);
			break;
		case 'p':
			ppm = atoi(optarg);
			break;
		case 'r':
			devid = atoi(optarg);
			break;
		case 'h':
		default:
			usage();
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "need frequency\n");
		exit(-2);
	}

	// Read initial center frequency arguement
	freq = (int)(atof(argv[optind]) * 1000000.0);
	// Check frequency arguement is in-band
	if(freq<VOR_BAND_MIN || freq > HAM_2M_BAND_MAX) {
		fprintf(stderr, "invalid frequency\n");
		exit(-2);
	}

	// Configure signal handler and actions
	sigact.sa_handler = sighandler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGTERM, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);

	// Initialize RTL USB Device
	if (initRtl(devid, freq)){
		exit(-1);
	}

	// TODO: Implement Scan, Identify, Track, and Localize state machine

	// Run VOR Tracker
	runRtlVorTracker(freq);
	
	// wait for VOR station status
	//

	// Cancel VOR Tracker
	cancelRtlVorTracker();

	sighandler(0);
	exit(0);
}


static void sighandler(int signum)
{
	exit(0);
}
