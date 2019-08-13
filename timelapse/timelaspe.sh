#/bin/bash
#sudo raspistill -n -e bmp -vf -hf -w 128 -h 128 -t 10800000 -tl 10000 -o frames/frame%04d.bmp &
sudo raspistill -n -e bmp -vf -hf -w 128 -h 128 -t 10800000 -tl 100 -o frames/frame%04d.bmp &
