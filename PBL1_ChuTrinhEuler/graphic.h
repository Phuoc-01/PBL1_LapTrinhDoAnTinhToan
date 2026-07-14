#ifndef GRAPHICS_H
#define GRAPHICS_H

void initVertexColors(int n);
void initVertexPositions(int n);
void drawBorder();
void drawGraphHeader(const char *title);
void drawVertex(int id, int isHighlight);
void drawEdge(int u, int v, int color, int thickness, int isDirected);
void drawFullGraph(int highlightVertex);
void drawStepInfo(int step, int total, int from, int to);
void simulateEulerCycle(int cycle[], int len);
void drawGraphAndSimulate(int cycle[], int len);
void setAnimationSpeedValue(int speed);

extern int animationSpeed;

#endif

