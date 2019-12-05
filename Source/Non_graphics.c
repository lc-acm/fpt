
#include <Non_graphics.h>


static int input_error ;


int check_input_error_flag ()
{
  return input_error ;
}



int inI ()
// input an integer
// its value is returned
{
  int i ;
  int x ;

  i = scanf("%d",&x) ;
  if (i == 1) {
     input_error = 0 ;
  } else {
     input_error = 1 ;
     printf("\nInput is not recognized as an int, 0 returned.\n") ;
     x = 0 ;
  } 

  return x ;
}



void outI (int x)
// output an integer
{
  printf("%d",x) ;
}




double inD ()
// input a double
// its value is returned
{
  int i ;
  double x ;

  i = scanf("%lf",&x) ;
  if (i == 1) {
     input_error = 0 ;
  } else {
     input_error = 1 ;
     printf("\nInput is not recognized as a double, 0 returned.\n") ;
     x = 0 ;
  } 

  return x ;
}







void outD (double x)
// output a double...switches to scientific notation
// for the extremely small and the extremely large
{

  if (x == 0.0) {
     printf("%.10lf",x) ;
  }
  else if (fabs(x) < 1e-10) {
     printf("%.10e",x) ;
  } else if (fabs(x) > 1e10) {
     printf("%.10e",x) ;
  } else {
     printf("%.10lf",x) ;
  }

}






void inS (void *p)
// the wisdom of the void * 
// allows for the input to go into
// a packed arrary of doubles (for instance)
{
  char *cp ;

  cp = (char *) p ;  
  scanf("%s",cp) ;
  input_error = 0 ;
}




void outS (const void *p)
// the wisdom of the void * 
// allows for the output to come from
// a packed arrary of doubles (for instance)
{
  char *cp ;
  
  cp = (char *) p ;
  printf("%s",cp) ;

}










void pack (void *destination, void *source)
// pack a null-terminated array of double-characters
// into an array of single-byte-characters
// The null terminator is also packed
// destination and source can point to the same
// actual space.
{
  char *cp ;
  double *dp ;
  int i ; 
  double d ;
  char a;

  dp = (double *) source ;
  cp = (char *) destination ;

  i = -1 ;
  do {
   i++ ;

   d = floor(dp[i] + 0.5) ;

   if (d < 0) a = 0 ;
   else if (d > 255) a = 255 ;
   else a = (char)d ;
  
   cp[i] = a ;

  } while (a != 0) ;
  
  // this also copies over the null terminator
  // as it should
}







void unpack (void *destination, void *source)
// unpack a null-terminated array of single-byte
// characters into an array of  double-characters.
// the null terminator is also unpacked.
// destination and source can point to the same
// actual space provided it is of sufficient size
// to hold the unpacked data.
{
  char *cp ;
  double *dp ;
  int i ;

  cp = (char *) source ;
  dp = (double *) destination ;

  i = 0 ; 
  while (cp[i] != 0) {
    // printf("i = %d  cp[i] = %c\n",i,cp[i]) ;
    i++ ;
  }

  cp += i ;
  dp += i ;
  
  while (i >= 0) {
    *dp = (double)(*cp) ;
    dp-- ;
    cp-- ;
    i-- ;
  }

  // this also copies over the null terminator
  // as it should
}









int get_timeI (int *hms)
// hms had better be at least 3 ints long
// returns 1 for success, 0 for failure
// which is the opposite of what the standard
// gettimeofday returns
{
 int failure ;
 struct timeval Tp, *tp ;
 struct timezone Tzp, *tzp ;
 time_t  numseconds, *clock ;
 struct tm *x ;

 tp = &Tp ;
 tzp = &Tzp ;
 failure = gettimeofday(tp,tzp) ; // 1 for fail, 0 for success
 numseconds = tp-> tv_sec ;
 clock = &numseconds ;

 x =  localtime(clock) ; 

 hms[0] =     x->tm_hour ;
 hms[1] =     x->tm_min ;
 hms[2] =     x->tm_sec ;

 return (1 - failure) ;

}




int get_timeD (double *hms)
// hms had better be at least 3 doubles long
// returns 1 for success, 0 for failure
// which is the opposite of what the standard
// gettimeofday returns
{
 int ihms[3] ;
 int s ;

 s = get_timeI (ihms) ;

 hms[0] = ihms[0] ;
 hms[1] = ihms[1] ;
 hms[2] = ihms[2] ;

 return s ;
}





///////////////////////////////////////////////////////



double ind ()
// synonym for inD
{
  double x ;

  x = inD() ;

  return x ;
}



void outd (double x)
// synonym for outD
{
  outD(x) ;
}



void outsci (double x)
// output in scientific notation
{
  printf("%.10e",x) ;
}




void outs (const void *p)
// synonym for outS
{
  outS(p) ;
}



int get_time (double *hms)
// synonym for get_timeD
{
  get_timeD(hms) ;
}


double loge (double x)
// synonym for log
{
  double y ;
  y = log(x) ;
  return y ;
}



double rem (double a, double b)
// synonym for fmod
{
  double r ;
  r = fmod(a,b) ;
  return r ;
}




double quo (double a, double b)
// whole number of (a divided by b) rounded toward zero
{
  double d,q ;

  d = a/b ;

  if (d < 0) {
    q = -floor(-d) ;
  }  else {
    q = floor(d) ;
  }

  return q ;
}





#define MKI_LIMIT 1000000000
int mki (double x)
// convert doubles to ints in [-billion,billion] 
// symmetric about zero
// not really a tool most people want to use, but you
// might use it in a preprocessor
{
  int r ;

  if (x < 0) {
    x = -x ;
    if (x > MKI_LIMIT) { x = MKI_LIMIT ; }
    r = (int)(x + 0.5) ;
    r = -r ;
  } else {
    if (x > MKI_LIMIT) { x = MKI_LIMIT ; }
    r = (int)(x + 0.5) ;
  }

  return r ;
}



int chka (double x, int n)
// Knowing the size, n, of an array, check if x (after rounding)
// is an in-range array subscript. If not, print an error message 
// and exit the program, otherwise return the rounded value.
// Usable in a preprocessor.
{
  int r ;

  if (x < 0) {
    printf("Negative Array Reference is ILLEGAL.\n") ;
    exit(0) ;
  }


  r = mki(x) ;
  if (r > n-1) {
    printf("\n") ;
    printf("After converting the array reference, %lf ,\n",x) ;
    printf("to the integer value, %d,\n",r) ;
    printf("it WON'T fit in the array's range of [0,%d)\n",n) ;
    printf("\n") ;
    exit(0) ;
  }

  return r ;
}

