N=40;
beta1=4;
beta2=6;
beta3=10;
f=[0 0.2 0.2 0.4 0.4 0.6 0.6 0.8 0.8 1];
a=[0 0 1 1 0 0 1 1 0 0];
b1=fir2(N-1,f,a,kaiser(N,beta1));
[h1,w1]=freqz(b1,1);
b2=fir2(N-1,f,a,kaiser(N,beta2));
[h2,w2]=freqz(b2,1);
b3=fir2(N-1,f,a,kaiser(N,beta3));
[h3,w3]=freqz(b3,1);

k=0:N-1;
Wm=2*pi*k./N;
Hk=[zeros(1,4) 0.5 ones(1,3) 0.5 zeros(1,3) 0.5 ones(1,3) 0.5 zeros(1,3) zeros(1,3) -0.5 -ones(1,3) -0.5 zeros(1,3) -0.5 -ones(1,3) -0.5 zeros(1,4)];
sitak=-Wm*(N-1)/2;
b4=real(ifft(Hk.*exp(j*sitak)));
[h4 w4]=freqz(b,1);




figure(1);
plot(w1/pi,20*log10(abs(h1)),w2/pi,20*log10(abs(h2)),w3/pi,20*log10(abs(h3)),w4/pi,20*log10(abs(h4)));
legend('凯塞窗beta=4','凯塞窗beta=6','凯塞窗beta=10','频率采样法')
grid;
axis([0 1 -130 10])
xlabel('归一化频率/\pi');
ylabel('幅度/dB');
title('两种不同方法设计（4）中滤波器幅值比较')
figure(2);
plot(w1/pi,angle(h1),w2/pi,angle(h2),w3/pi,angle(h3),w4/pi,angle(h4));
grid;
xlabel('归一化频率/\pi');
ylabel('相位');
title('两种不同方法设计（4）中滤波器相位比较')
legend('凯塞窗beta=4','凯塞窗beta=6','凯塞窗beta=10','频率采样法')