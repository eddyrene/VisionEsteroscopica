function [angle,a,b]=leastsquare_angle(I)

[M,N]=size(I);
x=zeros(1,6000);
y=zeros(1,6000);
puntos=0;

for i=1:M
    for j=1:N
        if I(i,j)==1
            puntos=puntos+1;
            x(puntos)=j;    
            y(puntos)=-i;
        end    
    end
end

c1=sum(y);  %Sy
c2=puntos;  %N
c3=sum(x);  %Sx
c4=x*(y');  %Sxy
c5=x*(x');  %Sxx

b=((c2*c4)-(c1*c3))/((c2*c5)-c3^2);
if isnan(b)
    angle=90;
else
    angle=atan(b);
    angle=(angle*180)/pi;
    if angle<=0
       angle=angle+180;
    end
end

a=(c1-c3*b)/c2;