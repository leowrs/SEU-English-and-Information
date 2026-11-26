clc
clear
syms z;
F(z)=(z^2-z)/((z-1)^3);
f=iztrans(F)
fplot(f,[-20,20]);