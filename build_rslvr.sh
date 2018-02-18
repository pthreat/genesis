#!/bin/bash

rm -f src/*

gcc -c lib/db/conn.c -o src/conn.o
gcc -c lib/util/list.c -o src/list.o
gcc -c lib/sql/queries.c -o src/queries.o
gcc -c lib/util/uri.c -o src/uri.o
gcc -c lib/util/net/ipgen.c -o src/ipgen.o

gcc -c rslvr.c -o src/rslvr.o

gcc src/*.o $(mysql_config --cflags --libs) -lcurl -lssl -lcrypto $(pkg-config --cflags --libs gumbo) -o ./rslvr
