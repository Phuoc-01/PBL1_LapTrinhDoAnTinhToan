#include "graphic.h"
#include "algorithm.h"
#include "ui.h"
#include <winbgim.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define RADIUS 22
#define SOLID_LINE 0
#define SOLID_FILL 1
#define DEFAULT_FONT 0
#define HORIZ_DIR 0

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

int vx[101], vy[101];
int centerX = 560, centerY = 420; 
int radiusLayout = 180;
int vertexColors[101];
int animationSpeed = 500;

extern int n, m;
extern int adj[101][101];
extern int isDirected;

void initVertexColors(int n){
    int colorList[] = {
        COLOR(255, 180, 180), COLOR(180, 255, 180), COLOR(180, 180, 255),
        COLOR(255, 255, 180), COLOR(255, 180, 255), COLOR(180, 255, 255),
        COLOR(255, 200, 160), COLOR(200, 160, 255), COLOR(160, 220, 180),
        COLOR(255, 220, 180)
    };
    for(int i=1; i<=n; i++){
        vertexColors[i] = colorList[i % 10];
    }
}


void initVertexPositions(int n){
    int dynamicRadiusLayout = 180;
    int dynamicVertexSize = 22;

    if (n > 20) {
        dynamicRadiusLayout = 250 + (n * 2); 
        dynamicVertexSize = 25 - (n / 5);    
        if (dynamicVertexSize < 8) dynamicVertexSize = 8; 
    }

    for(int i=1; i<=n; i++){
        double angle = 2 * 3.14159 * i / n - 3.14159 / 2;
        vx[i] = centerX + dynamicRadiusLayout * cos(angle);
        vy[i] = centerY + dynamicRadiusLayout * sin(angle);
    }
}

void drawBorder(){
    setcolor(COLOR(200, 180, 100));
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);
    setlinestyle(SOLID_LINE, 0, 1);
}

void drawGraphHeader(const char *title){
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(200, 180, 100));
    outtextxy((getmaxx() - textwidth((char*)title)) / 2, 30, (char*)title);
}

void drawVertex(int id, int isHighlight){
    char str[5];
    sprintf(str, "%d", id); 

    setcolor(DARKGRAY);
    circle(vx[id] + 2, vy[id] + 2, RADIUS);

    setfillstyle(SOLID_FILL, vertexColors[id]);
    setcolor(WHITE);
    fillellipse(vx[id], vy[id], RADIUS, RADIUS); 

    if(isHighlight){
        setcolor(COLOR(255, 200, 0));
        setlinestyle(SOLID_LINE, 0, 3);
        circle(vx[id], vy[id], RADIUS);
        setlinestyle(SOLID_LINE, 0, 1);
    }

    setbkcolor(vertexColors[id]); 
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    outtextxy(vx[id] - textwidth(str)/2, vy[id] - textheight(str)/2, str);
    setbkcolor(BLACK); 
}


void drawEdge(int u, int v, int color, int thickness, int isDirected) {
    setcolor(color);
    setlinestyle(SOLID_LINE, 0, thickness);
    
    line(vx[u], vy[u], vx[v], vy[v]);
    
    if (isDirected) {
        double angle = atan2(vy[v] - vy[u], vx[v] - vx[u]);
        
        int x_tip = vx[v] - RADIUS * cos(angle);
        int y_tip = vy[v] - RADIUS * sin(angle);
        
        int arrowLength = 12;      
        double arrowAngle = 0.5;   
        
        int x_wing1 = x_tip - arrowLength * cos(angle - arrowAngle);
        int y_wing1 = y_tip - arrowLength * sin(angle - arrowAngle);
        
        int x_wing2 = x_tip - arrowLength * cos(angle + arrowAngle);
        int y_wing2 = y_tip - arrowLength * sin(angle + arrowAngle);
        
        line(x_tip, y_tip, x_wing1, y_wing1);
        line(x_tip, y_tip, x_wing2, y_wing2);
    }
    
    setlinestyle(SOLID_LINE, 0, 1); 
}

void drawFullGraph(int highlightVertex, int isDirected){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(adj[i][j] > 0){
                drawEdge(i, j, COLOR(160, 160, 180), 2, isDirected);
            }
        }
    }
    for(int i=1; i<=n; i++){
        drawVertex(i, (i == highlightVertex));
    }
}

void drawStepInfo(int step, int total, int from, int to){
    char str[200];
    
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(20, 60, 250, 120); //250
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(COLOR(200, 180, 100));
    sprintf(str, "BUOC %d / %d", step, total);
    outtextxy(30, 70, str);
    
    setcolor(COLOR(100, 200, 200));
    sprintf(str, "Dang di: %d -> %d", from, to);
    outtextxy(30, 90, str);
}

void simulateEulerCycle(int cycle[], int len){
    cleardevice();
    drawBorder();
    drawGraphHeader("MO PHONG CHU TRINH EULER");
    drawFullGraph(-1, isDirected);
    
    for(int i = 0; i < len - 1; i++){
        drawStepInfo(i + 1, len - 1, cycle[i], cycle[i + 1]);
        
        drawEdge(cycle[i], cycle[i+1], COLOR(255, 100, 100), 4, isDirected);
        drawVertex(cycle[i+1], 1);
        
        delay(animationSpeed);
        
        drawEdge(cycle[i], cycle[i+1], COLOR(100, 200, 100), 3, isDirected);
        drawVertex(cycle[i+1], 0);
    }
    
    setcolor(COLOR(200, 180, 100));
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    char str[2000] = "Chu trinh Euler: ";
	int startX = 30;
	int startY = getmaxy() - 80;
	int currentX = startX;
	int currentY = startY;
	int limitX = getmaxx() - 50; 
	
	setcolor(COLOR(200, 180, 100));
	outtextxy(startX, currentY - 20, "KET QUA:");
	
	for (int i = 0; i < len; i++) {
	    char num[15];
	    sprintf(num, "%d%s", cycle[i], (i == len - 1) ? "" : " -> ");
	    
	    if (currentX + textwidth(num) > limitX) {
	        currentX = startX;   
	        currentY += 20;      
	    }
	    
	    outtextxy(currentX, currentY, num);
	    currentX += textwidth(num); 
	}
}

void drawGraphAndSimulate(int cycle[], int len){
    initVertexColors(n);
    initVertexPositions(n);
    
    initwindow(1260, 900); 
    setbkcolor(BLACK);
    cleardevice();
    
    if(len > 0){
        simulateEulerCycle(cycle, len);
    } else {
        drawBorder();
        drawGraphHeader("DO THI BAN DAU");
        drawFullGraph(-1, isDirected);
        setcolor(WHITE);
        outtextxy(30, getmaxy() - 40, "Nhan phim bat ky de dong cua so...");
        getch();
    }
    
    //delay(2000);
    getch();
    
    closegraph();
}

void setAnimationSpeedValue(int speed){
    animationSpeed = speed;
}

