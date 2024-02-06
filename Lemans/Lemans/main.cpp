#include<windows.h>
#include"icb_gui.h"
#include"ic_image.h"
#include <time.h>

HANDLE hTimerQueue = NULL;
ICBYTES OyunAlan�,InfoAlan�;
ICBYTES Fullmap, map,Araba,Araba1,ArabaMain,SText,S�ralamaText,tText,infoCar,tempInfo;
int FRM,FRM2,keyboard;
int botSpeed = 1;
int mapSpeed = 15,speedText,S�raText,timeText,highScore;
int ArabaMainXcor =500, ArabaMainYcor = 450;
int bot0Turn = 0;
int bot1Turn = 0;
int fullScreenX=1200,FullscreenY=800;
int startGame = 0;
int carCrash = 0;
int score = 0;
int timer = 120;
int carPassed = 0;

void botThread0();
void botThread1();

struct forThreads {
	//int threadNumber;
	int coorX;
	int coorY;
	int isleft = 0;
	int isforward = 0;

};
struct forThreads Cars[4];

void scoreFunction(void* p)
{
	SetText(S�raText, S�ralamaText);
	ICG_printf(S�raText, "%d", *(int*)p);
}
void setTime(void* p) {
	SetText(timeText, tText);
	ICG_printf(timeText, "%d", *(int*)p);
}
void timeFunction() {
	timer -= 1;
	setTime((void*)&timer);
}


void ICGUI_Create()
{
	ICG_MWSize(fullScreenX, FullscreenY);
	//ICG_MWTitle("LeMans");
	ICG_MWColor(50, 150, 80);
	ICG_MWPosition(150, 1);
}

void bot0() {
	
	//botlar
	int car1onRoad = 0;
	if (bot0Turn == 0) {
		Cars[0].coorX = 500;
		Cars[0].coorY = 100;
	}
	else if (botSpeed > 0) {
		Cars[0].coorX = 500;
		Cars[0].coorY = 5;
	}
	else if (botSpeed <= 0) {
		Cars[0].coorX = 500;
		Cars[0].coorY = 620;
	}
	
	ReadImage("ferrari.bmp", Araba);
	while (true) {

		//Bot �ne mi gidiyor arkaya m� ?
		if (mapSpeed > 15 && mapSpeed <= 25)
		{
			botSpeed = 1;	
		}
		else if (mapSpeed == 15) {
			botSpeed = 0;
		}
		else if (mapSpeed >= 25)
		{
			botSpeed = 4;			
		}
		else if (mapSpeed <= 8)
		{
			botSpeed = -4;	
		}
		else if (mapSpeed < 15)
		{	
			botSpeed = -3;
		}

		if (ArabaMainYcor <= Cars[0].coorY && ArabaMainYcor + 3 >= Cars[0].coorY)
		{
			if (botSpeed < 0)
			{
				//S�ralamaText = "Arkadan geldi ve bot ge�ti";
			}
			else if (botSpeed > 0)
			{
				//S�ralamaText = "Ge�tin";
				score += 10;
				carPassed += 1;
				timer += 2;
				if (carPassed >= 3) {
					score += 30;
					carPassed = carPassed % 3;
					PasteNon0(infoCar, 120, 450, InfoAlan�);
				}
				else if (carPassed == 2) {
					PasteNon0(infoCar, 80, 450, InfoAlan�);
				}
				else if (carPassed == 1) {
					PasteNon0(tempInfo, 1, 1, InfoAlan�);
					PasteNon0(infoCar, 40, 450, InfoAlan�);
				}
				DisplayImage(FRM2, InfoAlan�);
				scoreFunction((void*)&score);

			}
		}


		//Sa�a gidiyorsa
		if (Cars[0].isleft == 0)
			
		{
			car1onRoad = OyunAlan�.U(Cars[0].coorX + 72, Cars[0].coorY);
			if (car1onRoad == -11580063)
			{
				Cars[0].coorX += 2;
			}
			else
			{
				Cars[0].isleft = 1;
			}
		}
		//Sola gidiyorsa
		if (Cars[0].isleft == 1)
			
		{
			car1onRoad = OyunAlan�.U(Cars[0].coorX - 6, Cars[0].coorY);
			if (car1onRoad == -11580063)
			{
				Cars[0].coorX -= 2;
			}
			else
			{
				Cars[0].isleft = 0;
			}
		}
		//bot yoldan ��km�� �ekilde spawn olmu�sa
		if (car1onRoad == -9781712) {

			Cars[0].coorX = 500;
		}
		//bot y�n� 
		if (Cars[0].coorY < 650)
		{
			Cars[0].coorY += botSpeed;
		}

		//Botun alttan ��k�� i�lemleris
		if (Cars[0].coorY >= 640) {
			
			bot0Turn = 1;
			for (int i = 0; i < Araba.DataLen(); i++)
			{
				Copy(Araba, 1, 1, Araba.X(), Araba.Y() -i, Araba);
			}
			
			break;
			
		}
		//Botun �stten ��k�� i�lemleri
		if (Cars[0].coorY <= 5) {
		
			for (int i = 0; i < Araba.DataLen(); i++)
			{
				Copy(Araba, 1, 1, Araba.X(), Araba.Y() - i, Araba);
			}
			
			bot0Turn = 1;
			break;
		}
		
		//�arp��ma durumlar�
		if (Cars[0].coorY + 70 >= ArabaMainYcor && Cars[0].coorY <= ArabaMainYcor) {
			if (Cars[0].coorX + 60 >= ArabaMainXcor && Cars[0].coorX <= ArabaMainXcor) {
				mapSpeed = 14;
				carCrash = 1;
			}
		}
		
		Sleep(20);
	}
	Sleep(1000);
	
	botThread0();
	}


	//bot2
	void bot1() {

		//botlar
		int car1onRoad = 0;
		if (bot1Turn == 0) {
			Cars[1].coorX = 700;
			Cars[1].coorY = 300;
		}
		else if (botSpeed > 0) {
			Cars[1].coorX = 500;
			Cars[1].coorY = 5;
		}
		else if (botSpeed <= 0) {
			Cars[1].coorX = 500;
			Cars[1].coorY = 620;
		}

		ReadImage("aston.bmp", Araba1);
		while (true) {

			//Bot �ne mi gidiyor arkaya m� ?
			if (mapSpeed > 15 && mapSpeed <= 25)
			{
				botSpeed = 1;
			}
			else if (mapSpeed == 15) {
				botSpeed = 0;
			}
			else if (mapSpeed >= 25)
			{
				botSpeed = 4;
			}
			else if (mapSpeed <= 8)
			{
				botSpeed = -4;
			}
			else if (mapSpeed < 15)
			{
				botSpeed = -3;
			}

			if (ArabaMainYcor <= Cars[1].coorY && ArabaMainYcor +3 >= Cars[1].coorY)
			{
				if (botSpeed < 0)
				{
					//S�ralamaText = "Arkadan geldi ve bot ge�ti";
				}
				else if (botSpeed > 0)
				{

					score += 10;
					carPassed += 1;
					timer += 2;
					if (carPassed >= 3) {
						score += 30;
						carPassed = carPassed % 3;
						PasteNon0(infoCar, 120, 450, InfoAlan�);

					}
					else if (carPassed == 2) {
						PasteNon0(infoCar, 80, 450, InfoAlan�);
					}
					else if (carPassed == 1) {
						PasteNon0(tempInfo, 1, 1, InfoAlan�);
						PasteNon0(infoCar, 40, 450, InfoAlan�);
					}
					DisplayImage(FRM2, InfoAlan�);

					scoreFunction((void*)&score);
				}
			}

			//Sa�a gidiyorsa
			if (Cars[1].isleft == 0)

			{
				car1onRoad = OyunAlan�.U(Cars[1].coorX + 72, Cars[1].coorY);
				if (car1onRoad == -11580063)
				{
					Cars[1].coorX += 2;
				}
				else
				{
					Cars[1].isleft = 1;
				}
			}
			//Sola gidiyorsa
			if (Cars[1].isleft == 1)

			{
				car1onRoad = OyunAlan�.U(Cars[1].coorX - 6, Cars[1].coorY);
				if (car1onRoad == -11580063)
				{
					Cars[1].coorX -= 2;
				}
				else
				{
					Cars[1].isleft = 0;
				}
			}
			//bot yoldan ��km�� �ekilde spawn olmu�sa
			if (car1onRoad == -9781712) {

				Cars[1].coorX = 500;
			}
			//bot y�n� 
			if (Cars[1].coorY < 650)
			{
				Cars[1].coorY += botSpeed;
			}

			//Botun alttan ��k�� i�lemleris
			if (Cars[1].coorY >= 640) {

				bot1Turn = 1;
				for (int i = 0; i < Araba1.DataLen(); i++)
				{
					Copy(Araba1, 1, 1, Araba1.X(), Araba1.Y() - i, Araba1);
				}

				break;

			}
			//Botun �stten ��k�� i�lemleri
			if (Cars[1].coorY <= 5) {

				for (int i = 0; i < Araba1.DataLen(); i++)
				{
					Copy(Araba1, 1, 1, Araba1.X(), Araba1.Y() - i, Araba1);
				}

				bot1Turn = 1;
				break;
			}

			//�arp��ma durumlar�
			if (Cars[1].coorY + 70 >= ArabaMainYcor && Cars[1].coorY <= ArabaMainYcor) {
				if (Cars[1].coorX + 60 >= ArabaMainXcor && Cars[1].coorX <= ArabaMainXcor) {
					mapSpeed = 14;
					carCrash = 1;
				}
			}

			Sleep(10);
		}
		Sleep(1000);
		botThread1();
	}

void InfoScreens() {
	PasteNon0(tempInfo, 1, 1, InfoAlan�);
	while (startGame == 1 )
	{
		
		//Speed Text 
		if (mapSpeed >= 25 && mapSpeed <= 29)
		{
			SText = "300";
		}
		else if (mapSpeed > 29)
		{
			SText = "350";
		}
		else if (mapSpeed >= 20 && mapSpeed < 25)
		{
			SText = "250";
		}
		else if (mapSpeed >= 15 && mapSpeed < 20)
		{
			SText = "200";
		}
		else if (mapSpeed >= 10 && mapSpeed < 15)
		{	
			SText = "150";
		}
		else if (mapSpeed <= 10)
		{
			SText = "100";
		}
		Sleep(100);
	}
	
}
	
void botThread0() {
	DWORD dw;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot0, NULL, 0, &dw);
}
void botThread1() {
	DWORD dw;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot1, NULL, 0, &dw);
}



void GamePlay(void*)
{
	HANDLE hTimer = NULL;
	DWORD dw;
	hTimerQueue = CreateTimerQueue();
	if (NULL == hTimerQueue)
	{
		return;
	}
	CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)timeFunction, NULL, 0, 1000, 0);
	
	startGame = 1;
	int MapXcor = 1, MapYcor = 12000;
	int Car1Xcor = 500, Car1Ycor = 200;
	int carMainRenk;
	ReadImage("pistsonbibak.bmp", Fullmap);
	ReadImage("ferrari.bmp", Araba);
	ReadImage("aston.bmp", Araba1);
	ReadImage("mc.bmp", ArabaMain);
	

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot0, NULL, 0, &dw);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot1, NULL, 0, &dw);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InfoScreens, NULL, 0, &dw);
	PlaySound("Opening.wav", NULL, SND_ASYNC | SND_LOOP);
	
	while (true)
	{
		//Map ve Yar��c�m�z burda �izdiriliyor.
		Copy(Fullmap, MapXcor, MapYcor, 1001, 750, map);
		PasteNon0(map, 1, 1, OyunAlan�);
		PasteNon0(ArabaMain, ArabaMainXcor, ArabaMainYcor, OyunAlan�);
		PasteNon0(Araba, Cars[0].coorX, Cars[0].coorY, OyunAlan�);
		PasteNon0(Araba1, Cars[1].coorX, Cars[1].coorY, OyunAlan�);
		SetText(speedText, SText);

		//tu� kontrol�
		keyboard = ICG_LastKeyPressed();
		
		//pit kontorlleri
		if (MapYcor > 200 && MapYcor < 250) {
			if (ArabaMainXcor > 70 && ArabaMainXcor < 380) {
				carCrash = 0;
			}
		}

		//Main yar��c�m�z�n yol kontrol� 
		carMainRenk = OyunAlan�.U(ArabaMainXcor+30 , ArabaMainYcor );

		if (carMainRenk != -11580063 &&  carMainRenk != -14069100 && carMainRenk != -5376)
		{
			if (carMainRenk == -9211520)
			{
				if (mapSpeed >= 20)
				{
					mapSpeed = 19;
				}
				
			}
			else if (carMainRenk == -1 || carMainRenk == -2677467)
			{
				if (mapSpeed >= 30)
				{
					mapSpeed = 25;
				}

			}
			else {
				
				mapSpeed = 5;

			}

		}

#ifdef _DEBUG
		Sleep(20);//DEBUG MODU YAVA� OLDU�U ���N DAHA AZ BEKLET�YORUZ
#else
		Sleep(60); //Release mode is fast so we delay more
#endif

		int nextPixel = OyunAlan�.U(ArabaMainXcor,300);
		if (nextPixel == 0x6abe30) {
			//PasteNon0(Araba, 100, 100, OyunAlan�);
		}
		DisplayImage(FRM, OyunAlan�);
		
		MapYcor -= mapSpeed;
		if (MapYcor <= 1  ) {
			MapYcor = 12050;
		}
	}
}


void WhenKeyPressed(int k)
{

	keyboard = k;
	int keyboard2 = k;

	if (keyboard == 39) 
	{
		//sa� ok tu�una bas�ld�ysa //IF RIGHT ARROW KEY PRESSED

		ArabaMainXcor += 15;
	}
	if (keyboard == 37) 
	{
		//sol ok tu�una bas�ld�ysa//IF LEFT ARROW KEY PRESSED

		ArabaMainXcor -= 15;
	}
	if (keyboard2 == 38 && carCrash != 1) 
	{
		// Yukari yon tusuna basilinca
		if (mapSpeed <= 30) 
		{
			mapSpeed += 2;
		}
	}
	if (keyboard2 == 40 && carCrash != 1)
	{
		// Assagi yon tusuna basilinca
		if (mapSpeed >= 10) 
		{
			mapSpeed -= 2;
		}
	}
	
	
	//space tu�u renk kontrol�  11580063 asfalt 9211520 k�rm�z� 2677467 beyaz 9211520 pitasfalt 
	/*if (keyboard == 32 )
	{
		carMainRenk = 0;
		carMainRenk = OyunAlan�.U(ArabaMainXcor - 2, ArabaMainYcor -2);

	}*/

}

void StartScreen() {

	while (true) {

	}
}

void ICGUI_main()
{

	ReadImage("passed.bmp", infoCar);
	CreateImage(OyunAlan�, 1000, 749, ICB_UINT);
	CreateImage(InfoAlan�, 200, 749, ICB_UINT);
	OyunAlan� = 0xffffff;
	FRM = ICG_FrameThin(0, 0, 1200, 749);
	FRM2 = ICG_FrameThin(1001, 0, 200, 749);
	DisplayImage(FRM, OyunAlan�);
	ReadImage("scoreboardy.bmp", tempInfo);
	//StartScreen();
	DisplayImage(FRM2, InfoAlan�);

	highScore = ICG_SLEdit(1068, 128, 68, 26, "");
	timeText = ICG_SLEdit(1068, 285, 68, 26, "");
	speedText = ICG_SLEdit(1068, 205, 68, 26, "");
	S�raText = ICG_SLEditSunken(1068, 367, 68, 26, "");
	ICG_TButton(1050, 20, 100, 55, "Start", GamePlay, NULL);
	ICG_SetOnKeyPressed(WhenKeyPressed);

}