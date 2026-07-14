#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "ui.h"
#include "algorithm.h"
#include "graphic.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    int continueChoice = 1;
    
    while(continueChoice == 1){
        print_header();
        
        memset(resultCycle, 0, sizeof(resultCycle));
        
        // ========== BUOC 1: CHON THUAT TOAN ==========
        printf(CONSOLE_STEP CONSOLE_BOLD "\n CHON THUAT TOAN\n" CONSOLE_RESET);
        printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
        printf(CONSOLE_MENU "  1. " CONSOLE_RESET);
        printf(CONSOLE_WHITE "Thuat toan Fleury     \n" CONSOLE_RESET);
        printf(CONSOLE_MENU "  2. " CONSOLE_RESET);
        printf(CONSOLE_WHITE "Thuat toan Hierholzer \n" CONSOLE_RESET);
        printf(CONSOLE_GOLD "\n  >> Lua chon (1/2): " CONSOLE_RESET);
        
        int selectedAlgo; 
        scanf("%d", &selectedAlgo);
        if(selectedAlgo != 1 && selectedAlgo !=2) continue;
        
        // ========== BUOC 2: CHON LOAI DO THI ==========
        printf(CONSOLE_STEP CONSOLE_BOLD "\n CHON LOAI DO THI\n" CONSOLE_RESET);
        printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
        printf(CONSOLE_MENU "  1. " CONSOLE_RESET);
        printf(CONSOLE_WHITE "Do thi vo huong\n" CONSOLE_RESET);
        printf(CONSOLE_MENU "  2. " CONSOLE_RESET);
        printf(CONSOLE_WHITE "Do thi co huong\n" CONSOLE_RESET);
        printf(CONSOLE_GOLD "\n  >> Lua chon (1/2): " CONSOLE_RESET);
        
        int graphType;
        scanf("%d", &graphType);
        if(graphType != 1 && graphType !=2) continue;
        
        // ========== BUOC 3: CHON CACH NHAP DU LIEU ==========
        printf(CONSOLE_STEP CONSOLE_BOLD "\n CHON CACH NHAP DU LIEU\n" CONSOLE_RESET);
        printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
        printf(CONSOLE_MENU "  1. " CONSOLE_RESET);
        printf(CONSOLE_WHITE "Nhap tu ban phim (Console)\n" CONSOLE_RESET);
        printf(CONSOLE_MENU "  2. " CONSOLE_RESET);
        printf(CONSOLE_WHITE "Nhap tu file\n" CONSOLE_RESET);
        printf(CONSOLE_GOLD "\n  >> Lua chon (1/2): " CONSOLE_RESET);
        
        int inputChoice;
        scanf("%d", &inputChoice);
        if(inputChoice != 1 && inputChoice !=2) continue;
        
        
        if(inputChoice == 1){
            printf(CONSOLE_STEP CONSOLE_BOLD "\n? NHAP DU LIEU TU CONSOLE\n" CONSOLE_RESET);
            printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
            
            printf(CONSOLE_WHITE "  So dinh: " CONSOLE_RESET);
            scanf("%d", &n); if (n < 1 || n >= MAXN) {print_error("Du lieu khong hop le!"); getchar(); getchar(); continue;}
            printf(CONSOLE_WHITE "  So canh: " CONSOLE_RESET);
            if(graphType==1){
            	scanf("%d", &m); if (m < 0 || m > 4950) {print_error("Du lieu khong hop le!"); getchar(); getchar(); continue; }
            }
            else if(graphType==2){
            	scanf("%d", &m); if (m < 0 || m > 9900) {print_error("Du lieu khong hop le!"); getchar(); getchar(); continue; }
            }
            
            memset(adj, 0, sizeof(adj));
            resetVisitedF();
            if(selectedAlgo==1){
            	for(int i=1; i<= MAXN-1; i++){
			        deg[i]=0;
			        in_deg[i]=0;
			        out_deg[i]=0;
			    }
            }
            else if(selectedAlgo==2){
            	initH();
            }
         
            printf(CONSOLE_GRAY "\n  Nhap cac canh (u v):\n" CONSOLE_RESET);
            if(selectedAlgo==1){
            	for(int i=1; i<=m; i++){
			        int u,v;
			        printf(CONSOLE_GOLD "  Canh %d: " CONSOLE_RESET, i);
			        scanf("%d %d", &u, &v);
			        if(graphType==1){
			            adj[u][v]++;
			            adj[v][u]++;
			            deg[u]++;
			            deg[v]++;
			        }
			        else{
			            adj[u][v]++;
			            out_deg[u]++;
			            in_deg[v]++;
			        }
			    }
            }
            else if(selectedAlgo==2){
            	for(int i=0; i<m; i++){
			        int u,v;
			        printf(CONSOLE_GOLD "  Canh %d: " CONSOLE_RESET, i + 1);
			        scanf("%d %d", &u, &v);
			        adj[u][v]++;
			        out_degree[u]++;
			        if(graphType==1){
			            adj[v][u]++;
			            out_degree[v]++;
			        }
			        else{
			            in_degree[v]++;
			        }
			    }
            }
        }
        else if(inputChoice == 2){
            printf(CONSOLE_STEP CONSOLE_BOLD "\n? NHAP DU LIEU TU FILE\n" CONSOLE_RESET);
            printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
            printf(CONSOLE_STEP CONSOLE_BOLD "  Dong 1: n m\n" CONSOLE_RESET);
            printf(CONSOLE_STEP CONSOLE_BOLD "  m dong tiep theo: u v\n" CONSOLE_RESET);
            
            char filename[100];
            printf(CONSOLE_WHITE "  Ten file : (vi du : input.txt) " CONSOLE_RESET);
            scanf("%s", filename);
            
            FILE *file = fopen(filename, "r");
            if(!file){
                print_error("Khong the mo file!");
                printf(CONSOLE_GRAY "\n  Nhan Enter de tiep tuc..." CONSOLE_RESET);
                getchar(); getchar();
                continue;
            }
            
            memset(adj, 0, sizeof(adj));
            resetVisitedF();
            if(selectedAlgo==1){
            	for(int i=1; i<= MAXN-1; i++){
			        deg[i]=0;
			        in_deg[i]=0;
			        out_deg[i]=0;
			    }
            }
            else if(selectedAlgo==2){
            	initH();
            }
            
            if(fscanf(file, "%d %d", &n, &m) != 2){
                print_error("Du lieu file khong hop le!");
                fclose(file);
                printf(CONSOLE_GRAY "\n  Nhan Enter de tiep tuc..." CONSOLE_RESET);
                getchar(); getchar();
                continue;
            }
            
            if(selectedAlgo==1){
            	for(int i=1; i<=m; i++){
			        int u,v;
			        fscanf(file, "%d %d", &u, &v);
			        if(graphType==1){
			            adj[u][v]++;
			            adj[v][u]++;
			            deg[u]++;
			            deg[v]++;
			        }
			        else{
			            adj[u][v]++;
			            out_deg[u]++;
			            in_deg[v]++;
			        }
			    }
            }
            else if(selectedAlgo==2){
            	for(int i=0; i<m; i++){
			        int u,v;
			        fscanf(file, "%d %d", &u, &v);
			        adj[u][v]++;
			        out_degree[u]++;
			        if(graphType==1){
			            adj[v][u]++;
			            out_degree[v]++;
			        }
			        else{
			            in_degree[v]++;
			        }
			    }
            }
            fclose(file);
            print_success("Doc file thanh cong!");
        } 
        else {
            print_error("Lua chon khong hop le!");
            printf(CONSOLE_GRAY "\n  Nhan Enter de tiep tuc..." CONSOLE_RESET);
            getchar(); getchar();
            continue;
        } 
        // ========== BUOC 4: TIM CHU TRINH ==========
        printf(CONSOLE_STEP CONSOLE_BOLD "\n? DANG TIM CHU TRINH EULER\n" CONSOLE_RESET);
        printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
        
        if(selectedAlgo == 1){
            printf(CONSOLE_STEP "  >> Su dung thuat toan FLEURY\n" CONSOLE_RESET);
        } else {
            printf(CONSOLE_STEP "  >> Su dung thuat toan HIERHOLZER\n" CONSOLE_RESET);
        }
 
        clock_t start = clock();
        isDirected = graphType - 1;
        if(selectedAlgo == 1){
            fleury_execute(isDirected, resultCycle, &resultLen);
        } else {
            hierholzer_execute(isDirected, resultCycle, &resultLen);
        }
        clock_t end = clock();
        double time_taken = (double)(end-start)/CLOCKS_PER_SEC;
        
        if(hasEuler==1){
        	// ========== BUOC 5: CHON CACH HIEN THI ==========
        	printf(CONSOLE_STEP CONSOLE_BOLD "\n? CHON CHE DO HIEN THI\n" CONSOLE_RESET);
        	printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
        	printf(CONSOLE_MENU "  1. " CONSOLE_RESET);
        	printf(CONSOLE_WHITE "Chi in ket qua (Console)\n" CONSOLE_RESET);
        	printf(CONSOLE_MENU "  2. " CONSOLE_RESET);
        	printf(CONSOLE_WHITE "Ve hinh + Mo phong chu trinh Euler\n" CONSOLE_RESET);
        	printf(CONSOLE_GOLD "\n  >> Lua chon (1/2): " CONSOLE_RESET);
   	
	        int displayChoice;
	        scanf("%d", &displayChoice);
	            
	        if(displayChoice == 1){
	            printf(CONSOLE_RESULT CONSOLE_BOLD "\n+--------------------------------------------------------------------------------+\n");
	            printf("?                            KET QUA CHU TRINH EULER                             ?\n");
	            printf("+--------------------------------------------------------------------------------?\n");
	            printf("? " CONSOLE_RESET);
	
	            for(int i = 0; i < resultLen; i++){
	                printf("%d", resultCycle[i]);
	                if(i < resultLen - 1) printf(" --> ");
	            }
	            printf("\n");
	            printf(CONSOLE_RESULT CONSOLE_BOLD "+--------------------------------------------------------------------------------+\n" CONSOLE_RESET);
	                
	            printf(CONSOLE_GRAY "\n  So buoc: %d\n", resultLen - 1);
	            printf("  Thoi gian: %.30f giay\n" CONSOLE_RESET, time_taken);
	            print_success("Hoan tat!");
	        } 
	        else if(displayChoice == 2){
	            printf(CONSOLE_STEP CONSOLE_BOLD "\n? MO PHONG\n" CONSOLE_RESET);
	            printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
	                
	            int speedChoice;
	            printf(CONSOLE_MENU "  Chon toc do mo phong:\n" CONSOLE_RESET);
	            printf(CONSOLE_GRAY "    1. Cham (1 giay/buoc)\n");
	            printf("    2. Trung binh (0.5 giay/buoc)\n");
	            printf("    3. Nhanh (0.2 giay/buoc)\n");
	            printf("    4. Rat nhanh (0.05 giay/buoc)\n" CONSOLE_RESET);
	            printf(CONSOLE_GOLD "    >> Chon (1-4): " CONSOLE_RESET);
	            scanf("%d", &speedChoice);
	                
	            int animationSpeed = 500;
	            switch(speedChoice){
	                case 1: animationSpeed = 1000; break;
	                case 2: animationSpeed = 500; break;
	                case 3: animationSpeed = 200; break;
	                case 4: animationSpeed = 50; break;
	                default: animationSpeed = 500;
	            }
	                
	            extern void setAnimationSpeedValue(int speed);
	            setAnimationSpeedValue(animationSpeed);
	                
	            printf(CONSOLE_GRAY "\n  Dang mo cua so do hoa...\n" CONSOLE_RESET);
	            drawGraphAndSimulate(resultCycle, resultLen);
	            print_success("Da mo phong thanh cong!");
	            printf(CONSOLE_GRAY "  Thoi gian thuc hien: %.30f giay\n" CONSOLE_RESET, time_taken);
	        } 
	        else {
	            print_error("Lua chon khong hop le!");
	        }
        }
        
        // ========== BUOC 6: HOI TIEP TUC ==========
        printf(CONSOLE_STEP CONSOLE_BOLD "\n? KET THUC\n" CONSOLE_RESET);
        printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
        printf(CONSOLE_MENU "  1. " CONSOLE_RESET);
        printf(CONSOLE_WHITE "Tiep tuc (Nhap do thi moi)\n" CONSOLE_RESET);
        printf(CONSOLE_MENU "  2. " CONSOLE_RESET);
        printf(CONSOLE_WHITE "Thoat chuong trinh\n" CONSOLE_RESET);
        printf(CONSOLE_GOLD "\n  >> Lua chon (1/2): " CONSOLE_RESET);
        scanf("%d", &continueChoice);
        
        if(continueChoice != 1){
            clear_screen();
            printf(CONSOLE_SUCCESS CONSOLE_BOLD);
            printf("\n+----------------------------------------------------------------------------+\n");
            printf("?                                                                            ?\n");
            printf("?                 CAM ON BAN DA SU DUNG CHUONG TRINH!                        ?\n");
            printf("?                            TAM BIET!                                       ?\n");
            printf("?                                                                            ?\n");
            printf("+----------------------------------------------------------------------------+\n");
            printf(CONSOLE_RESET);
            printf("\n");
        }
    }
    return 0;
}

