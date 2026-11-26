%八个点
n=0:7;
y1=zeros(size(n));
y2=zeros(size(n));
y3=zeros(size(n));
z1=zeros(size(n));
z2=zeros(size(n));
z3=zeros(size(n));
N=length(n);
for k=1:N
if n(k)<4&n(k)>=0;
y1(k)=n(k);
z1(k)=4-n(k);
elseif n(k)>=4&n(k)<8 ;
y2(k)=8-n(k);
z2(k)=n(k)-4;
else
y3(k)=0;
z3(k)=0;
end
end
y=y1+y2+y3;
z=z1+z2+z3;
subplot(221);
stem(n,y);
xlabel('n');
ylabel('y');
title('三角波序列时域波形')
subplot(223);
stem(n,z);
xlabel('n');
ylabel('z');
title('反三角波序列时域波形')
w=(0:N-1)/N;
Y=fft(y,N);
Z=fft(z,N);
subplot(222);
plot(w,abs(Y));
subplot(224);
plot(w,abs(Z));


%32个点
figure(2);
n=0:31;
y1=zeros(size(n));
y2=zeros(size(n));
y3=zeros(size(n));
z1=zeros(size(n));
z2=zeros(size(n));
z3=zeros(size(n));
N=length(n);
for k=1:N
if n(k)<4&n(k)>=0;
y1(k)=n(k);
z1(k)=4-n(k);
elseif n(k)>=4&n(k)<8 ;
y2(k)=8-n(k);
z2(k)=n(k)-4;
else
y3(k)=0;
z3(k)=0;
end
end
y=y1+y2+y3;
z=z1+z2+z3;
subplot(221);
stem(n,y);
xlabel('n');
ylabel('y');
title('三角波序列时域波形')
subplot(223);
stem(n,z);
xlabel('n');
ylabel('z');
title('反三角波序列时域波形')
w=(0:N-1)/N;
Y=fft(y,N);
Z=fft(z,N);
subplot(222);
plot(w,abs(Y));
subplot(224);
plot(w,abs(Z));
