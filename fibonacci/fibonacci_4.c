#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <string.h>


/***** Begin *****/
long int fibonacci(int n){
    long int data;
    double temp_1 = (1+sqrt(5))/2;
    double temp_2 = (1-sqrt(5))/2;
    double temp_3 = 1/sqrt(5.0);
    
    data = (long int)(temp_3*(pow(temp_1,n)-pow(temp_2, n)));
    return data;
}

int main(int argc,char* argv[])
{
	int numproc, myid, source;
	int num;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	//获取进程id
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	//获取进程数
	MPI_Comm_size(MPI_COMM_WORLD, &numproc);
	
	//按照进程数划分任务
	int local_num = 51/(numproc-1);
	int local_begin;
	int local_end;
	
	long int* data = (long int*)malloc(sizeof(long int)*51);
    long int* recv = (long int*)malloc(sizeof(long int)*51);
    memset(data, 51, 0);
    memset(recv, 51, 0);
	
	//0号进程控制I/O
	if(myid == 0){
		//get input
    	scanf("%d",&num);
    	getchar();
    	int j;
		for (source = 1; source < numproc; ++source){
			MPI_Recv(recv, 51, MPI_LONG, source, 99,
				MPI_COMM_WORLD, &status);
			if(source == numproc - 1){ //最后一个进程传来的数据
				local_end = 51;
				local_begin = local_num*(source-1);
			}
			else{
				local_end = local_num*source;
				local_begin = local_num*(source-1);
			}
			printf("id:%d,begin:%d,end:%d\n",source,local_begin,local_end);
			for(j=local_begin;j<local_end;j++){
				data[j]=recv[j];
			}
		}
		for(j = 1; j < num; j++){
			printf("%ld ", data[j]);
		}
		printf("%ld\n",data[num]);
	}
	else if(myid == (numproc - 1)){  //最后一个进程
		local_begin = local_num*(numproc-2);
		local_end = 51;
		int i;
		for(i=local_begin;i<local_end;i++){
			data[i] = fibonacci(i);
		}
		MPI_Send(data,51,MPI_LONG,0,99,MPI_COMM_WORLD);
	}
	else{
		local_begin = local_num*(myid - 1);
		local_end = local_num*myid;
		int i;
		for(i=local_begin;i<local_end;i++){
			data[i] = fibonacci(i);
		}
		MPI_Send(data,51,MPI_LONG,0,99,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
/***** End *****/