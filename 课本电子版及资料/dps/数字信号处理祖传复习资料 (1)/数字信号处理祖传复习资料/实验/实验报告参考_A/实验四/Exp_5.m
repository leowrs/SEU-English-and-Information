clear all;
rp=3;rs=18;fs=10000;
wr1=2*fs*tan(2*pi*1000/(2*fs));
wr2=2*fs*tan(2*pi*2000/(2*fs));
w1=2*fs*tan(2*pi*500/(2*fs));
w2=2*fs*tan(2*pi*3000/(2*fs));
[N,wn]=cheb1ord([w1 w2],[wr1 wr2],rp,rs,'s')
[B,A]=cheby1(N,rp,wn,'stop','s');
[num,den]=bilinear(B,A,fs);
[h,w]=freqz(num,den);
f=w/pi*5000;
plot(f,20*log10(abs(h)));
axis([100,3500,-100,10]);grid;
xlabel('Frequency in Hz'); ylabel('Gain in dB');
title('ÇÐ±ÈÑ©·òÊý×Ö´ø×èÂË²¨Æ÷');