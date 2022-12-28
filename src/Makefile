
CFLAGS+=-DDEBUGGING_HACKS

CFLAGS+=-Wall -Werror
CXXFLAGS=$(CFLAGS) -std=c++11

CPPFLAGS+=-I.
CPPFLAGS+=-I./lib

CSRC=

CCSRC=\
	main.cc\
	lib/memory.cc\
	lib/devices.cc\
	lib/saferead.cc\
	lib/rv32.cc\
	lib/dev/memcard.cc

COBJ=$(CSRC:.c=.o)
CCOBJ=$(CCSRC:.cc=.o)
OBJS=$(COBJ) $(CCOBJ)

.PHONY: all clean world

all: rvddt

rvddt: $(OBJS)
	$(LINK.cc) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS) 

clean:
	rm -f *.o rvddt

world: clean all
