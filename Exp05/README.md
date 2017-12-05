### 第五次计算机图形学实验

---------------------------

#### 实验题目1：使用种子填充算法和扫描线填充算法对下图所示的多边形进行填充

---------------------------

#### 1.实验目的
- （1）熟悉种子填充算法和扫描线填充算法,了解种子填充算法和扫描线的优缺点

---------------------------

#### 2.实验内容
- （1）使用种子填充算法对下图所示的多边形进行填充
- （2）使用扫描线填充算法对下图所示的多边形进行填充



#### 3.实验结果

种子填充算法实验截图：
![](assets/README-09c78.png)

------------------------
###### 二维变换



------------------------

实验说明： 此次采用Ubuntu下的OpenGL开发

-------------------------
实验源码：

### 种子填充算法
-------------------
```cpp
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
```
----------------

-------------------------------



---------------------------

####  4.实验体会

- 1.通过本实验，初步了解了种子填充算法和扫描线填充算法。
- 2.种子填充算法很容易，但是扫描线填充算法真的比较困难
，很多同学的能够做出来，但算法只适用于当前给出的图，
换个图就不行，这样不够鲁棒。要写一个比较通用的程序还是要
花费一些功夫的。
