N=40;
M=N-1;
f=[0 0.15 0.2 0.4 0.45 0.55 0.6 0.8 0.85 1];
a=[0 0 1 1 0 0 1 1 0 0];
wt=[2 1 2 1 2];
b=remez(M,f,a,wt);
[h w]=freqz(b,1);
subplot(211);
plot(w/pi,20*log10(abs(h)));
axis([0,1,-80,10]);
grid;
xlabel('归一化频率/\pi');
ylabel('幅度/dB');
title('雷米兹交替算法')
subplot(212);
plot(w/pi,angle(h));
grid;
xlabel('归一化频率/\pi');
ylabel('相位');