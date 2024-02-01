#include<windows.h>
#include"icb_gui.h"
#include"ic_image.h"

ICBYTES OyunAlan�,FULSCREEN;
ICBYTES Fullmap, map,Araba,ArabaMain;
int FRM,keyboard;
int botSpeed = 1;
int mapSpeed = 1;
int ArabaMainXcor =500, ArabaMainYcor = 450;
int bot0Turn = 0;
int bot1Turn = 0;

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
	ICG_MWSize(1200, 900);
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
		if (mapSpeed >= 15 && mapSpeed <= 25)
		{
			botSpeed = 1;
		}
		else if (mapSpeed >= 25)
		{
			botSpeed = 2;
		}
		else if (mapSpeed <= 15)
		{
			botSpeed = 0;
		}
		else if (mapSpeed <= 10)
		{
			botSpeed = -1;
		}



		//Sa�a gidiyorsa
		if (Cars[0].isleft == 0)
			
		{
			car1onRoad = OyunAlan�.U(Cars[0].coorX + 72, Cars[0].coorY);
			if (car1onRoad == -11580063)
			{
				Cars[0].coorX += 5;
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
				Cars[0].coorX -= 5;
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
		if (Cars[0].coorY >= 650) {
			
			bot0Turn = 1;
			for (int i = 0; i < Araba.DataLen(); i++)
			{
				Copy(Araba, 1, 1, Araba.X(), Araba.Y()-i, Araba);
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
				mapSpeed = 1;
				botSpeed = -2;
			}
		}
		
		Sleep(10);
	}
	Sleep(1000);
	ReadImage("ferrari.bmp", Araba);
	botThread0();
	}
	

void botThread0() {
	DWORD dw;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot0, NULL, 0, &dw);
}

void GamePlay(void*)
{
	DWORD dw;
	int MapXcor = 1, MapYcor = 5400;
	int Car1Xcor = 500, Car1Ycor = 200;
	ReadImage("pist.bmp", Fullmap);
	ReadImage("ferrari.bmp", Araba);
	ReadImage("mc.bmp", ArabaMain);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot0, NULL, 0, &dw);
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot1, NULL, 0, &dw);

	int i = 0;
	while (true)
	{
		//Map ve Yar��c�m�z burda �izdiriliyor.
		Copy(Fullmap, MapXcor, MapYcor, 999, 799, map);
		PasteNon0(map, 1, 1, OyunAlan�);
		PasteNon0(ArabaMain, ArabaMainXcor, ArabaMainYcor, OyunAlan�);
		PasteNon0(Araba, Cars[0].coorX, Cars[0].coorY, OyunAlan�);

		//tu� kontrol�
		keyboard = ICG_LastKeyPressed();
		

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
			MapYcor = 5399; i = 0;
		}
	}
}


void WhenKeyPressed(int k)
{

	keyboard = k;
	int keyboard2 = k;

	if (keyboard == 39) {//sa� ok tu�una bas�ld�ysa //IF RIGHT ARROW KEY PRESSED
		ArabaMainXcor += 15;
	}
	if (keyboard == 37) {//sol ok tu�una bas�ld�ysa//IF LEFT ARROW KEY PRESSED
		ArabaMainXcor -= 15;
	}
	if (keyboard2 == 38) {// Yukari yon tusuna basilinca
		
		if (mapSpeed <= 30) {
			mapSpeed += 2;
		}
	}
	if (keyboard2 == 40) {
		
		if (mapSpeed >= 10) {
			mapSpeed -= 2;
		}
	}

}


void ICGUI_main()
{
	CreateImage(OyunAlan�, 1000, 800, ICB_UINT);
	OyunAlan� = 0xffffff;
	FRM = ICG_FrameMedium(25, 25, 1200, 1000);
	DisplayImage(FRM, OyunAlan�);
	ICG_TButton(1050, 50, 100, 55, "Start", GamePlay, NULL);
	ICG_SetOnKeyPressed(WhenKeyPressed);

}