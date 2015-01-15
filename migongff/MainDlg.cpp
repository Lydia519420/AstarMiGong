#include "stdafx.h"
#include <windows.h>
#include <mmsystem.h>
#include <windowsx.h>
#include <stdlib.h>
#include "resource.h"
#include "MainDlg.h"
#pragma comment(lib, "WINMM.LIB")

#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>
int deep=0;//��ʾ���
int deep_Flag;//��ʾ��ȱ�־
 
struct mark //�����Թ��ڵ���������� 
{ 
	int x; 
	int y; 
}; 
struct mark start,end; //start,end��ںͳ��ڵ����� 

   

	
struct Element //ջԪ�أ� 
{ 
		double f;//���ۺ���
	double g;//����
	double h;//��������
	int x,y; //x��,y�� 
	//int d; //d��һ���ķ��� 
}; 

	Element elem,e; 

typedef struct LStack //��ջ 
{ 

	Element elem; 
	struct LStack *next; 
}*PLStack; 

	PLStack Open,Close; 
    PLStack S1,S2;
/*************ջ����****************/ 
int InitStack(PLStack &S)
{
	S=NULL;
	return 1;
}


int InitStack1(PLStack &S)//�����ջ 
{ 
	//S=NULL;
	S=(PLStack)malloc(sizeof(LStack));
	S->elem.g=0;
	S->elem.h=sqrt(((end.x-start.x)*(end.x-start.x)+(end.y-start.y)*(end.y-start.y)));
	S->elem.f=S->elem.h;
	S->elem.x=start.x;
	S->elem.y=start.y;

    S->next=NULL;
	return 1; 
} 

int StackEmpty(PLStack S)//�ж�ջ�Ƿ�Ϊ�� 
{ 
	if(S==NULL) 
		return 1; 
	else 
		return 0; 
} 

int Push(PLStack &S, Element e)//ѹ��������Ԫ�� 
{ 
	PLStack p; 
	p=(PLStack)malloc(sizeof(LStack)); 
	p->elem=e; 
	p->next=S; 
	S=p; 
	return 1; 
} 

int Push1(PLStack &S, Element e)//ѹ��������Ԫ�� 
{ 
	//float g0,f0,h0;
	PLStack p; 
	PLStack q,t;

	p=(PLStack)malloc(sizeof(LStack));
	p->elem.g=deep;//��ʾ���
//	p->elem.h=sqrt(((end.x-e.x)*(end.x-e.x)+(end.y-e.y)*(end.y-e.y))*1.0);
	p->elem.h=abs(end.x-e.x)+abs(end.y-e.y);
	p->elem.f=p->elem.h+p->elem.g;
//	p->elem=e; 
	p->elem.x=e.x;
	p->elem.y=e.y;
	p->next=NULL;

	if(NULL==S||p->elem.f<=S->elem.f)
	{
		p->next=S;
		S=p;
		//return 1;
	}
	else
	{
		//if(p->elem.f<S->elem.f)
	//	{
	////		p->next=S;
	//		S=p;
	//	}
	//	else{
			q=S;
			t=q->next;
			while(t!=NULL)
			{
				//t=q;
			//	q=q->next;
				if(p->elem.f>t->elem.f)
				{
					q=t;
					t=t->next;
				}
				else
					break;
			}
			p->next=t;
			q->next=p;
	//	}
	}
	return 1;
	

} 

int Pop(PLStack &S,Element &e) //ջ��Ԫ�س�ջ 
{ 
	PLStack p; 
	if(!StackEmpty(S)) 
	{ 
		e=S->elem; 
		p=S; 
		S=S->next; 
		free(p); 
		return 1; 
	} 
	else 
		return 0; 
} 
int maze[18][25];
int maze1[18][25]={
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,1,1,1,0,0,1,0,1,0,0,1,1,0,1,1,1,0,1,1,1,0,1},
			{1,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,1},
			{1,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1},
			{1,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,1,0,1,0,1},
			{1,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,1},
			{1,0,0,1,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,1,1,1},
			{1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1},
			{1,0,1,1,1,1,0,1,0,1,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1},
			{1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,1},
			{1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1},
			{1,0,0,0,1,1,1,1,0,1,0,0,1,1,0,1,0,1,0,1,0,0,1,0,1},
			{1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1},
			{1,0,0,1,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,1},
			{1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,0,0,0,0,1,0,1},
			{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};
int maze2[18][25]={
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,1,1,1,0,0,1,0,1,0,0,1,1,0,1,1,1,1,1,1,1,0,1},
			{1,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,1},
			{1,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0,1},
			{1,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,1,0,1,0,1},
			{1,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,1},
			{1,0,0,1,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,1,1,1},
			{1,1,0,0,1,1,0,1,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1},
			{1,0,1,1,1,1,0,1,0,1,1,0,1,0,0,0,0,1,0,1,0,1,1,0,1},
			{1,1,0,1,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1,0,0,0,0,1},
			{1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1},
			{1,0,0,0,1,1,1,1,0,1,0,0,1,1,0,1,0,1,0,1,0,0,1,0,1},
			{1,0,0,1,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,1,0,0,1,0,1},
			{1,0,0,1,0,0,1,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,1,0,1},
			{1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,0,0,0,0,1,0,1},
			{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};
int maze3[18][25]={
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,1,1,1},
			{1,1,0,1,1,1,0,0,1,0,1,0,0,1,0,1,1,1,0,1,1,1,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1,0,1},
			{1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1},
			{1,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,1,0,1,0,1,0,1},
			{1,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,1},
			{1,0,0,1,1,0,0,1,0,1,0,1,0,1,1,1,0,1,0,0,0,0,1,1,1},
			{1,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,1,1,1,0,1},
			{1,0,1,1,1,1,0,1,0,1,1,0,1,0,0,1,0,1,0,0,0,1,1,0,1},
			{1,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,0,1,1,1,0,0,0,0,1},
			{1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,0,0,1},
			{1,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,1,0,1},
			{1,0,0,1,0,0,0,1,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1},
			{1,0,0,1,0,0,1,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,1,0,1},
			{1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,0,1,0,0,0,0,0,0,1},
			{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};
int maze4[18][25]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

};
int add[4][2]={{1,0},{0,1},{-1,0},{0,-1}};//�������������� ��������Ϊ�����ϱ� 


int Flag=0;//��־  �����жϳ������û��
int M_Flag=0;//��־�������жϵ�ͼ����û��

int p_Lsize=32;//СͼƬ�ĳ���
int p_Hsize=31;//СͼƬ�Ŀ��



int MazePath(int maze[18][25]) 
{ 

	struct mark start,end; //start,end��ںͳ��ڵ����� 


	start.x=1;
	start.y=0;
	end.x=16;
	end.y=24;

	int i,j,d;
	int a,b; 





	InitStack(S1); 
	InitStack(S2); 

	maze[start.x][start.y]=2; //��ڵ����ϱ�� 
	elem.x=start.x; 
	elem.y=start.y; 
	//elem.d=-1; //��ʼΪ-1 

	Push(S1,elem); 
	while(!StackEmpty(S1)) //ջ��Ϊ�� ��·������ 
	{ 
		Pop(S1,elem); 
		i=elem.x; 
		j=elem.y; 
	//	d=elem.d+1; //��һ������ 
		while(d<4) //��̽���������������� 
		{ 
		a=i+add[d][0]; 
		b=j+add[d][1]; 
		if(a==end.x && b==end.y && maze[a][b]==0) //������˳��� 
		{ 
			elem.x=i; 
			elem.y=j; 
		//	elem.d=d; 
			Push(S1,elem); 
			elem.x=a; 
			elem.y=b; 
		//	elem.d=8; //�������Ϊ-1 �ж��Ƿ��˳��� 
			Push(S1,elem); 

			while(S1) //�������� ������Թ�·������ 
			{ 
				Pop(S1,e); 
				Push(S2,e); 
			} 

		//	while(S2) 
		//	{ 
		//		Pop(S2,e); 
			//	printf("-->(%d,%d,%d)",e.x,e.y,e.d);

		//		maze[e.x][e.y] = 9;
		//	} 
			//	system("PAUSE"); 
			return 0;  
		} 

		if(maze[a][b]==0) //�ҵ�����ǰ���ķǳ��ڵĵ� 
		{ 
			maze[a][b]=2; //����߹��˵� 
			elem.x=i; 
			elem.y=j; 
		//	elem.d=d; 
			Push(S1,elem); //��ǰλ����ջ 
			i=a; //��һ��ת��Ϊ��ǰ�� 
			j=b; 
			//d=-1; 
		} 
		//	d++; 
	} 
	} 
	printf("\n");
	return 0;
}

int Judge(Element e,PLStack Close)//���ڲ鿴����չ�Ľڵ��Ƿ��Ѿ�������close����
{
	PLStack P;
	P=Close;
    while(Close!=NULL)
	{
		if((Close->elem.x==e.x)&&(Close->elem.y==e.y))//˵���Ѿ����ڸýڵ�
			return 0;
		Close=Close->next;

	}
	Close=P;
	return 1;
}

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
	case WM_LBUTTONDOWN:

		
		break;
	default :
		break;
    }

    return FALSE;
}

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
    return TRUE;
}

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
//	PlaySound("SystemStart",NULL,SND_ALIAS|SND_ASYNC);

   	 int i,j;
	// int line = 0;//������¼����
//	 int row=0;//������¼����
	 //FILE *Fp = NULL;  //�������ļ�
/*	 if((Fp = fopen("E:\\maze2.txt","r")) == NULL) 
	 {
		 MessageBox(NULL,TEXT("��ͼ�������,ע���Ƿ�����е�ͼ�ļ���"),TEXT("Error!"),0);
		 exit(0);
	 }
	  
	while (!feof(Fp))
	{
		for(row=0;row<25;row++)
			fscanf(Fp,"%d",&maze[line][row]);
		line++;
	  
	}
/*	int maze[18][25]={
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,1,1,1,0,0,1,0,1,0,0,1,1,0,1,1,1,1,1,1,1,0,1},
			{1,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,1},
			{1,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1},
			{1,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,1,0,1,0,1},
			{1,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,1},
			{1,0,0,1,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,1,1,1},
			{1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1},
			{1,0,1,1,1,1,0,1,0,1,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1},
			{1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,1},
			{1,1,0,0,0,0,0,0,0,1,1,0,0,1,0,1,0,1,0,1,0,0,0,0,1},
			{1,0,0,0,1,1,1,1,0,1,0,0,1,1,0,1,0,1,0,1,0,0,1,0,1},
			{1,0,0,1,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,1,0,0,1,0,1},
			{1,0,0,1,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,1},
			{1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,0,0,0,0,1,0,1},
			{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};*/
   
		HWND hmap,h1,h3,h5,h7;
	    HDC hm,h2,h4,h6,h8;
     	hmap = GetDlgItem(hwnd,IDC_MAP);
		hm = GetDC(hmap);
			h1 = GetDlgItem(hwnd,IDC_P1);
			h2 = GetDC(h1);
				h3 = GetDlgItem(hwnd,IDC_P2);
				h4 = GetDC(h3);
					h5 = GetDlgItem(hwnd,IDC_P3);
					h6 = GetDC(h5);
						h7 = GetDlgItem(hwnd,IDC_P4);
						h8 = GetDC(h7);

	if(IsDlgButtonChecked(hwnd,IDC_M1)>0)
	{
		//	 MessageBox(NULL,TEXT("h"),TEXT("hello"),0);
		/*
     	 if((Fp = fopen("E:\\maze0.txt","r")) == NULL) 
		 {
		 MessageBox(NULL,TEXT("��ͼ�������,ע���Ƿ�����е�ͼ�ļ���"),TEXT("Error!"),0);
		 exit(0);
		 }
		 */
		for(i=0;i<18;i++)
			for(j=0;j<25;j++)
				maze[i][j]=maze1[i][j];
	  
	}
	else if(IsDlgButtonChecked(hwnd,IDC_M2)>0)
	{
		for(i=0;i<18;i++)
			for(j=0;j<25;j++)
				maze[i][j]=maze2[i][j];
	  
	  

	}
    else if(IsDlgButtonChecked(hwnd,IDC_M3)>0)
	{
		for(i=0;i<18;i++)
			for(j=0;j<25;j++)
				maze[i][j]=maze3[i][j];
	  
	  

	}

	
		
    switch(id)
    {
        case IDC_GO:

			if(1==M_Flag)
			{
				MessageBox(NULL,TEXT("�Թ��Ѿ�������!"),TEXT("�Թ��Ѿ�����!"),0);
				break;
			}
			if((0==IsDlgButtonChecked(hwnd,IDC_M1))&&(0==IsDlgButtonChecked(hwnd,IDC_M2))&&(0==IsDlgButtonChecked(hwnd,IDC_M3)))
			{
				MessageBox(NULL,TEXT("��ѡ���Թ����Թ�����Ϊ��!"),TEXT("С��!"),0);
				break;
			}
			/*
				while (!feof(Fp))
				{
			for(row=0;row<25;row++)
				fscanf(Fp,"%d",&maze[line][row]);
			line++;
				}
				*/

			

				for(j=0;j<25;j++)
				{
                    BitBlt(hm,j*32,0,p_Lsize,p_Hsize,h6,0,0,SRCCOPY);
					Sleep(10);
				}
				for(i=0;i<18;i++)
				{
                    BitBlt(hm,24*32,i*32,p_Lsize,p_Hsize,h6,0,0,SRCCOPY);
					Sleep(10);
				}
				for(j=24;j>=0;j--)
				{
                    BitBlt(hm,j*32,17*32,p_Lsize,p_Hsize,h6,0,0,SRCCOPY);
					Sleep(10);
				}
				for(i=17;i>=0;i--)
				{
                    BitBlt(hm,0,i*32,p_Lsize,p_Hsize,h6,0,0,SRCCOPY);
					Sleep(10);
				}
				for(i=1;i<17;i++){
					for(j=1;j<24;j++){
						if(maze[i][j]==1)
						{
                           BitBlt(hm,j*32,i*32,p_Lsize,p_Hsize,h8,0,0,SRCCOPY);
						   Sleep(5);
						}
					/*	else
						{
							BitBlt(hm,j*32,i*32,p_Lsize,p_Hsize,h4,0,0,SRCCOPY);
							Sleep(50);
						}*/
					}
				}

                BitBlt(hm,0,32,p_Lsize,p_Hsize,h4,0,0,SRCCOPY); //�����
				Sleep(100);
				BitBlt(hm,24*32,16*32,p_Lsize,p_Hsize,h4,0,0,SRCCOPY);//������
				Sleep(100);
			   /*    	MazePath(maze);
                      while(S2) 
					{ 
						Pop(S2,e);
		            
					
					
						BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	PlaySound("E:\\music\\walk.wav", NULL, SND_FILENAME | SND_ASYNC);

					//	SetTimer(hwnd,0,2000,NULL);
						Sleep(250);
						BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h4,0,0,SRCCOPY);
					 }*/
				M_Flag=1;
					  	
						Sleep(100);
						
			        	MessageBox(NULL,TEXT("��ͼ�Ѿ����ã�����ð����!"),TEXT("��ͼ���"),0);
          break;

		case IDC_GO1:
             
			if(0==M_Flag)
			{
				MessageBox(NULL,TEXT("��ͼ��û�л��ã����Ȼ��õ�ͼ!"),TEXT("���Ȼ��õ�ͼ!"),0);
				break;
			}
			Flag=0;



	
	//int add[4][2]={{1,0},{0,1},{-1,0},{0,-1}};//�������������� ��������Ϊ�����ϱ� 

	 start.x=1;
	start.y=0;
	end.x=16;
	end.y=24;

	InitStack(Open); //����open ��
	InitStack(Close); //����close��

	//maze[start.x][start.y]=2; //��ڵ����ϱ�� 
	elem.x=start.x; 
	elem.y=start.y; 
	

	Push(Open,elem); //��ʼ�ڵ����open��

	while(!StackEmpty(Open)&&Flag==0) //ջ��Ϊ�� ��·������ 
	{ 
		Pop(Open,elem); //��open���еĵ�ǰԪ�������

	             	BitBlt(hm,32+(elem.y-1)*32,32+(elem.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
						Sleep(100);
					BitBlt(hm,32+(elem.y-1)*32,32+(elem.x-1)*32,33,33,h4,0,0,SRCCOPY);

		Push(Close,elem);//����open��ȡ������Ԫ�ط���close��
		//��չ��Ԫ�ص������ӽڵ�
		//�����ر��ע�⣬����Ԫ�ص���������浱���ӽڵ㣬���е�Ԫ�ض�����
    	//�ж����ӽ������ӽڵ��ǲ��ǿ�����,���еĻ��ͽ����ӽڵ���open��
		
			if(0==maze[elem.x][elem.y+1]&&0==Flag)
			{
				
				e.x=elem.x;
				e.y=elem.y+1;
			

				if(Judge(e,Close))
					Push(Open,e);
				if(e.x==end.x&&e.y==end.y)//�жϸõ��ǲ����յ�
				{
					Flag=1;//��ʾ�����Ѿ��ҵ�Ŀ����
						Pop(Open,e);
					Push(Close,e);

					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
			 		Sleep(50);
					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h4,0,0,SRCCOPY);

				
					Sleep(100);
							//	Sleep(1000);
					
    				MessageBox(NULL,TEXT("��ϲ"),TEXT("��ϲС����"),0);
				}
			}
			if(0==maze[elem.x+1][elem.y]&&0==Flag)
			{
				e.x=elem.x+1;
				e.y=elem.y;
				if(Judge(e,Close))
					Push(Open,e);
				if(e.x==end.x&&e.y==end.y)
				{
					Flag=1;//��ʾ�����Ѿ��ҵ�Ŀ����
					Pop(Open,e);
					Push(Close,e);
						BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
			 		Sleep(50);
					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h4,0,0,SRCCOPY);

		
					Sleep(100);
							//	Sleep(1000);
				
    				MessageBox(NULL,TEXT("��ϲ"),TEXT("��ϲС����"),0);
				}
			}
		  
            if(0==maze[elem.x-1][elem.y]&&0==Flag)
			{
				e.x=elem.x-1;
				e.y=elem.y;
				if(Judge(e,Close))
					Push(Open,e);
				if(e.x==end.x&&e.y==end.y)
				{
					Flag=1;//��ʾ��;���Ѿ��ҵ�Ŀ����
					Pop(Open,e);
					Push(Close,e);
						BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
			 		Sleep(50);
					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h4,0,0,SRCCOPY);
				
					Sleep(100);
							//	Sleep(1000);
				
    				MessageBox(NULL,TEXT("��ϲ"),TEXT("��ϲС����"),0);
				}
			}
			if(0==maze[elem.x][elem.y-1]&&0==Flag)
			{
				e.x=elem.x;
				e.y=elem.y-1;
				if(Judge(e,Close))
					Push(Open,e);
				if(e.x==end.x&&e.y==end.y)
				{
					Flag=1;//��ʾ�����Ѿ��ҵ�Ŀ����
						Pop(Open,e);
					Push(Close,e);
						BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
			 		Sleep(50);
					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h4,0,0,SRCCOPY);
					
					Sleep(100);
							//	Sleep(1000);
					
    				MessageBox(NULL,TEXT("��ϲ"),TEXT("��ϲС����"),0);
				}
			}
	}

	if(0==Flag)
	{
    	
		Sleep(1000);
				//	Sleep(1000);
    	MessageBox(NULL,TEXT("�Թ��߲���ȥ��!"),TEXT("�Թ��߲���ȥ��!"),0);
	}

    break;
    case IDC_GO2:
		if(0==M_Flag)
			{
				MessageBox(NULL,TEXT("��ͼ��û�л��ã����Ȼ��õ�ͼ!"),TEXT("���Ȼ��õ�ͼ!"),0);
				break;
			}
			Flag=0;



//	struct mark start,end; //start,end��ںͳ��ڵ����� 
	//int add[4][2]={{1,0},{0,1},{-1,0},{0,-1}};//�������������� ��������Ϊ�����ϱ� 

 start.x=1;
	start.y=0;
	end.x=16;
	end.y=24;

	InitStack(Open); //����open ��
	InitStack(Close); //����close��

	//maze[start.x][start.y]=2; //��ڵ����ϱ�� 
	elem.x=start.x; 
	elem.y=start.y; 
	
	deep_Flag=0;
	Push1(Open,elem); //��ʼ�ڵ����open��
	deep++;
	while(!StackEmpty(Open)&&Flag==0) //ջ��Ϊ�� ��·������ 
	{ 
		Pop(Open,elem); //��open���еĵ�ǰԪ�������

	             	BitBlt(hm,32+(elem.y-1)*32,32+(elem.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
						Sleep(100);
					BitBlt(hm,32+(elem.y-1)*32,32+(elem.x-1)*32,33,33,h4,0,0,SRCCOPY);

		Push(Close,elem);//����open��ȡ������Ԫ�ط���close��
		//��չ��Ԫ�ص������ӽڵ�
		//�����ر��ע�⣬����Ԫ�ص���������浱���ӽڵ㣬���е�Ԫ�ض�����
    	//�ж����ӽ������ӽڵ��ǲ��ǿ�����,���еĻ��ͽ����ӽڵ���open��
			//Sleep(5000);
			if(0==maze[elem.x][elem.y+1]&&0==Flag)
			{
				
				deep_Flag++;
				e.x=elem.x;
				e.y=elem.y+1;
			

				if(Judge(e,Close)){
					Push1(Open,e);
				}
				else
					deep_Flag--;
				if(e.x==end.x&&e.y==end.y)//�жϸõ��ǲ����յ�
				{
					Flag=1;//��ʾ�����Ѿ��ҵ�Ŀ����
					//	Pop(Open,e);
					Push(Close,e);

					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
			 		Sleep(50);
					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h4,0,0,SRCCOPY);

				
					Sleep(100);
							//	Sleep(1000);
					
    				MessageBox(NULL,TEXT("��ϲ"),TEXT("��ϲС����"),0);
				}
			}
			if(0==maze[elem.x+1][elem.y]&&0==Flag)
			{
				deep_Flag++;
				e.x=elem.x+1;
				e.y=elem.y;
				if(Judge(e,Close)){
					Push1(Open,e);
				}
				else
					deep_Flag--;
				if(e.x==end.x&&e.y==end.y)
				{
					Flag=1;//��ʾ�����Ѿ��ҵ�Ŀ����
					//Pop(Open,e);
					Push(Close,e);
						BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
			 		Sleep(50);
					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h4,0,0,SRCCOPY);

		
					Sleep(100);
							//	Sleep(1000);
				
    				MessageBox(NULL,TEXT("��ϲ"),TEXT("��ϲС����"),0);
				}
			}
		  
            if(0==maze[elem.x-1][elem.y]&&0==Flag)
			{
					deep_Flag++;
				e.x=elem.x-1;
				e.y=elem.y;
				if(Judge(e,Close)){
					Push1(Open,e);
				}
				else
					deep_Flag--;
				if(e.x==end.x&&e.y==end.y)
				{
					Flag=1;//��ʾ��;���Ѿ��ҵ�Ŀ����
				//	Pop(Open,e);
					Push(Close,e);
						BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
			 		Sleep(50);
					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h4,0,0,SRCCOPY);
				
					Sleep(100);
							//	Sleep(1000);
				
    				MessageBox(NULL,TEXT("��ϲ"),TEXT("��ϲС����"),0);
				}
			}
			if(0==maze[elem.x][elem.y-1]&&0==Flag)
			{
					deep_Flag++;
				e.x=elem.x;
				e.y=elem.y-1;
				if(Judge(e,Close)){
					Push1(Open,e);
				}
				else
					deep_Flag--;
				if(e.x==end.x&&e.y==end.y)
				{
					Flag=1;//��ʾ�����Ѿ��ҵ�Ŀ����
					//	Pop(Open,e);
					Push(Close,e);
						BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h2,0,0,SRCCOPY);
					//	SetTimer(hwnd,0,2000,NULL);
			 		Sleep(50);
					BitBlt(hm,32+(e.y-1)*32,32+(e.x-1)*32,33,33,h4,0,0,SRCCOPY);
					
					Sleep(100);
							//	Sleep(1000);
					
    				MessageBox(NULL,TEXT("��ϲ"),TEXT("��ϲС����"),0);
				}
			}
			if(0==deep_Flag)
				deep--;
			if(1==deep_Flag)
				deep++;
			deep_Flag=0;
	}

	if(0==Flag)
	{
    	
		Sleep(1000);
				//	Sleep(1000);
    	MessageBox(NULL,TEXT("�Թ��߲���ȥ��!"),TEXT("�Թ��߲���ȥ��!"),0);
	}

    break;

	case IDC_GO3:
		M_Flag=0;
		Flag=0;
		for(i=0;i<18;i++)
			for(j=0;j<25;j++)
				BitBlt(hm,j*32,i*32,p_Lsize,p_Hsize,h4,0,0,SRCCOPY);
		break;
//	case C2:
	//	MessageBox(NULL,TEXT("Hello"),TEXT("ceshi"),0);
	//	break;
        default:
	    	break;
    }
}

void Main_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}