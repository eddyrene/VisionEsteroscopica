#include "CapturaStereo.h"

///Mat's for frame's storage.
Mat frameR, frameL;
///Streams for string's concatenation (Images names).
stringstream LeftStrm, RightStrm;
string LeftName, RightName;
///Stream for progress display.
stringstream CounterDisp;

char c;
int cont = 0; //Actual picture counter
int LeftIndex=1, RightIndex=2;
int TotalPhotos=25; //Total amount of pictures to take.
bool EncontradoI, EncontradoD;
int PatternWidth = 8, PatternHeight = 6;
vector<Point2f> pointBufL;
vector<Point2f> pointBufR;
clock_t prevTimestamp = 0;
int delay = 2000;
bool blinkOutput = false;

static void help()
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

void main(int argc, char** argv)
{
	help();
	#pragma region Recuperación parámetros.
	for(int i=1; i< argc; i++)
	{
		if(string(argv[i]) == "-L" || string(argv[i]) == "-l" )
		{
			if( sscanf(argv[++i], "%i", &LeftIndex) != 1 || LeftIndex < 0)
			{
				cout << "Invalid Left camera index value.\n" << endl;
				help();
				exit(0);
			}
		}
		else if( string(argv[i]) == "-R" || string(argv[i]) == "-r")
		{
			if( sscanf(argv[++i], "%i", &RightIndex) != 1 || RightIndex < 0)
			{
				cout << "Invalid Right camera index value.\n" << endl;
				help();
				exit(0);
			}
		}
		else if( string(argv[i]) == "-N" || string(argv[i]) == "-n")
		{
			if(sscanf(argv[++i], "%i", &TotalPhotos) != 1 || TotalPhotos < 8)
			{
				cout << "Invalid quantity of pictures to take.\n" << endl;
				help();
				exit(0);
			}
		}
	}
	#pragma endregion

	//Start cameras.
	VideoCapture capL(LeftIndex);
	VideoCapture capR(RightIndex);

	system("mkdir Captures");
	
	/*if(!capDer.open(1)){
		cout<<"No se pudo abrir la camara derecha. Asegurese que esta conectada";
		cin.get();		exit(0);	}
	if(!capIzq.open(2)){
		cout<<"No se pudo abrir la camara izquierda. Asegurese que esta conectada";
		cin.get();		exit(0);	}

	waitKey(6000);*/
	while(true)
	{
		//Take a frame from each camera.
		capR>>frameR;
		capL>>frameL;

		EncontradoI = false;
		EncontradoD = false;
		blinkOutput = false;

		c = waitKey(10);

		EncontradoI = findChessboardCorners(frameL, Size(PatternWidth, PatternHeight), pointBufL, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
		EncontradoD = findChessboardCorners(frameR, Size(PatternWidth, PatternHeight), pointBufR, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
		
		if(c == 27 || cont == TotalPhotos) 
			break; //Exit if Enter is pressed or all pictures captured.
		else if(EncontradoI && EncontradoD && clock() - prevTimestamp > delay*1e-3*CLOCKS_PER_SEC)
		{
			cont++;
			
			LeftStrm.str("");
			RightStrm.str("");

			LeftStrm << "Captures/izq_" << cont << ".jpg";
			RightStrm << "Captures/der_" << cont << ".jpg";
			
			LeftName = LeftStrm.str();
			RightName = RightStrm.str();

			imwrite( LeftName, frameL); // Save frameL with the LeftName name.
			imwrite( RightName, frameR);

			prevTimestamp = clock();

			bitwise_not(frameL, frameL);
			bitwise_not(frameR, frameR);
				
			blinkOutput = true;
		}		
		CounterDisplay(frameL, cont, TotalPhotos); //Display capture progress.
		
		if(EncontradoI)
			drawChessboardCorners(frameL, Size(PatternWidth, PatternHeight), Mat(pointBufL), true);
		if(EncontradoD)
			drawChessboardCorners(frameR, Size(PatternWidth, PatternHeight), Mat(pointBufR), true);
		
		// Show the images.
		imshow("Right", frameR);
		imshow("Left", frameL);
		
		if(blinkOutput)
			waitKey(delay / 2);
	}
}

void CounterDisplay(Mat view, int Counter, int Total)
{
	/*Display a progress message in view.*/
	const Scalar BLUE(255,0,0); //Inverse order. (B G R).
	
	CounterDisp.str("");
	CounterDisp << "Photo " << Counter << " of " << Total;
	string msj = CounterDisp.str();
	
	int baseLine = 0;
	Size textSize = getTextSize(msj, 1, 1.5, 1.5, &baseLine);        
	Point textOrigin(view.cols - 2*textSize.width - 10, view.rows - 2*baseLine - 10);
	
	putText(view, msj, textOrigin, 1, 1, BLUE);
}