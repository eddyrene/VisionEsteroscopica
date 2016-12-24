function I=objeto(L,k)

[M,N]=size(L);
I=zeros(M,N);

for i=1:M
    for j=1:N
        if(L(i,j)==k)
            I(i,j)=1;
        else
            I(i,j)=0;
        end
    end
end
