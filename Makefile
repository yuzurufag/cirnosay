.PHONY: all clean

all: pictures/Makefile
	${MAKE} -C pictures
	${MAKE} -C src

pictures/Makefile:
	pictures/genmake.sh > pictures/Makefile

clean: pictures/Makefile
	${MAKE} -C pictures clean
	rm -f pictures/Makefile
	${MAKE} -C src clean
