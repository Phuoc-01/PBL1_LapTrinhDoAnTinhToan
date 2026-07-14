#include <stdio.h>
#include <string.h>

#define MAXN 101

int n, m;
int a[MAXN][MAXN];
int visited[MAXN];
int deg[MAXN];
int path[200000];
int idx;

void resetGraph() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            a[i][j] = 0;
        }
    }
}

void resetVisited() {
    for(int i = 1; i <= n; i++) visited[i] = 0;
}

void dfs(int u) {
    visited[u] = 1;
    for(int v = 1; v <= n; v++) {
        if(a[u][v] == 1 && !visited[v]) {
            dfs(v);
        }
    }
}

int isBridgeU(int u, int v) {
    a[u][v] = a[v][u] = 0;
    
    resetVisited();
    dfs(u);
    
    a[u][v] = a[v][u] = 1;
    
    return !visited[v];
}

int isBridgeD(int u, int v) {
    a[u][v] = 0;
    
    resetVisited();
    dfs(u);
    
    a[u][v] = 1;
    
    return !visited[v];
}

void nhap_vo_huong_console() {
    printf("\n--- NHAP DO THI VO HUONG ---\n");
    printf("Nhap so dinh va so canh: ");
    scanf("%d %d", &n, &m);
    resetGraph();
    for(int i = 1; i <= n; i++) deg[i] = 0;
    
    printf("Nhap %d canh (u v):\n", m);
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        a[u][v] = a[v][u] = 1;
        deg[u]++;
        deg[v]++;
    }
}

void nhap_co_huong_console() {
    printf("\n--- NHAP DO THI CO HUONG ---\n");
    printf("Nhap so dinh va so canh: ");
    scanf("%d %d", &n, &m);
    resetGraph();
    for(int i = 1; i <= n; i++) deg[i] = 0;
    
    printf("Nhap %d canh (u v):\n", m);
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        a[u][v] = 1;
        deg[u]++;
        deg[v]--;
    }
}

void nhap_vo_huong_file(FILE *f) {
    fscanf(f, "%d %d", &n, &m);
    resetGraph();
    for(int i = 1; i <= n; i++) deg[i] = 0;
    
    for(int i = 1; i <= m; i++) {
        int u, v;
        fscanf(f, "%d %d", &u, &v);
        a[u][v] = a[v][u] = 1;
        deg[u]++;
        deg[v]++;
    }
}

void nhap_co_huong_file(FILE *f) {
    fscanf(f, "%d %d", &n, &m);
    resetGraph();
    for(int i = 1; i <= n; i++) deg[i] = 0;
    
    for(int i = 1; i <= m; i++) {
        int u, v;
        fscanf(f, "%d %d", &u, &v);
        a[u][v] = 1;
        deg[u]++;
        deg[v]--;
    }
}

int kiem_tra_euler_vo_huong() {
    for(int i = 1; i <= n; i++) {
        if(deg[i] % 2 == 1) {
            return 0;
        }
    }
    return 1;
}

int kiem_tra_euler_co_huong() {
    for(int i = 1; i <= n; i++) {
        if(deg[i] != 0) {
            return 0;
        }
    }
    return 1;
}

void euler_vo_huong(FILE *out) {
    if(!kiem_tra_euler_vo_huong()) {
        fprintf(out, "Khong co chu trinh Euler\n");
        return;
    }
    
    int curr = 1;
    idx = 0;
    path[idx++] = curr;
    
    int edge_count = m;
    int temp_a[MAXN][MAXN];
    memcpy(temp_a, a, sizeof(a));
    
    for(int i = 1; i <= edge_count; i++) {
        int next = -1;
        
        for(int v = 1; v <= n; v++) {
            if(a[curr][v] == 1) {
                next = v;
                if(!isBridgeU(curr, v)) break;
            }
        }
        
        if(next == -1) {
            fprintf(out, "Khong tim thay duong di Euler\n");
            return;
        }
        
        path[idx++] = next;
        a[curr][next] = a[next][curr] = 0;
        curr = next;
    }
    
    fprintf(out, "Chu trinh Euler: ");
    for(int i = 0; i < idx; i++) fprintf(out, "%d ", path[i]);
    fprintf(out, "\n");
    
    memcpy(a, temp_a, sizeof(a));
}

void euler_co_huong(FILE *out) {
    if(!kiem_tra_euler_co_huong()) {
        fprintf(out, "Khong co chu trinh Euler\n");
        return;
    }
    
    int curr = 1;
    idx = 0;
    path[idx++] = curr;
    
    int edge_count = m;
    int temp_a[MAXN][MAXN];
    memcpy(temp_a, a, sizeof(a));
    
    for(int i = 1; i <= edge_count; i++) {
        int next = -1;
        
        for(int v = 1; v <= n; v++) {
            if(a[curr][v] == 1) {
                next = v;
                if(!isBridgeD(curr, v)) break;
            }
        }
        
        if(next == -1) {
            fprintf(out, "Khong tim thay duong di Euler\n");
            return;
        }
        
        path[idx++] = next;
        a[curr][next] = 0;
        curr = next;
    }
    
    fprintf(out, "Chu trinh Euler: ");
    for(int i = 0; i < idx; i++) fprintf(out, "%d ", path[i]);
    fprintf(out, "\n");
    
    memcpy(a, temp_a, sizeof(a));
}

int main() {
    int mode, type;
    
    printf("\n======== THUAT TOAN FLEURY ========\n");
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
    
    if(mode == 1) {
        if(type == 1) {
            nhap_vo_huong_console();
            euler_vo_huong(stdout);
        } else if(type == 2) {
            nhap_co_huong_console();
            euler_co_huong(stdout);
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
            euler_vo_huong(fout);
        } else if(type == 2) {
            nhap_co_huong_file(fin);
            euler_co_huong(fout);
        }
        
        fclose(fin);
        fclose(fout);
        printf("Da ghi ket qua vao file %s\n", output_file);
    }
    
    return 0;
}