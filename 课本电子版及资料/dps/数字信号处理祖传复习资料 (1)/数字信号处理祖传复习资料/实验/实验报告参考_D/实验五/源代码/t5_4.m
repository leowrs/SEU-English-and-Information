clear all
N=40;
beta1=4;
beta2=6;
beta3=10;
f=[0 0.2 0.2 0.4 0.4 0.6 0.6 0.8 0.8 1];
m=[0,0,1,1,0,0,1,1,0,0];
a=fir2(39,f,m,kaiser(N,beta1));
b=fir2(39,f,m,kaiser(N,beta2));
c=fir2(39,f,m,kaiser(N,beta3));
[h1,w1]=freqz(a);
[h2,w2]=freqz(b);
[h3,w3]=freqz(c);
subplot(3,2,1)
plot(w1/pi,20*log10(abs(h1)));
grid on;
xlabel('归一化频率/\pi');
ylabel('幅度/dB');
title('beta=4 时凯塞窗专用线性相位滤波器幅频特性');
subplot(3,2,2);
plot(w1/pi,angle(h1));
grid on
xlabel('归一化频率/\pi');
ylabel('相位');
title('beta=4时凯塞窗专用线性相位滤波器相频特性');
subplot(3,2,3)
plot(w2/pi,20*log10(abs(h2)));
grid on
xlabel('归一化频率/\pi');
ylabel('幅度/dB');
title('beta=6时凯塞窗专用线性相位滤波器幅频特性');
subplot(3,2,4);
plot(w2/pi,angle(h2));
grid on
xlabel('归一化频率/\pi');
ylabel('相位');
title('beta=6时凯塞窗专用线性相位滤波器相频特性');
subplot(3,2,5)
plot(w3/pi,20*log10(abs(h3)));
grid on
xlabel('归一化频率/\pi');
ylabel('幅度/dB');
title('beta=10时凯塞窗专用线性相位滤波器幅频特性');
subplot(3,2,6);
plot(w3/pi,angle(h3));
grid on
xlabel('归一化频率/\pi');
ylabel('相位');
title('beta=10时凯塞窗专用线性相位滤波器相频特性');
