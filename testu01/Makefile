
.SUFFIXES:
#
.SUFFIXES: .cpp .o .c .h


.PHONY: clean cleandist
PROCESSOR:=$(shell uname -m)
ifeq ($(PROCESSOR), aarch64)
OPTIFLAG =
else
OPTIFLAG = -march=native
endif

CFLAGS = -fPIC -std=c99 -O3 $(OPTIFLAG) -Wall -Wextra -Wshadow -Wno-implicit-function-declaration

LIBS=build/lib/libmylib.a build/lib/libprobdist.a build/lib/libtestu01.a
LIBSCMD= build/lib/libtestu01.a  build/lib/libprobdist.a build/lib/libmylib.a  -lm
LIBTARGET=build/lib/libmylib.a
EXECUTABLES=testLizardPwlcm 
HEADERS=include/main.h


all: $(EXECUTABLES)

TestU01.zip:
	(curl -OL http://simul.iro.umontreal.ca/testu01/TestU01.zip)

TestU01-1.2.3: TestU01.zip
	(unzip -qo TestU01.zip)

$(LIBTARGET): TestU01-1.2.3
	(cd TestU01-1.2.3 && ./configure --prefix="$$(dirname "$$(pwd)")/build" && make -j 6 && make -j 6 install)

testLizardPwlcm: $(LIBTARGET) $(HEADERS) toolex.o lizard.o pwlcm.o
	$(CC) $(CFLAGS) -o testLizardPwlcm src/testLizardPwlcm.c toolex.o lizard.o pwlcm.o $(LIBSCMD) -I../source -Ibuild/include/ -Iinclude -Isrc/lizardpwlcm

toolex.o: src/lizardpwlcm/toolex.c
	$(CC) -g -c src/lizardpwlcm/toolex.c -o toolex.o
lizard.o: src/lizardpwlcm/lizard.c
	$(CC) -g -c src/lizardpwlcm/lizard.c -o lizard.o
pwlcm.o: src/lizardpwlcm/pwlcm.c
	$(CC) -g -c src/lizardpwlcm/pwlcm.c -o pwlcm.o 

clean:
	rm -f $(EXECUTABLES)

cleandist:
	rm -r -f build
	rm -r -f TestU01-1.2.3
	rm -f $(EXECUTABLES)
