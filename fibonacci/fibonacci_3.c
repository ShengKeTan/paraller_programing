#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>


#define MAX_NUM 10000

struct Data
{
    int num;
    long int fibo[MAX_NUM];
};

/***** Begin *****/
void fibonacci(void *data){
    struct Data *tmp = (struct Data*)data;
    int i;
    
    double temp_1 = (1+sqrt(5))/2;
    double temp_2 = (1-sqrt(5))/2;
    double temp_3 = 1/sqrt(5.0);
    if(tmp->num == 0){
        tmp->fibo[0] = 1;
        return;
    }
    if(tmp->num == 1){
        tmp->fibo[0] = 1;
        return;
    }
    tmp->fibo[0] = 1;
    tmp->fibo[1] = 1;
#pragma omp parallel for
    for(i=2;i<tmp->num;i++){
        tmp->fibo[i] = (long int)(temp_3*(pow(temp_1,i+1)-pow(temp_2, i+1)));
    }
}

int main()
{
    struct Data data;
    int num = 10000;
    int i;
    
    double start, finish, diff;
    
    //get input
    //scanf("%d",&num);
   // getchar();
    data.num = num;
    
    start = clock();  //开始计时
    fibonacci(&data);
    finish = clock(); //结束计时
    diff = (finish - start)/CLOCKS_PER_SEC;
    
    
    //output
    /*for(i = 0; i < num; i++){
        if(i == num - 1){
            printf("%ld", data.fibo[i]);
        }
        else{
            printf("%ld ", data.fibo[i]);
        }
    }*/
    printf("num_size:%d\ntimes:%lf(s)\n",num,diff);
    
    return 0;
}
/***** End *****/

