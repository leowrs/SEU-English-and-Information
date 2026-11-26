clear all;
N=40;
f=[0 0.15 0.2 0.4 0.45 0.55 0.6 0.8 0.85 1];
a=[0 0 1 1 0 0 1 1 0 0];
wt=[2 1 2 1 2];
b=remez(N-1,f,a,wt);
[h,w]=freqz(b,1);
plot(w/pi,20*log10(abs(h)));
axis([0 1 -70 10]);grid;
xlabel('归一化频率/\pi')
ylabel('幅度/dB')
title('雷米兹交替算法设计专用线性相位滤波器');
