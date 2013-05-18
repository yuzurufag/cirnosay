# Cirnosay

`cirnosay` - speaking Cirno

# Installation
    ./download_pictures.sh
    cmake . && make install

Or, if you preffer, you can run `cirnosay` without installation:

    ./download_pictures.sh
    cmake -DIN_PLACE:BOOL=ON . && make
    ./src/cirnosay "I'm the Strongest\!"

Dependencies: `cmake` and `imlib2`
