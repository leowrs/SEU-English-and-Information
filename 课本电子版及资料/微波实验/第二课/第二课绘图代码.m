figure;
subplot(2,1,1);
plot(freq, ,'LineWidth',1);             %反射系数模值频率特性
title('输入端反射系数模值曲线');
xlabel('频率（Hz）');
ylabel('输入端反射系数模值');
axis([fmin fmax 0 0.5]);
grid minor;
grid on;

subplot(2,1,2);
plot(freq, ,'LineWidth',1);             %驻波比频率特性
title('输入端电压驻波比曲线');
xlabel('频率（Hz）');
ylabel('VSWR');
axis([fmin fmax 0 4]);
grid minor;
grid on;

figure;
subplot(2,1,1)
plot(freq, ,'LineWidth',1)                %输入阻抗实部频率特性
title('输入阻抗实部曲线');
xlabel('频率（Hz）');
ylabel('输入阻抗实部值');
grid on;
subplot(2,1,2)                      %输入阻抗虚部频率特性
plot(freq, ,'LineWidth',1) 
title('输入阻抗虚部曲线');
xlabel('频率（Hz）');
ylabel('输入阻抗虚部值');
grid on;
