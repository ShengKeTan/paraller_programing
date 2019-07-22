#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

#define MAX_NUM 100

struct Data
{
    int num;
    long int fibo[MAX_NUM];
};


/***** Begin *****/
void *fibonacci(void *data){
    struct Data *tmp = (struct Data*)data;
    int i;
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
    for(i=2;i<tmp->num;i++){
        tmp->fibo[i] = tmp->fibo[i-1] + tmp->fibo[i-2];
    }
}

int main()
{
    struct Data data;
    pthread_t th;
    int ret;
    int num;
    int i;
    //get input
    scanf("%d",&num);
    getchar();
    data.num = num;

    //create thread
    ret = pthread_create(&th, NULL, fibonacci, (void *)&data);
    pthread_join(th, NULL);

    //output
    for(i = 0; i < num; i++){
        if(i == num - 1){
            printf("%ld", data.fibo[i]);
        }
        else{
        printf("%ld ", data.fibo[i]);
        }
    }
    printf("\n");

    return 0;
}
/***** End *****/

