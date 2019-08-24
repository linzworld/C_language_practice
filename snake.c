//ʹ����ͷ��β��ͬ��ӡ�ķ���
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <time.h>

void food();
void background();
void gotoxy();	//���ƹ��
void wall();	//�߿���Ϸ�ı߽�
void show();
void move();
void turn();
void check();
void ini();
//ȫ�ֱ���
int  dx[4] = { -1, 0, 1, 0 };
int  dy[4] = { 0, 1, 0, -1 };
int sum = 5;  //���ܳ���
int over = 0;//��Ϸ�Ƿ����
int speed;   //ˢ���ٶ�
char map[17][17];//��ӡ�ĵ�ͼ
int score=0;

struct snake 
{
    int x, y;  //�������� 
    int dir;  //����ֻ����ͷ�ķ��������õģ� 
} s[100];


/**************************************************/
void background()//��ӭ����
{int i;
	gotoxy(15,10);
	printf("������������������������������������������");
		for(i=11;i<15;i++)
		{
			gotoxy(15,i);printf("��");
			gotoxy(55,i);printf("��");
		}
	gotoxy(21, 13);
	printf("Welcome to the Happy Snake");
	gotoxy(15, 15);
	printf("������������������������������������������");
	gotoxy(15, 18);
	printf("��Ϸ˵����");
	printf("'w''s''a''d'������������");
	gotoxy(15, 19);
	printf("����ENTER���Լ���");

	getchar();	//��ͣ������
}

/*************************************************/

void gotoxy(int x, int y)	//���Ŀ���
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

/************************************************/

void ini() //��ʼ������
{  
    int i, j;
    speed = 250;
    over = 0;
    sum = 5;
	for (i = 0; i < 100; i++) //��ʼ����ͷ����������ݣ�ÿ���ߵ�һ���㶼��Ϊһ���ڵ�
    {  //һ���ڵ����һ���ṹ�����ͱ��������������
        s[i].dir = 0;
        s[i].x = 0;
        s[i].y = 0;
    }
    s[0].x = 2; s[0].y = 2;  //��ͼ���Ͻǳ�ʼ������һ������Ϊ5����
    s[1].x = 2; s[1].y = 3;
    s[2].x = 2; s[2].y = 4;
    s[3].x = 2; s[3].y = 5;
    s[4].x = 2; s[4].y = 6; 
    
    s[4].dir = 1;//��ͷ
    srand(time(0));//��������
    for (i = 0; i < 17; i++) 
    {  //���õ�ͼ
        for (j = 0; j < 17; j++) 
        {
            map[i][j] = '*';

        }
    }
    for (i = 1; i < 16; i++) //��ӡ������ͨ�����ε�д
    {
        for (j = 1; j < 16; j++) 
		{
            map[i][j] = ' ';
        }
    }
    map[s[4].x][s[4].y] ='H';  //������ͷ
    for (i = 0; i < sum - 1; i++) {  //��������
        map[s[i].x][s[i].y] = 'X';
    }
    wall();
	food();
}
/*****************************************************/
void wall()//��ӡǽ
{
	int i,j;
	for(i=0;i<17;i++)
	{
		for(j=0;j<17;j++)
		{
		if(i==0||i==16)
			{
				gotoxy(2*i,j);
				printf("��");
			}
		if(j==0||j==16)
			{
				gotoxy(2*i,j);
				printf("��");
			}
		}

	}
	
    for (i = 0; i < 17; i++) 
    {  
        for (j = 0; j < 17; j++) 
        {
             if(map[i][j]=='H'||map[i][j]== 'X')//��ʼ������
			{
				gotoxy(2*i,j);
				printf("��");
			}

		}
	}
	for(i=0;i<30;i++)//��ӡ�ֽ���
			{
				gotoxy(40,i);
				printf("^");
			}
	gotoxy(48,5);
	printf("THE HAPPY SNAKE");
	gotoxy(48,7);
	printf("YOUR SCORE:%d",sum-5);
}

/*****************************************************/
void show() 
{								//��ʾ���� 
	int i,j;
    while (1) 
	{
        Sleep(speed);  //����ˢ���ٶ�
        turn();//������һ��������������Ȼ��ʹ��ͷ�ڵ�ķ���ֵ�����ı�
        move();//����turnת��������ߵ��ƶ������޸ģ���move��check����Ƿ�over
            if (over) 
            {		//��������������Խ��еĲ��� 
					gotoxy(48,15);		//��Ϸ����ʱ��ѡ��
					printf("GAME OVER!");
					gotoxy(48,17);
					printf("NEW  GAME:��'r'");
					gotoxy(48,18);
					printf("EXIT GAME:��'q'\n");
                while (1) 
                {

                char ch = _getch();
					if (ch == 113) 
					{  //���롮q������ 
						return;
					}
					else if (ch == 114) 
					{  //���롮r�����¿�ʼ 
						
						for(i=1;i<16;i++)
						{
							for(j=1;j<16;j++)
							{
								gotoxy(2*i,j);
								printf("  ");
							}
						}

					sum=5;
					score=0;
					gotoxy(42,15);//�������
					printf("	                         ");
					gotoxy(42,17);//�������
					printf("	                         ");
					gotoxy(42,18);//�������
					printf("	                         ");
					ini();
						break;
					}
				}
            }
      }
}

/*************************************************/
void food() 
{  //����ʳ��
    int x, y;
    while (1) 
    {
        x = (int)(15 * rand() / (RAND_MAX + 1.0));  //�������һ��ʳ�������
        y = (int)(15 * rand() / (RAND_MAX + 1.0));
        if ((map[x][y] == ' ')&&(x<16&&x>0)&&(y<16&&y>0)) //����ǿո����ڸô�����ʳ��
        {  
            map[x][y] = 'O';
			gotoxy(2*x,y);
				printf("��");
            break;
        }
    }
}

/**************************************************/
void move() 
{  //���ƶ�
    int i;
    int t = sum;	//t��¼��ǰ���ܳ��� 
    check();  //�ƶ�ǰ��鰴��ǰ�����ƶ�һ��������
    if (t == sum) {  //û�гԵ�ƻ��
        for (i = 0; i < sum - 1; i++) {
            if (i == 0) {  //��β���괦��ɿո񣬰���β������ǰһ����������� 
                map[s[i].x][s[i].y] =' ';
					gotoxy(2*(s[i].x),s[i].y);
					printf("  ");
                s[i].x = s[i + 1].x;
                s[i].y = s[i + 1].y;
            }
            else {  //ÿ���������궼��Ϊ��ǰһ�����������
                s[i].x = s[i + 1].x;
				s[i].y = s[i + 1].y;
            }
            map[s[i].x][s[i].y] = 'X';  //�ѵ�ͼ���������괦���ַ����óɡ�X��
        }
        s[sum - 1].x = s[sum - 1].x + dx[s[sum - 1].dir];  //��ͷ����ǰ�����ƶ�һ�� 
        s[sum - 1].y = s[sum - 1].y + dy[s[sum - 1].dir];
        map[s[sum - 1].x][s[sum - 1].y] = 'H';  //�ѵ�ͼ����ͷ���괦���ַ����óɡ�H��
		if(map[s[sum - 1].x][s[sum - 1].y] = 'H')
		{gotoxy(2*(s[i].x),s[i].y);
		printf("��");}
    }
    else	//�Ե�ƻ����sum���1��
	{  
        map[s[sum - 2].x][s[sum - 2].y] = 'X';  //�ѵ�ͼ��ԭ��ͷ���괦���ַ����óɡ�X��
				s[sum - 1].x = s[sum - 2].x + dx[s[sum - 2].dir];  //����ͷ��������ԭ��ͷ�ص�ǰ�����ƶ�һ�������� 
				s[sum - 1].y = s[sum - 2].y + dy[s[sum - 2].dir];
				s[sum - 1].dir = s[sum - 2].dir;					//����ͷ����Ϊԭ��ͷ�ķ���
		map[s[sum - 1].x][s[sum - 1].y] = 'H';						//�ѵ�ͼ����ͷ���괦���ַ����óɡ�H��
		if(map[s[sum - 1].x][s[sum - 1].y] = 'H')
		{
			gotoxy(2*(s[sum - 1].x),s[sum - 1].y);
			printf("��");
		}
        food();
    }

}

/****************************************************/
void check() {  //����Ƿ��������߳Ե�ʳ��
    int x, y;
    x = s[sum - 1].x + dx[s[sum - 1].dir];  //��¼����ǰ�����ƶ�һ�����ͷ������ 
    y = s[sum - 1].y + dy[s[sum - 1].dir];
    if (map[x][y] == '*' || map[x][y] == 'X') 
	{  //�����ͼ�ϸ����괦�ַ�Ϊ��*����X�������� 
        if (x != s[0].x || y != s[0].y) //��β���� 
		{  
            over = 1;
        }
    }
    else if (map[x][y] == 'O') 
	{  //�Ե�ƻ�� 
			sum++;  //�����ܳ���1 
			gotoxy(59,7);
			printf("%d",++score);
			speed = ((300- sum * 20)>100) ? (300- sum * 20) : 150; //�ٶȼӿ� 
    }
}

/*******************************************************/
void turn() {  //ת��
    if (_kbhit()) 
    {
        char dir = _getch();  //��ȡ����ļ� 
        switch (dir) 
        {  //�ı䷽�� 
        case 'a': s[sum - 1].dir =    (s[sum - 1].dir == 2)?2:0; break;
        case 's': s[sum - 1].dir =    (s[sum - 1].dir == 3)?3:1; break;
        case 'd': s[sum - 1].dir =    (s[sum - 1].dir == 0)?0:2; break;
        case 'w': s[sum - 1].dir =    (s[sum - 1].dir == 1)?1:3; break;
        }
    }
}

/********************************************************/
int main(int argc, char *argv[])
{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//���ؿ���̨�Ĺ��
		CONSOLE_CURSOR_INFO cci;
		GetConsoleCursorInfo(hOut, &cci);
		cci.bVisible = FALSE;
		SetConsoleCursorInfo(hOut, &cci);

	system("mode con cols=80 lines=30  ");//�ı����̨���ڵĴ�С
    background();//��ӡ��ӭ�Ľ���
    system("cls");//������������Ϸ����
    ini();//��Ϸ��ʼ,��ʼ������
    show();
    return 0;
}