#ifndef ALGORITHM_H
#define ALGORITHM_H

#define MAXN 101

extern int n, m;
extern int adj[MAXN][MAXN];
extern int temp_adj[MAXN][MAXN];
extern int resultCycle[200005];
extern int resultLen;
extern int isDirected;
extern int hasEuler;

extern int deg[MAXN];
extern int in_deg[MAXN];
extern int out_deg[MAXN];
extern int visitedF[MAXN];
extern int pathF[200005];
extern int idxF;

void resetVisitedF();
int countReachable(int u);
int isPathExist(int s, int t);
int isBridge(int u, int v, int isDirected);
void fleury_execute(int isDirected, int *cycle, int *len);

extern int in_degree[MAXN], out_degree[MAXN];
extern int stackH[200005];
extern int resH[200005];

void initH();
void hierholzer_execute(int isDirected, int *cycle, int *len);

#endif

