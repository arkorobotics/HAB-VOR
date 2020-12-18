CFLAGS=-Ofast -W -D WITH_RTL  -I /usr/local/include/librtlsdr


OS := $(shell uname)
ifeq ($(OS), Darwin)
    # Run MacOS commands 
    LIBS=  -lusb-1.0 -lpthread -L /usr/local/lib -lrtlsdr -lm
else
    # check for Linux and run other commands
    LIBS=  -lusb-1.0 -lpthread -L /usr/local/lib -lrtlsdr -lm -lrt 
endif


all: vortracker

vortracker: rtl.o vor.o vortrack.o
	$(CC) -o vortracker rtl.o vor.o vortrack.o $(LIBS) $(LDFLAGS)

test:	vor.o test.o
	$(CC) -o test vor.o test.o $(LIBS) $(LDFLAGS)

clean:
	rm -f *.o vortracker
