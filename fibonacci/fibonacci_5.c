#include <stdio.h>
#include <math.h>

#define DATA_SIZE 60
#define THREAD_NUN 10


/***** Begin *****/
__global__ void fibonacci(long int* data,double a,double b, double c){
    int tid = threadIdx.x;
    int i;
    const int size = DATA_SIZE/THREAD_NUN;
    for(i=tid*size;i<(tid+1)*size;i++){
        data[i] = (long int)((c*(pow(a,i)-pow(b,i)))+0.5);
    }
}

int main()
{   
    int num, i;
    long int data[DATA_SIZE];

    long int* result; 
    cudaMalloc((long int **)&result,sizeof(long int)*DATA_SIZE);
    
    double temp_1 = (1+sqrt(5))/2;
    double temp_2 = (1-sqrt(5))/2;
    double temp_3 = 1/sqrt(5.0);

    fibonacci<<<1,THREAD_NUN>>>(result,temp_1,temp_2,temp_3);
    cudaMemcpy(&data,result,sizeof(long int)*DATA_SIZE,cudaMemcpyDeviceToHost);

    //get input
    scanf("%d",&num);
    getchar();

    for(i=1;i<num;i++){
        printf("%ld ", data[i]);
    }
    printf("%ld\n", data[num]);

    return 0;
}
/***** End *****/