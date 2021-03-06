#define INRATE 2000000
#define FSINT 50000
#define IFFREQ 50000

#define DOWNSC (INRATE/FSINT)   // 40

#define INBUFSZ (DOWNSC*2048)   // 81920

#define VOR_BAND_MIN 108000000
#define VOR_BAND_MAX 117950000

#define HAM_2M_BAND_MIN 144000000
#define HAM_2M_BAND_MAX 148000000

extern int freq;
