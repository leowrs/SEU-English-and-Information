% Original Author: GitHub @leowrs (https://github.com/leowrs)
	t=-3:0.2:3;
	f = (t+3).*(t>=-3&t<=0)+(-t+3).*(t>0&t<=3);
	
	n=length(f);
	Y1=fft(f,n);
	Y2=fftshift(Y1);
	w=(-3:0.2:3)*(5/n);
	
	figure(3);
	subplot(3,1,1);plot([t1 t2],f);%时域波形
	title('时域波形');xlabel('时间');ylabel('幅值');
	grid on;
	subplot(3,1,2);plot(w1,abs(Y1));%正频率的幅度谱
	title('幅度谱');xlabel('频率');ylabel('幅值');
	grid on;
	subplot(3,1,3);plot(w1,angle(Y1));%相位谱
	title('相位谱');xlabel('频率');ylabel('相位');
	grid on;
