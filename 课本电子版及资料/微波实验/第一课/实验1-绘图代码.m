


%%题目1
figure;
subplot(2,1,1);
plot(z_norm,abs(),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('反射系数的幅度在传输线上的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
ylim([-1.5 1.5]);
grid on;

subplot(2,1,2);
plot(z_norm,angle(),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('反射系数的相位在传输线上的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
ylim([-pi pi]);
yticks([-pi -0.5*pi 0 0.5*pi pi]);
yticklabels({'-\pi','-0.5\pi','0','0.5\pi','\pi'});
grid on;

%%题目2 
figure;
subplot(2,1,1);
plot(z_norm,abs(),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('传输线上电压波幅度的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
ylim([0 2]);
grid on;

subplot(2,1,2);
plot(z_norm,abs(),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('传输线上电流波幅度的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
grid on;

%%题目3
figure;
subplot(2,1,1);
plot(z_norm,real(),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('传输线上输入阻抗实部的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
grid on;
ylim([-200 200]);

subplot(2,1,2);
plot(z_norm,imag(),'LineWidth',1);
set(gca,'Xdir','reverse'); 
title('传输线上输入阻抗虚部的分布','FontWeight','bold');
xlabel('距离终端负载的位置（归一化）');
grid on;
ylim([-200 200]);
