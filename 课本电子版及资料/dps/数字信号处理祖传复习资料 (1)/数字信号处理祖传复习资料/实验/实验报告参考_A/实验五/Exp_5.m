clear all;
N=40;
Hk=[zeros(1,3) 0.5 ones(1,5) 0.5 zeros(1,1) 0.5 ones(1,5) 0.5 ...
zeros(1,5) -0.5 -ones(1,5) -0.5 zeros(1,1) -ones(1,5) -0.5 zeros(1,3)];
k=0:N-1;
hn=real(ifft(Hk.*exp(-j*pi*(N-1)*k/N)));
[H w]=freqz(hn, 1);
plot(w/pi, 20*log10(abs(H)));
axis([0 1 -80 10]);grid;
xlabel('归一化频率/\pi')
ylabel('幅度/dB')
title('频率采样法设计专用线性相位滤波器');
