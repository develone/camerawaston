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
[U,S,V] = svd(imG);

for i = 1:128
for j= 1:128
imB(i,j) = I(i,j,3);
endfor
endfor
figure; imagesc(imG);colormap 'gray';colorbar;
title 'GR suband';
%for i = 1:128
%W(i) = i/100;
%endfor
%sigma3cr = var(imG,[],1);
sigma3c = var(imG,0,1);
figure
stem(sigma3c);
title 'sigma Col';
grid;
sigma3r = var(imG,0,2);
figure
stem(sigma3r)
title 'sigma Row';
grid
sigma3 = var(imG);
figure
stem(sigma3)
figure
covG = cov(imG);
imagesc(covG);colormap 'gray';colorbar;
title  'COV';
figure
corG = corr(imG);
imagesc(corG);colormap 'gray';colorbar;
title 'COR';
[UR,SR,VR] = svd(covG);
##
#
#https://lists.gnu.org/archive/html/help-octave/2004-05/msg00066.html
#
##
sv = diag(SR);
n_sv = 100*sv/sum(sv);
figure
plot(n_sv);
title 'nor sv the Diag of Covarance'
