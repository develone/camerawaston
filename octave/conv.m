%linear convolution program

clc;
clear all;
close all;
disp('linear convolution program');

x=input('enter i/p x(n):');
m=length(x);
h=input('enter i/p h(n):');
n=length(h);

x=[x,zeros(1,n)];
subplot(2,2,1), stem(x);
title('i/p sequencce x(n)is:');
xlabel('---->n');
ylabel('---->x(n)');grid;

h=[h,zeros(1,m)];
subplot(2,2,2), stem(h);
title('i/p sequencce h(n)is:');
xlabel('---->n');
ylabel('---->h(n)');grid;
disp('convolution of x(n) & h(n) is y(n):');
y=zeros(1,m+n-1);

for i=1:m+n-1
            y(i)=0;
            for j=1:m+n-1
                        if(j<i+1)
                                    y(i)=y(i)+x(j)*h(i-j+1);
                        end
            end
end

y
subplot(2,2,[3,4]),stem(y);
title('convolution of x(n) & h(n) is :');
xlabel('---->n');
ylabel('---->y(n)');grid; 
