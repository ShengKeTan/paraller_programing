//
//  akari_1.h
//  ab
//
//  Created by Doris on 2019/7/19.
//  Copyright © 2019年 tsk. All rights reserved.
//

#ifndef akari_1_h
#define akari_1_h

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

#define EMPTY -2  //空白位置       -2    0
#define DOT -3     //无法放置      -3    1
#define COVER -4   //被点亮         -4   2
#define BARRIER -1  //无数字黑块    -1    3
#define BARRIER_0 0  //数字0黑块    0   4
#define BARRIER_1 1  //           1 5
#define BARRIER_2 2  //           2 6
#define BARRIER_3 3  //           3 7
#define BARRIER_4 4  //           4 8
#define BLUB 5     //电灯          5  9

typedef int Elem_type;


/*黑色方块结点 */
typedef struct Node{
    int number;  //黑色方块中的数字0～4
    size_t row;//size_t是unsigned int
    size_t col;
    struct Node* next;
}Num_barrier, *Barrier_list;

int m;//row num
int n;//column num

Elem_type* g_broad;//the global broad

void read_dimension(FILE*, int*, int*);
void read_broad(FILE*,Elem_type*);
void print_broad(Elem_type*);
Barrier_list create_barrier_list(Elem_type*);

void copy_broad(Elem_type*, const Elem_type*);

int check_complete(Elem_type*);

int solve_puzzle(Barrier_list, Elem_type*);
int put_blub(int, int, Elem_type*);
int put_dot(int, int, Elem_type*);

int handle_empty(int, Elem_type*);
int next_empty(int, Elem_type*);



#endif /* akari_1_h */

