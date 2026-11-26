clear
clc
x1=0:3
y1=[1,1,1,1]
x2=0:4
y2=[1,0.5,0.25,0.125,0.0625]

for i=0:7
    x(i+1)=i;
    f(i+1)=my_conv(y1,y2,i);
end
f2=conv(y1,y2);
plot(x,f,"r*",x,f2,"k-")

function y=my_conv(x1,x2,t)
    y=0;
    for k=1:t+1
        if(k<=4&&(t+2-k)<=5)
        y=y+x1(k)*x2(t+2-k);
        end
    end
end

