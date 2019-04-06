#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include "Operate.h"

void gotoxy(int x, int y)                  //Set light mark position(One of the most important part)
{
	COORD coord;
	HANDLE handle;
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);//get handle
	SetConsoleCursorPosition(handle, coord);
}

void createMap()        //create map
{
	int i;
	for (i = 0; i <= MAP_WIDTH; i += 2)  //print up and down border
	{
		gotoxy(i, 0);
		printf("?");        //one cube has two point
		gotoxy(i, MAP_HEIGHT);
		printf("?");
	}
	for (i = 1; i < MAP_HEIGHT; i++)    //print left and right border
	{
		gotoxy(0, i);
		printf("?");
		gotoxy(MAP_WIDTH, i);
		printf("?");
	}
}

void initSnake()//init snake body
{
	snake *tail;
	int i;
	tail = (snake*)malloc(sizeof(snake));//insert body
	tail->x = 24;
	tail->y = 5;
	tail->next = NULL;
	for (i = 1; i < 4; i++)//first length:4
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}
	while (tail != NULL)//print body
	{
		gotoxy(tail->x, tail->y);
		printf("¡ö");
		tail = tail->next;
	}
}

int eatSelf()//judge if eat itself(head hit's body)
{
	snake *body;
	body = head->next;
	while (body != NULL)
	{
		if (body->x == head->x && body->y == head->y)
		{
			return 1;
		}
		body = body->next;
	}
	return 0;
}

void createFood()
{
	snake *body;
	srand((unsigned)time(NULL));
	do
	{
		food.x = rand() % (MAP_WIDTH - 4) + 2;
	} while ((food.x % 2) != 0);    //make sure it is odd
	food.y = rand() % (MAP_HEIGHT - 2) + 1;
	body = head;
	while (body->next != NULL)
	{
		if (body->x == food.x && body->y == food.y)
		{
			createFood();
		}
		body = body->next;
	}
	//food is not in the body
	gotoxy(food.x, food.y);
	printf("$");
}

void ifHitWall()//hit the wall
{
	if (head->x == 0 || head->x == MAP_WIDTH || head->y == 0 || head->y == MAP_HEIGHT )
	{
		flag = HIT;
		endGame();
	}
}

void snakeMove()           //only move one step
{
	snake *nexthead, *q;
	ifHitWall();//judge if hit wall.if hit gameover;
	nexthead = (snake*)malloc(sizeof(snake));
	if (Direction == U)
	{
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
		if (nexthead->x == food.x && nexthead->y == food.y)//there is food
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				gotoxy(q->x, q->y);
				printf("¡ö");
				q = q->next;
			}
			score += add;
			createFood();
		}
		else                                               //no food
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				gotoxy(q->x, q->y);
				printf("¡ö");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);//use space to cover tail
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (Direction == D)
	{
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
		if (nexthead->x == food.x && nexthead->y == food.y)  //there is food
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				gotoxy(q->x, q->y);
				printf("¡ö");
				q = q->next;
			}
			score += add;
			createFood();
		}
		else                               //no food
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				gotoxy(q->x, q->y);
				printf("¡ö");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);//use space to cover tail
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (Direction == L)
	{
		nexthead->x = head->x - 2;
		nexthead->y = head->y;
		if (nexthead->x == food.x && nexthead->y == food.y)//there is food
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				gotoxy(q->x, q->y);
				printf("¡ö");
				q = q->next;
			}
			score += add;
			createFood();
		}
		else                                //no food
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				gotoxy(q->x, q->y);
				printf("¡ö");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);//use space to cover tail
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (Direction == R)
	{
		nexthead->x = head->x + 2;
		nexthead->y = head->y;
		if (nexthead->x == food.x && nexthead->y == food.y)//there is food
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				gotoxy(q->x, q->y);
				printf("¡ö");
				q = q->next;
			}
			score += add;
			createFood();
		}
		else                                         //no food
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				gotoxy(q->x, q->y);
				printf("¡ö");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);//use space to cover tail
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (eatSelf())       //judge if can eat itself
	{
		flag = EAT;
		endGame();
	}
}

void pause()
{
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE))
			break;
	}
}

void runGame()//control the game
{
	gotoxy(64, 16);
	printf("Use¡ü.¡ý.¡û.¡ú.to control snake move.");
	gotoxy(64, 17);
	printf("F1:speed up£¬F2:speed down.");
	gotoxy(64, 18);
	printf("ESC £ºexit the game.");
	gotoxy(64, 19);
	printf("Space£ºpause.");
	Direction = R;   //the initation direction
	clickEvent();
}

void initGame()//start window
{
	gotoxy(40, 12);
	printf("WELCOME TO RETRO SNAKE!\n");
	gotoxy(41, 14);
	printf("press to continue...");
	getchar();
	system("cls");
	gotoxy(40, 12);
	printf("use¡ü.¡ý.¡û.¡ú.to control snake move.\n");
	gotoxy(48, 13);
	printf("press to continue...");
	getchar();
	system("cls");
}

void endGame()      //game over
{
	system("cls");
	gotoxy(24, 12);
	if (flag == HIT || flag == EAT || flag == EXIT)
	{
		printf("GAMEOVER!");
	}
	gotoxy(24, 13);
	printf("Your score: %d\n\n\n\n", score);
	gotoxy(24, 14);
	printf("Press to end...\n");
	gotoxy(24, 15);
	system("pause");
	exit(0);
}

void gameStart()    //start game
{
	initGame();
	chooseHardLevel();
	createMap();
	initSnake();
	createFood();
}

void chooseHardLevel() {
	gotoxy(40, 12);
	printf("The harder,per food's score is higher.");
	gotoxy(40, 13);
	printf("E:easy\tN:normal\tH:hard\tP:professor\tI:impossible");
	gotoxy(40, 14);
	printf("Enter the hard level(E/N/H/P/I): ");
	char c = getchar();
	switch (c) {
	case 'E':case'e':sleeptime = 200; add = 6;  break;
	case 'N':case 'n':sleeptime = 150; add = 8; break;
	case 'H':case 'h':sleeptime = 100; add = 10; break;
	case 'P':case 'p':sleeptime = 50; add = 20; break;
	case 'I':case 'i':sleeptime = 30; add = 30;  break;
	default:sleeptime = 150; add = 8; break;
	}
	system("cls");
}

void clickEvent()
{
	for (;;)
	{
		gotoxy(64, 10);
		printf("Score £º%d  ", score);
		gotoxy(64, 11);
		printf("Per food score £º%d", add);
		if (GetAsyncKeyState(VK_UP) && Direction != D)
		{
			Direction = U;
		}
		else if (GetAsyncKeyState(VK_DOWN) && Direction != U)
		{
			Direction = D;
		}
		else if (GetAsyncKeyState(VK_LEFT) && Direction != R)
		{
			Direction = L;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && Direction != L)
		{
			Direction = R;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			flag = EXIT;
			break;
		}
		Sleep(sleeptime);
		snakeMove();
	}
}
