/*

Program & Concept by ::

	Chinmay Phutela

		Shaurya Sanger

			Shubham Kumar Jain

*/


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<dos.h>

#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define UP_ARROW 72
#define DOWN_ARROW 80

typedef struct TiLe
{
	int DaTa;
	int Location;
	struct TiLe *right,*down,*left,*up;
}TiLe;

int USERSCREEN();
int Modes();
int Instructions();
int Statistics();
int Architects();
int Scoreboard(int score,int status);
int Evaluate(int score);

int CrEaTe_MaIn();
int SetLocation();
int DiSpLaY();
int CoLoR_sTyLe(int DaTa,int Location);
int fUnCtIoN(int mode);
int GaMe_OvEr(int mode);
int GeNeRaTe_RaNdOm();

void sHiFt_uP(TiLe *P);
void sHiFt_dOwN(TiLe *P);
void sHiFt_lEfT(TiLe *P);
void sHiFt_rIgHt(TiLe *P);

TiLe *sTaRt=NULL;
TiLe *temp,*temp1,*temp2;
TiLe *sTaRtU=NULL,*sTaRtD=NULL,*sTaRtL=NULL,*sTaRtR=NULL;
TiLe *p1,*p2,*p3;

union REGS i, o;

int initmouse()
{
   i.x.ax = 0;
   int86(0X33,&i,&o);
   return ( o.x.ax );
}

void showmouseptr()
{
   i.x.ax = 1;
   int86(0X33,&i,&o);
}

void hidemouseptr()
{
   i.x.ax = 2;
   int86(0X33,&i,&o);
}

void getmousepos(int *button, int *x, int *y)
{
   i.x.ax = 3;
   int86(0X33,&i,&o);

   *button = o.x.bx;
   *x = o.x.cx;
   *y = o.x.dx;
}

void restrictmouseptr(int x1, int y1, int x2, int y2)
{
   i.x.ax = 7;
   i.x.cx = x1;
   i.x.dx = x2;
   int86(0X33,&i,&o);

   i.x.ax = 8;
   i.x.cx = y1;
   i.x.dx = y2;
   int86(0X33,&i,&o);
}

int main()
{
	int gdriver=DETECT,gmode;
	int midx, midy;
	int i,count,adn;
	float octave[7]={130.81,146.83,164.81,174.61,196.220,246.94};

	initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");

	setbkcolor(15);
	midx = getmaxx() / 2;
	midy = getmaxy() / 2;

	while(!kbhit())
	{
		adn=random(7);
		sound(octave[adn]*10);
		delay(190);
		nosound();
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		settextstyle(SANS_SERIF_FONT,HORIZ_DIR,4);
		setcolor(3);
		outtextxy(midx-50,midy,"CSS");
		setcolor(8);
		outtextxy(midx+30,midy,"GAMES");
		settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
		outtextxy(midx,midy+30,"presents");
	}

	cleardevice();

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
	setcolor(8);
	outtextxy(midx,midy,"2048");
	delay(300);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	setcolor(3);
	outtextxy(midx,midy+80,"LOADING . . .");
	setcolor(8);
	rectangle(midx-100,midy+100,midx+100,midy+115);
	setfillstyle(1,3);
	i=midx-98;
	for(count=0;count<25;count++)
	{
		bar(i,midy+102,i+6,midy+113);
		adn=random(7);
		sound(octave[adn]*10);
		delay(200);
		nosound();
		i=i+8;
	}
	setfillstyle(1,15);
	bar(midx-100,midy+100,midx+100,midy+115);
	bar(midx-52,midy+60,midx+100,midy+100);
	setcolor(3);
	outtextxy(midx,midy+80,"PRESS ANY KEY TO CONTINUE");
	setcolor(15);
	settextjustify(LEFT_TEXT, RIGHT_TEXT);
	getch();
	getch();

	cleardevice();
	USERSCREEN();

	getch();
	closegraph();
	return 0;
}

int USERSCREEN()
{
	int button,x,y,status;
	int midx,midy;
	midx=getmaxx()/2;
	midy=getmaxy()/2;

	cleardevice();
	setbkcolor(15);

	setfillstyle(1,8);
	bar(0, 0, getmaxx(),130);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
	outtextxy(midx-60,80,"2048");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	setfillstyle(1,8);
	bar(midx-50, midy-100, midx+50,midy-70);
	setcolor(8);
	fillellipse(midx-50,midy-85,15,15);
	fillellipse(midx+50,midy-85,15,15);
	setfillstyle(1,3);
	bar(midx-48, midy-98, midx+48,midy-72);
	setcolor(3);
	fillellipse(midx-48,midy-85,13,13);
	fillellipse(midx+48,midy-85,13,13);
	setcolor(15);
	outtextxy(midx-12,midy-87,"PLAY");

	setfillstyle(1,8);
	bar(midx-50, midy-65, midx+50,midy-35);
	setcolor(8);
	fillellipse(midx-50,midy-50,15,15);
		fillellipse(midx+50,midy-50,15,15);
	setfillstyle(1,3);
	bar(midx-48, midy-63, midx+48,midy-37);
	setcolor(3);
	fillellipse(midx-48,midy-50,13,13);
	fillellipse(midx+48,midy-50,13,13);
	setcolor(15);
	outtextxy(midx-47,midy-52,"INSTRUCTIONS");

	setfillstyle(1,8);
	bar(midx-50, midy-30, midx+50,midy-0);
	setcolor(8);
	fillellipse(midx-50,midy-15,15,15);
	fillellipse(midx+50,midy-15,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy-28, midx+48,midy-2);
	setcolor(3);
	fillellipse(midx-48,midy-15,13,13);
	fillellipse(midx+48,midy-15,13,13);
	setcolor(15);
	outtextxy(midx-40,midy-17,"STATISTICS");

	setfillstyle(1,8);
	bar(midx-50, midy+5, midx+50,midy+35);
	setcolor(8);
	fillellipse(midx-50,midy+20,15,15);
	fillellipse(midx+50,midy+20,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy+7, midx+48,midy+33);
	setcolor(3);
	fillellipse(midx-48,midy+20,13,13);
	fillellipse(midx+48,midy+20,13,13);
	setcolor(15);
	outtextxy(midx-40,midy+18,"ARCHITECTS");

	setfillstyle(1,8);
	bar(midx-50, midy+40, midx+50,midy+70);
	setcolor(8);
	fillellipse(midx-50,midy+55,15,15);
	fillellipse(midx+50,midy+55,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy+42, midx+48,midy+68);
	setcolor(3);
	fillellipse(midx-48,midy+55,13,13);
	fillellipse(midx+48,midy+55,13,13);
	setcolor(15);
	outtextxy(midx-12,midy+53,"EXIT");

	status = initmouse();
	if ( status == 0 )
	{
		cleardevice();
		printf("Mouse support not available.\n");
	}
	else
	{
		showmouseptr();
		restrictmouseptr(midx-75,midy-98,midx+75,midx+68);
		getmousepos(&button,&x,&y);
		while(!kbhit())
		{
			getmousepos(&button,&x,&y);
			if(button==1)
				{
				if(x>(midx-75)&&x<(midx+75))
				{
					if(y>(midy-98)&&y<(midy-72))
					{
						Modes();
					}
					else if(y>(midy-68)&&y<(midy-37))
					{
						Instructions();
					}
					else if(y>(midy-28)&&y<(midy-2))
					{
						Statistics();
					}
					else if(y>(midy+7)&&y<(midy+33))
					{
						Architects();
					}
					else if(y>(midy+42)&&y<(midy+68))
					{
						exit(1);
					}
				}
				button=-1;
			}
		}

	}
	hidemouseptr();
	return 0;
}

int Modes()
{
	int midx,midy,x,y,button,status;
	hidemouseptr();
	cleardevice();
	initmouse();

	midx=getmaxx()/2;
	midy=getmaxy()/2;

	setbkcolor(15);

	setfillstyle(1,8);
	bar(0, 0, getmaxx(),130);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
	outtextxy(midx-70,80,"MODES");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);


	setfillstyle(1,8);
	bar(midx-50, midy-65, midx+50,midy-35);
	setcolor(8);
	fillellipse(midx-50,midy-50,15,15);
	fillellipse(midx+50,midy-50,15,15);
	setfillstyle(1,3);
	bar(midx-48, midy-63, midx+48,midy-37);
	setcolor(3);
	fillellipse(midx-48,midy-50,13,13);
	fillellipse(midx+48,midy-50,13,13);
	setcolor(15);
	outtextxy(midx-12,midy-52,"1024");

	setfillstyle(1,8);
	bar(midx-50, midy-30, midx+50,midy-0);
	setcolor(8);
	fillellipse(midx-50,midy-15,15,15);
	fillellipse(midx+50,midy-15,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy-28, midx+48,midy-2);
	setcolor(3);
	fillellipse(midx-48,midy-15,13,13);
	fillellipse(midx+48,midy-15,13,13);
	setcolor(15);
	outtextxy(midx-12,midy-17,"2048");

	setfillstyle(1,8);
	bar(midx-50, midy+5, midx+50,midy+35);
	setcolor(8);
	fillellipse(midx-50,midy+20,15,15);
	fillellipse(midx+50,midy+20,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy+7, midx+48,midy+33);
	setcolor(3);
	fillellipse(midx-48,midy+20,13,13);
	fillellipse(midx+48,midy+20,13,13);
	setcolor(15);
	outtextxy(midx-12,midy+18,"4096");

	setfillstyle(1,8);
	bar(midx-50, midy+40, midx+50,midy+70);
	setcolor(8);
	fillellipse(midx-50,midy+55,15,15);
	fillellipse(midx+50,midy+55,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy+42, midx+48,midy+68);
	setcolor(3);
	fillellipse(midx-48,midy+55,13,13);
	fillellipse(midx+48,midy+55,13,13);
	setcolor(15);
	outtextxy(midx-12,midy+53,"8192");

	status = initmouse();
	if ( status == 0 )
	{
		cleardevice();
		printf("Mouse support not available.\n");
	}
	else
	{
		showmouseptr();
		getmousepos(&button,&x,&y);
		while(!kbhit())
		{
			getmousepos(&button,&x,&y);
			if(button==1)
			{
				if(x>(midx-75)&&x<(midx+75))
				{
					if(y>(midy-68)&&y<(midy-37))
					{
						fUnCtIoN(1024);
					}
					else if(y>(midy-28)&&y<(midy-2))
					{
						fUnCtIoN(2048);
					}
					else if(y>(midy+7)&&y<(midy+33))
					{
						fUnCtIoN(4096);
					}
					else if(y>(midy+42)&&y<(midy+68))
					{
						fUnCtIoN(8192);
					}
				}
				button=-1;
			}
		}

	}

	getch();
	hidemouseptr();
	USERSCREEN();
	return 0;
}

int Instructions()
{
	int midx,midy,x,y,button,status;
	cleardevice();
	initmouse();
	hidemouseptr();

	midx=getmaxx()/2;
	midy=getmaxy()/2;

	setbkcolor(15);

	setfillstyle(1,8);
	bar(0, 0, getmaxx(),130);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
	outtextxy(midx-150,80,"INSTRUCTIONS");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	setfillstyle(1,8);
	bar(midx-75, midy-75, midx+75,midy+75);
	setcolor(8);
	fillellipse(midx-75,midy,75,75);
	fillellipse(midx+75,midy,75,75);
	setfillstyle(1,3);
	bar(midx-73, midy-73, midx+73,midy+73);
	setcolor(3);
	fillellipse(midx-73,midy,73,73);
	fillellipse(midx+73,midy,73,73);
	setcolor(15);
	outtextxy(midx-60,midy-20," Join the numbers ");
	outtextxy(midx-60,midy,   "        &         ");
	outtextxy(midx-60,midy+20,"get the 2048 tile !");

	getch();
	USERSCREEN();
	return 0;
}

int Statistics()
{
	FILE *fp;
	int midx,midy,x,y,button,status;
	int highscore;
	char a[7];
	cleardevice();
	initmouse();
	hidemouseptr();

	midx=getmaxx()/2;
	midy=getmaxy()/2;

	setbkcolor(15);

	setfillstyle(1,8);
	bar(0, 0, getmaxx(),130);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
	outtextxy(midx-130,80,"STATISTICS");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	setfillstyle(1,8);
	bar(midx-50, midy-30, midx+50,midy-0);
	setcolor(8);
	fillellipse(midx-50,midy-15,15,15);
	fillellipse(midx+50,midy-15,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy-28, midx+48,midy-2);
	setcolor(3);
	fillellipse(midx-48,midy-15,13,13);
	fillellipse(midx+48,midy-15,13,13);
	setcolor(15);
	outtextxy(midx-40,midy-17,"BEST SCORE :");

	setfillstyle(1,8);
	bar(midx-50, midy+5, midx+50,midy+35);
	setcolor(8);
	fillellipse(midx-50,midy+20,15,15);
	fillellipse(midx+50,midy+20,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy+7, midx+48,midy+33);
	setcolor(3);
	fillellipse(midx-48,midy+20,13,13);
	fillellipse(midx+48,midy+20,13,13);
	setcolor(15);

	fp=fopen("Stats.dat","r");
	if(fp==NULL)
		highscore=0;
	else
		highscore=getw(fp);
	fclose(fp);
	gcvt(highscore,7,a);
	outtextxy(midx-10,midy+18,a);
	getch();
	USERSCREEN();
	return 0;
}

int Architects()
{
	int midx,midy,x,y,button,status;
	cleardevice();
	initmouse();
	hidemouseptr();

	midx=getmaxx()/2;
	midy=getmaxy()/2;

	setbkcolor(15);

	setfillstyle(1,8);
	bar(0, 0, getmaxx(),130);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
	outtextxy(midx-150,80,"ARCHITECTS");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);


	setfillstyle(1,8);
	bar(midx-50, midy-65, midx+50,midy-35);
	setcolor(8);
	fillellipse(midx-50,midy-50,15,15);
	fillellipse(midx+50,midy-50,15,15);
	setfillstyle(1,3);
	bar(midx-48, midy-63, midx+48,midy-37);
	setcolor(3);
	fillellipse(midx-48,midy-50,13,13);
	fillellipse(midx+48,midy-50,13,13);
	setcolor(15);
	outtextxy(midx-30,midy-52,"CHINMAY");

	setfillstyle(1,8);
	bar(midx-50, midy-30, midx+50,midy-0);
	setcolor(8);
	fillellipse(midx-50,midy-15,15,15);
	fillellipse(midx+50,midy-15,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy-28, midx+48,midy-2);
	setcolor(3);
	fillellipse(midx-48,midy-15,13,13);
	fillellipse(midx+48,midy-15,13,13);
	setcolor(15);
	outtextxy(midx-30,midy-17,"SHAURYA");

	setfillstyle(1,8);
	bar(midx-50, midy+5, midx+50,midy+35);
	setcolor(8);
	fillellipse(midx-50,midy+20,15,15);
	fillellipse(midx+50,midy+20,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy+7, midx+48,midy+33);
	setcolor(3);
	fillellipse(midx-48,midy+20,13,13);
	fillellipse(midx+48,midy+20,13,13);
	setcolor(15);
	outtextxy(midx-30,midy+18,"SHUBHAM");
	getch();
	USERSCREEN();
	return 0;
}

int CrEaTe_MaIn()
{
	TiLe *sTiLe,*ssTiLe;
	int i=0;
	for(i=0;i<4;i++)
	{
		sTiLe=(TiLe *)malloc(sizeof(TiLe));
		sTiLe->DaTa=0;
		sTiLe->right=sTiLe->down=sTiLe->left=sTiLe->up=NULL;
		if(sTaRt==NULL)
			sTaRt=sTiLe;
		else
		{
			temp=sTaRt;
			while(temp->down!=NULL)
				temp=temp->down;
			temp->down=sTiLe;
			sTiLe->up=temp;
		}
	}
	temp=sTaRt;
	temp1=NULL;
	while(temp!=NULL)
	{
		for(i=0;i<3;i++)
		{
			ssTiLe=(TiLe *)malloc(sizeof(TiLe));
			ssTiLe->DaTa=0;
			ssTiLe->right=ssTiLe->down=ssTiLe->left=ssTiLe->up=NULL;
			if(temp1==NULL)
			{
				temp->right=ssTiLe;
				ssTiLe->left=temp;
				temp1=ssTiLe;
			}
			else
			{
				temp1->right=ssTiLe;
				ssTiLe->left=temp1;
				temp1=ssTiLe;
			}
		}
		temp=temp->down;
		temp1=NULL;
	}

	temp=sTaRt;
	while(temp->down!=NULL)
	{
		temp1=temp->right;
		temp2=temp->down->right;
		while(temp1!=NULL)
		{
			temp1->down=temp2;
			temp2->up=temp1;
			temp1=temp1->right;
			temp2=temp2->right;
		}
		temp=temp->down;
	}
	return 0;
}

int SetLocation()
{
	int L=1;
	temp1=sTaRt;
	while(temp1!=NULL)
	{
		temp=temp1;
		while(temp!=NULL)
		{
			temp->Location=L;
			L++;
			temp=temp->right;
		}
		temp1=temp1->down;
	}
	return 0;
}

int DiSpLaY()
{
	int midx=getmaxx()/2;
	int midy=getmaxy()/2;

	setviewport(midx-125, midy-100, midx+125,midy+150,1);
	setfillstyle(1,8);
	bar(0,0,250,250);
	setfillstyle(1,7);
	bar(5,5,245,245);

	temp1=sTaRt;
	while(temp1!=NULL)
	{
		temp=temp1;
		while(temp!=NULL)
		{
			CoLoR_sTyLe(temp->DaTa,temp->Location);
			temp=temp->right;
		}
		temp1=temp1->down;
	}
	return 0;
}

int CoLoR_sTyLe(int DaTa,int Location)
{
	int fillstyle;
	char disp[6];
	switch(DaTa)
	{
		case 0:fillstyle=0;
			strcpy(disp,"0");
			break;
		case 2:fillstyle=11;
			strcpy(disp,"2");
			break;
		case 4:fillstyle=10;
			strcpy(disp,"4");
			break;
		case 8:fillstyle=12;
			strcpy(disp,"8");
			break;
		case 16:fillstyle=14;
			strcpy(disp,"16");
			break;
		case 32:fillstyle=13;
			strcpy(disp,"32");
			break;
		case 64:fillstyle=6;
			strcpy(disp,"64");
			break;
		case 128:fillstyle=3;
			strcpy(disp,"128");
			break;
		case 256:fillstyle=9;
			strcpy(disp,"256");
			break;
		case 512:fillstyle=2;
			strcpy(disp,"512");
			break;
		case 1024:fillstyle=5;
			strcpy(disp,"1024");
			break;
		case 2048:fillstyle=4;
			strcpy(disp,"2048");
			break;
		case 4096:fillstyle=1;
			strcpy(disp,"4096");
			break;
		case 8192:fillstyle=8;
			strcpy(disp,"8192");
	}
	setfillstyle(1,fillstyle);
	switch(Location)
	{
		case 1:bar(13, 13, 63,63);
			outtextxy(38,38,disp);
			break;
		case 2:bar(71, 13, 121,63);
			outtextxy(88,38,disp);
			break;
		case 3:bar(129, 13, 179,63);
			outtextxy(138,38,disp);
			break;
		case 4:bar(187, 13, 237,63);
			outtextxy(188,38,disp);
			break;
		case 5:bar(13, 71, 63,121);
			outtextxy(38,88,disp);
			break;
		case 6:bar(71, 71, 121,121);
			outtextxy(88,88,disp);
			break;
		case 7:bar(129, 71, 179,121);
			outtextxy(138,88,disp);
			break;
		case 8:bar(187, 71, 237,121);
			outtextxy(188,88,disp);
			break;
		case 9:bar(13, 129,63,179);
			outtextxy(38,138,disp);
			break;
		case 10:bar(71, 129, 121,179);
			outtextxy(88,138,disp);
			break;
		case 11:bar(129, 129, 179,179);
			outtextxy(138,138,disp);
			break;
		case 12:bar(187, 129, 237,179);
			outtextxy(188,138,disp);
			break;
		case 13:bar(13, 187, 63,237);
			outtextxy(38,188,disp);
			break;
		case 14:bar(71, 187, 121,237);
			outtextxy(88,188,disp);
			break;
		case 15:bar(129, 187, 179,237);
			outtextxy(138,188,disp);
			break;
		case 16:bar(187, 187, 237,237);
			outtextxy(188,188,disp);
			break;
	}
	return 0;
}

int fUnCtIoN(int mode)
{
	char press;
	int status=-2,flag=0;
	int SCORE=0;
	int i,midx,midy;

	cleardevice();
	setbkcolor(15);
	setfillstyle(1,8);
	bar(0, 0, getmaxx(),130);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
	outtextxy(midx-50,80,"2048");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	initmouse();
	hidemouseptr();

	midx=getmaxx()/2;
	midy=getmaxy()/2;

	//CrEaTiOn oF mUlTi lInK lIsT
	CrEaTe_MaIn();
	SetLocation();

	setviewport(midx-125, midy-100, midx+125,midy+150,1);
	setfillstyle(1,8);
	bar(0,0,250,250);
	setfillstyle(1,7);
	bar(5,5,245,245);

	//TrAvErSaL oF mUlTi lInK lIsT
	for(i=0;i<2;i++)
		GeNeRaTe_RaNdOm();
	DiSpLaY();
	_setcursortype(_NOCURSOR);

	sTaRtU=sTaRt;
	sTaRtD=sTaRt->down->down->down;
	sTaRtL=sTaRt;
	sTaRtR=sTaRt->right->right->right;

	do{
		if(kbhit())
		{
			press=getch();
			status=GaMe_OvEr(mode);
			if(status==0)
			{
			//uP aRrOw KeY
			if(press==72)
			{
				flag=0;
				p1=sTaRtU;
				while(p1!=NULL)
				{
					p2=p1;
					p3=p1;
					while(p2!=NULL)
					{
						if(p2->DaTa==0)
						{
							sHiFt_uP(p2);
						}
						p2=p2->down;
					}
					while(p3->down->DaTa!=0)
					{
						if(p3->DaTa==p3->down->DaTa)
						{
							p3->DaTa=(p3->DaTa)*2;
							p3->down->DaTa=0;
							SCORE=SCORE+(p3->DaTa);
							sHiFt_uP(p3->down);
							flag=1;
						}
						p3=p3->down;
					}
					p1=p1->right;
				}
				clearviewport();
				DiSpLaY();
				delay(200);
				clearviewport();
				GeNeRaTe_RaNdOm();
				DiSpLaY();
			}

			//dOwN aRrOw KeY
			if(press==80)
			{
				flag=0;
				p1=sTaRtD;
				while(p1!=NULL)
				{
					p2=p1;
					p3=p1;
					while(p2!=NULL)
					{
						if(p2->DaTa==0)
						{
							sHiFt_dOwN(p2);
						}
						p2=p2->up;
					}
					while(p3->up->DaTa!=0)
					{
						if(p3->DaTa==p3->up->DaTa)
						{
							p3->DaTa=(p3->DaTa)*2;
							p3->up->DaTa=0;
							SCORE=SCORE+(p3->DaTa);
							sHiFt_dOwN(p3->up);
							flag=1;
						}
						p3=p3->up;
					}
					p1=p1->right;
				}
				clearviewport();
				DiSpLaY();
				delay(200);
				clearviewport();
				GeNeRaTe_RaNdOm();
				DiSpLaY();
			}

			//lEfT aRrOw KeY
			if(press==75)
			{
				flag=0;
				p1=sTaRtL;
				while(p1!=NULL)
				{
					p2=p1;
					p3=p1;
					while(p2!=NULL)
					{
						if(p2->DaTa==0)
						{
							sHiFt_lEfT(p2);
						}
						p2=p2->right;
					}
					while(p3->right->DaTa!=0)
					{
						if(p3->DaTa==p3->right->DaTa)
						{
							p3->DaTa=(p3->DaTa)*2;
							p3->right->DaTa=0;
							SCORE=SCORE+(p3->DaTa);
							sHiFt_lEfT(p3->right);
							flag=1;
						}
						p3=p3->right;
					}
					p1=p1->down;
				}
				clearviewport();
				DiSpLaY();
				delay(200);
				clearviewport();
				GeNeRaTe_RaNdOm();
				DiSpLaY();
			}

			//RiGhT aRrOw KeY
			if(press==77)
			{
				flag=0;
				p1=sTaRtR;
				while(p1!=NULL)
				{
					p2=p1;
					p3=p1;
					while(p2!=NULL)
					{
						if(p2->DaTa==0)
						{
							sHiFt_rIgHt(p2);
						}
						p2=p2->left;
					}
					while(p3->left->DaTa!=0)
					{
						if(p3->DaTa==p3->left->DaTa)
						{
							p3->DaTa=(p3->DaTa)*2;
							p3->left->DaTa=0;
							SCORE=SCORE+(p3->DaTa);
							sHiFt_rIgHt(p3->left);
							flag=1;
						}
						p3=p3->left;
					}
					p1=p1->down;
				}
				clearviewport();
				DiSpLaY();
				delay(200);
				clearviewport();
				GeNeRaTe_RaNdOm();
				DiSpLaY();
			}
			}
			else if(status==1)
			{
				press=27;
			}
			else if(status==-1)
			{
				press=27;
			}

		}
	}while(press!=27);
	clearviewport();
	setviewport(midx-125, midy-100, midx+125,midy+150,0);
	setviewport(0, 0, getmaxx(),getmaxy(),1);
	cleardevice();
	Scoreboard(SCORE,status);
	return 0;
}

void sHiFt_uP(TiLe *P)
{
	while(P->down!=NULL)
	{
		P->DaTa=P->down->DaTa;
		P->down->DaTa=0;
		if(P->DaTa==0)
		{
			P->DaTa=P->down->down->DaTa;
			P->down->down->DaTa=0;
			if(P->DaTa==0)
			{
				P->DaTa=P->down->down->down->DaTa;
				P->down->down->down->DaTa=0;
			}
		}
		P=P->down;
	}
}

void sHiFt_dOwN(TiLe *P)
{
	while(P->up!=NULL)
	{
		P->DaTa=P->up->DaTa;
		P->up->DaTa=0;
		if(P->DaTa==0)
		{
			P->DaTa=P->up->up->DaTa;
			P->up->up->DaTa=0;
			if(P->DaTa==0)
			{
				P->DaTa=P->up->up->up->DaTa;
				P->up->up->up->DaTa=0;
			}
		}
		P=P->up;
	}
}

void sHiFt_lEfT(TiLe *P)
{
	while(P->right!=NULL)
	{
		P->DaTa=P->right->DaTa;
		P->right->DaTa=0;
		if(P->DaTa==0)
		{
			P->DaTa=P->right->right->DaTa;
			P->right->right->DaTa=0;
			if(P->DaTa==0)
			{
				P->DaTa=P->right->right->right->DaTa;
				P->right->right->right->DaTa=0;
			}
		}
		P=P->right;
	}
}

void sHiFt_rIgHt(TiLe *P)
{
	while(P->left!=NULL)
	{
		P->DaTa=P->left->DaTa;
		P->left->DaTa=0;
		if(P->DaTa==0)
		{
			P->DaTa=P->left->left->DaTa;
			P->left->left->DaTa=0;
			if(P->DaTa==0)
			{
				P->DaTa=P->left->left->left->DaTa;
				P->left->left->left->DaTa=0;
			}
		}
		P=P->left;
	}
}

int GaMe_OvEr(int mode)
{
	int status=-2,flag=0;
	temp1=sTaRt;
	while(temp1!=NULL)
	{
		temp=temp1;
		while(temp!=NULL)
		{
			if(temp->DaTa==mode)
			{
				status=1;
				break;
			}
			if(temp->DaTa==temp->right->DaTa||temp->DaTa==temp->down->DaTa||temp->DaTa==0)
			{
				flag=1;
			}
			temp=temp->right;
		}
		if(status==1)
			break;
		temp1=temp1->down;
	}
	if(flag==1&&status==-2)
		status=0;
	else if(flag==0&&status==-2)
		status=-1;
	return status;
}

int GeNeRaTe_RaNdOm()
{
	int A[]={2,2,2,2,2,2,2,2,2,4};
	int L;
	int flag=0;
	randomize();
	label:L=random(16)+1;
	temp1=sTaRt;
	while(temp1!=NULL)
	{
		temp=temp1;
		while(temp!=NULL)
		{
			if(temp->Location==L)
			{
				if(temp->DaTa==0)
				{
					temp->DaTa=A[random(10)];
					flag=1;
					break;
				}
			}
			temp=temp->right;
		}
		temp1=temp1->down;
	}
	if(flag==0)
		goto label;
	return 0;
}

int Scoreboard(int score,int status)
{
	int midx,midy,x,y,button;
	char a[7];
	cleardevice();

	midx=getmaxx()/2;
	midy=getmaxy()/2;

	setbkcolor(15);

	setfillstyle(1,8);
	bar(0, 0, getmaxx(),130);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
	outtextxy(midx-140,80,"SCOREBOARD");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	if(status==1)
	{
		setcolor(0);
		outtextxy(midx-40,midy-25,"   YOU WIN !!! ");
	}
	else if(status==-1)
	{
		setcolor(0);
		outtextxy(midx-40,midy-25,"   YOU LOSE !!! ");
	}

	setfillstyle(1,8);
	bar(midx-50, midy-30, midx+50,midy-0);
	setcolor(8);
	fillellipse(midx-50,midy-15,15,15);
	fillellipse(midx+50,midy-15,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy-28, midx+48,midy-2);
	setcolor(3);
	fillellipse(midx-48,midy-15,13,13);
	fillellipse(midx+48,midy-15,13,13);
	setcolor(15);
	outtextxy(midx-40,midy-17,"YOUR SCORE :");

	setfillstyle(1,8);
	bar(midx-50, midy+5, midx+50,midy+35);
	setcolor(8);
	fillellipse(midx-50,midy+20,15,15);
	fillellipse(midx+50,midy+20,15,15);
	setfillstyle(1,3);
	setfillstyle(1,3);
	bar(midx-48, midy+7, midx+48,midy+33);
	setcolor(3);
	fillellipse(midx-48,midy+20,13,13);
	fillellipse(midx+48,midy+20,13,13);
	setcolor(15);
	gcvt(score,7,a);
	outtextxy(midx-20,midy+18,a);
	getch();
	Evaluate(score);
	USERSCREEN();
	return 0;
}

int Evaluate(int score)
{
	FILE *fp1,*fp2;
	int highscore;
	fp1=fopen("Stats.dat","r");
	if(fp1==NULL)
	{
		fp2=fopen("Stats.dat","w");
		putw(score,fp2);
		fclose(fp2);
	}
	else
	{
		highscore=getw(fp1);
		if(highscore<score)
		{
			fp2=fopen("temp.dat","w");
			putw(score,fp2);
			fclose(fp2);
			fclose(fp1);
			remove("Stats.dat");
			rename("temp.dat","Stats.dat");
		}
		else
			fclose(fp1);
	}
	return 0;
}