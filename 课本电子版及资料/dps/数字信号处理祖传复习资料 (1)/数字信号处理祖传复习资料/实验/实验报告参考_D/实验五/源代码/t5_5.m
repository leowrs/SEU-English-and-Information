clear all
N=40;
Hk=[zeros(1,3),0.5,ones(1,5),0.5,zeros(1,1),0.5,ones(1,5),0.5,zeros(1,5),-0.5,-ones(1,5),-0.5,0,-0.5,-ones(1,5),-0.5,zeros(1,2)];
k=0:N-1;
hn=real(ifft(Hk.*exp(-j*pi*(N-1)*k/N)));
[H,w]=freqz(hn, 1);
subplot(2,1,1);
plot(w/pi, 20*log10(abs(H)));
axis([0 1 -120 10]);
grid;
xlabel('归一化频率/\pi')
ylabel('幅度/dB')
title('频率采样法频谱图');
subplot(2,1,2);
plot(w/pi,angle(H));
grid;
xlabel('归一化频率/\pi')
ylabel('相位')
title('频率采样法相频图');