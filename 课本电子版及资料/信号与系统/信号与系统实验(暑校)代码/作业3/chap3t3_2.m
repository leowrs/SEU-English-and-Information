clc
clear

for i=1:200
    w(i)=(i-1)/10;
    F=@(t)f(t).*exp(-1j*w(i).*t);
    G1(i)=integral(F,-inf,inf);
end
hold on;

for i=1:10000
    g(i)=f((i-5001)/1000);
    W(i)=(i-1)*0.2*pi;
end
G2=fft(g)/1000;

subplot(1,2,1);
plot(w,abs(G1),W(1:32),abs(G2(1:32)),"k*");xlabel('w');ylabel('F');title('幅度频谱');
subplot(1,2,2);
plot(w,angle(G1),W(1:32),angle(G2(1:32)),"k*");xlabel('w');ylabel('Fi');title('相位频谱');
function y=f(t)
    y=cos(t*pi/2).*(heaviside(t+1)-heaviside(t-1));
end