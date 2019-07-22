//
//  main.cpp
//  ab
//
//  Created by Doris on 2019/7/19.
//  Copyright © 2019年 tsk. All rights reserved.
//

#include"akari_1.h"


int main() {
    
    FILE *fp;
    double start, finish, diff;
    if((fp = fopen("/Users/Doris/Desktop/lab/ab/ab/akari.txt", "r")) == NULL)
        return 1;
    read_dimension(fp, &m, &n);//读取行数和列数
    g_broad = (Elem_type*) malloc(sizeof(Elem_type) * m * n);//动态分配内存给矩阵
    read_broad(fp, g_broad);//读取文件中的数据存入变量g_broad中
    //print_broad(g_broad);
    Barrier_list barriers = create_barrier_list(g_broad);
    
    start = clock();
    int solved = solve_puzzle(barriers, g_broad);
    finish = clock();
    diff = (finish - start) / CLOCKS_PER_SEC;
    if(solved) {
        print_broad(g_broad);
    }else
        printf("no solution!\n");
    printf("Time duration: %lf s \n", diff);
    
    free(g_broad);
    fclose(fp);
    
    Barrier_list p;
    for(p = barriers; p;) {
        barriers = barriers->next;
        free(p);
        p = barriers;
    }
    return 0;
    
}
/*从文件读取数据：行、列 */
void read_dimension(FILE* fp, int* row, int* col) {
    printf("Please input the row & column:\n");
    fscanf(fp, "%d %d", row, col);
}
/*从文件读取初始数据 */
void read_broad(FILE* fp, Elem_type* broad) {
    printf("Please input the broad:\n");
    int i;
    for(i = 0; i < m*n; i++)
        fscanf(fp, "%d", &broad[i]);
}
/*输出矩阵 */
void print_broad(Elem_type* broad) {
    int r, c;
    for(r = 0; r < m; r++) {
        for(c = 0; c < n; c++)
            printf("%4d ", broad[r*n + c]);
        printf("\n");
    }
}

Barrier_list create_barrier_list(Elem_type* broad) {//创建黑色方块链表
    
    int i;
    Barrier_list header, p;
    header = p = NULL;
    for(i = 0; i < m*n; i++){
        if(broad[i] == BARRIER_0){
            Barrier_list q = (Barrier_list)malloc(sizeof(Num_barrier));
            q->row = i / n;
            q->col = i % n;
            q->number = 0;
            (header == NULL) ? (header = p = q) : (p->next = q, p=p->next);
        }
    }
    
    for(i = 0; i < m*n; i++){
        if(broad[i] == BARRIER_4){
            Barrier_list q = (Barrier_list)malloc(sizeof(Num_barrier));
            q->row = i / n;
            q->col = i % n;
            q->number = 4;
            (header == NULL) ? (header = p = q) : (p->next = q, p=p->next);
        }
    }
    for(i = 0; i < m*n; i++){
        if(broad[i] == BARRIER_3){
            Barrier_list q = (Barrier_list)malloc(sizeof(Num_barrier));
            q->row = i / n;
            q->col = i % n;
            q->number = 3;
            (header == NULL) ? (header = p = q) : (p->next = q, p=p->next);
        }
    }
    for(i = 0; i < m*n; i++){
        if(broad[i] == BARRIER_1){
            Barrier_list q = (Barrier_list)malloc(sizeof(Num_barrier));
            q->row = i / n;
            q->col = i % n;
            q->number = 1;
            (header == NULL) ? (header = p = q) : (p->next = q, p=p->next);
        }
    }
    for(i = 0; i < m*n; i++){
        if(broad[i] == BARRIER_2){
            Barrier_list q = (Barrier_list)malloc(sizeof(Num_barrier));
            q->row = i / n;
            q->col = i % n;
            q->number = 2;
            (header == NULL) ? (header = p = q) : (p->next = q, p=p->next);
        }
    }
    if(p != NULL) p->next = NULL;
    return header;
}
int solve_puzzle(Num_barrier* barrier, Elem_type* broad) {
    
    if(NULL != barrier) {//first phase：处理黑块
        Num_barrier* p;
        Elem_type* cp_broad;
        int r, c;
        int handle = 0;
        
        cp_broad = (Elem_type*)malloc(sizeof(Elem_type) * m * n);
        copy_broad(cp_broad, broad);
        
        p = barrier;
        r = p->row;
        c = p->col;
        
        switch(p->number){
            case 4:   //一种可能
                if(put_blub(r-1, c, cp_broad)
                   &&put_blub(r, c-1, cp_broad)
                   &&put_blub(r+1, c, cp_broad)
                   &&put_blub(r, c+1, cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                break;
            case 3:    //四种可能
                if(put_blub(r-1, c, cp_broad)
                   &&put_blub(r, c-1,cp_broad)
                   &&put_blub(r+1, c, cp_broad)
                   &&put_dot(r, c+1,cp_broad)) {
                    
                    handle = solve_puzzle(p->next, cp_broad);
                }
                //restore the state of broad
                copy_broad(cp_broad, broad);
                if(!handle && put_dot(r-1, c, cp_broad)
                   &&put_blub(r, c-1,cp_broad)
                   &&put_blub(r+1, c, cp_broad)
                   &&put_blub(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                //
                copy_broad(cp_broad, broad);
                if(!handle && put_blub(r-1, c, cp_broad)
                   &&put_dot(r, c-1,cp_broad)
                   &&put_blub(r+1, c, cp_broad)
                   &&put_blub(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                //
                copy_broad(cp_broad, broad);
                if(!handle && put_blub(r-1, c, cp_broad)
                   &&put_blub(r, c-1,cp_broad)
                   &&put_dot(r+1, c, cp_broad)
                   &&put_blub(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next,cp_broad);
                break;
            case 2:   //6种可能
                if(put_blub(r-1, c, cp_broad) //上  灯
                   &&put_blub(r, c-1,cp_broad)  //左  灯
                   &&put_dot(r+1, c, cp_broad)  //下
                   &&put_dot(r, c+1,cp_broad))  //右
                    handle = solve_puzzle(p->next, cp_broad);
                copy_broad(cp_broad, broad);
                if(!handle && put_dot(r-1, c, cp_broad)
                   &&put_blub(r, c-1,cp_broad)
                   &&put_dot(r+1, c, cp_broad)
                   &&put_blub(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                copy_broad(cp_broad, broad);
                if(!handle && put_blub(r-1, c, cp_broad)
                   &&put_dot(r, c-1,cp_broad)
                   &&put_dot(r+1, c, cp_broad)
                   &&put_blub(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                copy_broad(cp_broad,broad);
                if(!handle && put_dot(r-1, c, cp_broad)
                   &&put_dot(r, c-1,cp_broad)
                   &&put_blub(r+1, c, cp_broad)
                   &&put_blub(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                copy_broad(cp_broad, broad);
                if(!handle && put_dot(r-1, c, cp_broad)
                   &&put_blub(r, c-1,cp_broad)
                   &&put_blub(r+1, c, cp_broad)
                   &&put_dot(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                copy_broad(cp_broad, broad);
                if(!handle && put_blub(r-1, c, cp_broad)
                   &&put_dot(r, c-1,cp_broad)
                   &&put_blub(r+1, c, cp_broad)
                   &&put_dot(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                break;
            case 1 :    //四种可能
                if(put_blub(r-1, c, cp_broad)
                   &&put_dot(r, c-1,cp_broad)
                   &&put_dot(r+1, c, cp_broad)
                   &&put_dot(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                copy_broad(cp_broad, broad);
                if(!handle && put_dot(r-1, c, cp_broad)
                   &&put_blub(r, c-1,cp_broad)
                   &&put_dot(r+1, c, cp_broad)
                   &&put_dot(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                copy_broad(cp_broad, broad);
                if(!handle && put_dot(r-1, c, cp_broad)
                   &&put_dot(r, c-1,cp_broad)
                   &&put_blub(r+1, c, cp_broad)
                   &&put_dot(r, c+1,cp_broad))
                    handle = solve_puzzle(p->next, cp_broad);
                copy_broad(cp_broad, broad);
                if(!handle && put_dot(r-1, c, cp_broad)  //上
                   &&put_dot(r, c-1,cp_broad)    //左
                   &&put_dot(r+1, c, cp_broad)  //下
                   &&put_blub(r, c+1,cp_broad))  //右灯
                    handle = solve_puzzle(p->next, cp_broad);
                break;
            case 0:
                if(put_dot(r-1, c,cp_broad) //上方
                   && put_dot(r, c-1, cp_broad) //左边
                   && put_dot(r+1, c, cp_broad)  //下边
                   && put_dot(r, c+1, cp_broad)) //右边
                    handle = solve_puzzle(p->next, cp_broad);
                break;
            default:
                break;
        }
        //free(cp_broad);
        cp_broad = NULL;
        return handle;
    } else {//second phase：处理白块
        return handle_empty(next_empty(-1, broad), broad);
    }
}
/** name:next_empty
 * function:获取下一个未被灯光覆盖的方块
 * input：int cur：当前坐标， int* broad：处理过的数据数组
 * return：i：下一个方块坐标；  -1:不存在未被覆盖的方块
 */
int next_empty(int cur, Elem_type* broad){
    int i;
    for(i = cur+1; i < m *n; i++)
        if(broad[i] == EMPTY)
            return i;
    
    return -1;
}
/**name：handle_empty
 * function：处理未被点亮的空白方块,尝试在该位置放置灯泡
 * input：int cur：空白方块坐标
 *        int* broad：处理完成黑色方块的数据数组
 * output：处理结果   1:处理完成，得到正确结果
 *                  0:处理失败，不存在解
 */
int handle_empty(int cur, Elem_type* broad) {
    
    Elem_type* cp_broad;
    int handle = 0;
    
    if(check_complete(broad)){   //验证结果正确性
        copy_broad(g_broad, broad);
        return 1;
    }
    if(cur == -1)   //没有空白位置
        return 0;
    
    cp_broad = (Elem_type*)malloc(sizeof(Elem_type) * m * n);
    copy_broad(cp_broad, broad);
    
    put_blub(cur / n, cur % n, cp_broad);//在cur所在的位置放一个灯，cur/n和cur%n是为了得到坐标
    handle = handle_empty(next_empty(cur, cp_broad), cp_broad);
    if(!handle){
        //retore the previous state of the broad
        copy_broad(cp_broad, broad);
        handle =  handle_empty(next_empty(cur, cp_broad), cp_broad);
    }
    
    free(cp_broad);
    return handle;
}
/*
 *Copy the src broad to des
 */
void copy_broad(Elem_type* des, const Elem_type* src) {
    int i;
    for(i = 0; i < m*n; i++)
        des[i] = src[i];
}
/** name：check_complete
 * function：最终效果检查，是否所有的空白位置都被灯光覆盖
 * input：int* broad：处理过后的数据数组
 * return：1:不存在未被照亮的方块  0:存在未被照亮的方块
 */
int check_complete(Elem_type* broad){
    int i;
    for(i = 0; i < m*n; i++)
        if(broad[i] == EMPTY || broad[i] == DOT)    //存在empty or dot   broad[i] < COVER
            return 0;
   int ps[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
    for (int i = 0; i < m*n; i++) {
        if(broad[i] >= 0 && broad[i]<=4){
            int cnt = 0;
            int x = i/n;
            int y = i%n;
            for (int k = 0; k < 4; ++k) {
                int dx = x + ps[k][0], dy = y + ps[k][1];
                int tmp = dx*m + dy;
                if (dx >= 0 && dx < m && dy >= 0 && dy < n && broad[tmp] == 5) ++cnt;
            }
            if (cnt != broad[i]) {
                return 0;
            }
        }
    }
    return 1;
}
/**name：put_blub
 * function：在坐标（row，col）处放置灯泡，并且点亮相应方块
 * input：int row：x坐标
 *        int col：y坐标
 *        int* broad：处理过的数据数组
 * return：放置结果  1:成功   0:失败
 */

int put_blub(int row, int col, Elem_type* broad) {
    
    int r, c;
    //坐标是否合法，非法无需处理
    if((row < 0 && row >= m)
       || (col < 0 && col >= n))
        return 0;
    //judge can put? ：为cover、dot、barrier不能放置
    if(broad[row * n + col] != EMPTY && broad[row*n+col] != BLUB)
        return 0;
    else if(broad[row*n+col] == BLUB)
        return 1;
    
    broad[row * n + col] = BLUB;
    // illuminate four directions：empty、dot、cover
    for(r = row -1 , c = col; r >= 0 && broad[r*n+c] < BARRIER; r--)  //点亮上方
        broad[r*n + c] = COVER;
    for(r = row, c = col - 1; c >= 0 && broad[r* n+c] < BARRIER; c--)  //点亮左边
        broad[r*n + c] = COVER;
    for(r = row + 1, c = col; r < m && broad[r*n + c] < BARRIER; r++)  //点亮下方
        broad[r*n + c] = COVER;
    for(r = row, c = col +1; c < n && broad[r*n + c] < BARRIER; c++)  //点亮右边
        broad[r*n + c] = COVER;
    return 1;
    
}
/**name：put_dot
 * function：设置标记点，标记该位置不能放置灯泡，优化后续的白块处理效率
 * input：int row：x坐标
 *        int col：y坐标
 *        int* broad：处理过后的数据数组
 * return：能否放置标记   1:放置成功   0:放置失败
 */
int put_dot(int row, int col, Elem_type* broad) {
    if((row >= 0 && row < m)
       && (col >= 0 && col < n)){  //判断位置是否在矩阵内
        if(broad[row*n + col] == BLUB)
            return 0;
        
        if(broad[row*n + col] == EMPTY) {
            broad[row*n + col] = DOT;
        }
    }
    return 1;
}

