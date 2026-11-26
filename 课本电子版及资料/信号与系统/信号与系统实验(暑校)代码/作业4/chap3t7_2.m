clc;
clear;
p=8,q=8;
for n=0:15
    x1(n+1)=exp(-(n-p)^2/q);
    m(n+1)=n;
end
for i=1:16
    W(i)=(i-1)/16*pi;
end
X1=fft(x1);
p=13;
for n=0:15
    x2(n+1)=exp(-(n-p)^2/q);
end
for i=1:16
    W(i)=(i-1)/16*pi;
end
X2=fft(x2);
p=14;
for n=0:15
    x3(n+1)=exp(-(n-p)^2/q);
end
for i=1:16
    W(i)=(i-1)/16*pi;
end
X3=fft(x3);
subplot(3,3,1);
stem(m,x1);xlabel('n');ylabel('x');title('时域序列');
subplot(3,3,2);
plot(W,abs(X1));xlabel('w');ylabel('F');title('幅度频谱');
subplot(3,3,3);
plot(W,angle(X1));xlabel('w');ylabel('Fi');title('相位频谱');
subplot(3,3,4);
stem(m,x2);xlabel('n');ylabel('x');title('时域序列');
subplot(3,3,5);
plot(W,abs(X2));xlabel('w');ylabel('F');title('幅度频谱');
subplot(3,3,6);
plot(W,angle(X2));xlabel('w');ylabel('Fi');title('相位频谱');
subplot(3,3,7);
stem(m,x3);xlabel('n');ylabel('x');title('时域序列');
subplot(3,3,8);
plot(W,abs(X3));xlabel('w');ylabel('F');title('幅度频谱');
subplot(3,3,9);
plot(W,angle(X3));xlabel('w');ylabel('Fi');title('相位频谱');