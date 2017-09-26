#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
const int n = 100;
const int a = 300;
int translationx(int x){
x+=500;//圆心坐标x
return x;
}
int translationy(int y){
y+=500;
return y;//圆心坐标y
}
int main(){
	initgraph(1000, 1000);
	int x=0;
	int y=0;
	int t=0;
	double trad=0.0;
	for(int i=0;i<360;i++){
		moveto(translationx(x),translationy(y));
		trad=t*0.0174533;
		x=a*cos(trad)*cos(trad)*cos(trad);
		y=a*sin(trad)*sin(trad)*sin(trad);
		t++;
		lineto(translationx(x),translationy(y));
	}
	circle(translationx(0),translationy(0),a);
	line(translationx(0),translationy(0),translationx(0-a),translationy(0));
	line(translationx(0),translationy(-a),translationx(0),translationy(a));
	system("pause");
	closegraph();
return 0;

}