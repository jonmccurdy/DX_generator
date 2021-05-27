#include <Rcpp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  /* clock() */
using namespace Rcpp;

#define K_MAX	3500
#define PP 2147483647  //2^31-1
#define B_X1 536869888 //LYD:
#define K_X1 47
#define T_X1 1

unsigned long MODP(unsigned long z) {return ((((z)&PP)+((z)>>31)) &PP);}

static long long XX[K_MAX];
static int Initial, I_X, T_X, K_X;           /* running index */

static Int32 seed;
static double res;
static int nseed = 1;

void DX_Init(Int32 seed)
{
  int i;
  K_X=K_X1;
  T_X=T_X1;
  srand(seed);
  
  for (i=0; i<K_X; i++) XX[i] = rand() & PP;
  
  I_X=K_X-1;
}

double * user_unif_rand()
{
  DX_Init(seed);
  int II0 = I_X;
  if(++I_X >= K_X)  I_X = 0;     /*wrap around running index */
  XX[I_X] = MODP(B_X1 * XX[I_X] + XX[II0]);
  res = (double) XX[I_X] * 2.32830643653869e-10;
  return &res;
}

void  user_unif_init(Int32 seed_in) { seed = seed_in;}
int * user_unif_nseed() { return &nseed; }
int * user_unif_seedloc() { return (int *) &seed; }
