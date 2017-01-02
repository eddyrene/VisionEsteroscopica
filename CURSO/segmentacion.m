clear all
close all

pkg load image;


I=imread('img1.jpg');
imshow(I);
figure

Ig=rgb2gray(I);
imhist(Ig);
figure
imshow(Ig);
mu=graythresh(Ig);

Ib=im2bw(Ig,mu);
figure
imshow(Ib);


%BW = edge(Ig,'canny');
%figure
%imshow(BW)
se = strel('square',3);
BB=imdilate(Ig,se)-Ig;
mu=graythresh(BB);
BW=im2bw(BB,mu);
figure
imshow(BW);
title('Bordes morfológicos');


CBW= ~BW;
figure
imshow(CBW)

%CBWU=uint8(CBW);

IUB=and(Ib,CBW);
figure
imshow(IUB)
title('Imagen de bordes y segmentos');

[IL,N]=bwlabel(IUB);
figure
imshow(IL);
title('Imagen etiquetada');

O=objeto(IL,126);
figure
imshow(O);

input("Nada");
