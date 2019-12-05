

#include <FPT.h>   


int swidth, sheight ;



void Draw(double degrees)
{
   double xcen,ycen,radius ;

   int i,n ;
   double delta,u,v ;
   double x0,y0, x1,y1,x2,y2 ;
   double color ;
   double r,g,b ;

   G_clear() ;

   n = 24 ;
   xcen = 0.5*swidth ; ycen = 0.5*sheight ; 

   if (swidth < sheight) { radius = 0.4*swidth ;}
   else { radius = 0.4*sheight ; }

   delta = 360.0/n ;
   for (i = 0 ; i < n ; i+=1) {
     u =  degrees + i*delta ;
     v =  u + delta ;
     u *= (M_PI/180) ;
     v *= (M_PI/180) ;

     x0 = xcen ;
     y0 = ycen ;

     x1 = xcen + radius*cos(u) ;
     y1 = ycen + radius*sin(u) ;

     x2 = xcen + radius*cos(v) ;
     y2 = ycen + radius*sin(v) ;

     if (i == 0) {
       r = 1 ; g = 1 ; b = 0 ;
     } else if (i % 2 == 0) {
       r = 1 ; g = 0 ; b = 0 ;
     } else {
       r = 0 ; g = 0 ; b = 1 ;
     }
     

     G_rgb (r,g,b) ;
     G_fill_triangle(x0,y0, x1,y1, x2,y2) ;

   }
}





int test02(int numreps, int sleepflag, int microseconds)
{
     double degrees ;
     int i ;

     swidth = 500 ;
     sheight = 600 ;

     if(! G_init_graphics (swidth, sheight)) return -1;

     for (i = 0 ; i < numreps ; i++) {

        degrees = i ;

	Draw(degrees);
        G_display_image() ;
	if (sleepflag) usleep(microseconds) ;
     }

     G_close();


     return 1;
}


//INTERESTING!!!! usleep(0) slows the simulation down quite
// a bit over not calling usleep at all, ergo the use
// of sleepflag

int main (int argc, char **argv)
{
  int numreps, sleepflag, microseconds ;

  if (argc != 4) {
    printf("Usage : pgm numreps sleepflag(0/1) microseconds\n") ;
    exit(0) ;
  }

  numreps = atoi(argv[1]) ;
  sleepflag = atoi(argv[2]) ;
  microseconds = atoi(argv[3]) ;
  test02(numreps, sleepflag, microseconds) ;

}
