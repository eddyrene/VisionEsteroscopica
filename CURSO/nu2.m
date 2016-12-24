function nupq=nu(I,p,q,M,N)

gamma=((p+q)/2)+1;
m=mpq(I,0,0,M,N);
X=mpq(I,1,0,M,N)/m;
Y=mpq(I,0,1,M,N)/m;
nupq=mupq(I,p,q,M,N,X,Y)/(mupq(I,0,0,M,N,X,Y)^gamma);