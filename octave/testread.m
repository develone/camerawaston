clear
a = imread('thumb0003.bmp');
w = 128;
h = 128;
x = 1;
for i = 1:128
	for j = 1:128
		b(i,j) = a(x);
		x = x + 1;
	endfor	
endfor
sizeof(b)
c = svd(b);

