/*本程序采用Ubunru系统下的OpenGL开发
 *      2017 邱日
 */
#include <GL/glut.h>
const int windowHeight= 400;
const int windowWidth= 400;
typedef struct Edge{
        int ymax;
        float x;
        float deltax;
        struct Edge* next;
}LinkEdge,*LinkpEdge;
typedef struct{
        int nline;
        LinkpEdge pEdge;
}linestruct;
Edge *EdgeTable[windowHeight];
Edge *ActiveEdgeTable;
//linestruct ActiveEdgeTable[4];/*活动边表*/
float point[]={1.0*2/20,1.0*9/20,     1.0*7/20,1.0*7/20,    1.0*13/20,1.0*11/20   ,1.0*13/20,1.0*5/20,
                1.0*7/20,1.0*1/20,    1.0*2/20,1.0*3/20,    1.0*2/20,1.0*9/20};//20为基准//7个点
int Points[]={0,0,       0,0,     0,0,       0,0,
        0,0,       0,0,       0,0};
int scale=400;
void initPoints(){
        int i;
        for(i=0;i<2*7;i++){
                Points[i]=1.0*(scale*point[i]);
        }
}
int getmaxY(){
        int maxY=0;
        int i;
        for(i=0;i<7;i++){//总共7个点
                if(Points[2*i+1]>maxY){
                        maxY=Points[2*i+1];//找最大的y
                }
        }
        return maxY;
}
void mkEdgeTable(){
        int i;
        int x0,x1,x2,x3;
        int y0,y1,y2,y3;
        int ymin;/*下端点y坐标*/
        int ymax;/*上端点坐标*/
        float x;/*下端点x坐标*/
        float deltax;/*斜率的倒数*/
        for(i=0;i<7;i++){
                //当前点(x1,y1)
                x1=Points[2*i];
                y1=Points[2*i+1];
                //前一个点(x0,y0)
                x0=Points[(2*(i-1)+7)%7];//这次总共7个点
                y0=Points[(2*(i-1)+1+7)%7];
                //后一个点(x2,y2);
                x2=Points[(2*(i+1)+7)%7];//这次总共7个点
                y2=Points[(2*(i+1)+1+7)%7];
                //后后的点(x3,y3);
                x3=Points[(2*(i+2)+7)%7];//这次总共7个点
                y3=Points[(2*(i+2)+1+7)%7];

                if(y1==y2)continue;/*若是水平线，跳出本次循环，不要*/
                ymin=y1>y2?y2:y1;/*下端点坐标*/
                ymax=y1>y2?y1:y2;/*上端点坐标*/
                x=y1>y2?x2:x1;/*下端点x坐标*/
                deltax=(x1-x2)*1.0f/(y1-y2);/*dx=1/k*/
                /*y0<y1<y0 y1 y3<y2<y1 y2*/
                if(((y0<y1)&&(y1<y2))||((y3<y2)&&(y2<y1))){
                        ymin++;
                        x+=deltax;
                }
                LinkpEdge p=(LinkpEdge)malloc(sizeof(LinkEdge));
                p->ymax=ymax;
                p->x=x;
                p->deltax=deltax;
                p->next=EdgeTable[ymin]->next;
                EdgeTable[ymin]->next=p;
        }

}
void initEdgeTable(){
        int i;
        int maxY=getmaxY();
        for(i=0;i<maxY;i++){
                EdgeTable[i]=(LinkpEdge)malloc(sizeof(LinkEdge));
                EdgeTable[i]->next=NULL;
        }
}
void Scan(){
        int maxY=getmaxY();
        int i;
        Edge *ptemp;
        Edge *p=ActiveEdgeTable;
        Edge *pdraw=ActiveEdgeTable;
        Edge *p_temp;
        for(i=0;i<maxY;i++){
                while(EdgeTable[i]->next){
                        ptemp=EdgeTable[i]->next;
                        p=ActiveEdgeTable;
                        while(p->next){
                                if(ptemp->x>p->next->x){
                                        p=p->next;
                                        continue;
                                }
                                if(ptemp->x==p->next->x && ptemp->deltax>p->next->deltax){
                                        p=p->next;
                                        continue;
                                }
                                break;
                        }
                        EdgeTable[i]->next=ptemp->next;
                        ptemp->next=p->next;
                        p->next=ptemp;
                }
                pdraw=ActiveEdgeTable;
                int x;
                while(pdraw->next&&pdraw->next->next){
                        for(x=pdraw->next->x;x<pdraw->next->next->x;x++){
                                 glVertex2i(x, i);
                        }
                        pdraw=pdraw->next->next;
                }

                pdraw=ActiveEdgeTable;
                while(pdraw->next){
                        if(pdraw->next->ymax==i){
                                p_temp=pdraw->next;
                                pdraw->next=p_temp->next;
                                p_temp->next=NULL;
                                free(p_temp);
                        }
                        else{
                                pdraw=pdraw->next;
                        }
                }
                pdraw=ActiveEdgeTable;
                while (pdraw->next) {
                        pdraw->next->x+=pdraw->next->deltax;
                        pdraw=pdraw->next;

                }
        }


}
void initActiveEdgeTable(){
        ActiveEdgeTable=(LinkpEdge)malloc(sizeof(LinkEdge));
        ActiveEdgeTable->next=NULL;
}
void ScanLine()
{
        initEdgeTable();
        initActiveEdgeTable();
        mkEdgeTable();
        Scan();
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0f);
    //glBegin(GL_POINTS);//必须是加上s，要不然显示不了
    //glBegin(GL_LINES);//必须是加上s，要不然显示不了
    glBegin(GL_LINE_LOOP);
    initPoints();
    int i;
    for(int i=0;i<7;i++){
            glVertex2f((float)1.0*Points[2*i], (float)1.0*Points[2*i+1]);
    }
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    ScanLine();
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
        glutCreateWindow("ScanLine");
        init();
        glutDisplayFunc(&Display);
        glutMainLoop();
        return 0;
}
