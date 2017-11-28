#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*-----------------����ԭ��----------------------*/
void Menu(void);                                 //���˵�
void Rule(void);                                 //����˵��
void Strategy(void);                             //��������� 
char getfirst(void);                             //������ȷ�Լ�⣨ֻ��ȡÿ�е�һ�����룩 
void BoardImg(int Board[],char Img[]) ;          //��ӡ����ͼ�� 
void BoardMove(int order,int move,int Board[]);  //���û����ӣ�1~9�������������飨0��1��ʽ��
int Initial(int order,int Board[]);              //��ʼ�������� 
int WinnerCheck(int Board[]);                    //ʤ���б𣬷���3������ʤ����0������ʤ�� 
int Full(int Board[]);                           //�������б𣬷���һ���ϴ���ֵ 
void DOG_Easy(int Board[]);                      //����AI�����Ѷȣ���ʹ��������ӷ�ʽ 
void DOG_Hard(int Board[]);                      //����AI�������Ѷȣ���ʹ��ʧ�ܵķ��ز��ԣ��������ӣ������Ĺ�ֵ����(ֻ��ֵ��һ�־���) 
void FirstMove(int Board[]);                     //��һ�̶ֹ��ŷ����������м����ӣ�������ĸ����� 
int isLegalMove(int n,int Board[]);              //�ж��ŷ��Ƿ�Ϸ�������1���Ϸ�����0���Ƿ��� 
int EvaValue(int Board[]);                       //�����ֵ�����������п������ӵĵط����������������Ӹ��� 
int twoCount(int Board[]);                       //�������ж����ӣ�����б��������ͬ���ӣ�����������Σ�վ��� 

/*----------------������------------------------*/
int main(void)
{
Label_begin:
	
	int order=0;             //�Ⱥ����б�,1��ʾ����,0��ʾ���� 
	int choice;              //�û���ģʽѡ��
	int move;                //�û������� 
	int level;               //�û�ѡ���AI�Ѷ�
	int dogmove; 			 //AI������ 
	int depth=9;             //�����ܲ�������ʼ��Ϊ9�����Լ�����
	int Board[9]={100,100,100,100,100,100,100,100,100} ;   //�������飬�ýϴ�����ֽ��г�ʼ�����Ա����ʤ���б�
	char Img[9]={'_','_','_','_','_','_','_','_','_'} ;    //����ͼ�Σ��»��߱�ʾ�գ�X��ʾ���֣�O��ʾ���� 
	 
Label_menu:	

	Menu();
	choice=getfirst();

	while(choice<'1'||choice>'3')
		{
		printf("�����������������룺\n");	
		choice=getfirst();
		}
					
	switch(choice)
	{
		case '1': printf("      <��ѡ�����˶���>\n");
				  Rule();
		          break;
		case '2': printf("      <��ѡ���˻�����>\n");				
		          break;
		case '3': printf("        <������Ĳ���>\n");
				  Strategy();
				  printf("\n");
	              goto Label_menu;
    }
    
 	while(choice=='1')              //���˶���ģʽ 
    {
    	BoardImg(Board,Img); 
    	order=(order+1)%2;          //�ж��Ⱥ���
    	
    	if(order==1)
    	printf("\n���������ӣ�");
    	if(order==0)
    	printf("\n���������ӣ�");
    	
       	scanf("%d",&move);           //��ȡ�û����� 
       	if(move==0)					 //�������0�򷵻����˵� 
       	{
			choice=getchar();
       		break;
		}
    	       			         	
       	BoardMove(order,move,Board); //���û����Ӵ����������� 
       	
       	if(WinnerCheck(Board)==3)
       	{
		   BoardImg(Board,Img); 
		   printf("\n<����ʤ��!>\n\n\n<���¿�ʼ>\n");
		   order=Initial(order,Board);
		} 
		if(WinnerCheck(Board)==0)
       	{
		   BoardImg(Board,Img); 
		   printf("\n<����ʤ��!>\n\n\n<���¿�ʼ>\n");
		   order=Initial(order,Board);
		} 
		if(Full(Board)<100)
		{
		   BoardImg(Board,Img); 
		   printf("\n<˫������!>\n\n\n<���¿�ʼ>\n");
		   order=Initial(order,Board);
		}
	}
	
	if(choice=='2')                        //����AI�Ѷ�ѡ�� 
	{
			printf("\n��ѡ�����AI�Ѷȣ�   1.��      2.����\n");
			level=getfirst();		
			while(level<'1'||level>'2')
			{
				printf("�����������������룺\n");	
				level=getfirst();
			}
			switch(level)
			{
			case '1': printf("      <��ѡ����Ѷ�>\n");
				  Rule();
		          break;
			case '2': printf("      <��ѡ�������Ѷ�>\n");
				  Rule();
		          break;	
			}
			
	}
		
		while(choice=='2')           //�˻�����ģʽ 
	{	
		BoardImg(Board,Img);
		order=(order+1)%2;          //�ж��Ⱥ���
    	if(order==1)
    	{
    		printf("\n��������ӣ�");    	
       		scanf("%d",&move);           //��ȡ�û����� 
			if(move==0)					 //�������0�򷵻����˵� 
       		{
				choice=getchar();
       			break;
			}
			BoardMove(order,move,Board); //���û����Ӵ����������� 	
			depth--;
		}		   
       	
        
       	if(order==0&&level=='1')       //��ģʽ 
       	{
    		printf("\n����˼����...\n");
    		DOG_Easy(Board);
    	}
    	
    	if(order==0&&level=='2')      //����ģʽ 
		{	
			printf("\n����˼����...\n");	
			if(depth==8)
			{
				FirstMove(Board);   //��һ�̶ֹ��ŷ� 			
			}	
			else
			{	 			
				DOG_Hard(Board);  
			}
			
			depth--;
		}
	
       	     
    	if(WinnerCheck(Board)==3)
       	{
		   BoardImg(Board,Img); 
		   printf("\n<���ʤ��!>\n\n\n<���¿�ʼ>\n");
		   order=Initial(order,Board);
		   depth=9;
		} 
		if(WinnerCheck(Board)==0)
       	{
		   BoardImg(Board,Img); 
		   printf("\n<AIʤ��!>\n\n\n<���¿�ʼ>\n");
		   order=Initial(order,Board);
		   depth=9;
		} 
		if(Full(Board)<100)
		{
		   BoardImg(Board,Img); 
		   printf("\n<˫������!>\n\n\n<���¿�ʼ>\n");
		   order=Initial(order,Board);
		   depth=9;
		}
	}
       	  	
		goto Label_begin;
	return 0;
 } 
 
 /*-------------���к���------------------------*/
void Menu(void)
{
	printf("*******************************\n");
	printf("*   ��ӭ���������壡��ѡ��  *\n");
	printf("*                             *\n");
	printf("*      1.���˶���             *\n");
	printf("*      2.�˻�����             *\n");
	printf("*      3.���������           *\n");
	printf("*                             *\n");
	printf("*��Tip:����ʱ����0�������˵���*\n");
	printf("*******************************\n");
 } 
 
 void Rule(void)
 {
 	printf("\n");
	printf("NO.1  �뿴��С���̣�С���̵�9�����ֱַ��Ӧ���̵ľŸ�λ�á�\n");
 	printf("NO.2  ���磬��������7���������̵����Ͻ����ӡ�\n");
 	printf("NO.3  _��ʾ�գ�X��ʾ���֣�O��ʾ���֡�\n");
 	printf("\n");
 	printf("��������:\n");
 	printf("\n");
 }             
 
 void Strategy(void)
 {
 	printf("\n");
 	printf("���ֵ�����ѡ�����ĸ����䣬����ѡ������м�λ�á�\n");
 	printf("���ֵ�����ѡ�����м�λ�ã�������ĸ����䡣\n");
 	printf("\n");
 }
 
 char getfirst(void)
 {
 	int ch;
	ch=getchar();
	while(getchar()!='\n')
	    continue;
	return ch;		
 }
 
 void BoardImg(int Board[],char Img[])
 {
 	int i;      //����������� 
 	int j=0;    //���д�ӡʱ�ļ������� 
 	for(i=0;i<=8;i++)
 	{
 		if(Board[i]==100)
		Img[i]='_'	;
		if(Board[i]==1)
		Img[i]='X'	;
		if(Board[i]==0)
		Img[i]='O'	;
	}
	for(i=0;i<=8;i++)
	{
		printf("%2c",Img[i]);
		j++;
		if(j%3==0)
		printf("\n");
	}
 }
 
  void BoardMove(int order,int move,int Board[])
 {
 		switch(move)
 		{
 			case 1: Board[6]=order;break;
 			case 2: Board[7]=order;break;
 			case 3: Board[8]=order;break;
 			case 4: Board[3]=order;break;
 			case 5: Board[4]=order;break;
 			case 6: Board[5]=order;break;
 			case 7: Board[0]=order;break;
 			case 8: Board[1]=order;break;
 		    case 9: Board[2]=order;break;
		 }
 }

 int WinnerCheck(int Board[])
{
	int winner;       //3��ʾ����ʤ����0��ʾ����ʤ��
	int i;            //�����������
	int ignore;       //����м��ɹ��������м�� 
	for(i=0;i<=6;i=i+3) //�м�� 
	{
		winner=Board[i]+Board[i+1]+Board[i+2];
		if(winner==3)
		{
		ignore=1;
		break;
	    }
		if(winner==0)
		{
		ignore=1;
		break;
	    }
	}
	
	if(ignore!=1)
	{
	for(i=0;i<=2;i++)  //�м�� 
	{
		winner=Board[i]+Board[i+3]+Board[i+6];
		if(winner==3)
		break;
		if(winner==0)
		break;
	}
	}
	                     /*�ԽǼ��*/ 
	if((Board[0]+Board[4]+Board[8])==3)
	winner=3;
	if((Board[2]+Board[4]+Board[6])==3)
	winner=3;
	if((Board[0]+Board[4]+Board[8])==0)
	winner=0;
	if((Board[2]+Board[4]+Board[6])==0)
	winner=0;
	
	return winner;
}

int Full(int Board[])
{
	int full=0;
	int i;
	for(i=0;i<=8;i++)
	full+=Board[i];
	return full;
 } 
 
int Initial(int order,int Board[])
 {
 	int i;
 	order=0;  
	for(i=0;i<=8;i++)
	Board[i]=100;
	return order;
 }
 
void DOG_Easy(int Board[])
 {

 	int dogmove;                  //AI�������   
 	do
 	{
 		srand((unsigned)time(NULL));
 		dogmove=rand()%9;        //����0~8�����				     
	 }	while(Board[dogmove]!=100);
 	Board[dogmove]=0;
 }
 
 void FirstMove(int Board[])
 {
 
	if(Board[4]==1)
	{
		int dogmove;
		srand((unsigned)time(NULL));
		do
		{
			dogmove=rand()%9;
		}while(dogmove!=0&&dogmove!=2&&dogmove!=6&&dogmove!=8);
		
		Board[dogmove]=0;		
	}
	else
	{
			Board[4]=0;
	}
 }
 
 int isLegalMove(int n,int Board[])
 {
 	return Board[n]==100 ? 1 : 0 ;
 }
 
 int EvaValue(int Board[])
 {
 	int i;
 	int value=0;
 	int CopyArr[9];                     //����һ����ʱ���鸴��Board
	for(i=0;i<9;i++)
	{
		CopyArr[i]=Board[i];
	 } 
	  
 	for(i=0;i<9;i++)                    //�������п������ӵĵط� 
 	{
 		if(isLegalMove(i,CopyArr))
 		{
 			CopyArr[i]=0;
		 }
	 }
	 	 
	 //*����б��ֵ 
	 if((CopyArr[0]+CopyArr[1]+CopyArr[2])==0) value++;
	 if((CopyArr[3]+CopyArr[4]+CopyArr[5])==0) value++;
	 if((CopyArr[6]+CopyArr[7]+CopyArr[8])==0) value++;
	 if((CopyArr[0]+CopyArr[3]+CopyArr[6])==0) value++;
	 if((CopyArr[1]+CopyArr[4]+CopyArr[7])==0) value++;
	 if((CopyArr[2]+CopyArr[5]+CopyArr[8])==0) value++;
	 if((CopyArr[0]+CopyArr[4]+CopyArr[8])==0) value++;
	 if((CopyArr[2]+CopyArr[4]+CopyArr[6])==0) value++;
	
	 return value;
 }
 
 int twoCount(int Board[])
 { 
 	int count=0;       //�����Ӹ��� 
 	int danger=-1;      //һ���ض���Σ�վ��� �������ʾΪ100,100,1,100,0,100,1,100,100���Լ���Գƾ��棩 
 	int sum;
 	int i;
 	
 	for(i=0;i<9;i++)
 	{
 		sum+=Board[i];    
	}
	if(sum==602)          //�����Σ�վ�����ڣ�danger��ֵӦ��Ϊ602	
	{
		if(((Board[0]+Board[4]+Board[8])==2)||((Board[2]+Board[4]+Board[6])==2))
		{
			danger=1000;
		}
		 
	}
	
 	for(i=0;i<=6;i=i+3) //�м�� 
	{
		if((Board[i]+Board[i+1]+Board[i+2])==102)
		{
			count++;
		}
	
	}
	
	for(i=0;i<=2;i++)  //�м�� 
	{
		if((Board[i]+Board[i+3]+Board[i+6])==102)
		{
			count++;
		}
	}
                 	 //�ԽǼ��
	if((Board[0]+Board[4]+Board[8])==102)   count++;
	if((Board[2]+Board[4]+Board[6])==102)   count++;
	
	return danger>count? danger : count ;
 }
 
 void DOG_Hard(int Board[])
 {
 	int i;
 	int flag=0;         //�������������ӣ���1��������0 
	int isTwo=0;        //����жԷ���������1��������0
 	int bestmove;       //����߷� 
 	int ignore=0;       //�����⵽�ж����ӣ������м�� 
	int value=-1;       //��ʼ��һ�������ֵ����Ϊ-1�Ա��ֵ�������´���ֵ 
	int MaxValue;       //��õĹ�ֵ��������Ҫ���ϸ��� 
	
	/*������������*/
 	for(i=0;i<=6;i=i+3) //�м�� 
	{
		if((Board[i]+Board[i+1]+Board[i+2])==100)
		{
			if(Board[i]==100)    Board[i]=0;			
			if(Board[i+1]==100)  Board[i+1]=0;
			if(Board[i+2]==100)  Board[i+2]=0;
			ignore=1;
			flag=1;
			break;
		}
	
	}
	
	if(ignore==0)
	{
		for(i=0;i<=2;i++)  //�м�� 
		{
			if((Board[i]+Board[i+3]+Board[i+6])==100)
			{
				if(Board[i]==100)    Board[i]=0;			
				if(Board[i+3]==100)  Board[i+3]=0;
				if(Board[i+6]==100)  Board[i+6]=0;
				flag=1;
				break;
			}
		}
	}
	                     //�ԽǼ��
	if((Board[0]+Board[4]+Board[8])==100)
	{
		if(Board[0]==100)		Board[0]=0;		   
		if(Board[4]==100)		Board[4]=0;			  
		if(Board[8]==100)		Board[8]=0;  
		flag=1;
		
	}
	
	if((Board[2]+Board[4]+Board[6])==100)
	{
		if(Board[2]==100)		Board[2]=0;		   
		if(Board[4]==100)		Board[4]=0;			  
		if(Board[6]==100)		Board[6]=0;  
		flag=1;
		
	}
	
	 /*���Է�������*/
	 if(flag==0)
	 {
		for(i=0;i<=6;i=i+3) //�м�� 
		{
			if((Board[i]+Board[i+1]+Board[i+2])==102)
			{
				if(Board[i]==100)    Board[i]=0;			
				if(Board[i+1]==100)  Board[i+1]=0;
				if(Board[i+2]==100)  Board[i+2]=0;
				isTwo=1; 
				ignore=1;
				break;
			}
	
		}
	
		if(ignore==0)
		{
			for(i=0;i<=2;i++)  //�м�� 
			{
				if((Board[i]+Board[i+3]+Board[i+6])==102)
				{
					if(Board[i]==100)    Board[i]=0;			
					if(Board[i+3]==100)  Board[i+3]=0;
					if(Board[i+6]==100)  Board[i+6]=0;
					isTwo=1; 
					break;
				}
			}
		}
	                     //�ԽǼ��
		if((Board[0]+Board[4]+Board[8])==102)
		{
			if(Board[0]==100)		Board[0]=0;		   
			if(Board[4]==100)		Board[4]=0;			  
			if(Board[8]==100)		Board[8]=0;  
			isTwo=1; 
		}
	
		if((Board[2]+Board[4]+Board[6])==102)
		{
			if(Board[2]==100)		Board[2]=0;		   
			if(Board[4]==100)		Board[4]=0;			  
			if(Board[6]==100)		Board[6]=0;  
			isTwo=1; 
		}
	}
 	
	
	/*��ⲻ�������Է������Ӿ�������Ӳ��ù�ֵ������ֵ*/
	if((isTwo==0)&&(flag==0))
	{	
		int dogmove;
		int CopyArr[9];                     //����һ����ʱ���鸴��Board
		for(i=0;i<9;i++)
		{
			CopyArr[i]=Board[i];
	 	} 
	 	
	 	for(i=0;i<9;i++)                             //��ֹһ��Σ�յ������������ĳһ���ӻ�������о����ڶ����� 
	 	{
	 		if(isLegalMove(i,CopyArr))
	 		{
	 			if((twoCount(CopyArr)==1000))       //��Σ����� 
	 			{	 				
					do
					{
						srand((unsigned)time(NULL));
						dogmove=rand()%9;
					}while(dogmove!=1&&dogmove!=3&&dogmove!=5&&dogmove!=7);
					Board[dogmove]=0;
					return ;
				}
				else
				{
					CopyArr[i]=1;
	 				if(twoCount(CopyArr)>1)
	 				{
	 					Board[i]=0;
	 					return ;
					}
					CopyArr[i]=100;          //�����߷�
				}
	 			
			}
		}
		
	
		for(i=0;i<9;i++)
	 	{
	 		if(isLegalMove(i,CopyArr))
	 		{
	 			CopyArr[i]=0;
	 			MaxValue=EvaValue(CopyArr);
	 			if(MaxValue>=value)
	 			{
	 				value=MaxValue;	
	 				bestmove=i;          //��������߷� 
				}
				CopyArr[i]=100;          //�����߷�
					
			}
		}
		Board[bestmove]=0;
	}
}
	 	
	
