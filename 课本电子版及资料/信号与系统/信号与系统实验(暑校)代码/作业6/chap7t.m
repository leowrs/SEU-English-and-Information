clc
clear
b=[3,-9,6];
a=[1,3,2];
[z,p,k]=tf2zp(b,a);
zplane(z,p);