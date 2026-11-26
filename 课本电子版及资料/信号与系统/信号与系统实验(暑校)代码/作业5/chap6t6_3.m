clc
clear
for n=1:1000
    x(n)=(n-1)*0.005;
    w(n)=exp(x(n)*pi*(1j));
    H(n)=(1+2*w(n)^(-1)+w(n)^(-2))/(1+0.61*w(n)^(-2));
end
mag=abs(H);
phase=angle(H);
subplot(3,2,1)
plot(x,mag);title("幅频特性");
subplot(3,2,2)
plot(x,phase);title("相频特性");
subplot(3,2,3)
loglog(x,mag);title("幅频特性");
subplot(3,2,4)
semilogx(x,phase);title("相频特性");
