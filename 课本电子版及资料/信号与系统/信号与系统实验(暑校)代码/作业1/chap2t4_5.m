clear
hold on
for i=-10:10
    x(i+11)=i/10
    k(i+11)=e(i/10)
end
plot(x,k,"r--")

n=5

[j,m]=sigshift(k,x,n)
plot(m,j,"m-")

function r=e(t)
    if t>=0
        r=1
    else
        r=0
    end
end

function [y,n]=sigshift(x,m,n0)
    for i=1:size(m')
        n(i)=m(i)-n0;
        y(i)=x(i);
    end
end