#include<windows.h>
#include"icb_gui.h"
#include"ic_image.h"

ICBYTES OyunAlan�,InfoAlan�;
ICBYTES Fullmap, map,Araba,ArabaMain,SText,S�ralamaText;
int FRM,FRM2,keyboard;
int botSpeed = 1;
int mapSpeed = 15,speedText,S�raText;
int ArabaMainXcor =500, ArabaMainYcor = 450;
int bot0Turn = 0;
int bot1Turn = 0;
int fullScreenX=1200,FullscreenY=800;
int startGame = 0;
int carCrash = 0;

void botThread0();
void botThread1();

struct forThreads {
	//int threadNumber;
	int coorX=500;
	int coorY=100;
	int isleft = 0;
	int isforward = 0;
};
struct forThreads Cars[4];

void ICGUI_Create()
{
	ICG_MWSize(fullScreenX, FullscreenY);
	ICG_MWTitle("Le Mans");
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

		if (ArabaMainYcor == Cars[0].coorY)
		{
			if (botSpeed < 0)
			{
				S�ralamaText = "Arkadan geldi ve bot ge�ti";
			}
			else if (botSpeed > 0)
			{
				S�ralamaText = "Bizim araba Botu ge�ti";
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

		//Botun alttan ��k�� i�lemleri
		if (Cars[0].coorY >= 640) {
			
			bot0Turn = 1;
			for (int i = 0; i < Araba.DataLen(); i++)
			{
				Copy(Araba, 1, 1, Araba.X(), Araba.Y() -i, Araba);
				PasteNon0(Araba, Cars[0].coorX, Cars[0].coorY, OyunAlan�);
				Sleep(10);
			}
			
			break;
			
		}
		//Botun �stten ��k�� i�lemleri
		if (Cars[0].coorY <= 5) {
			
			for (int i = 0; i < Araba.DataLen(); i++)
			{
				Copy(Araba, 1, 1, Araba.X(), Araba.Y() - i, Araba);
				PasteNon0(Araba, Cars[0].coorX, Cars[0].coorY, OyunAlan�);
				Sleep(10);
			}
			bot0Turn = 1;
			break;
		}
		
		//�arp��ma durumlar�
		if (Cars[0].coorY + 104 >= ArabaMainYcor && Cars[0].coorY <= ArabaMainYcor) {
			if (Cars[0].coorX + 70 >= ArabaMainXcor && Cars[0].coorX <= ArabaMainXcor) {
				mapSpeed = 8;
				botSpeed = -2;
				carCrash = 1;
			}
		}
		
		Sleep(10);
	}
	Sleep(1000);
	ReadImage("ferrari.bmp", Araba);
	botThread0();
	}

void InfoScreens() {

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

void GamePlay(void*)
{
	DWORD dw;
	startGame = 1;
	int MapXcor = 1, MapYcor = 12000;
	int Car1Xcor = 500, Car1Ycor = 200;
	ReadImage("Anapist.bmp", Fullmap);
	ReadImage("ferrari.bmp", Araba);
	ReadImage("mc.bmp", ArabaMain);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot0, NULL, 0, &dw);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InfoScreens, NULL, 0, &dw);
	int i = 0;
	while (true)
	{
		//Map ve Yar��c�m�z burda �izdiriliyor.
		Copy(Fullmap, MapXcor, MapYcor, 1001, 750, map);
		PasteNon0(map, 1, 1, OyunAlan�);
			PasteNon0(ArabaMain, ArabaMainXcor, ArabaMainYcor, OyunAlan�);
		PasteNon0(Araba, Cars[0].coorX, Cars[0].coorY, OyunAlan�);
		SetText(speedText, SText);
		SetText(S�raText, S�ralamaText);

		//tu� kontrol�
		keyboard = ICG_LastKeyPressed();
		
		if (MapYcor > 200 && MapYcor < 250) {
			if (ArabaMainXcor > 120 && ArabaMainXcor < 380) {
				carCrash = 0;
			}
		}
#ifdef _DEBUG
		Sleep(20);//DEBUG MODU YAVA� OLDU�U ���N DAHA AZ BEKLET�YORUZ
#else
		Sleep(60); //Release mode is fast so we delay more
#endif
		int nextPixel = OyunAlan�.U(ArabaMainXcor,300);
		if (nextPixel == 0x6abe30) {
			PasteNon0(Araba, 100, 100, OyunAlan�);
		}
		DisplayImage(FRM, OyunAlan�);
		
		MapYcor -= mapSpeed;
		if (MapYcor <= 10  ) {
			MapYcor = 12000; i = 0;
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
			mapSpeed += 1;
		}
	}
	if (keyboard2 == 40 && carCrash != 1)
	{
		// Assagi yon tusuna basilinca
		if (mapSpeed >= 10) 
		{
			mapSpeed -= 1;
		}
	}

}


void ICGUI_main()
{

	CreateImage(OyunAlan�, 1000, 749, ICB_UINT);
	CreateImage(InfoAlan�, 200, 749, ICB_UINT);
	OyunAlan� = 0xffffff;
	InfoAlan� = 0x22ff22;
	FRM = ICG_FrameThin(0, 0, 1200, 749);
	FRM2 = ICG_FrameThin(1001, 0, 200, 749);
	DisplayImage(FRM, OyunAlan�);
	DisplayImage(FRM2, InfoAlan�);
	speedText = ICG_SLEdit(1050, 150, 100, 55, "Speed:");
	S�raText = ICG_SLEdit(1050, 350, 200, 55, "Speed:");
	ICG_TButton(1050, 50, 100, 55, "Start", GamePlay, NULL);
	ICG_SetOnKeyPressed(WhenKeyPressed);

}