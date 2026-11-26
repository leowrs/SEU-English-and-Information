clear
clc
Fn=1;
step=0.1;
%1
k=input("请输入取样频率/Hz");
Tm=input("请输入取样区间上下限绝对值");
s1=input("请输入插值区间下限");
s2=input("请输入插值区间上限");
Fs=Fn*k;
T=1/Fs;
Nc=Tm/T;
for n=-Nc:1:Nc
    nT(n+Nc+1)=T*n;
    f(n+Nc+1)=((sin(pi*nT(n+Nc+1))+eps)/(pi*nT(n+Nc+1)+eps))^2;
end
t=s1:step:s2;
for N=1:length(t)
    for n=1:length(nT)
        ff(n)=f(n)*(sin(pi*Fs*(t(N)-nT(n))+eps)/(pi*Fs*(t(N)-nT(n))+eps))^2;
    end
fa(N)=sum(ff);
end
y=((sin(pi*t)+eps)./(pi*t+eps)).^2;
plot(t,fa,t,y);grid;
hold on
plot(nT,f,'*');
axis([s1,s2,-0.5,1.5]);
error(1)=max(abs(fa-y))
hold off