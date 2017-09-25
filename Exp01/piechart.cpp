#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <sstream>
using namespace std;
const int BAR_START_X=400;
const int BAR_START_Y=180;
const int BAR_WIDTH= 60;
const int BAR_HEIGHT=45;
const int TITLE_X=120;
const int TITLE_Y=450;
const char TITLE_TEXT[40]={"the pie chart of market"};
float stangle =0;
double dcita = 360.0/100.0;
float top = 400.0;
float left = 200.0;
float w = 40.0;
float h = 100.0;
int mycolor[6]={BLUE,GREEN,CYAN,RED,MAGENTA,LIGHTBLUE};
double percent[6]={0.50,0.20,0.10,0.05,0.10,0.05};
char Text[6][20]={"50%","20%","10%","5%","10%","5%"};
char Name[6][20]={"Computer","printer","plotter","scanner","computer paper","hard disk"};
void show(){
	float x=200,y=300,radis=100.0;
	float endangle;
	int textx;
	int texty;
	int barleft=BAR_START_X;
	int bartop=BAR_START_Y;
	initgraph(1000, 1000); 
	for(int i=0;i<6;i++){
		endangle = stangle +dcita*100*percent[i];
		setfillstyle(mycolor[i]);
		pieslice(x,y,stangle,endangle,radis);
		textx=x+radis*0.5*cos(0.5*(stangle+endangle)*0.0174533);
		//1 degree = 0.0174533 rad
		texty=y-radis*0.5*sin(0.5*(stangle+endangle)*0.0174533);
		outtextxy(textx,texty,Text[i]);
		bar3d(barleft,bartop,barleft+BAR_WIDTH,bartop+BAR_HEIGHT,3,true);
		outtextxy(barleft+BAR_WIDTH+10,bartop+20,Name[i]);
		bartop+=BAR_HEIGHT;
		outtextxy(TITLE_X,TITLE_Y,TITLE_TEXT);
		stangle = endangle;
		top=top+h;
	}
	outtextxy(20,100,"这里仅供展示");
	outtextxy(20,150,"请按任意键手动输入数据！");
	getch(); 
	closegraph(); 
}
template<class T>
void to_string(string & result,const T& t){
    //to_string 用了类模板，将数值类型如int之类转化成string类型
    //to_string函数要用到sstream.h这个头文件（原stringstream.h较老，已弃用）
    //原理是创建一个流，把值传递如流中，获取转换后的字符转并将其写入目的字符串
        ostringstream oss;//创建一个流
        oss<<t;//把值传递如流中
        result=oss.str();//获取转换后的字符转并将其写入result
}
char InputText[6][10]={NULL};
void getPercent(){
InputAgain:
	double totalpercent=0.0;
	for(int i=0;i<6;i++){
		if(i!=5){
			cout<<"请输入"<<Name[i]<<"的百分比(eg:0.17)：";
			cin>>percent[i];
			totalpercent+=percent[i];
		}
		else{
			if(totalpercent>1){
				cout<<"对不起，你输入的百分比之和已经超过100%,请重新输入！";
				goto InputAgain;
			}
			double all=1.0;
			percent[5]=all-totalpercent;
			cout<<percent[5];
		}

		int Temp=(int)ceil(percent[i]*100);
		cout<<"Temp"<<Temp;
		itoa(Temp,InputText[i],10);
		char *b="%";
		strcat(InputText[i],b);
		cout<<Name[i]<<"百分比是"<<InputText[i]<<endl;
	}
	system("pause");
}
void InputData(){
	getPercent();
	float x=200,y=300,radis=100.0;
	float endangle;
	int textx;
	int texty;
	int barleft=BAR_START_X;
	int bartop=BAR_START_Y;
	initgraph(1000, 1000); 
	for(int i=0;i<6;i++){
		endangle = stangle +dcita*100*percent[i];
		setfillstyle(mycolor[i]);
		pieslice(x,y,stangle,endangle,radis);
		textx=x+radis*0.5*cos(0.5*(stangle+endangle)*0.0174533);
		//1 degree = 0.0174533 rad
		texty=y-radis*0.5*sin(0.5*(stangle+endangle)*0.0174533);
		outtextxy(textx,texty,InputText[i]);
		bar3d(barleft,bartop,barleft+BAR_WIDTH,bartop+BAR_HEIGHT,3,true);
		outtextxy(barleft+BAR_WIDTH+10,bartop+20,Name[i]);
		bartop+=BAR_HEIGHT;
		outtextxy(TITLE_X,TITLE_Y,TITLE_TEXT);
		stangle = endangle;
		top=top+h;
	}
	getch(); 
	closegraph(); 
	
}
int main(){
	show();
	InputData();
	return 0;
}
