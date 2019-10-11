clear
close all
I = imread('r3thumb0000.bmp');
for i = 1:128
for j= 1:128
imR(i,j) = I(i,j,1);
endfor
endfor
figure; imagesc(imR);colormap 'gray';colorbar;

for i = 1:128
for j= 1:128
imG(i,j) = I(i,j,2);
endfor
endfor
figure; imagesc(imG);colormap 'gray';colorbar;


for i = 1:128
for j= 1:128
imB(i,j) = I(i,j,3);
endfor
endfor
figure; imagesc(imG);colormap 'gray';colorbar;
%for i = 1:128
%W(i) = i/100;
%endfor
%sigma3cr = var(imG,[],1);
sigma3c = var(imG,0,1);
figure
stem(sigma3c)
sigma3r = var(imG,0,2);
figure
stem(sigma3r)

sigma3 = var(imG);
figure
stem(sigma3)
