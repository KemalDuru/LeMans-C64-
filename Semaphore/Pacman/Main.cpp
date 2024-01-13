#include"icb_gui.h"
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<math.h>

#define NUMBER_OF_SEMAPHORES 3
int FRM1;
int shipX = 350, shipY = 250;
int count = 2;
int numberOfBox = 9;
int current;
int flag = 1, flag1 = 1;
int threadCount = 2;

HANDLE HSemaphore;
HANDLE hTimerQueue = NULL;
ICBYTES image;


struct forThreads {
	int threadNumber;
	int coorX = 999;
	int coorY = 999;
	int isSelected = 0;
};
struct forThreads left[9];
struct forThreads right[9];

void ICGUI_Create()
{
	ICG_MWSize(800, 600);
	ICG_MWTitle("Semaphore");

}
VOID CALLBACK slidingBox(PVOID lpParam, BOOLEAN TimerOrWaitFired) {

	if (count % 2 == 0) {
		
		while (1) {

				int x = 10;
				FillRect(image, shipX, shipY, 100, 50, 0x4876ff);
				FillRect(image, shipX + x, shipY+10, 20, 20, 0x8b6914);
				x = x + 30;
				FillRect(image, shipX + x, shipY+10, 20, 20, 0x8b6914);
				x = x + 30;
				FillRect(image, shipX + x, shipY+10, 20, 20, 0x8b6914);
				x = 10;
				shipX -= 1;
				FillRect(image, shipX, shipY, 100, 50, 0x8b6914);
				FillRect(image, shipX + x, shipY+10, 20, 20, 0x2e8b57);
				x = x + 30;
				FillRect(image, shipX + x, shipY+10, 20, 20, 0x2e8b57);
				x = x + 30;
				FillRect(image, shipX + x, shipY+10, 20, 20, 0x2e8b57);

				Sleep(5);




			if (shipX == 250) {

				for (int i = 0; i < 9; i++) {
					if (left[i].isSelected == 1) {
						FillRect(image, right[i].coorX, right[i].coorY, 20, 20, 0xffdead);
						right[i].coorX = 600 + (rand() % 50);
						right[i].coorY = rand() % 500;
						left[i].isSelected = 0;
						right[i].isSelected = 0;
						DisplayImage(FRM1, image);
					}
					Sleep(50);
					if (left[i].isSelected == 0) {
						FillRect(image, left[i].coorX, left[i].coorY, 20, 20, 0x2e8b57);
						DisplayImage(FRM1, image);
					}
				}
				threadCount += 1;
				break;

			}
			DisplayImage(FRM1, image);
		}
	}
	if (count % 2 == 1) {
		while (1) {
			int x = 10;
			FillRect(image, shipX, shipY, 100, 50, 0x4876ff);
			FillRect(image, shipX + x, 270, 20, 20, 0x8b6914);
			x = x + 30;
			FillRect(image, shipX + x, 270, 20, 20, 0x8b6914);
			x = x + 30;
			FillRect(image, shipX + x, 270, 20, 20, 0x8b6914);
			x = 10;
			shipX += 1;
			FillRect(image, shipX, shipY, 100, 50, 0x8b6914);
			FillRect(image, shipX + x, 270, 20, 20, 0x2e8b57);
			x = x + 30;
			FillRect(image, shipX + x, 270, 20, 20, 0x2e8b57);
			x = x + 30;
			FillRect(image, shipX + x, 270, 20, 20, 0x2e8b57);
			Sleep(5);
			if (shipX == 450) {
				x = 10;
				FillRect(image, shipX + x, 270, 20, 20, 0x8b6914);
				x = x + 30;
				FillRect(image, shipX + x, 270, 20, 20, 0x8b6914);
				x = x + 30;
				FillRect(image, shipX + x, 270, 20, 20, 0x8b6914);

				for (int i = 0; i < 9; i++) {
					if (right[i].isSelected == 1) {
						FillRect(image, left[i].coorX, left[i].coorY, 20, 20, 0xffdead);
						left[i].coorX = rand() % 50;
						left[i].coorY = rand() % 400;
						left[i].isSelected = 0;
						right[i].isSelected = 0;
						DisplayImage(FRM1, image);
					}
					Sleep(50);
					if (right[i].isSelected == 0) {
						FillRect(image, right[i].coorX, right[i].coorY, 20, 20, 0x2e8b57);
						DisplayImage(FRM1, image);
					}
				}
				threadCount += 1;
				break;

			}
			DisplayImage(FRM1, image);
		}

	}
	count += 1;
}

void createBox() {

	for (int i = 0; i < 9; i++) {
		FillRect(image, left[i].coorX, left[i].coorY, 20, 20, 0x2e8b57);
	}
}

void findCloserRight() {
	int smallestNumber;
	int calculate = 0;
	int a = 0;
	while (flag1 == 0) {

	}
	if (flag1 == 1) {
		flag1 = 0;
		for (int i = 0; i < numberOfBox; i++) {
			a = pow(250 - right[i].coorX, 2) + pow(275 - right[i].coorY, 2);
			calculate = sqrt(a);
			if (i == 0) {
				smallestNumber = calculate;
				current = i;
			}
			else if (calculate < smallestNumber) {
				smallestNumber = calculate;
				current = i;
			}
		}
		left[current].coorX = right[current].coorX;
		left[current].coorY = right[current].coorY;
		right[current].isSelected = 1;
		right[current].coorX = 0;
		right[current].coorY = 1000;
		left[current].isSelected = 1;
		flag1 = 1;

	}
}

void findCloser() {
	int smallestNumber;
	int calculate = 0;
	int a = 0;
	while (flag == 0) {

	}
	if (flag == 1) {
		flag = 0;
		for (int i = 0; i < numberOfBox; i++) {
			a = pow(250 - left[i].coorX, 2) + pow(275 - left[i].coorY, 2);
			calculate = sqrt(a);
			if (i == 0) {
				smallestNumber = calculate;
				current = i;
			}
			else if (calculate < smallestNumber) {
				smallestNumber = calculate;
				current = i;
			}
		}
		right[current].coorX = left[current].coorX;
		right[current].coorY = left[current].coorY;
		left[current].isSelected = 1;
		left[current].coorX = 1000;
		left[current].coorY = 1000;
		right[current].isSelected = 1;
		flag = 1;
		DisplayImage(FRM1, image);
	}

}

void* Play(LPVOID vv) {

	DWORD dwWaXitResult = WaitForSingleObject(HSemaphore, INFINITE);
	while (shipX != 250 && shipX != 450) {

	}
	if (threadCount % 2 == 0) {
		findCloser();
	}
	else if (threadCount % 2 == 1 && threadCount > 4) {
		findCloserRight();
	}
	Sleep(5000);
	DisplayImage(FRM1, image);
	ReleaseSemaphore(HSemaphore, 1, NULL);

	return(0);
}

void ICGUI_main()
{
	HANDLE hTimer = NULL;
	hTimerQueue = CreateTimerQueue();
	DWORD ThreadID;
	DWORD dw;
	CreateImage(image, 800, 600, ICB_UINT);
	image = 0xffdead;
	for (int i = 0; i < 9; i++) {
		left[i].threadNumber = i;
		left[i].coorX = rand() % 200;
		left[i].coorY = rand() % 500;
		left[i].isSelected = false;
	}

	FRM1 = ICG_FrameThin(0, 0, 600, 600);
	createBox();
	FillRect(image, 250, 0, 300, 600, 0x4876ff);
	FillRect(image, shipX, shipY, 100, 50, 0x8b6914);
	CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)slidingBox, NULL, 0, 5000, 0);

	HSemaphore = CreateSemaphore(
		NULL,
		NUMBER_OF_SEMAPHORES,
		NUMBER_OF_SEMAPHORES,
		NULL);
	for (int x = 0; x < 100; x++)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Play, &left[x], 0, &ThreadID);
	}
	DisplayImage(FRM1, image);

}