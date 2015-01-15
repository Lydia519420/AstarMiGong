#include<stdio.h> 
#include<stdlib.h> 
#include<malloc.h>
#include"migong.h"
#include "stdafx.h"


struct mark //�����Թ��ڵ���������� 
{ 
	int x; 
	int y; 
}; 

struct Element //ջԪ�� 
{ 
	int x,y; //x��,y�� 
	int d; //d��һ���ķ��� 
}; 

typedef struct LStack //��ջ 
{ 
	Element elem; 
	struct LStack *next; 
}*PLStack; 


/*************ջ����****************/ 

int InitStack(PLStack &S)//�����ջ 
{ 
	S=NULL; 
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
//	p=(PLStack)malloc(sizeof(LStack)); 
	p->elem=e; 
	p->next=S; 
	S=p; 
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
	//	free(p); 
		return 1; 
	} 
	else 
		return 0; 
} 


/***************���Թ�·������***********************/ 
void MazePath() 
{ 
	int i,j,d;
	int a,b; 
  /*�Թ���ʼ��*/
	int maze[7][7]={
			{0,1,1,1,1,1,1},
			{0,0,0,1,0,1,1},
			{1,1,0,1,1,1,1},
			{0,1,0,0,0,0,1},
			{1,1,1,1,1,0,1},
			{1,1,0,0,1,0,0},
			{1,1,1,1,1,1,0}
		};

    struct mark start,end;//���ڱ���Թ���ʼ��ͽ�����
	start.x=0;
	start.x=0;
	end.y =6;
	end.y =6;

	int add[4][2]={{1,0},{0,1},{-1,0},{0,-1}};//�к������� ����Ϊ��������

	Element elem,e; 
	PLStack S1, S2; 
	InitStack(S1); 
	InitStack(S2); 

	maze[start.x][start.y]=2; //��ڵ����ϱ�� 
	elem.x=start.x; 
	elem.y=start.y; 
	elem.d=-1; //��ʼΪ-1 

	Push(S1,elem); //��ڽ�ջ

	while(!StackEmpty(S1)) //ջ��Ϊ�� ��·������ 
	{ 
		Pop(S1,elem); 
		i=elem.x; 
		j=elem.y; 
		d=elem.d+1; //��һ������ 
		while(d<4) //��̽�������� 
		{ 

			a=i+add[d][0]; 
			b=j+add[d][1]; 

			if(a==end.x && b==end.y && maze[a][b]==0) //������˳��� 
			{ 
			elem.x=i; 
			elem.y=j; 
			elem.d=d; 

			Push(S1,elem); //��ջ

			elem.x=a; 
			elem.y=b; 
			elem.d=8; //�������Ϊ-1 �ж��Ƿ��˳��� 

			Push(S1,elem); //���һ��Ԫ�ؽ�ջ

				while(S1) //�������� ������Թ�·������ ��s1��ת��s2��
				{ 
					Pop(S1,e); 
					Push(S2,e);   
				} 
				while(S2) 
				{ 
					Pop(S2,e); 
				//	printf("-->(%d,%d,%d)",e.x,e.y,e.d);
					maze[e.x][e.y] = 9;
				} 
				return; //��������ѭ��
			} 
        	if(maze[a][b]==0) //�ҵ�����ǰ���ķǳ��ڵĵ� 
			{ 
				maze[a][b]=2; //����߹��˵� 
				elem.x=i; 
				elem.y=j; 
				elem.d=d; 
				Push(S1,elem); //��ǰλ����ջ 
				i=a; //��һ��ת��Ϊ��ǰ�� 
	    		j=b; 
	    		d=-1; 
			} 
	    	d++; 
		} 
	} 
//	printf("û���ҵ������߳����Թ���·��\n"); 
} 
