#!/bin/sh

cd ../lib && make clean && make && cd ../app2 && make clean && make && make install && serieViaUSB -l