include ../dirs.mk
C_DATA_DIR:=\"$(subst ",\\",$(subst \\,\\\\,$(DATA_DIR)))\" #")

LDFLAGS:=`pkg-config --libs imlib2`
CXXFLAGS:=-O3 -g -std=c++11 -Wall -Wextra -Werror -DDATA_DIR="${C_DATA_DIR}"

CANVAS_OBJ:=canvas/border_simple.o canvas/compose.o canvas/picture.o canvas/text.o
OBJ:=char.o cirnosay.o findfile.o out.o palette.o picture.o utils.o ${CANVAS_OBJ}

cirnosay: ${OBJ}
	${CXX} ${OBJ} ${LDFLAGS} -o cirnosay

clean:
	rm -f cirnosay ${OBJ} config.h

# for i in `find -iname '*.cpp'`;do echo -n $(dirname $i)/;$CXX -MM $i;done
./utils.o: utils.cpp utils.h
./canvas/text.o: canvas/text.cpp canvas/text.h canvas/canvas.h canvas/../char.h
./canvas/compose.o: canvas/compose.cpp canvas/compose.h canvas/canvas.h \
 canvas/../char.h
./canvas/picture.o: canvas/picture.cpp canvas/picture.h canvas/canvas.h \
 canvas/../char.h canvas/../palette.h canvas/../picture.h
./canvas/border_simple.o: canvas/border_simple.cpp canvas/border_simple.h \
 canvas/canvas.h canvas/../char.h
./palette.o: palette.cpp palette.h
./char.o: char.cpp char.h
./findfile.o: findfile.cpp findfile.h
./picture.o: picture.cpp picture.h palette.h
./cirnosay.o: cirnosay.cpp canvas/border_simple.h canvas/canvas.h \
 canvas/../char.h canvas/compose.h canvas/picture.h canvas/../palette.h \
 canvas/../picture.h canvas/text.h findfile.h out.h utils.h
./out.o: out.cpp out.h canvas/canvas.h canvas/../char.h
