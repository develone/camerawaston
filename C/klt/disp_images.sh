#!/bin/bash
cp thumb0000.bmp $1thumb0000.bmp
cp thumb0000r.pgm $1thumb0000r.pgm
cp thumb0000g.pgm $1thumb0000g.pgm
cp thumb0000b.pgm $1thumb0000b.pgm
cp feat1r.ppm $1feat1r.ppm
cp feat1g.ppm $1feat1g.ppm
cp feat1b.ppm $1feat1b.ppm
cp feat1r.txt $1feat1r.txt
cp feat1g.txt $1feat1g.txt
cp feat1b.txt $1feat1b.txt
cp thumb0000.bmp $1thumb0000.bmp
gpicview $1thumb0000.bmp &
gpicview $1thumb0000r.pgm &
gpicview $1thumb0000g.pgm &
gpicview $1thumb0000b.pgm &

gpicview $1feat1r.ppm &
gpicview $1feat1g.ppm &
gpicview $1feat1b.ppm &

cat feat1r.txt 
cat feat1g.txt 
cat feat1b.txt 
