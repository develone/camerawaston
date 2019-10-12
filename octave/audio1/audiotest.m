close all; clear
##infocr = audioinfo('Cracked.wav')
[y,s] = audioread('Cracked.wav');
yy = y(125000:150000);
figure; plot(yy);grid
#figure; plot(y);grid
yyy = fft(yy);
mag = abs(yyy);
figure; plot(mag);
##infocr = audioinfo('Not.wav')
[y,s] = audioread('Not.wav');
yy = y(125000:150000);
figure; plot(yy);grid
#figure; plot(y);grid
yyy = fft(yy);
mag = abs(yyy);
figure; plot(mag);
