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

int verbose = 0;
int interval=2;
int freq ;

int initRtl(int dev_index, int fr);
int runRtlSample(void);
int devid = 0;
int ppm = 0;
int gain = 0;


static void sighandler(int signum);

static void usage(void)
{
	fprintf(stderr, "vor-nav by Arko \n\n");
	fprintf(stderr, "vortrack by Thierry Leconte Copyright (c) 2018 \n\n");
	fprintf(stderr, "Usage: vortrack [-g gain] [-l interval ] [-p ppm] [-r device] frequency in MHz\n\n");
	fprintf(stderr, " -g gain :\t\t\tgain in tenth of db (ie : 500 = 50 db)\n");
	fprintf(stderr, " -p ppm :\t\t\tppm freq shift\n");
	fprintf(stderr, " -r n :\t\t\trtl device number\n");
	fprintf(stderr, " -l interval :\t\t\ttime between two measurements\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int i, c;
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
	freq = (int)(atof(argv[optind]) * 1000000.0);

	if(freq<VOR_BAND_MIN || freq > 150000000) {
		fprintf(stderr, "invalid frequency\n");
		exit(-2);
	}

	sigact.sa_handler = sighandler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGTERM, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);


	if (initRtl(devid, freq))
		exit(-1);
	runRtlSample();

	sighandler(0);
	exit(0);

}


static void sighandler(int signum)
{
	exit(0);
}
