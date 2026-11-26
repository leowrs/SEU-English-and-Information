N=40;
k=0:N-1;
Wm=2*pi*k./N;
Hk=[zeros(1,4) 0.5 ones(1,3) 0.5 zeros(1,3) 0.5 ones(1,3) 0.5 zeros(1,3) zeros(1,3) -0.5 -ones(1,3) -0.5 zeros(1,3) -0.5 -ones(1,3) -0.5 zeros(1,4)];
sitak=-Wm*(N-1)/2;
b=real(ifft(Hk.*exp(j*sitak)));
[h w]=freqz(b,1);
subplot(211);
plot(w/pi,20*log10(abs(h)));
axis([0 1 -80 10]);
grid;
xlabel('归一化频率/\pi');
ylabel('幅度/dB');
title('频率采样法')
subplot(212);
plot(w/pi,angle(h));
grid;
xlabel('归一化频率/\pi');
ylabel('相位');