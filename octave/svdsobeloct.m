clear

kx= [1 ,0 ,-1; 2,0,-2; 1, 0 ,-1];
ky= [1,2,1; 0,0, 0; -1, -2 ,-1];

I = imread("thumb0058.bmp");
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

H = conv2(double(im1),kx,'same');
V = conv2(double(im1),ky,'same');
E = sqrt(H.*H + V.*V); % or sqrt(H.^2+V.^2)
figure
imshow(E, []) 

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

H = conv2(double(im2),kx,'same');
V = conv2(double(im2),ky,'same');
E = sqrt(H.*H + V.*V); % or sqrt(H.^2+V.^2)
figure
imshow(E, []) 


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

H = conv2(double(im3),kx,'same');
V = conv2(double(im3),ky,'same');
E = sqrt(H.*H + V.*V); % or sqrt(H.^2+V.^2)
figure
imshow(E, []) 