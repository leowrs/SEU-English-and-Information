clear
for i=-50:50
    x(i+51)=i/10
    k(i+51)=f(i/10-2)*e(i/10-2)
end
plot(x,k)

function r=e(t)
    if t>=0
        r=1
    else
        r=0
    end
end

function r=f(t)
    r=(t+1)*(e(t+1)-e(t-1))
end