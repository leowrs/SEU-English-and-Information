T=0.001;
fs=1/T;
fc=300;
fr=200;
Ap=0.8;
As=20;
wc=2*fs*tan(2*pi*fc/(2*fs));
wr=2*fs*tan(2*pi*fr/(2*fs));

[N,wn]=cheb1ord(wc,wr,Ap,As,'s');
[num,den]=cheby1(N,Ap,wn,'high','s');
[b,a]=bilinear(num,den,fs);
sys=tf(b,a,T)
[h,w]=freqz(b,a);
f=w/(2*pi)*fs;
plot(f,20*log10(abs(h)));
axis([0,500,-80,10]);grid;
xlabel('频率/Hz');
ylabel('幅度/dB');
title('切比雪夫数字高通滤波器滤波器幅频响应');


