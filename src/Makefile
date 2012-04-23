LDFLAGS:=`pkg-config --libs imlib2`
CDIR:='"'$(shell pwd|sed -e 's/\\/\\\\/g' -e 's/"/\\"/g')'/"'
CXXFLAGS:=-O3 -g -std=c++11 -Wall -DBUILD_DIR=${CDIR}

CANVAS_OBJ=canvas/picture.o canvas/text.o canvas/border_simple.o canvas/compose.o
OBJ=cirnosay.o picture.o palette.o out.o char.o utils.o ${CANVAS_OBJ}

cirnosay: ${OBJ}
	${CXX} ${OBJ} ${LDFLAGS} -o cirnosay

clean:
	rm -f cirnosay ${OBJ} config.h

# find -iname '*.cpp' -exec $CXX -MM {} \;
utils.o: utils.cpp utils.h
text.o: canvas/text.cpp canvas/text.h canvas/canvas.h canvas/../char.h
compose.o: canvas/compose.cpp canvas/compose.h canvas/canvas.h \
 canvas/../char.h
picture.o: canvas/picture.cpp canvas/picture.h canvas/canvas.h \
 canvas/../char.h canvas/../palette.h canvas/../picture.h
border_simple.o: canvas/border_simple.cpp canvas/border_simple.h \
 canvas/canvas.h canvas/../char.h
palette.o: palette.cpp palette.h
char.o: char.cpp char.h
picture.o: picture.cpp picture.h palette.h
cirnosay.o: cirnosay.cpp canvas/border_simple.h canvas/canvas.h \
 canvas/../char.h canvas/compose.h canvas/picture.h canvas/../palette.h \
 canvas/../picture.h canvas/text.h out.h utils.h
out.o: out.cpp out.h canvas/canvas.h canvas/../char.h
