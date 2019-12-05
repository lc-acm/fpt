

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

   G_clear();

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
     G_fill_triangle (x0,y0, x1,y1, x2,y2) ;
   }
}





int test01()
{
     int sig = 0 ;
     int p[2], x,y, i ;
     double degrees ;

     swidth = 500 ;
     sheight = 600 ;

     if(! G_init_graphics (swidth, sheight)) return -1;

     Draw(0);
     G_display_image() ;

     i = 0 ;
     while(sig != 'q') {

        sig = Gi_events(p) ;
        x = p[0] ; y = p[1] ;
        degrees = sqrt(x*x + y*y) ;
	printf("i = %d   sig = %d  x = %d   y = %d\n",i,sig,x,y) ;
	i++ ;

        if (sig == -4) {
	  // window resize
          swidth = x ; sheight = y ;
	}

	Draw(degrees);
        G_display_image() ;
     }

     G_close();

     return 1;
}



int main (int argc, char **argv)
{

  test01() ;
}
