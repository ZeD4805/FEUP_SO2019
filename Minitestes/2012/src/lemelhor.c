/* ppb.c
 *  The Hungry Birds Problem - pass arguments to threads and receive values from them when they finish!

Program invocation:
	./ppb <n. babybirds> <n. food portions> <n. refills>

Invocation example:
     ./ppb 3 5 10000
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define MAXBABIES 100

int finish = 0;	// termination of simulation (flagged by parent bird)
int foodbits = 0;	// is the current number of bits of food in the "food-teat"

typedef struct _checkerarg {	// conveys info to checker
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
	int *eating;	// ptr to number of babies that are eating at a time
	pthread_mutex_t *mut; // for overall concurrency control to shared data
}checkerarg;
typedef struct _parentarg {	// conveys info to parent bird
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
}parentarg;
typedef struct babyarg {	// conveys info to baby birds
	int id;	// baby identification
	int *eating;	// ptr to number of babies that are eating at a time
}babyarg;

void *checker(void *);	// checker thread
void *parent(void *);	// parent thread
void *baby(void *);	// baby thread


int main(int argc, char *argv[]) {

setbuf(stdout, NULL);
	int B;	// number of babies
	int F;	// number of bits of food of each refill
	long R;	// number of refills - parent bird can then retire!
	int working = 0;	// represents the binary state of parent bird:
	int eating = 0;	// number of babies that are eating at a time
	parentarg pa;	// conveys info to parent bird (and checker!)
	checkerarg ca;	// conveys info to parent bird (and checker!)
	babyarg ba[MAXBABIES];	// conveys baby identification
	pthread_t tchecker, tparent, tbaby[MAXBABIES];

if( argc != 4) {
	printf("Program invoked with wrong number of arguments.\n");
	printf("Program usage: %s <n. babybirds> <n. food portions> <n. refills>\n", argv[0]);
	exit(-1);
    }
else {
	B = atoi(argv[1]);
	F = atoi(argv[2]);
	R = atoi(argv[3]);
	}
printf("\nSimulation started\n");

// a preencher com o seu código:

// criar thread checker (também SEM passar argumentos!)
checker = (checkerarg){}
pthread_create(&tchecker, NULL, checker, NULL);

// criar thread parent bird
pa = (parentarg){F, R, &working};
pthread_create(&tparent, NULL, parent, &pa);

// criar threads baby birds
for(int i = 0; i<B; i++){
	ba[i] = (babyarg){i, &eating};
	pthread_create(tbaby + i, NULL, baby, ba + i);
}
// esperar por thread parent
int *parentResult;
pthread_join(tparent, (void **)&parentResult);
// esperar por threads baby
int **babyResult;
babyResult = malloc(B * sizeof(int *));
for(int i = 0; i < B; i++)
{
	pthread_join(tbaby[i], (void **)(babyResult + i));
}

// NÃO esperar pelo thread checker, pois é "detached"!

printf("\nSimulation finished\n");
exit (0);

} // main()


void *parent(void *arg) {	// parent bird thread
parentarg *parg = (parentarg *)arg;
printf ("\n\tParent starting");

printf ("\n\tParent finishing");
int *res = malloc(sizeof(int));
*res = 0;
return res;
}


void *baby(void *arg){	// baby thread
babyarg *barg = (babyarg *)arg;
printf ("\n   Baby bird beginning");

printf ("\n   Baby bird finishing");
int *res = malloc(sizeof(int));
return res;
}

void *parent(void *arg) {	// parent bird thread
parentarg *parg = (parentarg *)arg;
printf ("\n\tParent starting");
for(int i = 0; i < parg->r; i++)
{
	while(foodbits > 0);
	foodbits+=parg->f;
}
finish = 1;
printf ("\n\tParent finishing");
int *res = malloc(sizeof(int));
*res = 0;
return res;
}

void *baby(void *arg){	// baby thread
babyarg *barg = (babyarg *)arg;
printf ("\n   Baby bird beginning");
while(finish != 1){
	if(foodbits>0){
		--foodbits;
		for(int i = 0; i < 1000000; i++);
	}
}
printf ("\n   Baby bird finishing");
int *res = malloc(sizeof(int));
return res;
}