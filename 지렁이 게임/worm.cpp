#include <stdio.h>
#include <Windows.h>
#include "Turboc.h"



int item[2] = { 0,0 };
int map[20][20] = {
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
};
int snake[289][2] = {
		{0,0}
};
int snakeRotate = 1;

int score = 0;
int BestScore = 0;
bool menu = true;
bool isgameOver = false;


void file();


void Main();
void GetKeyMain(bool* tocle, bool *loop);
void drawMain();



void Game();
void GetKeyGame();
void MoveSnake();
void RandomItem();
void drawMap();
void GameOver();

int main()
{
	file();
	Main();
	return 0;
}

void file()
{
	FILE* fd;
	int data;
	fd = fopen("test.txt", "r");
	int a = 0;
	int b = 0;


	while (fscanf(fd, "%d", &data) != EOF)
	{
		
		if (data == 3)
		{
			++a;
			b = 0;
		}
		else
		{
			if (a - 1 < 0)
				break;
			map[a-1][b] = data;
			++b;
			
		}

	}

	fclose(fd);
}



void Main()
{
	bool tocle = false;
	bool loop = true;
	drawMain();
	while (loop)
	{
		bool t = tocle;
		GetKeyMain(&tocle, &loop);

		if (t != tocle)
			drawMain();
	}
}

void GetKeyMain(bool *tocle, bool *loop)
{
		if (GetAsyncKeyState(VK_UP))
		{
			if (!*tocle)
			{
			menu = !menu;
			*tocle = true;
			}

		}
		else
		{
			*tocle = false;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			if (menu)
			{
				Game();
				drawMain();
			}
			else
			{
				*loop = false;
			}
		}
}

void drawMain()
{
	system("cls");
	printf("★★★★★★★★★★★★★★★★  Best score :%d\n", BestScore);
	for (int i = 0; i < 3; i++)
	{
		printf("★                            ★\n");
	}
	
	if (menu)
	{
		printf("★         %s게임시작         ★\n","★");
		printf("★         %s게임종료         ★\n","☆");
	}
	else
	{
		printf("★         %s게임시작         ★\n","☆");
		printf("★         %s게임종료         ★\n","★");
	}


	for (int i = 0; i < 3; i++)
	{
		printf("★                            ★\n");
	}

	printf("★★★★★★★★★★★★★★★★\n");
}






void Game()
{
	for (int i = 0; i < 289; i++)
	{
		for (int r = 0; r < 2; r++)
		{
			snake[i][r] = -1;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		snake[i][1] = 9;
		snake[i][0] = 10 + i;
	}

	score = 0;
	snakeRotate = 2;
	RandomItem();
	isgameOver = false;
	while(!isgameOver)
	{
		Sleep(500);
		GetKeyGame();
		MoveSnake();
		drawMap();
	}
}

void GetKeyGame()
{
	if (GetAsyncKeyState(VK_UP))
	{
		snakeRotate = 2;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		snakeRotate = 1;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		snakeRotate = 3;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		snakeRotate = 4;
	}

}

void RandomItem()
{
	/*
	bool www = true;
	while (www)
	{
		item[0] = rand() % (17) + 1;
		item[1] = rand() % (17) + 1;
		
		for (int i = 0; i < score + 4; i++)
		{
			if (item[0] != snake[i][0] && item[1] != snake[i][1])
			{
				www = false;
				break;
			}

		}
	}
	*/
		int itemPos = 0;
		srand(time(NULL));
		itemPos = random(285 - score) + 1;

		bool bre = false;
		for (int i = 1; i <= 17; i++)
		{
			for (int e = 1; e <= 17; e++)
			{
				bool s = true;



				for (int t = score + 3; t >= 0; t--)
				{
					if (snake[t][0] == i && snake[t][1] == e)//snake 조건문작성
					{
						s = false;
						break;
					}
				}

				if (itemPos == 0 && s)//item
				{
					printf("⊙");
					s = false;
					item[0] = i;
					item[1] = e;

					clrscr();
					bre = true;
					break;
				}
				else if (s)
					--itemPos;
			}
			if (bre)
				break;
		}


}

void MoveSnake()
{
	for (int i = 0; i < score + 3; i++)
	{
		snake[score - i + 3][0] = snake[score - i + 2][0];
		snake[score - i + 3][1] = snake[score - i + 2][1];
	}

	switch(snakeRotate)
	{
		case 1:
			snake[0][0] += 1;
			break;
		case 2:
			snake[0][0] -= 1;
			break;
		case 3:
			snake[0][1] += 1;
			break;
		case 4:
			snake[0][1] -= 1;
	}

	if (snake[0][0] == item[0] && snake[0][1] == item[1])
	{
		++score;
		RandomItem();
	}


	if (map[snake[0][0]][snake[0][1]] == 2)
		GameOver();

	for (int i = 0; i < score + 3; i++)
	{
		if (snake[0][0] == snake[score - i + 3][0] && snake[0][1] == snake[score - i + 3][1])
			GameOver();
	}

}



void drawMap()
{
	system("cls");

	
	for (int i = 0; i < 19; i++)
	{
		for (int e = 0; e < 19; e++)
		{
			bool s = true;
			for (int t = score + 3; t >= 0; t--)
			{
				if (snake[t][0] == i && snake[t][1] == e)//snake 조건문작성
				{
					if (t == 0)
						printf("◆");
					else
						printf("◈");
					s = false;
				}
			}

			if (s)
			{
				if (item[0] == i && item[1] == e)//item
				{
					printf("⊙");
				}
				else if (map[i][e] == 2)
				{
					printf("■");
				}
				else if(s)
				{
					printf("□");
				}
			}
		}
		printf("\n");

	}		
	printf("score : %d",score);
}

void GameOver()
{
	Sleep(3000);
	if (BestScore < score)
		BestScore = score;
	isgameOver = true;
}

/*
int main()
{
	int a = 0;
	scanf_s("%d", &a);

	for (int i = 1; i < (a * 2 + 1) - i; i++)
	{
		for (int b = 0; b < i; b++)
		{
			printf(" ");
		}

		for (int e = 0; e < (a * 2 + 1) - i * 2; e++)
		{
			printf("*");
		}
		printf("\n");
	}
}




int main()
{
	int n = 8;
	for (int i = 1; i < (n * 2 + 1) - i; i++)
	{
		for (int b = 0; b < i; b++)
		{
			printf(" ");
		}

		for (int e = 0; e < (n * 2 + 1) - i * 2; e++)
		{
			printf("*");
		}
		printf("\n");
	}




}*/