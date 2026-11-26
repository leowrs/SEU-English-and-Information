clear
clc
y1=[3,11,7,0,-1,4,2];
y2=[2,3,0,-5,2,1];
f1=my_conv(y1,y2);
f2=conv(y1,y2);
[M,N]=size(f1);
for i=1:N
    x(i)=i-1;
end
subplot(1,2,1)
stem(x,f1);
subplot(1,2,2)
stem(x,f2);
f1
f2

function c=my_conv(x1,x2)
    [M1,N1]=size(x1);
    [M2,N2]=size(x2);
    for i=0:N1+N2-2
        c(i+1)=0;
        for k=1:i+1
            if(k<=N1&&(i+2-k)<=N2)
                c(i+1)=c(i+1)+x1(k)*x2(i+2-k);
            end
        end
    end

end

