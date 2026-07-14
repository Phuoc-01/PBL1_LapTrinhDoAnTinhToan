#include "algorithm.h"
#include "ui.h"
#include <string.h>
#include <stdio.h>

int n,m;
int adj[MAXN][MAXN];
int temp_adj[MAXN][MAXN];
int resultCycle[200005];
int resultLen;
int isDirected;
int hasEuler;

/* --------------------------------
    THUAT TOAN FLEURY
 --------------------------------*/
 
int deg[MAXN];
int in_deg[MAXN];
int out_deg[MAXN];
int visitedF[MAXN];
int pathF[200005];
int idxF;
 
void resetVisitedF(){
    for(int i=1; i<=n; i++){
        visitedF[i] = 0;
    }
}

int isConnected() {
    int visited[MAXN] = {0};
    int startNode = -1;

    for (int i=1; i<=n; i++) {
        int degree = 0;
        for (int j=1; j<=n; j++) if (adj[i][j] > 0) degree++;
        if (degree > 0) {
            startNode = i;
            break;
        }
    }

    if (startNode == -1) return 1;

    int stack[MAXN], top = 0;
    stack[top++] = startNode;
    visited[startNode] = 1;
    while (top > 0) {
        int u = stack[--top];
        for (int v=1; v<=n; v++) {
            if (adj[u][v] > 0 && !visited[v]) {
                visited[v] = 1;
                stack[top++] = v;
            }
        }
    }

    for (int i=1; i<=n; i++) {
        int degree = 0;
        for (int j = 1; j <= n; j++) if (adj[i][j] > 0) degree++;
        if (degree > 0 && !visited[i]) return 0; 
    }
    return 1;
}

int countReachable(int u){
    visitedF[u] = 1;
    int count = 1;
    for(int v=1; v<=n; v++){
        if(temp_adj[u][v]>0 && !visitedF[v]){
            count += countReachable(v);
        }
    }
    return count;
}

int isPathExist(int s, int t) {
    int visited[MAXN] = {0};
    int stack[MAXN], top = 0;
    
    stack[top++] = s;
    visited[s] = 1;
    
    while(top > 0) {
        int u = stack[--top];
        if (u == t) return 1;
        for (int v = 1; v <= n; v++) {
            if (temp_adj[u][v] > 0 && !visited[v]) {
                visited[v] = 1;
                stack[top++] = v;
            }
        }
    }
    return 0;
}

int isBridge(int u, int v, int isDirected){
    int degreeU = 0;
    for(int i=1; i<=n; i++){
        if(temp_adj[u][i]>0) degreeU++;
    }
    if(degreeU<=1) return 0;

    if (isDirected) {
        temp_adj[u][v]--; 
        
        int canGoBack = isPathExist(v, u); 
        
        temp_adj[u][v]++;
        return !canGoBack; 
    } 
    else {
        resetVisitedF(); 
        int count1 = countReachable(u);
        
        temp_adj[u][v]--;
        temp_adj[v][u]--;

        resetVisitedF();
        int count2 = countReachable(u);

        temp_adj[u][v]++;
        temp_adj[v][u]++;

        return (count1 > count2);
    }
}

void fleury_execute(int isDirected, int *cycle, int *len){
	memcpy(temp_adj, adj, sizeof(adj));
    // Step 1: Kiem tra dieu kien va chon dinh xuat phat
    int odd_nodes = 0;
    int startNode = -1;
    if(!isDirected){
        for(int i=1; i<=n; i++){
            if(deg[i]%2 != 0){
                odd_nodes++;
                if(startNode == -1) startNode = i;
            }
        }
        if(startNode == -1){
            for(int i=1; i<=n; i++){
                if(deg[i]>0){
                    startNode = i; 
                    break;
                }
            }
        }
        if(odd_nodes != 0 && odd_nodes != 2){
        	*len = 0;
    		print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    		hasEuler = 0;
            return;
        }
    }
    else{
        int start_candidates = 0, end_candidates = 0;
        for(int i=1; i<=n; i++){
            if(out_deg[i] - in_deg[i] == 1){
                start_candidates++;
                startNode = i;
            }
            else if (in_deg[i] - out_deg[i] == 1){
                end_candidates++;
            }
            else if (in_deg[i] != out_deg[i]){
            	*len = 0;
    			print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    			hasEuler = 0;
                return;
            }
        }
        if(startNode == -1){
            for(int i=1; i<=n; i++){
                if(out_deg[i]>0){
                    startNode = i;
                    break;
                }
            }
        }
    }
    if(startNode == -1){
    	*len = 0;
    	print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    	hasEuler = 0;
        return;
    }
    if (!isConnected()) {
        *len = 0;
        print_error("Do thi KHONG co chu trinh hay duong di Euler!");
        hasEuler = 0;
        return;
    }

    // Step 2: Thuc hien thuat toan
    int curr = startNode;
    idxF = 0;
    pathF[idxF++] = curr;
    
    for(int step=0; step<m; step++){
        int nextV = -1;
        for(int v=1; v<=n; v++){
        	if (nextV == -1) nextV = v; 
            if(temp_adj[curr][v]>0){
                nextV = v;
                if(!isBridge(curr, v, isDirected)) break;
            }
        }
        if(nextV != -1){
            pathF[idxF++] = nextV;
            if(!isDirected){
                temp_adj[curr][nextV]--;
                temp_adj[nextV][curr]--;
            }
            else{
                temp_adj[curr][nextV]--;
            }
            curr = nextV;
        }
    }
    // Step 3: Tra ve ket qua
    *len = idxF;
    if((*len!=m)&&(*len!=m+1)){
    	print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    	hasEuler = 0;
        return;
    }
    for(int i = 0; i < idxF; i++){
        cycle[i] = pathF[i];
    }
    if(cycle[0]==cycle[*len-1]){
    	print_success("Do thi CO chu trinh Euler!");
    	hasEuler = 1;
    }
    else{
    	print_success("Do thi CO duong di Euler!");
    	hasEuler = 1;
    }
}

/* --------------------------------
    THUAT TOAN HIERHOLZER
 --------------------------------*/
int in_degree[MAXN], out_degree[MAXN];
int stackH[200005];
int resH[200005];

void initH(){
    memset(adj, 0, sizeof(adj));
    memset(in_degree, 0, sizeof(in_degree));
    memset(out_degree, 0, sizeof(out_degree));
    memset(resH, 0, sizeof(resH));
    memset(stackH, 0, sizeof(stackH));
}

void hierholzer_execute(int isDirected, int *cycle, int *len){
    int startNode = -1;
    int oddCount = 0;
    int startNodes = 0, endNodes = 0;
    int hasEdges = 0;

    //Step 1: Xac dinh dinh xuat phat
    if(!isDirected){
        int firstNodeWithEdge = -1;
        for(int i=1; i<=n; i++){
            if(out_degree[i]>0){
                if(firstNodeWithEdge == -1) firstNodeWithEdge = i;
                hasEdges = 1;
            }
            if(out_degree[i]%2 != 0){
                oddCount++;
                if(startNode == -1) startNode = i;
            }
        }
        if(startNode == -1) startNode = firstNodeWithEdge;

        if(oddCount != 0 && oddCount != 2){
        	*len = 0;
    		print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    		hasEuler = 0;
            return;
        }
    }
    else{
        int firstNodeWithEdge = -1;
        for(int i=1; i<=n; i++){
            if(out_degree[i]>0 || in_degree[i]>0) hasEdges = 1;
            if(out_degree[i]>0 && firstNodeWithEdge == -1){
                firstNodeWithEdge = i;
            }
            int diff = out_degree[i]-in_degree[i];
            if(diff==1){
                startNodes++;
                startNode = i;
            }
            else if (diff==-1){
                endNodes++;
            }
            else if (diff!=0){
            	*len = 0;
    			print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    			hasEuler = 0;
                return;
            }
        }
        if(startNode == -1) startNode = firstNodeWithEdge;

        if(!((startNodes==0 && endNodes==0)||(startNodes==1 && endNodes==1))){
        	*len = 0;
    		print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    		hasEuler = 0;
            return;
        }
    }
    if (!hasEdges || startNode == -1){
    	*len = 0;
    	print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    	hasEuler = 0;
        return;
    }
    
    // Step 2: Thuc hien thuat toan
    memcpy(temp_adj, adj, sizeof(adj));
    int top = 0;
    int resIdx = 0;
    stackH[top++] = startNode;

    while(top>0){
        int u = stackH[top-1];
        int found = 0;
        for(int v=1; v<=n; v++){
            if(temp_adj[u][v]>0){
                stackH[top++]=v;
                temp_adj[u][v]--;
                if(!isDirected) temp_adj[v][u]--;
                found = 1;
                break;
            }
        }
        if(!found){
            resH[resIdx++]=u;
            top--;
        }
    }

    // Step 3: Kiem tra lien thong
    if(resIdx-1 < m){
    	*len = 0;
    	print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    	hasEuler = 0;
        return;
    }
    
    // Step 4: Tra ve ket qua
    *len = resIdx;
    if((*len!=m)&&(*len!=m+1)){
    	print_error("Do thi KHONG co chu trinh hay duong di Euler!");
    	hasEuler = 0;
        return;
    }
    for(int i = 0; i < resIdx; i++){
        cycle[i] = resH[resIdx - 1 - i];
    }
    if(cycle[0]==cycle[*len-1]){
    	print_success("Do thi CO chu trinh Euler!");
    	hasEuler = 1;
    }
    else{
    	print_success("Do thi CO duong di Euler!");
    	hasEuler = 1;
    }
}

