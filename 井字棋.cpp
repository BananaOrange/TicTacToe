#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*-----------------函数原型----------------------*/
void Menu(void);                                 //主菜单
void Rule(void);                                 //规则说明
void Strategy(void);                             //井字棋策略 
char getfirst(void);                             //输入正确性检测（只读取每行第一个输入） 
void BoardImg(int Board[],char Img[]) ;          //打印棋盘图形 
void BoardMove(int order,int move,int Board[]);  //将用户落子（1~9）存入棋盘数组（0或1形式）
int Initial(int order,int Board[]);              //初始化空棋盘 
int WinnerCheck(int Board[]);                    //胜利判别，返回3（先手胜）或0（后手胜） 
int Full(int Board[]);                           //满棋盘判别，返回一个较大数值 
void DOG_Easy(int Board[]);                      //对弈AI（简单难度），使用随机落子方式 
void DOG_Hard(int Board[]);                      //对弈AI（正常难度），使用失败的防守策略（检测二连子）和糟糕的估值策略(只估值下一手局面) 
void FirstMove(int Board[]);                     //第一手固定着法，优先在中间落子，其次是四个角落 
int isLegalMove(int n,int Board[]);              //判断着法是否合法，返回1（合法），0（非法） 
int EvaValue(int Board[]);                       //局面估值函数，将所有可以落子的地方填满，计算三连子个数 
int twoCount(int Board[]);                       //返回所有二连子（行列斜有两个相同棋子）个数或者最危险局面 

/*----------------主程序------------------------*/
int main(void)
{
Label_begin:
	
	int order=0;             //先后手判别,1表示先手,0表示后手 
	int choice;              //用户的模式选择
	int move;                //用户的落子 
	int level;               //用户选择的AI难度
	int dogmove; 	         //AI的落子 
	int depth=9;             //落子总步数，初始化为9后做自减运算
	int Board[9]={100,100,100,100,100,100,100,100,100} ;   //棋盘数组，用较大的数字进行初始化，以便后续胜利判别
	char Img[9]={'_','_','_','_','_','_','_','_','_'} ;    //棋盘图形，下划线表示空，X表示先手，O表示后手 
	 
Label_menu:	

	Menu();
	choice=getfirst();

	while(choice<'1'||choice>'3')
		{
		printf("输入有误，请重新输入：\n");	
		choice=getfirst();
		}
					
	switch(choice)
	{
		case '1': printf("      <已选择两人对弈>\n");
				  Rule();
		          break;
		case '2': printf("      <已选择人机对弈>\n");				
		          break;
		case '3': printf("        <井字棋的策略>\n");
				  Strategy();
				  printf("\n");
	              goto Label_menu;
    }
    
 	while(choice=='1')              //两人对弈模式 
    {
    	BoardImg(Board,Img); 
    	order=(order+1)%2;          //判断先后手
    	
    	if(order==1)
    	printf("\n先手请落子：");
    	if(order==0)
    	printf("\n后手请落子：");
    	
       	scanf("%d",&move);           //读取用户落子 
       	if(move==0)		     //如果输入0则返回主菜单 
       	{
			choice=getchar();
       		break;
		}
    	       			         	
       	BoardMove(order,move,Board); //将用户落子存入棋盘数组 
       	
       	if(WinnerCheck(Board)==3)
       	{
		   BoardImg(Board,Img); 
		   printf("\n<先手胜利!>\n\n\n<重新开始>\n");
		   order=Initial(order,Board);
		} 
		if(WinnerCheck(Board)==0)
       	{
		   BoardImg(Board,Img); 
		   printf("\n<后手胜利!>\n\n\n<重新开始>\n");
		   order=Initial(order,Board);
		} 
		if(Full(Board)<100)
		{
		   BoardImg(Board,Img); 
		   printf("\n<双方和棋!>\n\n\n<重新开始>\n");
		   order=Initial(order,Board);
		}
	}
	
	if(choice=='2')                        //对弈AI难度选择 
	{
			printf("\n请选择对弈AI难度：   1.简单      2.正常\n");
			level=getfirst();		
			while(level<'1'||level>'2')
			{
				printf("输入有误，请重新输入：\n");	
				level=getfirst();
			}
			switch(level)
			{
			case '1': printf("      <已选择简单难度>\n");
				  Rule();
		          break;
			case '2': printf("      <已选择正常难度>\n");
				  Rule();
		          break;	
			}
			
	}
		
		while(choice=='2')           //人机对弈模式 
	{	
		BoardImg(Board,Img);
		order=(order+1)%2;          //判断先后手
    	if(order==1)
    	{
    		printf("\n玩家请落子：");    	
       		scanf("%d",&move);           //读取用户落子 
			if(move==0)	     //如果输入0则返回主菜单 
       		{
				choice=getchar();
       			break;
			}
			BoardMove(order,move,Board); //将用户落子存入棋盘数组 	
			depth--;
		}		   
       	
        
       	if(order==0&&level=='1')       //简单模式 
       	{
    		printf("\n电脑思考中...\n");
    		DOG_Easy(Board);
    	}
    	
    	if(order==0&&level=='2')      //正常模式 
		{	
			printf("\n电脑思考中...\n");	
			if(depth==8)
			{
				FirstMove(Board);   //第一手固定着法 			
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
		   printf("\n<玩家胜利!>\n\n\n<重新开始>\n");
		   order=Initial(order,Board);
		   depth=9;
		} 
		if(WinnerCheck(Board)==0)
       	{
		   BoardImg(Board,Img); 
		   printf("\n<AI胜利!>\n\n\n<重新开始>\n");
		   order=Initial(order,Board);
		   depth=9;
		} 
		if(Full(Board)<100)
		{
		   BoardImg(Board,Img); 
		   printf("\n<双方和棋!>\n\n\n<重新开始>\n");
		   order=Initial(order,Board);
		   depth=9;
		}
	}
       	  	
		goto Label_begin;
	return 0;
 } 
 
 /*-------------所有函数------------------------*/
void Menu(void)
{
	printf("*******************************\n");
	printf("*   欢迎来到井字棋！请选择：      *\n");
	printf("*                             *\n");
	printf("*      1.两人对弈              *\n");
	printf("*      2.人机对弈              *\n");
	printf("*      3.井字棋策略            *\n");
	printf("*                             *\n");
	printf("*（Tip:对弈时输入0返回主菜单）    *\n");
	printf("*******************************\n");
 } 
 
 void Rule(void)
 {
 	printf("\n");
	printf("NO.1  请看向小键盘，小键盘的9个数字分别对应棋盘的九个位置。\n");
 	printf("NO.2  比如，键入数字7，则在棋盘的左上角落子。\n");
 	printf("NO.3  _表示空，X表示先手，O表示后手。\n");
 	printf("\n");
 	printf("棋盘如下:\n");
 	printf("\n");
 }             
 
 void Strategy(void)
 {
 	printf("\n");
 	printf("先手的最优选择是四个角落，次优选择才是中间位置。\n");
 	printf("后手的最优选择是中间位置，其次是四个角落。\n");
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
 	int i;      //遍历数组计数 
 	int j=0;    //分行打印时的计数变量 
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
	int winner;       //3表示先手胜利，0表示后手胜利
	int i;            //遍历数组变量
	int ignore;       //如果行检测成功，忽略列检测 
	for(i=0;i<=6;i=i+3) //行检测 
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
	for(i=0;i<=2;i++)  //列检测 
	{
		winner=Board[i]+Board[i+3]+Board[i+6];
		if(winner==3)
		break;
		if(winner==0)
		break;
	}
	}
	                     /*对角检测*/ 
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

 	int dogmove;                  //AI随机落子   
 	do
 	{
 		srand((unsigned)time(NULL));
 		dogmove=rand()%9;        //生成0~8随机数				     
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
 	int CopyArr[9];                     //定义一个临时数组复制Board
	for(i=0;i<9;i++)
	{
		CopyArr[i]=Board[i];
	 } 
	  
 	for(i=0;i<9;i++)                    //填满所有可以落子的地方 
 	{
 		if(isLegalMove(i,CopyArr))
 		{
 			CopyArr[i]=0;
		 }
	 }
	 	 
	 //*行列斜估值 
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
 	int count=0;       //二连子个数 
 	int danger=-1;     //一种特定的危险局面 ，数组表示为100,100,1,100,0,100,1,100,100（以及其对称局面） 
 	int sum;
 	int i;
 	
 	for(i=0;i<9;i++)
 	{
 		sum+=Board[i];    
	}
	if(sum==602)          //如果此危险局面存在，danger的值应该为602	
	{
		if(((Board[0]+Board[4]+Board[8])==2)||((Board[2]+Board[4]+Board[6])==2))
		{
			danger=1000;
		}
		 
	}
	
 	for(i=0;i<=6;i=i+3) //行检测 
	{
		if((Board[i]+Board[i+1]+Board[i+2])==102)
		{
			count++;
		}
	
	}
	
	for(i=0;i<=2;i++)  //列检测 
	{
		if((Board[i]+Board[i+3]+Board[i+6])==102)
		{
			count++;
		}
	}
                 	 //对角检测
	if((Board[0]+Board[4]+Board[8])==102)   count++;
	if((Board[2]+Board[4]+Board[6])==102)   count++;
	
	return danger>count? danger : count ;
 }
 
 void DOG_Hard(int Board[])
 {
 	int i;
	int isTwo=0;        //如果有二连子置1，否则置0
 	int bestmove;       //最佳走法 
 	int ignore=0;       //如果检测到行二连子，跳过列检测 
	int value=-1;       //初始化一个局面估值，设为-1以便估值函数更新此数值 
	int MaxValue;       //最好的估值分数，需要不断更新 
	 /*检测二连子*/
 	for(i=0;i<=6;i=i+3) //行检测 
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
		for(i=0;i<=2;i++)  //列检测 
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
	                     //对角检测
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
	
	/*检测不到二连子就随机落子并用估值函数估值*/
	if(isTwo==0)
	{	
		int dogmove;
		int CopyArr[9];                     //定义一个临时数组复制Board
		for(i=0;i<9;i++)
		{
			CopyArr[i]=Board[i];
	 	} 
	 	
	 	for(i=0;i<9;i++)                    //防止一种危险的情况，即先手某一落子会造成行列均存在二连子 
	 	{
	 		if(isLegalMove(i,CopyArr))
	 		{
	 			if((twoCount(CopyArr)==1000))       //最危险情况 
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
					CopyArr[i]=100;          //撤销走法
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
	 				bestmove=i;          //保存最佳走法 
				}
				CopyArr[i]=100;              //撤销走法
					
			}
		}
		Board[bestmove]=0;
	}
}
	 	
	
