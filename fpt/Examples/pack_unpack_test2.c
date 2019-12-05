#include <FPT.h>


int main()
{
  double x[1000] ;
  // double y[8000] ;
  // if storage is sufficient, source and destination
  // can be same array
  int i ;

  outS("enter a word : ") ;

  inS(x) ;

  outS(x) ;  
  outS("_hello\n") ;


  //  unpack(y, x) ;
  unpack(x, x) ;

  i = 0 ;
  //  while (y[i] != 0) { y[i] += 2.0 ; i++ ; }
  while (x[i] != 0) { x[i] += 2.0 ; i++ ; }

  //  pack(x, y) ;
  pack(x, x) ;

  outS(x) ;  
  outS("_goodbye\n") ;
}
