#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
 int Xc = 300;
 int Yc = 300;
const int L = 300;
const int H = 400;
const int p = 6;
const int n = 100;
int para_curve(){
	initgraph(1000, 1000);
	int X= (int)sqrt(2*p*H);
	if(X>L/2)X=L/2;
	int dx = 2*X/n;
	int m = n/2;
	int x=0;
	int y=0;
	for(int i=-m;i<=m;i++){
	x = i*dx;
	y=x*x/(4*p);
		if(i==-m){
			moveto(Xc+x,Yc-y);
		}else{
			lineto(Xc+x,Yc-y);
		}
	}
	system("pause");
	closegraph();
	return 0;
}
int main(){
	para_curve();
	return 0;
}