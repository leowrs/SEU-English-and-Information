function y=Gauss(n,p,q)
[M,N]=size(n);
for i=1:M
    for j=1:N
        if n(i,j)<0||n(i,j)>15
            y(i,j)=0;
        else
            y(i,j)=exp(-(n(i,j)-p)^2/q);
        end
    end
end