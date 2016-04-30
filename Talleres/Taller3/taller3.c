#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	int k;
	int n;
}str_params;

void *sumkn(void* param){
	str_params str_p = *((str_params *)param);
	int *result = (int *)malloc(sizeof(int));
	
	int x;
	x = (str_p.n-1)/str_p.k;
	*result = (str_p.k)*x*(x+1)/2;
	pthread_exit((void*)result);
}

int main(int argc, char *argv[]){
	int num[3];	//3, 5, 15
	int lim;	//10
	int i;
	pthread_t id[3];
	int *results[3];
	str_params param[3];
	int resultado = 0;
	if(argc!=4){
		printf("Error! se debe ejecutar así: ./exe <num1><num2><limite>");
		exit(0);
	}
	num[0]=atoi(argv[1]);	//3
	num[1]=atoi(argv[2]);	//5
	num[2]=num[0]*num[1];	//15
	lim = atoi(argv[3]);	//10

	for (i = 0; i < 3; ++i){
		param[i].k=num[i];
		param[i].n=lim;
		pthread_create(&id[i],NULL,sumkn,(void*)&param[i]);
	}

	for (i = 0; i < 3; ++i){
		pthread_join(id[i],(void**)&results[i]);
		printf("Resultado[%d]: %d\n",i+1,*results[i]);
	}

	resultado = *results[0]+*results[1]-*results[2];
	printf("Resutlado: %d\n",resultado);
	return 0;
}