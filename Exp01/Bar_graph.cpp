#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
using namespace std;
const int LEGEND_LB_X=10;
const int LEGEND_LB_Y=100;
const int LEGEND_HEIGHT=30;
const int INIT_BAR_LEFT=150;
const int BAR_WIDTH=50;
const int BAR_BOTTOM=600;
const char YELLOW_TEXT[14]={"nation income"};
const char RED_TEXT[21]={"total social product"};
const char YEAR_TEXT[3][10]={"1949","1956","1978"};
void My_yellow_bar(int left_bottom_x,int left_bottom_y,int bar_height){
	setfillstyle(YELLOW);
	bar(left_bottom_x,left_bottom_y-bar_height,left_bottom_x+BAR_WIDTH,left_bottom_y);
}
void My_red_bar(int left_bottom_x,int left_bottom_y,int bar_height){
	setfillstyle(RED);
	bar(left_bottom_x,left_bottom_y-bar_height,left_bottom_x+BAR_WIDTH,left_bottom_y);
}
void My_legend_bar(){
	My_yellow_bar(LEGEND_LB_X,LEGEND_LB_Y,LEGEND_HEIGHT);
	My_red_bar(LEGEND_LB_X,LEGEND_LB_Y+LEGEND_HEIGHT+30,LEGEND_HEIGHT);
	outtextxy(LEGEND_LB_X+BAR_WIDTH+10,LEGEND_LB_Y-LEGEND_HEIGHT,YELLOW_TEXT);
	outtextxy(LEGEND_LB_X+BAR_WIDTH+10,LEGEND_LB_Y+LEGEND_HEIGHT+30-LEGEND_HEIGHT,RED_TEXT);
}
int Year_left_X=INIT_BAR_LEFT;
int Year_Time=0;
const int Year_bar_distance=2*BAR_WIDTH+100;
void Year_red_yellow_Bar(int yellow_bar_height,int red_bar_height){
	My_yellow_bar(Year_left_X,BAR_BOTTOM,yellow_bar_height);
	My_red_bar(Year_left_X+BAR_WIDTH,BAR_BOTTOM,red_bar_height);
	outtextxy(Year_left_X+BAR_WIDTH/2,BAR_BOTTOM+10,YEAR_TEXT[Year_Time]);Year_Time++;
	Year_left_X+=Year_bar_distance;

}
void show(){
	initgraph(1000, 1000); 
	My_legend_bar();
	Year_red_yellow_Bar(30,45);
	Year_red_yellow_Bar(100,190);
	Year_red_yellow_Bar(200,400);
	outtextxy(400,650,"stat- histogram");
	outtextxy(20,200,"这里仅供展示");
	outtextxy(20,250,"请按任意键手动输入数据！");
	getch(); 
	closegraph();
};
bool InputDataInit=false;
void InputData(){
	if(!InputDataInit){
		Year_left_X=INIT_BAR_LEFT;
		Year_Time=0;
		//重新初始化
		InputDataInit=true;
	}
	int nation_1949,social_1949,nation_1956,social_1956,
			nation_1978,social_1978;
	cout<<"请输入1949年的nation income(default:30):";
	cin>>nation_1949;
	cout<<"请输入1949年的total social product(default:45):";
	cin>>social_1949;
	cout<<"请输入1956年的nation income(default:100):";
	cin>>nation_1956;
	cout<<"请输入1956年的total social product(default:190):";
	cin>>social_1956;
	cout<<"请输入1978年的nation income(default:200):";
	cin>>nation_1978;
	cout<<"请输入1978年的total social product(default:400):";
	cin>>social_1978;
	system("pause");
	initgraph(1000, 1000); 
	My_legend_bar();
	Year_red_yellow_Bar(nation_1949,social_1949);
	Year_red_yellow_Bar(nation_1956,social_1956);
	Year_red_yellow_Bar(nation_1978,social_1978);
	outtextxy(400,650,"stat- histogram");
	//outtextxy(20,200,"这里仅供展示");
	//outtextxy(20,250,"请按任意键手动输入数据！");
	getch(); 
	closegraph();

}
int main(){
	show();
	InputData();
	return 0;
}
