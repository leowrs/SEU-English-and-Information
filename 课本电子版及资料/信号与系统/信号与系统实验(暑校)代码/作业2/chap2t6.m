clear
clc
for i=1:200
    x1(i)=(i-101)/10;
    y1(i)=my_conv(@f1,@f2,0.1,x1(i));
end

for i=1:200
    x2(i)=(i-101)/10;
    y2(i)=my_conv(@f1,@f2,0.01,x2(i));
end
plot(x1,y1,"r--",x2,y2,"k-")

function y=my_conv(fun1,fun2,step,t)
    y=0;
    for k=-100/step:100/step
        y=y+step*fun1(k*step)*fun2(t-k*step);
    end
end

function y=f1(t)
    y=heaviside(t)*sin(t);
end

function y=f2(t)
    y=heaviside(t+1);
end