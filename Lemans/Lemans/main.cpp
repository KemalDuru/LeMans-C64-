#include<windows.h>
#include"icb_gui.h"
#include"ic_image.h"
#include <time.h>

HANDLE hTimerQueue = NULL;
ICBYTES OyunAlan�, InfoAlan�;
ICBYTES Fullmap, map, Araba, Araba1, ArabaMain, SText, S�ralamaText, tText, hText, infoCar, tempInfo, crashedCar, HomeScreen, HomeScreen2, HomeScreen3, carScreen1, carScreen2, carScreen3, carScreen4, info, gameOver, bayrak, fullbayrak;
int FRM, FRM2, keyboard;
int botSpeed = 1;
int mapSpeed = 15, speedText, S�raText, timeText, highScore, hscore = 0, fotoS�ras� = 0, iscarchoose = 0, carchoose = 0, isinfo = 0, infoS�ras� = 0, gameover = 0;
int ArabaMainXcor = 500, ArabaMainYcor = 450;
int bot0Turn = 0;
int bot1Turn = 0;
int fullScreenX = 1000, FullscreenY = 799;
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
struct forThreads Cars[2];

void scoreFunction(void* p)
{
	SetText(S�raText, S�ralamaText);
	ICG_printf(S�raText, "%d", *(int*)p);

}
void highscoreFunction(void* a) {

	SetText(highScore, hText);
	ICG_printf(highScore, "%d", *(int*)a);
}

void setTime(void* s) {

	SetText(timeText, tText);
	ICG_printf(timeText, "%d", *(int*)s);
}
void timeFunction() {
	while (startGame == 1 && timer > 0)
	{
		timer -= 1;
		Sleep(1000);
	}


}

void ICGUI_Create()
{
	ICG_MWSize(fullScreenX, FullscreenY);
	ICG_MWTitle("LeMans");
	ICG_MWColor(50, 150, 80);
	ICG_MWPosition(150, 1);
}

void RestartGame() {

	botSpeed = 1;
	mapSpeed = 15;
	fotoS�ras� = 0;
	iscarchoose = 0;
	isinfo = 0;
	infoS�ras� = 0;
	gameover = 0;
	ArabaMainXcor = 500;
	ArabaMainYcor = 450;
	bot0Turn = 0;
	bot1Turn = 0;
	fullScreenX = 1000, FullscreenY = 799;
	startGame = 0;
	carCrash = 0;
	score = 0;
	timer = 120;
	carPassed = 0;
}

void bot0() {

	//botlar
	int car1onRoad = 0;
	if (bot0Turn == 0) {
		Cars[0].coorX = 500;
		Cars[0].coorY = 50;
	}
	else if (botSpeed > 0) {
		Cars[0].coorX = 500;
		Cars[0].coorY = 5;
	}
	else if (botSpeed <= 0) {
		Cars[0].coorX = 500;
		Cars[0].coorY = 620;
	}

	if (carchoose == 0)

	{
		ReadImage("ferrari.bmp", Araba);

	}
	else if (carchoose == 1)

	{
		ReadImage("mc.bmp", Araba);
	}
	else if (carchoose == 2)

	{
		ReadImage("ferrari.bmp", Araba);

	}
	else if (carchoose == 3)

	{
		ReadImage("ferrari.bmp", Araba);

	}

	while (startGame == 1) {

		//Bot �ne mi gidiyor arkaya m� ?
		if (mapSpeed > 15 && mapSpeed <= 25)
		{
			botSpeed = 2;
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
			botSpeed = -2;
		}

		if (botSpeed == 2 || botSpeed == -2)
		{
			if (ArabaMainYcor <= Cars[0].coorY && ArabaMainYcor + 2 > Cars[0].coorY)
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


				}

			}
		}
		else if (botSpeed == 4 || botSpeed == -4)
		{
			if (ArabaMainYcor <= Cars[0].coorY && ArabaMainYcor + 4 > Cars[0].coorY)
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


				}

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
				Copy(Araba, 1, 1, Araba.X(), Araba.Y() - i, Araba);
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
		if (Cars[0].coorY + 100 >= ArabaMainYcor && Cars[0].coorY <= ArabaMainYcor) {
			if (Cars[0].coorX + 70 >= ArabaMainXcor && Cars[0].coorX <= ArabaMainXcor) {
				if (carCrash == 0) {
					PlaySound("carCrash.wav", NULL, SND_SYNC);
					PlaySound("brokenEngine.wav", NULL, SND_ASYNC | SND_LOOP);
				}
				mapSpeed = 14;
				carCrash = 1;
			}
		}

		Sleep(10);
	}

	Sleep(1000);
	if (startGame == 1)
	{

		botThread0();
	}

}


//bot2
void bot1() {

	//botlar
	int car1onRoad = 0;
	if (bot1Turn == 0) {
		Cars[1].coorX = 700;
		Cars[1].coorY = 200;
	}
	else if (botSpeed > 0) {
		Cars[1].coorX = 500;
		Cars[1].coorY = 5;
	}
	else if (botSpeed <= 0) {
		Cars[1].coorX = 500;
		Cars[1].coorY = 620;
	}

	if (carchoose == 0)

	{
		ReadImage("aston.bmp", Araba1);

	}
	else if (carchoose == 1)

	{
		ReadImage("aston.bmp", Araba1);

	}
	else if (carchoose == 2)

	{
		ReadImage("merso.bmp", Araba1);

	}
	else if (carchoose == 3)

	{
		ReadImage("aston.bmp", Araba1);
	}

	while (startGame == 1) {

		//Bot �ne mi gidiyor arkaya m� ?
		if (mapSpeed > 15 && mapSpeed <= 25)
		{
			botSpeed = 2;
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
			botSpeed = -2;
		}

		if (botSpeed == 2 || botSpeed == -2)
		{
			if (ArabaMainYcor <= Cars[1].coorY && ArabaMainYcor + 2 > Cars[1].coorY)
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


				}

			}
		}
		else if (botSpeed == 4 || botSpeed == -4)
		{
			if (ArabaMainYcor <= Cars[1].coorY && ArabaMainYcor + 4 > Cars[1].coorY)
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


				}

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
		if (Cars[1].coorY + 100 >= ArabaMainYcor && Cars[1].coorY <= ArabaMainYcor) {
			if (Cars[1].coorX + 70 >= ArabaMainXcor && Cars[1].coorX <= ArabaMainXcor) {
				if (carCrash == 0) {
					PlaySound("carCrash.wav", NULL, SND_SYNC);
					PlaySound("brokenEngine.wav", NULL, SND_ASYNC | SND_LOOP);
				}
				mapSpeed = 14;
				carCrash = 1;
			}
		}

		Sleep(10);
	}
	Sleep(1000);
	if (startGame == 1)
	{
		botThread1();
	}

}

void InfoScreens() {
	PasteNon0(tempInfo, 1, 1, InfoAlan�);
	while (startGame == 1)
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
		scoreFunction((void*)&score);
		highscoreFunction((void*)&hscore);
		setTime((void*)&timer);
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

void GameOvers() {
	int adana = 3131;
	startGame = 0;
	gameover = 1;
	fullScreenX = 1000;
	ICG_MWSize(fullScreenX, FullscreenY);
	PlaySound("gameOver.wav", NULL, SND_ASYNC | SND_LOOP);
	PasteNon0(gameOver, 1, 1, OyunAlan�);

	DisplayImage(FRM, OyunAlan�);
	
}


void GamePlay()
{
	DWORD dw;


	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)timeFunction, NULL, 0, &dw);
	int MapXcor = 1, MapYcor = 12000;
	int Car1Xcor = 500, Car1Ycor = 200;
	int carMainRenk;
	ReadImage("pistsonbibak.bmp", Fullmap);
	
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot0, NULL, 0, &dw);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot1, NULL, 0, &dw);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InfoScreens, NULL, 0, &dw);
	PlaySound("Speed.wav", NULL, SND_ASYNC | SND_LOOP);

	while (timer > 0 && startGame == 1)
	{
		//Map ve Yar��c�m�z burda �izdiriliyor.
		Copy(Fullmap, MapXcor, MapYcor, 1001, 750, map);
		PasteNon0(map, 1, 1, OyunAlan�);

		if (carCrash == 0) {
			PasteNon0(ArabaMain, ArabaMainXcor, ArabaMainYcor, OyunAlan�);
		}
		else if (carCrash == 1) {
			PasteNon0(crashedCar, ArabaMainXcor, ArabaMainYcor, OyunAlan�);
		}
		PasteNon0(Araba, Cars[0].coorX, Cars[0].coorY, OyunAlan�);
		PasteNon0(Araba1, Cars[1].coorX, Cars[1].coorY, OyunAlan�);
		SetText(speedText, SText);

		//tu� kontrol�
		keyboard = ICG_LastKeyPressed();

		//pit kontrolleri
		if (MapYcor > 200 && MapYcor < 250) {
			if (ArabaMainXcor > 70 && ArabaMainXcor < 380) {
				carCrash = 0;
				PlaySound("Speed.wav", NULL, SND_ASYNC | SND_LOOP);
			}
		}

		//Main yar��c�m�z�n yol kontrol� 
		carMainRenk = OyunAlan�.U(ArabaMainXcor + 30, ArabaMainYcor);

		if (carMainRenk != -11580063 && carMainRenk != -14069100 && carMainRenk != -5376)
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
			else if (carCrash !=1)
			 {

				mapSpeed = 5;

			}
			

		}

#ifdef _DEBUG
		Sleep(20);//DEBUG MODU YAVA� OLDU�U ���N DAHA AZ BEKLET�YORUZ
#else
		Sleep(60); //Release mode is fast so we delay more
#endif

		int nextPixel = OyunAlan�.U(ArabaMainXcor, 300);
		if (nextPixel == 0x6abe30) {
			//PasteNon0(Araba, 100, 100, OyunAlan�);
		}
		DisplayImage(FRM, OyunAlan�);

		MapYcor -= mapSpeed;
		if (MapYcor <= 1) {
			MapYcor = 12050;
		}


		if (hscore <= score) {

			hscore = score;

		}
		

		}
	PlaySound("gameOver.wav", NULL, SND_SYNC);
	GameOvers();
	}

void StartScreen() {

	if (fotoS�ras� == 0)
	{
		PasteNon0(HomeScreen, 1, 1, OyunAlan�);

	}
	else if (fotoS�ras� == 1)
	{
		PasteNon0(HomeScreen2, 1, 1, OyunAlan�);
	}
	else if (fotoS�ras� == 2)
	{
		PasteNon0(HomeScreen3, 1, 1, OyunAlan�);

	}


	DisplayImage(FRM, OyunAlan�);


}
void CarChoose() {

	if (carchoose == 0)
	{
		PasteNon0(carScreen1, 1, 1, OyunAlan�);

	}
	else if (carchoose == 1)
	{
		PasteNon0(carScreen2, 1, 1, OyunAlan�);
	}
	else if (carchoose == 2)
	{
		PasteNon0(carScreen3, 1, 1, OyunAlan�);

	}
	else if (carchoose == 3)
	{
		PasteNon0(carScreen4, 1, 1, OyunAlan�);

	}


	DisplayImage(FRM, OyunAlan�);


}
void Infolar() {

	if (infoS�ras� == 0)
	{
		ReadImage("info1.bmp", info);
		PasteNon0(info, 1, 1, OyunAlan�);

	}
	else if (infoS�ras� == 1)
	{
		ReadImage("info2.bmp", info);
		PasteNon0(info, 1, 1, OyunAlan�);

	}
	else if (infoS�ras� == 2)
	{
		ReadImage("info3.bmp", info);
		PasteNon0(info, 1, 1, OyunAlan�);

	}



	DisplayImage(FRM, OyunAlan�);
}

void WhenKeyPressed(int k)
{

	keyboard = k;
	int keyboard2 = k;

	if (keyboard == 39)
	{
		//sa� ok tu�una bas�ld�ysa 
		if (startGame == 0 && iscarchoose == 0 && isinfo == 1)
		{
			if (infoS�ras� < 2)
			{
				infoS�ras�++;
				Infolar();
			}
			else if (infoS�ras� >= 2)
			{
				isinfo = 0;
				infoS�ras� = 0;
				StartScreen();
			}

		}
		else
		{
			ArabaMainXcor += 15;
		}

	}
	if (keyboard == 37)
	{
		//sol ok tu�una bas�ld�ysa
		if (startGame == 0 && iscarchoose == 0 && isinfo == 1)
		{
			if (infoS�ras� > 0)
			{
				infoS�ras�--;
				Infolar();
			}

		}
		else
		{
			ArabaMainXcor -= 15;
		}

	}
	if (keyboard2 == 38 && carCrash != 1)
	{
		// Yukari yon tusuna basilinca
		if (startGame == 0 && iscarchoose == 0 && isinfo == 0)
		{
			if (fotoS�ras� <= 0)
			{
				fotoS�ras� = 2;
			}
			else
			{
				fotoS�ras�--;
			}
			StartScreen();
		}
		else if (mapSpeed <= 30)
		{
			mapSpeed += 2;
		}

		//ara� se�im sayfas�
		if (iscarchoose == 1 && startGame == 0 && gameover == 0)
		{
			if (carchoose <= 0)
			{
				carchoose = 3;
			}
			else
			{
				carchoose--;
			}
			CarChoose();
		}
	}
	if (keyboard2 == 40 && carCrash != 1)
	{
		// Assagi yon tusuna basilinca
		if (startGame == 0 && iscarchoose == 0 && isinfo == 0 && gameover == 0)
		{
			if (fotoS�ras� >= 2)
			{
				fotoS�ras� = 0;
			}
			else
			{
				fotoS�ras�++;
			}
			StartScreen();
		}
		else if (mapSpeed >= 10)
		{
			mapSpeed -= 2;
		}

		//ara� se�im sayfas�
		if (iscarchoose == 1 && startGame == 0 && isinfo == 0)
		{
			if (carchoose >= 3)
			{
				carchoose = 0;
			}
			else
			{
				carchoose++;
			}
			CarChoose();
		}
	}

	if (keyboard2 == 13 && startGame == 0)
		//enter tu�u
	{
		if (iscarchoose == 0 && isinfo == 0 && gameover == 0)
		{
			if (fotoS�ras� == 0)
				//ba�la
			{
				DWORD dw;
				startGame = 1;
				fullScreenX = 1220;
				ICG_MWSize(fullScreenX, FullscreenY);
				CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GamePlay, NULL, 0, &dw);

			}
			else if (fotoS�ras� == 1)
				//ara� se�imi button
			{
				iscarchoose = 1;
				CarChoose();
			}
			else if (fotoS�ras� == 2)
				// �nfo button
			{
				isinfo = 1;
				Infolar();

			}

		}

		else if (iscarchoose == 1 && isinfo == 0 && gameover == 0)
		{
			if (carchoose == 0)

			{
				ReadImage("merso.bmp", ArabaMain);
				ReadImage("merso-crashed.bmp", crashedCar);
				ReadImage("ferrari.bmp", Araba);
				ReadImage("aston.bmp", Araba1);
				iscarchoose = 0;
				StartScreen();


			}
			else if (carchoose == 1)

			{
				ReadImage("ferrari.bmp", ArabaMain);
				ReadImage("ferrari-crash.bmp", crashedCar);
				ReadImage("mc.bmp", Araba);
				ReadImage("aston.bmp", Araba1);
				iscarchoose = 0;
				StartScreen();
			}
			else if (carchoose == 2)

			{
				ReadImage("aston.bmp", ArabaMain);
				ReadImage("aston-crashed.bmp", crashedCar);
				ReadImage("ferrari.bmp", Araba);
				ReadImage("merso.bmp", Araba1);
				iscarchoose = 0;
				StartScreen();
			}
			else if (carchoose == 3)

			{
				ReadImage("mc.bmp", ArabaMain);
				ReadImage("mc-crashed.bmp", crashedCar);
				ReadImage("ferrari.bmp", Araba);
				ReadImage("aston.bmp", Araba1);
				iscarchoose = 0;
				StartScreen();
			}
		}
		else if (gameover == 1)
		{
			gameover = 0;
			startGame = 0;
			carCrash = 0;
			RestartGame();
			PlaySound("opening.wav", NULL, SND_ASYNC | SND_LOOP);
			StartScreen();
		}



	}


}


void ICGUI_main()
{
	ReadImage("mc.bmp", ArabaMain);
	ReadImage("mc-crashed.bmp", crashedCar);
	ReadImage("passed.bmp", infoCar);
	ReadImage("scoreboardy.bmp", tempInfo);
	ReadImage("home1.bmp", HomeScreen);
	ReadImage("home2.bmp", HomeScreen2);
	ReadImage("home3.bmp", HomeScreen3);
	ReadImage("choose1.bmp", carScreen1);
	ReadImage("choose2.bmp", carScreen2);
	ReadImage("choose3.bmp", carScreen3);
	ReadImage("choose4.bmp", carScreen4);
	ReadImage("GameOver.bmp", gameOver);
	CreateImage(OyunAlan�, 1001, 749, ICB_UINT);
	CreateImage(InfoAlan�, 200, 749, ICB_UINT);
	OyunAlan� = 0xffffff;
	FRM = ICG_FrameThin(0, 0, 1200, 749);
	FRM2 = ICG_FrameThin(1001, 0, 200, 749);
	PasteNon0(tempInfo, 1, 1, InfoAlan�);
	PasteNon0(HomeScreen, 1, 1, OyunAlan�);
	DisplayImage(FRM, OyunAlan�);
	DisplayImage(FRM2, InfoAlan�);
	PlaySound("opening.wav", NULL, SND_ASYNC | SND_LOOP);
	highScore = ICG_SLEdit(1068, 128, 68, 26, "");
	timeText = ICG_SLEdit(1068, 285, 68, 26, "");
	speedText = ICG_SLEdit(1068, 205, 68, 26, "");
	S�raText = ICG_SLEditSunken(1068, 367, 68, 26, "");

	//ICG_TButton(1050, 20, 100, 55, "Start", StartScreen, NULL);
	ICG_SetOnKeyPressed(WhenKeyPressed);
}