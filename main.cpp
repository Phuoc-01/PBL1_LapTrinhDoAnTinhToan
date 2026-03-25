#include <stdio.h>
#include <string.h>

#define MAXN 101

int n, m;
int adj[MAXN][MAXN];   
int in_degree[MAXN];   
int out_degree[MAXN];  
int visited[MAXN];
int temp_adj[MAXN][MAXN];
int EC[MAXN*MAXN];

void init() {
    memset(adj, 0, sizeof(adj));
    memset(in_degree, 0, sizeof(in_degree));
    memset(out_degree, 0, sizeof(out_degree));
    memset(visited, 0, sizeof(visited));
}

void nhap_vo_huong() {
    printf("\n--- NHAP DO THI VO HUONG ---\n");
    printf("Nhap so dinh va so canh: ");
    scanf("%d %d", &n, &m);
    
    printf("Nhap %d canh (u v):\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v]++;
        adj[v][u]++;
        out_degree[u]++;  
        out_degree[v]++;
    }
}

void nhap_co_huong() {
    printf("\n--- NHAP DO THI CO HUONG ---\n");
    printf("Nhap so dinh va so canh: ");
    scanf("%d %d", &n, &m);
    
    printf("Nhap %d canh (u v):\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v]++;        
        out_degree[u]++;    
        in_degree[v]++;     
    }
}

int find_start_vo_huong() {
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] > 0) return i;
    }
    return -1;
}

int find_start_co_huong() {
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] > 0) return i;
    }
    return -1;
}

void dfs(int u, int graph[MAXN][MAXN]) {
    visited[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] > 0 && !visited[v]) {
            dfs(v, graph);
        }
    }
}

int isConnected() {
    int start = find_start_vo_huong();
    if (start == -1) return 0;
    
    memset(visited, 0, sizeof(visited));
    dfs(start, adj);
    
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] > 0 && !visited[i]) return 0;
    }
    return 1;
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
    
    
    memset(visited, 0, sizeof(visited));
    dfs(start, adj);
    for (int i = 1; i <= n; i++) {
        if ((in_degree[i] + out_degree[i] > 0) && !visited[i]) 
            return 0;
    }
    
    int rev_adj[MAXN][MAXN] = {0};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (adj[i][j] > 0) {
                rev_adj[j][i] = adj[i][j];
            }
        }
    }
    
    memset(visited, 0, sizeof(visited));
    dfs(start, rev_adj);
    for (int i = 1; i <= n; i++) {
        if ((in_degree[i] + out_degree[i] > 0) && !visited[i]) 
            return 0;
    }
    
    return 1;
}

int kiem_tra_chu_trinh_euler_vo_huong() {
    if (!isConnected()) {
        printf("Do thi khong lien thong!\n");
        return 0;
    }
    
    int dem_le = 0;
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] % 2 != 0) {
            dem_le++;
        }
    }
    
    if (dem_le == 0) return 1;
    
    printf("So dinh bac le: %d\n", dem_le);
    return 0;
}

int kiem_tra_chu_trinh_euler_co_huong() {
    if (!isStronglyConnected()) {
        printf("Do thi khong lien thong manh!\n");
        return 0;
    }
    
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] != out_degree[i]) {
            printf("Dinh %d: in_degree = %d, out_degree = %d\n", i, in_degree[i], out_degree[i]);
            return 0;
        }
    }
    return 1;
}

void euler_cycle_vo_huong(int u) {
    memcpy(temp_adj, adj, sizeof(adj));
    
    int stack[MAXN], top = 0;
    int ecSize = 0;
    
    stack[top++] = u;
    while (top > 0) {
        int x = stack[top-1];
        int found = 0;
        
        for (int y = 1; y <= n; y++) {
            if (temp_adj[x][y] > 0) {
                stack[top++] = y;
                temp_adj[x][y]--;
                temp_adj[y][x]--;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            EC[ecSize++] = x;
            top--;
        }
    }
    
    printf("Chu trinh Euler: ");
    for (int i = ecSize-1; i >= 0; i--) {
        printf("%d ", EC[i]);
    }
    printf("\n");
}

void euler_cycle_co_huong(int u) {
    memcpy(temp_adj, adj, sizeof(adj));
    
    int stack[MAXN], top = 0;
    int ecSize = 0;
    
    stack[top++] = u;
    while (top > 0) {
        int x = stack[top-1];
        int found = 0;
        
        for (int y = 1; y <= n; y++) {
            if (temp_adj[x][y] > 0) {
                stack[top++] = y;
                temp_adj[x][y]--;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            EC[ecSize++] = x;
            top--;
        }
    }
    
    printf("Chu trinh Euler: ");
    for (int i = ecSize-1; i >= 0; i--) {
        printf("%d ", EC[i]);
    }
    printf("\n");
}

int main() {
    printf("\n======== TIM CHU TRINH EULER ========\n");
    
    int choice;
    printf("Chon chu trinh euler vo huong hoac co huong\n");
    printf("1. Chu Trinh Euler Vo Huong\n");
    printf("2. Chu Trinh Euler Co Huong\n");
    printf("Lua chon cua ban: ");
    scanf("%d", &choice);
    
    init();
    
    if (choice == 1) {
        nhap_vo_huong();
        
        if (kiem_tra_chu_trinh_euler_vo_huong()) {
            int start = find_start_vo_huong();
            euler_cycle_vo_huong(start);
        } else {
            printf("\nKhong ton tai chu trinh Euler trong do thi vo huong!\n");
        }
    } 
    else if (choice == 2) {
        nhap_co_huong();
        
        if (kiem_tra_chu_trinh_euler_co_huong()) {
            int start = find_start_co_huong();
            euler_cycle_co_huong(start);
        } else {
            printf("\nKhong ton tai chu trinh Euler trong do thi co huong!\n");
        }
    } 
    else {
        printf("Lua chon khong hop le!\n");
    }
    
    return 0;
}