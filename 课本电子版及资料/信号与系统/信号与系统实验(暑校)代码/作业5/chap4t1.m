clc
clear
syms t s
f=exp(-0.2*t);
F=laplace(f);
H=1/(s+0.1)*(s+0.2);
R=F*H;
r=ilaplace(R);
fplot(r,[-10,100]);