#include <FPT.h>

// array [] notation test

int main()
{
  double i, x[10] ;

  printf("x[i] test\n") ;
  i = 0 ;
  while (i < 10) {
    x[i] = i+100 ;
    printf("x[%lf] = %lf\n",i,x[i]) ;
    i++ ;
  }

}

 
  
