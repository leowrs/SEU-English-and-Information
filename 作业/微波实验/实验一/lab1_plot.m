% Original Author: GitHub @leowrs (https://github.com/leowrs)
clear;
Eg=2;
Zg=50;
Z0=50;
lamuta=0.3;
bata=2*pi/lamuta;
z=0:0.01:1;     %归一化
Zl=[50,50*1i,-50*1i,50+50*1i,50-50*1i];
for k=1:5
T=(Zl(1,k)-Z0)/(Zl(1,k)+Z0)*exp(-2*1i*bata*z*lamuta);
%%题目1
figure;
subplot(2,1,1);
plot(z,abs(T),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('反射系数的幅度在传输线上的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
ylim([-1.5 1.5]);
grid on;

subplot(2,1,2);
plot(z,angle(T),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('反射系数的相位在传输线上的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
ylim([-pi pi]);
yticks([-pi -0.5*pi 0 0.5*pi pi]);
yticklabels({'-\pi','-0.5\pi','0','0.5\pi','\pi'});
grid on;

%%题目2 
Zinl=Z0*((Zl(1,k)+1i*Z0*tan(bata*lamuta))/(Z0+1i*Zl(1,k)*tan(bata*lamuta)));  %首先计算始端处阻抗
Vin=Eg*Zinl/(Zg+Zinl);                                              %接着计算出输入端电压
Tin=(Zl(1,k)-Z0)/(Zl(1,k)+Z0)*exp(-2*1i*bata*lamuta);                         %计算出输入端的反射系数               
A1=Vin/(exp(1j*bata*lamuta)*(1+Tin));                               %然后计算出A1
T=(Zl(1,k)-Z0)/(Zl(1,k)+Z0)*exp(-2*1i*bata*z*lamuta);   
U=A1*exp(1j*bata*z*lamuta).*(1+T);                                  %计算出任意点处的电压
I=A1/Z0*exp(1j*bata*z*lamuta).*(1-T); 
figure;
subplot(2,1,1);
plot(z,abs(U),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('传输线上电压波幅度的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
ylim([0 2]);
grid on;

subplot(2,1,2);
plot(z,abs(I),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('传输线上电流波幅度的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
grid on;

%%题目3
Zinl=Z0*((Zl(1,k)+1i*Z0*tan(bata*z*lamuta))./(Z0+1i*Zl(1,k)*tan(bata*z*lamuta)));
R_Zinl=real(Zinl);
figure;
subplot(2,1,1);
plot(z,real(Zinl),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('传输线上输入阻抗实部的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
grid on;
ylim([-200 200]);

subplot(2,1,2);
Zinl=Z0*((Zl(1,k)+1i*Z0*tan(bata*z*lamuta))./(Z0+1i*Zl(1,k)*tan(bata*z*lamuta)));
I_Zinl=imag(Zinl); 
if((max(I_Zinl))<1e-6||(max(I_Zinl))>1e10)
    I_Zinl = I_Zinl*0;
end
plot(z,I_Zinl,'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('传输线上输入阻抗虚部的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
grid on;
ylim([-200 200]);
end