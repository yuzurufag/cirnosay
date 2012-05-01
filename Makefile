.PHONY: all install clean

include dirs.mk

all:
	${MAKE} -C data/pictures
	${MAKE} -C src

install: all
	[ "${IN_PLACE}" -eq 0 ]
	mkdir -p "${DESTDIR}${BIN_DIR}" "${DESTDIR}${DATA_DIR}"
	cp -T src/cirnosay "${DESTDIR}${BIN_DIR}"/cirnosay
	cp -rT data "${DESTDIR}${DATA_DIR}"
	rm -f "${DESTDIR}${DATA_DIR}/pictures/Makefile" "${DESTDIR}${DATA_DIR}/pictures/.gitignore"

uninstall:
	[ "${IN_PLACE}" -eq 0 ]
	rm -rf "${DESTDIR}${BIN_DIR}/cirnosay" "${DESTDIR}${DATA_DIR}"

clean:
	${MAKE} -C data/pictures clean
	${MAKE} -C src clean
