clc;
clear;
p=8,q=2;
for n=0:15
    x(n+1)=exp(-((n-p)^2)/q);
end
for i=1:16
    W(i)=(i-1)/16*pi;
end
X1=fft(x);
q=4;
for n=0:15
    x(n+1)=exp(-(n-p)^2/q);
end
for i=1:16
    W(i)=(i-1)/16*pi;
end
X2=fft(x);
q=8;
for n=0:15
    x(n+1)=exp(-(n-p)^2/q);
end
for i=1:16
    W(i)=(i-1)/16*pi;
end
X3=fft(x);
plot(W,abs(X1),W,abs(X2),W,abs(X3));xlabel('w');ylabel('F');title('幅度频谱');