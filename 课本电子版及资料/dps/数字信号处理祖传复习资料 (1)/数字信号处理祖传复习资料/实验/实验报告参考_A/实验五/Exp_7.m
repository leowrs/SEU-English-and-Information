clear all;
fedge=[500 800];
mval=[0 1];
dev=[0.01 0.109];
fs=5000;
[N,fpts,mag,wt]=remezord(fedge,mval,dev,fs);
b=remez(N,fpts,mag,wt);
[h,w]=freqz(b,1);
plot(w*2500/pi,20*log10(abs(h)));
axis([0 2500 -80 10]);grid;
xlabel('频率/Hz')
ylabel('幅度/dB')
title('雷米兹交替算法设计线性相位高通FIR 数字滤波器');
