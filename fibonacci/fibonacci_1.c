//
//  main.c
//  fibonacci
//
//  Created by Doris on 2019/7/9.
//  Copyright © 2019年 tsk. All rights reserved.
//
#include <stdio.h>
long int fibonacci(int n);

int count = 0;

/***** Begin *****/
int main()
{
    int data = 50;
    long int out = 0;
    int i = 1;
    //scanf("%d",&data);
    while(i <= data){
        out = fibonacci(i);
        if(i==data) printf("%ld\n",out);
        else printf("%ld ",out);
        i++;
    }
    printf("num_size:50\ntotal_times:%d",count);
    return 0;
}
long int fibonacci(int n){
    long int a1=0,a2=1;
    long int a3=1;
    int i;
    if(n <= 0)
        return 0;
    else if(n == 1)
        return 1;
    else{
        for(i=0;i<n-1;i++){
            a3 = a1+a2;
            a1 = a2;
            a2 = a3;
            count++;
        }
    }
    return a3;
}
