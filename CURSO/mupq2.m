%Esta función calcula los momentos centrales
%I es la imagen
%p y q el orden de los momentos centrales
%M y N las dimensiones de la imagen
%X y Y las medias en x y y 

function mu=mupq(I,p,q,M,N,X,Y)


mu=0;
for i=1:N
    for j=1:M
        mu=mu+(i-X)^p*(j-Y)^q*I(j,i);
    end
end