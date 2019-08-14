#/bin/bash
#sudo raspistill -n -e bmp -vf -hf -w 128 -h 128 -t 10800000 -tl 10000 -o frames/frame%04d.bmp &
#-t, --timeout	: Time (in ms) before takes picture and shuts down (if not specified, set to 5s)
#-tl, --timelapse	: Timelapse mode. Takes a picture every <t>ms
#sudo raspistill -n -e bmp -vf -hf -w 128 -h 128 -t 10800000 -tl 100 -o frames/frame%04d.bmp &
#570 frames in 5 min 300 sec 1.9 sec / frame
sudo raspistill -n -e bmp -vf -hf -w 128 -h 128 -t 1020000 -tl 100 -o frames/frame%04d.bmp &
#933 frames in 10 min 600 sec 1.5 sec /frame
# mmal: Skipping frame 1 to restart at frame 389
# mmal: Skipping frame 390 to restart at frame 1081
# mmal: Skipping frame 1082 to restart at frame 1774
# mmal: Skipping frame 1775 to restart at frame 2467
# mmal: Skipping frame 2468 to restart at frame 3161
# mmal: Skipping frame 298070 to restart at frame 298581
# mmal: Skipping frame 298582 to restart at frame 299083
# mmal: Skipping frame 299084 to restart at frame 299593
#ffmpeg -r 15 -start_number 0000 -i frame%4d.bmp -s 128x128 -vcodec libx264 tt.mp4
#ffmpeg  -start_number 0000 -i frame%4d.bmp -b:v -crf 32 -r 5 out2.webm
#ffmpeg -i frame%04d.bmp -b:v 0 -crf 32 -r 5 out2.webm
