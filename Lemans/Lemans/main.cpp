#include<windows.h>
#include"icb_gui.h"
#include"ic_image.h"

ICBYTES OyunAlaný,FULSCREEN;
ICBYTES Fullmap, map,Araba,Araba2;
int FRM;

struct forThreads {
	//int threadNumber;
	int coorX=500;
	int coorY=200;
	int isleft = 0;
};

struct forThreads Cars[4];


void ICGUI_Create()
{
	ICG_MWSize(1200, 900);
}

void bot1() {
	//botlar
	int car1onRoad = 0;
	Cars[0].coorX = 500;
	Cars[0].coorY = 200;

	while (true) {


		if (Cars[0].isleft == 0)
			//Saða gidiyorsa
		{
			car1onRoad = OyunAlaný.U(Cars[0].coorX + 72, Cars[0].coorY);
			if (car1onRoad == -11580063)
			{
				Cars[0].coorX += 1;
			}
			else
			{
				Cars[0].isleft = 1;
			}
		}

		if (Cars[0].isleft == 1)
			//Sola gidiyorsa
		{
			car1onRoad = OyunAlaný.U(Cars[0].coorX - 6, Cars[0].coorY);
			if (car1onRoad == -11580063)
			{
				Cars[0].coorX -= 1;
			}
			else
			{
				Cars[0].isleft = 0;
			}
		}

		if (car1onRoad == -9781712) {
			//bot yoldan çýkmýþ þekilde spawn olmuþsa

			Cars[0].coorX = 500;
		}
		
		PasteNon0(Araba, Cars[0].coorX, Cars[0].coorY, OyunAlaný);
		
		Sleep(10);
	}

	}

	

void GamePlay(void*)
{
	DWORD dw;
	int MapXcor = 1, MapYcor = 5400,ArabaMainXcor=500,ArabaMainYcor = 600,keyboard;
	int Car1Xcor = 500, Car1Ycor = 200;
	ReadImage("pist.bmp", Fullmap);
	ReadImage("Araba.bmp", Araba);
	ReadImage("f1.bmp", Araba2);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot1, NULL, 0, &dw);


	int i = 0;
	while (true)
	{
		//Map ve Yarýþcýmýz burda çizdiriliyor.
		Copy(Fullmap, MapXcor, MapYcor, 1000, 1000, map);
		PasteNon0(map, 1, 1, OyunAlaný);
		PasteNon0(Araba2, ArabaMainXcor, ArabaMainYcor, OyunAlaný);
		

		//tuþ kontrolü
		keyboard = ICG_LastKeyPressed();
		if (keyboard == 39)//sað ok tuþuna basýldýysa //IF RIGHT ARROW KEY PRESSED
			ArabaMainXcor+=5;
		else if (keyboard == 37)//sol ok tuþuna basýldýysa//IF LEFT ARROW KEY PRESSED
			ArabaMainXcor-=5;


#ifdef _DEBUG
		Sleep(20);//DEBUG MODU YAVAÞ OLDUÐU ÝÇÝN DAHA AZ BEKLETÝYORUZ
#else
		Sleep(60); //Release mode is fast so we delay more
#endif
		int nextPixel = OyunAlaný.U(ArabaMainXcor,300);
		if (nextPixel == 0x6abe30) {
			PasteNon0(Araba, 100, 100, OyunAlaný);
		}
		DisplayImage(FRM, OyunAlaný);
		
		MapYcor -= 10;
		i++;
		if (i >= 540  ) {
			MapYcor = 5400; i = 0;
		}
	}
}

void ICGUI_main()
{
	CreateImage(OyunAlaný, 1000, 800, ICB_UINT);
	OyunAlaný = 0xffffff;
	FRM = ICG_FrameMedium(25, 25, 1200, 1000);
	DisplayImage(FRM, OyunAlaný);
	ICG_TButton(1050, 50, 100, 55, "Start", GamePlay, NULL);
}