clc
clear
for n=1:400
    w(n)=(n-1)*0.05;
    H(n)=2*1j*w(n)/(1j*w(n)^2+sqrt(2)*1j*w(n)+1);
end
mag=abs(H);
phase=angle(H);
subplot(2,2,1)
plot(w,mag);title("幅频特性");
subplot(2,2,2)
plot(w,phase);title("相频特性");
subplot(2,2,3)
loglog(w,mag);title("幅频特性");
subplot(2,2,4)
semilogx(w,phase);title("相频特性");