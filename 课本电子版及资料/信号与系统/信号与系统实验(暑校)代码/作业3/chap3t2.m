clc
clear
x=0:11
y=[1,2,3,4,5,6,6,5,4,3,2,1]
%1
for i=1:63
    w(i)=(i-1)*0.1;
    F(i)=0;
    for k=1:12   
        F(i)=F(i)+y(k)*exp(-1j*w(i)*k);
    end
end
%2
for i=1:12
    g(i)=y(i);
    W(i)=(i-1)/6*pi;
end
G2=fft(g);
%3
subplot(1,2,1);
plot(w,abs(F),W,abs(G2),"k*");xlabel('w');ylabel('F');title('幅度频谱');
subplot(1,2,2);
plot(w,angle(F),W,angle(G2),"k*");xlabel('w');ylabel('Fi');title('相位频谱');

