CFLAGS=-Ofast -W -D WITH_RTL  -I /usr/local/include/librtlsdr


OS := $(shell uname)
ifeq ($(OS), Darwin)
    # Mac OS X
    LIBS=  -lusb-1.0 -lpthread -L /usr/local/lib -lrtlsdr -lm
else
    # Linux
    LIBS=  -lusb-1.0 -lpthread -L /usr/local/lib -lrtlsdr -lm -lrt 
endif


all: vor-nav

vor-nav: rtl.o vor.o vornav.o
	$(CC) -o vor-nav rtl.o vor.o vornav.o $(LIBS) $(LDFLAGS)

test:	vor.o test.o
	$(CC) -o test vor.o test.o $(LIBS) $(LDFLAGS)

clean:
	rm -f *.o vor-nav
