# The Genesis Project

Genesis is a tool aimed to gather domain names by generating random / user defined IP addresses. You can think of it as a "web crawler" but it's only aim is to fetch href/src attributes from web sites in order to populate a crawl_pool table, which can be used afterwards for performing true crawling over the fetched domain names.

##Disclaimer

While web scraping is a gray area, the authors of this application take no responsability to whatever you might do with it.

## Getting started

Edit your config.h file to your preferences, create a MySQL Database that matches your parameters in config.h
Import the SQL file located at sql/genesis.sql

##Gumbo parser

This project uses a great library for parsing HTML https://github.com/google/gumbo-parser
You need to install this library before building the project

## Building

Run ./build.sh
