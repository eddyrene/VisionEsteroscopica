#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <sstream>
#include <time.h>
using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    help();
    captureIMG();
}

void MainWindow::captureIMG()
{
    clock_t prevTimestamp = 0;
    int delay = 200;
    VideoCapture capDer(0);
    VideoCapture capIzq(1);

    //system("mkdir Capturas");
    while(true)
    {
        capDer>>frameD;
        capIzq>>frameI;

        EncontradoD = false;
        EncontradoI = false;
        blinkOutput = false;

        c=waitKey(10);

        EncontradoD=findChessboardCorners(frameD,Size(PatternWidth,PatternHeight),pointBufR,CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
        EncontradoI=findChessboardCorners(frameI,Size(PatternWidth,PatternHeight),pointBufL,CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);

        if(c==27||cont==numFotos) break;
        else if(EncontradoD && EncontradoI && clock() - prevTimestamp > delay*1e-3*CLOCKS_PER_SEC )
        {
            cont++;

            cvtColor(frameD,GrisD,CV_RGB2GRAY);
            cvtColor(frameI,GrisI,CV_RGB2GRAY);

            msgIzq.str("");
            msgDer.str("");

            msgIzq<<"Capturas/izq_"<<cont<<".jpg";
            msgDer<<"Capturas/der_"<<cont<<".jpg";

            nombreIzq=msgIzq.str();
            nombreDer=msgDer.str();

            imwrite(nombreIzq,GrisI);
            imwrite(nombreDer,GrisD);

            prevTimestamp = clock();

            bitwise_not(frameD,frameD);
            bitwise_not(frameI,frameI);

            blinkOutput = true;

       }
        desplegarContador(frameD,cont,numFotos);

        if(EncontradoD)
            drawChessboardCorners(frameD,Size(PatternWidth, PatternHeight),Mat(pointBufR), true);

        if(EncontradoI)
            drawChessboardCorners(frameI,Size(PatternWidth, PatternHeight),Mat(pointBufL), true);

        imshow("Vista previa Derecha.",frameD);
        imshow("Vista previa Izquierda.",frameI);

        if(blinkOutput)
            waitKey(delay/2);
   }
    cout<<"Termina la captura de imagenes.\n\n";
}

void MainWindow::help()
{
    cout <<
        "Capture a given number of pair images to use in the Stereo Calibration.\n"
        "Colocar el patron en el campo de vista de ambas camaras.\n\n"
        "Usage: \n"
        "./stereo_capture -L LeftIndexCamera -R RightIndexCamera -N AmountOfPicturesToTake.\n\n" << endl;
    cout <<
        "Default Values:\n"
        "./stereo_capture -L 1 -R 2 -N 25\n\n";
}

void MainWindow::desplegarContador(Mat view,int Contador ,int Total)
{
    const Scalar BLUE(255,0,0);

    despContador.str("");
    despContador<<"Foto "<<Contador<<" de "<<Total<<" tomada.";
    string msj = despContador.str();

    int baseLine =0;
    Size textSize = getTextSize(msj,1,1,1,&baseLine);
    Point textOrigin(view.cols-2*textSize.width-10,view.rows-2*baseLine-10);

    putText(view,msj,textOrigin,1,1,BLUE);
}

MainWindow::~MainWindow()
{
    delete ui;
}
