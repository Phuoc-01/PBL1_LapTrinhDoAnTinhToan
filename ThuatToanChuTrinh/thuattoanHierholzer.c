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

void nhap_vo_huong_console() {
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

void nhap_co_huong_console() {
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

void nhap_vo_huong_file(FILE *f) {
    fscanf(f, "%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        fscanf(f, "%d %d", &u, &v);
        adj[u][v]++;
        adj[v][u]++;
        out_degree[u]++;
        out_degree[v]++;
    }
}

void nhap_co_huong_file(FILE *f) {
    fscanf(f, "%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        fscanf(f, "%d %d", &u, &v);
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

int kiem_tra_chu_trinh_euler_vo_huong(FILE *out) {
    if (!isConnected()) {
        if(out) fprintf(out, "Do thi khong lien thong!\n");
        else printf("Do thi khong lien thong!\n");
        return 0;
    }
    
    int dem_le = 0;
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] % 2 != 0) {
            dem_le++;
        }
    }
    
    if (dem_le == 0) return 1;
    
    if(out) fprintf(out, "So dinh bac le: %d\n", dem_le);
    else printf("So dinh bac le: %d\n", dem_le);
    return 0;
}

int kiem_tra_chu_trinh_euler_co_huong(FILE *out) {
    if (!isStronglyConnected()) {
        if(out) fprintf(out, "Do thi khong lien thong manh!\n");
        else printf("Do thi khong lien thong manh!\n");
        return 0;
    }
    
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] != out_degree[i]) {
            if(out) fprintf(out, "Dinh %d: in_degree = %d, out_degree = %d\n", i, in_degree[i], out_degree[i]);
            else printf("Dinh %d: in_degree = %d, out_degree = %d\n", i, in_degree[i], out_degree[i]);
            return 0;
        }
    }
    return 1;
}

void euler_cycle_vo_huong(int u, FILE *out) {
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
    
    if(out) fprintf(out, "Chu trinh Euler: ");
    else printf("Chu trinh Euler: ");
    
    for (int i = ecSize-1; i >= 0; i--) {
        if(out) fprintf(out, "%d ", EC[i]);
        else printf("%d ", EC[i]);
    }
    if(out) fprintf(out, "\n");
    else printf("\n");
}

void euler_cycle_co_huong(int u, FILE *out) {
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
    
    if(out) fprintf(out, "Chu trinh Euler: ");
    else printf("Chu trinh Euler: ");
    
    for (int i = ecSize-1; i >= 0; i--) {
        if(out) fprintf(out, "%d ", EC[i]);
        else printf("%d ", EC[i]);
    }
    if(out) fprintf(out, "\n");
    else printf("\n");
}

int main() {
    int mode, type;
    
    printf("\n======== THUAT TOAN STACK ========\n");
    printf("Chon che do nhap xuat:\n");
    printf("1. Console\n");
    printf("2. File\n");
    printf("Lua chon: ");
    scanf("%d", &mode);
    
    printf("\nChon loai do thi:\n");
    printf("1. Do thi vo huong\n");
    printf("2. Do thi co huong\n");
    printf("Lua chon: ");
    scanf("%d", &type);
    
    init();
    
    if(mode == 1) {
        if(type == 1) {
            nhap_vo_huong_console();
            if(kiem_tra_chu_trinh_euler_vo_huong(NULL)) {
                int start = find_start_vo_huong();
                euler_cycle_vo_huong(start, NULL);
            } else {
                printf("\nKhong ton tai chu trinh Euler!\n");
            }
        } else if(type == 2) {
            nhap_co_huong_console();
            if(kiem_tra_chu_trinh_euler_co_huong(NULL)) {
                int start = find_start_co_huong();
                euler_cycle_co_huong(start, NULL);
            } else {
                printf("\nKhong ton tai chu trinh Euler!\n");
            }
        }
    } else if(mode == 2) {
        char input_file[100], output_file[100];
        printf("Nhap ten file dau vao: ");
        scanf("%s", input_file);
        printf("Nhap ten file dau ra: ");
        scanf("%s", output_file);
        
        FILE *fin = fopen(input_file, "r");
        FILE *fout = fopen(output_file, "w");
        
        if(!fin || !fout) {
            printf("Loi mo file!\n");
            return 1;
        }
        
        if(type == 1) {
            nhap_vo_huong_file(fin);
            if(kiem_tra_chu_trinh_euler_vo_huong(fout)) {
                int start = find_start_vo_huong();
                euler_cycle_vo_huong(start, fout);
            } else {
                fprintf(fout, "\nKhong ton tai chu trinh Euler!\n");
            }
        } else if(type == 2) {
            nhap_co_huong_file(fin);
            if(kiem_tra_chu_trinh_euler_co_huong(fout)) {
                int start = find_start_co_huong();
                euler_cycle_co_huong(start, fout);
            } else {
                fprintf(fout, "\nKhong ton tai chu trinh Euler!\n");
            }
        }
        
        fclose(fin);
        fclose(fout);
        printf("Da ghi ket qua vao file %s\n", output_file);
    }
    
    return 0;
}