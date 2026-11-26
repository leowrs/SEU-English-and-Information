clc
clear
N=3;
M=N+1;
A=zeros(M,M);
A(1:2,1:2)=[1,1;4,1];
for n=3:M
    for m=1:M-n+1
        A(n,m)=(A(n-2,m+1)*A(n-1,1)-A(n-2,1)*A(n-1,m+1))/A(n-1,1);
    end
end
A