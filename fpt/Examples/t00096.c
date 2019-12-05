
#include <FPT.h>


double x[13] = {175,225,225,300,225,225,250,200,150,175,175,100,175} ;
double y[13] = {300,300,250,225,225,200,100,175,100,200,225,225,250} ;
double n = 13 ;


void translate (double dx, double dy)
{
  int i ;

  i = 0 ;
  while (i < n) {
     x[i] = x[i] + dx ;
     y[i] = y[i] + dy ;
     i = i + 1 ;
  }
}


void scale (double s)
{
  int i ;

  i = 0 ;
  while (i < n) {
     x[i] = s * x[i] ;
     y[i] = s * y[i] ;
     i = i + 1 ;
  }
}


void rotate (double degrees)
{
  int i ;
  double radians,c,s,t ;

  radians = degrees*M_PI/180.0 ;
  c = cos(radians) ;
  s = sin(radians) ;

  i = 0 ;
  while (i < n) {
      t    = x[i]*c - y[i]*s ;
      y[i] = y[i]*c + x[i]*s ;
      x[i] = t ;
      i = i + 1 ;
  }
}


void waste_time (int n)
{
  int i ;
  double x ;

  x = 1.0 ;
  for (i = 0 ; i < n ; i++) {
      x = sin(x) ;
  }
}


int main() 
{
 double j ;
 int q ;

 G_init_graphics (401, 401) ;

 // the original design is a bit too small
 // for the window so we make it larger
 translate(-200.0, -200) ;
 scale(1.5) ;
 translate(200.0, 200.0) ;


 j = 0 ;
 while (j < 100) {

   G_rgb(1.0, 1.0, 1.0) ;
   G_fill_rectangle(0, 0, 400, 400) ;
   G_rgb(0.0, 0.0, 0.0) ;
   G_rectangle(0, 0, 400, 400) ;

   G_rgb(0.0, 0.5, 1.0) ;
   G_fill_polygon(x,y,n) ;


   // q = G_wait_key() ;

   G_display_image() ;
   usleep(25000) ;  // microseconds 
   //   waste_time(700000) ;
   
   translate(-200.0, -200) ;
   scale(0.95) ;
   rotate(4.0) ;
   translate(200.0, 200.0) ;

   j=j+1 ;
 }

 G_rgb(1.0, 0.0, 0.0) ;
 G_fill_rectangle(0.0, 0.0, 400.0, 400.0) ;

 q = G_wait_key() ;
 while (q != 'q') {
   q = G_wait_key() ;
 }

}

