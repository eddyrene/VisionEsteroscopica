#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <sstream>
using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void desplegarContador(Mat view,int,int);
    void captureIMG();
    void help();
private:
    Ui::MainWindow *ui;
    stringstream msgIzq, msgDer,despContador;
    string nombreIzq,nombreDer;
    Mat frameD,frameI,GrisD,GrisI;
    char c;
    int cont = 0;
    int numFotos = 25;
    bool EncontradoD,EncontradoI,blinkOutput;
    int PatternWidth = 7, PatternHeight = 5;
    vector<Point2f> pointBufR,pointBufL;
};

#endif // MAINWINDOW_H
