clear;
%N=16 Deltaf=1/16
N=16;
f=1/16;
x=0:N-1;
y=sin(2*pi*0.125*x)+cos(2*pi*(0.125+f)*x);
xk=fft(y,N);
figure(1);
stem(x,abs(xk));
%N=16 Deltaf=1/64
N=16;
f=1/64;
x=0:N-1;
y=sin(2*pi*0.125*x)+cos(2*pi*(0.125+f)*x);
xk=fft(y,N);
figure(2);
stem(x,abs(xk));
%N=128 Deltaf=1/16
N=128;
f=1/16;
x=0:N-1;
y=sin(2*pi*0.125*x)+cos(2*pi*(0.125+f)*x);
xk=fft(y,N);
figure(3);
stem(x,abs(xk));
%N=128 Deltaf=1/64
N=128;
f=1/64;
x=0:N-1;
y=sin(2*pi*0.125*x)+cos(2*pi*(0.125+f)*x);
xk=fft(y,N);
figure(4);
stem(x,abs(xk));
