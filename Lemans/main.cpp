#include<windows.h>
#include"icb_gui.h"
#include"ic_image.h"

ICBYTES OyunAlan�,FULSCREEN;
ICBYTES Fullmap, map,Araba,Araba2;
int FRM;
int isleft = 0;
void ICGUI_Create()
{
	ICG_MWSize(1200, 900);
}

int bot1(int x, int y) {
	//botlar
	int car1onRoad = 0;
	int returnXcor = x;
	if (isleft == 0)
		//Sa�a gidiyorsa
	{
		car1onRoad = OyunAlan�.U(returnXcor + 72, y);
		if (car1onRoad == -11580063)
		{
			returnXcor += 5;
		}
		else
		{
			isleft = 1;
		}
	}

	if (isleft == 1)
		//Sola gidiyorsa
	{
		car1onRoad = OyunAlan�.U(returnXcor - 6, y);
		if (car1onRoad == -11580063)
		{
			returnXcor -= 5;
		}
		else
		{
			isleft = 0;
		}
	}

	if (car1onRoad == -9781712) {
		//bot yoldan ��km�� �ekilde spawn olmu�sa

		returnXcor = 500;
	}

	return returnXcor;
}

void GamePlay(void*)
{
	int MapXcor = 1, MapYcor = 5400,ArabaMainXcor=500,ArabaMainYcor = 600,keyboard;
	int Car1Xcor = 500, Car1Ycor = 200;
	ReadImage("pist.bmp", Fullmap);
	ReadImage("Araba.bmp", Araba);
	ReadImage("f1.bmp", Araba2);

	//silinecek
	int arr[1002];
	
	int i = 0;
	while (true)
	{
		//Map ve Yar��c�m�z burda �izdiriliyor.
		Copy(Fullmap, MapXcor, MapYcor, 1000, 1000, map);
		PasteNon0(map, 1, 1, OyunAlan�);
		PasteNon0(Araba2, ArabaMainXcor, ArabaMainYcor, OyunAlan�);
		PasteNon0(Araba, Car1Xcor, Car1Ycor, OyunAlan�);

		//deneme renk
		for (int i = 0; i < OyunAlan�.X(); i++)
		{
			arr[i] = OyunAlan�.U(1+i, Car1Ycor+100);
		}
		
		//bot hareketi
		Car1Xcor = bot1(Car1Xcor, Car1Ycor);

		//tu� kontrol�
		keyboard = ICG_LastKeyPressed();
		if (keyboard == 39)//sa� ok tu�una bas�ld�ysa //IF RIGHT ARROW KEY PRESSED
			ArabaMainXcor+=5;
		else if (keyboard == 37)//sol ok tu�una bas�ld�ysa//IF LEFT ARROW KEY PRESSED
			ArabaMainXcor-=5;


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
		
		MapYcor -= 10;
		i++;
		if (i >= 540  ) {
			MapYcor = 5400; i = 0;
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
}