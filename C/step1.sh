#!/bin/bash
sudo rm -f *.bmp
#sudo python ../python/takeshot.py
sudo raspistill -n -e bmp -vf -hf -w 128 -h 128 -t 120 -o left.bmp
sudo ./rd
