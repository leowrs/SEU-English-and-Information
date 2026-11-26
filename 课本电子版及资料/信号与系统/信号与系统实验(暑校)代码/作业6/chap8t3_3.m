clear
clc
%1
for n=1:100
    t(n)=(n-1)/10;
        F=@(tao)(2*tao.*exp(-tao)+exp(-tao)).*exp(-2*t(n)+2*tao);
        f(n)=integral(F,0,t(n));
end
subplot(1,2,1)
plot(t,f);xlabel("t(s)");ylabel("响应");title("零状态响应");
%2
b=[1,3];
a=[1,2,1];
t=0:0.1:9.9;
e=[exp(-2*t)];
sys=tf(b,a);
subplot(1,2,2)
lsim(sys,e,t);