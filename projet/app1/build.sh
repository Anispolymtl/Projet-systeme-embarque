#!/bin/sh

cd ../lib && make clean && make && cd ../app1 && make clean && make && make install && serieViaUSB -l