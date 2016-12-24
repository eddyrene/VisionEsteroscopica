%punto a analizar de la camara izquierda
x_left_1=zeros(2,2);
x_right_1=zeros(2,2);


x_left_2=zeros(2,2);
x_right_2=zeros(2,2);

I=imread('izq_1.bmp');
figure(1)
imshow(I)
[x_left_1(1,1),x_left_1(2,1)]=getpts(figure(1));
[x_left_2(1,1),x_left_2(2,1)]=getpts(figure(1));
%punto a analizar de la camara derecha

figure(2)
D=imread('der_1.bmp');
imshow(D)
[x_right_1(1,1),x_right_1(2,1)]=getpts(figure(2));
[x_right_2(1,1),x_right_2(2,1)]=getpts(figure(2));

[Xc_1_left,Xc_1_right] = stereo_triangulation(x_left_1,x_right_1,om,T,fc_left,cc_left,kc_left,alpha_c_left,fc_right,cc_right,kc_right,alpha_c_right)
[Xc_1_left2,Xc_1_right2] = stereo_triangulation(x_left_2,x_right_2,om,T,fc_left,cc_left,kc_left,alpha_c_left,fc_right,cc_right,kc_right,alpha_c_right)

sprintf('El vector de traslación (x,y,z)=(%3.3f,%3.3f,%3.3f) respecto a la cámara izquierda \n',Xc_1_left(1,1)/10,Xc_1_left(2,1)/10,Xc_1_left(3,1)/10)
sprintf('El vector de traslación (x,y,z)=(%3.3f,%3.3f,%3.3f) respecto a la cámara derecha',Xc_1_right(1,1)/10,Xc_1_right(2,1)/10,Xc_1_right(3,1)/10)

sprintf('El vector de traslación (x,y,z)=(%3.3f,%3.3f,%3.3f) respecto a la cámara izquierda \n',Xc_1_left2(1,1)/10,Xc_1_left2(2,1)/10,Xc_1_left2(3,1)/10)
sprintf('El vector de traslación (x,y,z)=(%3.3f,%3.3f,%3.3f) respecto a la cámara derecha',Xc_1_right2(1,1)/10,Xc_1_right2(2,1)/10,Xc_1_right2(3,1)/10)

d=sqrt((Xc_1_left2(1,1)-Xc_1_left(1,1))^2+(Xc_1_left2(2,1)-Xc_1_left(2,1))^2+(Xc_1_left2(3,1)-Xc_1_left(3,1))^2)