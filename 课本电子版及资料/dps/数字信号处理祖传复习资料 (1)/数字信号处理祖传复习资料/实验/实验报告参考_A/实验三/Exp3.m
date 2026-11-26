clear;
%%%%%%%  8个点
%三角波
x=0:7;
y1=zeros(size(x));
y2=zeros(size(x));
y3=zeros(size(x));
N=length(x);
for k=1:N
if x(k)<4&x(k)>=0;
y1(k)=x(k);
elseif x(k)>=4&x(k)<8 ;
y2(k)=8-x(k);
else
y3(k)=0;
end
end
y=y1+y2+y3;
figure(1);
subplot(1,2,1);
stem(x,y);
xk=fft(y,N);
subplot(1,2,2);
stem(x,abs(xk));
%反三角波
x=0:7;
y1=zeros(size(x));
y2=zeros(size(x));
y3=zeros(size(x));
N=length(x);
for k=1:N
if x(k)<4&x(k)>=0;
y1(k)=4-x(k);
elseif x(k)>=4&x(k)<8 ;
y2(k)=x(k)-4;
else
y3(k)=0;
end
end
y=y1+y2+y3;
figure(2);
subplot(1,2,1);
stem(x,y);
xk=fft(y,N);
subplot(1,2,2);
stem(x,abs(xk));

%%%%%%%% 32个点
%三角波
x=0:31;
y1=zeros(size(x));
y2=zeros(size(x));
y3=zeros(size(x));
N=length(x);
for k=1:N
if x(k)<4&x(k)>=0;
y1(k)=x(k);
elseif x(k)>=4&x(k)<8 ;
y2(k)=8-x(k);
else
y3(k)=0;
end
end
y=y1+y2+y3;
figure(3);
subplot(1,2,1);
stem(x,y);
xk=fft(y,N);
subplot(1,2,2);
stem(x,abs(xk));
%反三角波
x=0:31;
y1=zeros(size(x));
y2=zeros(size(x));
y3=zeros(size(x));
N=length(x);
for k=1:N
if x(k)<4&x(k)>=0;
y1(k)=4-x(k);
elseif x(k)>=4&x(k)<8 ;
y2(k)=x(k)-4;
else
y3(k)=0;
end
end
y=y1+y2+y3;
figure(4);
subplot(1,2,1);
stem(x,y);
xk=fft(y,N);
subplot(1,2,2);
stem(x,abs(xk));

