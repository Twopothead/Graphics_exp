/*本程序采用Ubunru系统下的OpenGL开发
 *      2017 邱日
 */
#include <GL/glut.h>
#include <cmath>
const int windowHeight= 400;
const int windowWidth= 400;
float point[]={1.0*0/100,1.0*0/100,     1.0*20/100,1.0*0/100,   1.0*15/100,1.0*15/100,  1.0*5/100,1.0*15/100,   1.0*0/100,1.0*0/100
,1.0*20/100,1.0*0/100,   1.0*10/100,1.0*30/100,         0,0};//20为基准//7个点
int Points[]={0,0,       0,0,     0,0,       0,0,       0,0,
        0,0,       0,0};

int homogeneousPoints[][3]={{0,0,1},       {0,0,1},     {0,0,1},       {0,0,1},       {0,0,1},
        {0,0,1},       {0,0,1}, {0,0,1}};
int resultPoints[][3]={{0,0,1},       {0,0,1},     {0,0,1},       {0,0,1},       {0,0,1},
        {0,0,1},       {0,0,1}, {0,0,1}};
int scale=400;
void myputpixel(float x,float y){
        glVertex2f(x+100.0,y+150.0);
}
void initPoints(){
        int i;
        for(i=0;i<2*8;i++){
                Points[i]=1.0*(scale*point[i]);
        }
}
void init_homogeneousPoints(){
        int i;
        for(i=0;i<8;i++){
                homogeneousPoints[i][0]=Points[2*i];
                homogeneousPoints[i][1]=Points[2*i+1];
        }
}
//void matrix_mul(int n,int b[][3],int T[3][3],int r[][3]){
void matrix_mul(int n,int b[][3],int T[3][3],int r[][3]){/*有几个点  n就等于几*/
        int i;
        for(i=0;i<n;i++){
                r[i][0]=b[i][0]*T[0][0]+b[i][1]*T[1][0]+b[i][2]*T[2][0];
                r[i][1]=b[i][0]*T[0][1]+b[i][1]*T[1][1]+b[i][2]*T[2][1];
                r[i][2]=b[i][0]*T[0][2]+b[i][1]*T[1][2]+b[i][2]*T[2][2];
        }
}
void matrix_mul_float(int n,int b[][3],float T[3][3],int r[][3]){/*有几个点  n就等于几*/
        int i;
        for(i=0;i<n;i++){
                r[i][0]=b[i][0]*T[0][0]+b[i][1]*T[1][0]+b[i][2]*T[2][0];
                r[i][1]=b[i][0]*T[0][1]+b[i][1]*T[1][1]+b[i][2]*T[2][1];
                r[i][2]=b[i][0]*T[0][2]+b[i][1]*T[1][2]+b[i][2]*T[2][2];
        }
}
void Transform1(){/*（1）关于对称（y=-x）的对称变换*/
        /*(x,y,1)->(-y,-x,1)*/
        init_homogeneousPoints();
        int T1[3][3]={  {0,-1,0},
                        {-1,0,0},
                        {0,0,1}};
        matrix_mul(8,homogeneousPoints,T1,resultPoints);

        glBegin(GL_LINE_LOOP);
        int i;
        for(int i=0;i<8;i++){
                myputpixel((float)1.0*resultPoints[i][0], (float)1.0*resultPoints[i][1]);
        }
        glEnd();

}
void Transform2(){/*（2）绕着原点逆时针旋转75度*/
        init_homogeneousPoints();
        float a,b,c,d;
        float theta=75*0.0174533f;
        a=cos(theta); b=sin(theta);
        c=-sin(theta);d=cos(theta);

        float T2[3][3]={  {a,b,0},
                        {c,d,0},
                        {0,0,1}};
        matrix_mul_float(8,homogeneousPoints,T2,resultPoints);

        glBegin(GL_LINE_LOOP);
        int i;
        for(int i=0;i<8;i++){
                myputpixel((float)1.0*resultPoints[i][0], (float)1.0*resultPoints[i][1]);
        }
        glEnd();

}
void Transform3(){/*（3）平移（x方向52，y方向60）*/
        init_homogeneousPoints();
        int T3[3][3]={  {1,0,0},
                        {0,1,0},
                        {52,60,1}};
        matrix_mul(8,homogeneousPoints,T3,resultPoints);

        glBegin(GL_LINE_LOOP);
        int i;
        for(int i=0;i<8;i++){
                myputpixel((float)1.0*resultPoints[i][0], (float)1.0*resultPoints[i][1]);
        }
        glEnd();

}

void Transform4(){/*（4）将原图放大为2倍，将原图缩小为0.5*/
        init_homogeneousPoints();
        int T4_big[3][3]={  {2,0,0},
                            {0,2,0},
                            {0,0,1}};/*4）将原图放大为2倍，*/
        matrix_mul(8,homogeneousPoints,T4_big,resultPoints);
        glBegin(GL_LINE_LOOP);
        int i;
        for(int i=0;i<8;i++){
                myputpixel((float)1.0*resultPoints[i][0], (float)1.0*resultPoints[i][1]);
        }
        glEnd();
        float T4_small[3][3]={  {0.5,0,0},
                              {0,0.5,0},
                               {0,0,1}};/*4）将原图放大为2倍，*/
        matrix_mul_float(8,homogeneousPoints,T4_small,resultPoints);
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<8;i++){
                myputpixel((float)1.0*resultPoints[i][0], (float)1.0*resultPoints[i][1]);
        }
        glEnd();



}
void Transform5(){/*（5）X方向错切15度*/
        init_homogeneousPoints();
        float b,c;
        b=0;/*沿着x轴错切*/
        c=tan(15*0.0174533f);
        float T5[3][3]={  {1,b,0},
                        {c,1,0},
                        {0,0,1}};
        matrix_mul_float(8,homogeneousPoints,T5,resultPoints);

        glBegin(GL_LINE_LOOP);
        int i;
        for(int i=0;i<8;i++){
                myputpixel((float)1.0*resultPoints[i][0], (float)1.0*resultPoints[i][1]);
        }
        glEnd();

}
void matrix3_3_mul(float A[3][3],float B[3][3],float result[3][3]){
        int i,j,k;
        for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                        result[i][j]=0;
                        for(k=0;k<3;k++){
                                result[i][j]+=A[i][k]*B[k][j];
                        }
                }
        }

}
void Exp_Trans1(){/*实现关于（10，15）点旋转90度；*/
/*实验指导：使用矩阵相乘实现二维图形变换*/
        init_homogeneousPoints();
        float Exp_TA[3][3]={  {1,0,0},
                              {0,1,0},
                            {-10,-15,1}};
        float a,b,c,d;
        float theta=90*0.0174533f;
        a=cos(theta); b=sin(theta);
        c=-sin(theta);d=cos(theta);
        float Exp_TB[3][3]={  {a,b,0},
                              {c,d,0},
                               {0,0,1}};
        float Exp_TC[3][3]={  {1,0,0},
                              {0,1,0},
                              {10,15,1}};
        float Exp_temp[3][3]={0};
        float Exp_T1[3][3]={0};
        matrix3_3_mul(Exp_TA,Exp_TB,Exp_temp);
        matrix3_3_mul(Exp_temp,Exp_TC,Exp_T1);
        matrix_mul_float(8,homogeneousPoints,Exp_T1,resultPoints);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        int i;
        for(int i=0;i<8;i++){
                myputpixel((float)1.0*resultPoints[i][0], (float)1.0*resultPoints[i][1]);
        }
        glEnd();

}
void Exp_Trans2(){/*实现关于  y=15x+30对称*/
/*y=kx+b,alpha = arctg(k)*/
/*实验指导：使用矩阵相乘实现二维图形变换*/
        init_homogeneousPoints();
        float b;
        b=30;
        float Exp_TA[3][3]={  {1,0,0},
                              {0,1,0},
                              {0,-b,1}};
        double alpha=atan(double(15));
        float Exp_TB[3][3]={  {cos(-alpha),sin(-alpha),0},
                              {-sin(-alpha),cos(-alpha),0},
                               {0,         0,           1}};
        float Exp_TC[3][3]={   {1,0,0},
                               {0,-1,0},
                               {0,0,1}};
        float Exp_TD[3][3]={  {cos(alpha),sin(alpha),0},
                              {-sin(alpha),cos(alpha),0},
                              {0           ,0      ,1}};
        float Exp_TE[3][3]={  {1,0,0},
                              {0,1,0},
                              {0,b,1}};
        float Exp_temp1[3][3]={0};
        float Exp_temp2[3][3]={0};
        float Exp_T2[3][3]={0};
        matrix3_3_mul(Exp_TA,Exp_TB,Exp_temp1);
        matrix3_3_mul(Exp_temp1,Exp_TC,Exp_temp2);
        matrix3_3_mul(Exp_temp2,Exp_TD,Exp_temp1);
        matrix3_3_mul(Exp_temp1,Exp_TE,Exp_T2);
        matrix_mul_float(8,homogeneousPoints,Exp_T2,resultPoints);
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
        int i;
        for(int i=0;i<8;i++){
                myputpixel((float)1.0*resultPoints[i][0], (float)1.0*resultPoints[i][1]);
        }
        glEnd();
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0f);
    //glBegin(GL_POINTS);//必须是加上s，要不然显示不了
    //glBegin(GL_LINES);//必须是加上s，要不然显示不了
    initPoints();
    glBegin(GL_LINE_LOOP);
    int i;
    for(int i=0;i<8;i++){
            myputpixel((float)1.0*Points[2*i], (float)1.0*Points[2*i+1]);
    }

    glEnd();
    Transform1();/*（1）关于对称（y=-x）的对称变换*/
    Transform2();/*（2）绕着原点逆时针旋转75度*/
    Transform3();/*（3）平移（x方向52，y方向60）*/
    Transform4();/*（4）将原图放大为2倍，将原图缩小为0.5*/
    Transform5();/*（5）X方向错切15度*/
    Exp_Trans1();/* 实现关于（10，15）点旋转90度；*/
    Exp_Trans2();/* 实现关于  y=15x+30对称*/
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);

    glEnd();
    glFlush();
}
void init(void){
    //glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
    /*这句话非常重要*/
}

int main(int argc,char* argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(50, 100);
        glutInitWindowSize(windowWidth, windowHeight);
        glutCreateWindow("Matrix Transform");
        init();
        glutDisplayFunc(&Display);
        glutMainLoop();
        return 0;
}

// 实验题目：编写程序实现图形的二维变换
// （1）关于对称（y=-x）的对称变换
// （2）绕着原点逆时针旋转75度
// （3）平移（x方向52，y方向60）
// （4）将原图放大为2倍，将原图缩小为0.5
// （5）X方向错切15度
// 实验目的：熟悉二维变换
// 实验指导：使用矩阵相乘实现二维图形变换
//
// 实现关于（10，15）点旋转90度；
// 实现关于  y=15x+30对称
