#include <FPT.h>


int main()
{
  double x[1000] ;
  double y[8000] ;
  int i ;

  outS("enter a word : ") ;

  inS(x) ;

  outS(x) ;  
  outS("_hello\n") ;


  unpack(y, x) ;

  i = 0 ;
  while (y[i] != 0) { y[i] += 2.0 ; i++ ; }

  pack(x, y) ;

  outS(x) ;  
  outS("_goodbye\n") ;
}
