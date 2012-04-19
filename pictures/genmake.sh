#!/bin/bash

PICTURES=(
	http://en.touhouwiki.net/images/c/c0/Touhoudex_Cirno.png
	http://en.touhouwiki.net/images/3/3c/Touhoudex_Chibi_Cirno.png
	http://en.touhouwiki.net/images/8/88/Touhoudex_EX_Cirno.png
)

genmake()
{
	echo ".PHONY: all clean"
	echo

	echo -n "all: "

	for URL in "${PICTURES[@]}";do
		NAME="$(basename "$URL")"
		echo -n "r_$NAME" "l_$NAME" ""
	done

	echo
	echo

	for URL in "${PICTURES[@]}";do
		NAME="$(basename "$URL")"
		echo    "r_$NAME:"
		echo -e "\twget" "$URL" -O "r_$NAME"
		echo -e "\tconvert" "r_$NAME" -filter Box -resize 64 -trim "r_$NAME"
		echo
		echo    "l_$NAME:"
		echo -e "\tconvert" "r_$NAME" -flop "l_$NAME"
		echo
	done

	echo "clean:"
	
	for URL in "${PICTURES[@]}";do
		NAME="$(basename "$URL")"
		echo -e "\trm" -f "r_$NAME" "l_$NAME"
	done
}

genmake
