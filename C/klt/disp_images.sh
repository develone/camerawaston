#!/bin/bash
cp thumb0000.bmp $1thumb0000.bmp
cp thumb0000.pgm $1thumb0000.pgm
cp feat1.ppm $1feat1.ppm
cp feat1.txt $1feat1.txt
cp thumb0000.bmp $1thumb0000.bmp
gpicview $1thumb0000.bmp &
gpicview $1thumb0000.pgm &
gpicview $1feat1.ppm &
cat feat1.txt 
