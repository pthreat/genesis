#!/bin/bash

export files=$(find ./lib -name "*.c");
export EXECUTABLE="genesis"
export SSL_FLAGS="-lssl -lcrypto"
export MYSQL_FLAGS=$(mysql_config --cflags --libs);
export SOURCES="src"

[ ! -d $SOURCES ] && mkdir $SOURCES

rm -f genesis
rm -f src/*

gcc -c vendor/htmlstreamparser/htmlstreamparser.c -o src/htmlstreamparser.o
gcc -c vendor/libyuarel/yuarel.c -o src/yuarel.o

for x in $files; do 
	echo "Compiling $x ..."
	export mod=$(echo $x | sed s/"\/"/"_"/g | sed s/\.c/\.o/g | sed s/"\._"//g )
	gcc -c $x -o "./src/$mod"
done

gcc src/*.o $(mysql_config --cflags --libs) -lcurl -lssl -lcrypto -o $EXECUTABLE

[ $? -eq 0 ] && echo "Build successful, you may want to run ./$EXECUTABLE now"
