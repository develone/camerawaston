clear
close all
I = imread("thumb0000.pgm");
figure; 
imagesc(I);
colormap 'gray'
colorbar;
grid;
im1 = I(20:69,30:79);
figure;
imagesc(im1);
colormap 'gray'
colorbar;
imwrite(im1,"thumb0002.pgm");
