clear all;
wc=2*pi*200;wr=2*pi*300;rp=1;rs=25;fs=1000;
[N,wn]=buttord(wc,wr,rp,rs,'s');
[B,A]=butter(N,wn,'s');
[num1,den1]=impinvar(B,A,fs); %脉冲相应不变法
[h1,w]=freqz(num1,den1);
w1=2*fs*tan(wc/(2*fs));
w2=2*fs*tan(wr/(2*fs));
[N,wn]=buttord(w1,w2,rp,rs,'s')
[B,A]=butter(N,wn,'s');
[num2,den2]=bilinear(B,A,fs); %双线性变换法
[h2,w]=freqz(num2,den2);
f=w/pi*500;
plot(f,20*log10(abs(h1)),'-.',f,20*log10(abs(h2)),'-');
axis([0,500,-80,10]);grid;
xlabel('Frequency in Hz'); ylabel('Gain in dB');
title('巴特沃思数字低通滤波器');
legend('脉冲相应不变法','双线性变换法',1);