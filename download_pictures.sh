#!/bin/bash

PICTURES=(
	http://en.touhouwiki.net/images/c/c0/Touhoudex_Cirno.png
	http://en.touhouwiki.net/images/3/3c/Touhoudex_Chibi_Cirno.png
	http://en.touhouwiki.net/images/8/88/Touhoudex_EX_Cirno.png
)

DIR=./data/pictures

cd "$(dirname -- "$0")"

rm -rf "$DIR"
mkdir -p "$DIR"

wget -P "$DIR" "${PICTURES[@]}"

for PICTURE in "$DIR"/*;do
	convert "$PICTURE" -filter Box -resize 64 -trim -flop "$PICTURE"
done
