clear
close all
I = imread("thumb0072.bmp");
for i = 1:256
for j= 1:256
im1(i,j) =I(i,j,1);
endfor
endfor
figure
imagesc(im1)
colormap 'gray'
colorbar
pca1 = svd(im1);
figure
plot(pca1)

for i = 1:256
for j= 1:256
im2(i,j) =I(i,j,2);
endfor
endfor
figure
imagesc(im2)
colormap 'gray'
colorbar
pca2 = svd(im2);
figure
plot(pca2)

for i = 1:256
for j= 1:256
im3(i,j) =I(i,j,3);
endfor
endfor
figure
imagesc(im3)
colormap 'gray'
colorbar
pca3 = svd(im3);
figure
plot(pca3)
c3 = corr(im3);
figure
imagesc(c3);
colormap 'gray';
colorbar
sigma3c = var(im3,0,1);
figure
stem(sigma3c)

sigma3r = var(im3,0,2);
figure
stem(sigma3r)

sigma3cr = var(im3);
figure
stem(sigma3cr)

