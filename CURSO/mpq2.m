%Esta función calcula los momentos 
%I es la imagen
%p y q el orden de los momentos centrales
%M y N las dimensiones de la imagen


function m=mpq(I,p,q,M,N)

%Función analizada en ejes x y y
% El indexado de una matriz es I(y,x)


m=0;
for i=1:N
    for j=1:M
        m=m+(i^p*j^q*I(j,i));
    end
end

