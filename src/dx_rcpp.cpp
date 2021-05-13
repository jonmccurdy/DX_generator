#include <Rcpp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  /* clock() */
using namespace Rcpp;

#define K_MAX	3500
#define PP 2147483647  //2^31-1
#define B_X1 536869888 //LYD:
#define B_X2 65011712 //LYD:
#define K_X2 47
#define T_X1 1
#define T_X2 1

unsigned long MODP(unsigned long z) {return ((((z)&PP)+((z)>>31)) &PP);}

static long long XX[K_MAX];
static int I_X, T_X, K_X;           /* running index */

void DX1_INIT(int seed, int K_X1)
{
  int i;
  K_X=K_X1;
  T_X=T_X1;
  srand(seed);
  
  for (i=0; i<K_X; i++) XX[i] = rand() & PP;
  
  I_X=K_X-1;
}

long long DX1()
{
  int II0 = I_X;
  if(++I_X >= K_X)  I_X = 0;     /*wrap around running index */
  XX[I_X] = MODP(B_X1 * XX[I_X] + XX[II0]);
  return XX[I_X];
}

//' Gets the Random Numbers
//'
//' @param nTry number of observations
//' @param seed seed to configure RNG
//' @param k DX parameter
//' @return nTry random numbers
// [[Rcpp::export]]
Rcpp::NumericVector rand_test(int nTry, int seed, int k) {
  NumericVector YY= no_init_vector(nTry);
  int i;
  DX1_INIT(seed, k);
  
  for(i=0; i<nTry; i++) YY[i] = DX1()/(double) PP;
  
  return YY;
}