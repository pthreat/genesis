#!/bin/bash

export files=$(ls lib);
export EXECUTABLE="genesis"
export SSL_FLAGS="-lssl -lcrypto"
export MYSQL_FLAGS=$(mysql_config --cflags --libs);
export SOURCES="src"
export LIB="lib"

[ ! -d $SOURCES ] && mkdir $SOURCES

rm -f genesis
rm -f src/*

for x in $files; do 
	echo "Compiling $x ..."
	export mod="${x}.o"
	gcc -c "$LIB/$x" -o "$SOURCES/$mod"
done

gcc -c vendor/htmlstreamparser/htmlstreamparser.c -o src/htmlstreamparser.o
gcc -c vendor/libyuarel/yuarel.c -o src/yuarel.o

gcc src/*.o $(mysql_config --cflags --libs) -lcurl -lssl -lcrypto -o $EXECUTABLE

[ $? -eq 0 ] && echo "Let the games ... BEGIN!"

