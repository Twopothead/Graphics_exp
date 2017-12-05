/*种子填充算法*/
/*开发环境vc6.0*/
#include <graphics.h> // 图形函数库
#include "stdio.h" //标准输入输出函数库
#include "conio.h" //控制台输入输出
#include "windows.h"
void MyFloodFill(int x,int y,int borderColor,int newColor)
{
	int color=getpixel(x,y);
	if((color!=borderColor)&&(color!=newColor)){
		putpixel (x,y,newColor);
		MyFloodFill(x,y+1,borderColor,newColor);
		MyFloodFill(x,y-1,borderColor,newColor);
		MyFloodFill(x-1,y,borderColor,newColor);
		MyFloodFill(x+1,y,borderColor,newColor);
	}
}
void MyDraw()
{
	initgraph(1000,800);
	int x=0;
	int y=0;
	int text[]={
	140,20,
	260,100,
	260,220,
	140,140,
	40 ,180,
	40 ,60,
	140,20
	};
	int i=0;
	moveto(x+text[0],y+text[1]);
	for(i=0;i<7;i++)
	{
		Sleep(1000);
	lineto((x+text[2*i]),(y+text[2*i+1]));

	}
	for(i=0;i<7;i++)
	{
		Sleep(1000);
	MyFloodFill(140+100,100+100,WHITE,GREEN);
	}
	getch();
	closegraph();
}
int main(){
MyDraw();
return 0;
}
//由于种子填充法递归层次较深，需要的栈空间比较大，而x86机器的默认栈大小为2MB，因此需要修改栈大小
//本程序运行环境为VC++6.0
//修改步骤
//1、点击工具栏的工程按钮
//2、点击设置—>link(链接)
//3、点击Y分类选择框—>Output
//4、叠队分配 改为10000000（尽量大）
//5、确定
