#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int n, m;
int adj[MAXN][MAXN];   
int in_degree[MAXN];   
int out_degree[MAXN];  
int visited[MAXN];

void nhap() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v]++;        
        out_degree[u]++;
        in_degree[v]++;
    }
}

int find_start() {
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] > 0) return i;
    }
    return -1;
}

void dfs(int u) {
    visited[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (adj[u][v] > 0 && !visited[v]) {
            dfs(v);
        }
    }
}

int isStronglyConnected() {
    int start = -1;
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] + in_degree[i] > 0) {
            start = i;
            break;
        }
    }
    if (start == -1) return 0;

    for (int i = 1; i <= n; i++) visited[i] = 0;
    dfs(start);
    for (int i = 1; i <= n; i++) {
        if ((in_degree[i] + out_degree[i] > 0) && !visited[i]) return 0;
    }

    for (int i = 1; i <= n; i++) visited[i] = 0;
   
    int rev[MAXN][MAXN];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            rev[i][j] = adj[j][i];

    int stack[MAXN], top = 0;
    stack[top++] = start;
    visited[start] = 1;
    while (top > 0) {
        int u = stack[--top];
        for (int v = 1; v <= n; v++) {
            if (rev[u][v] > 0 && !visited[v]) {
                visited[v] = 1;
                stack[top++] = v;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if ((in_degree[i] + out_degree[i] > 0) && !visited[i]) return 0;
    }
    return 1;
}

int hasEulerCycle() {
    if (!isStronglyConnected()) return 0;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] != out_degree[i]) return 0;
    }
    return 1;
}

void euler_cycle(int u) {
    int stack[MAXN], top = 0;
    int EC[MAXN*MAXN], ecSize = 0;

    stack[top++] = u;
    while (top > 0) {
        int x = stack[top-1];
        int found = 0;
        for (int y = 1; y <= n; y++) {
            if (adj[x][y] > 0) {
                stack[top++] = y;
                adj[x][y]--;
                found = 1;
                break;
            }
        }
        if (!found) {
            EC[ecSize++] = x;
            top--;
        }
    }

    for (int i = ecSize-1; i >= 0; i--) {
        printf("%d ", EC[i]);
    }
    printf("\n");
}

int main() {
    nhap();
    if (hasEulerCycle()) {
        int start = find_start();  
		if (start == -1) {
    		printf("Do thi khong co canh\n");
    		return;
		}
		euler_cycle(start);
    } else {
        printf("Khong ton tai chu trinh Euler\n");
    }
    return 0;
}