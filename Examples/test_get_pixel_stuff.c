
#include <FPT.h>   

int main()
{
   int    swidth, sheight ;
   double lowleftx, lowlefty, width, height ;
   double x[10],y[10] ;
   double numpoints,q, x0,y0,x1,y1 ;
   double p[2] ;
   int    i ;


   // must do this before you do 'almost' any other
   // graphical tasks 
   swidth = 400 ;  sheight = 500 ;
   G_init_graphics (swidth, sheight) ;


   // draw a point, a line, some rectangles, some triangles 

   G_rgb(1, 0, 0) ;  // red 
   G_point(200, 380) ;
   G_fill_rectangle (300,400, 50, 20) ;

   G_rgb(0, 1, 0) ;  // green
   //   G_line (0, 0, 400, 400) ; // won't show if part is off screen
   G_line (0, 0, 399, 399) ;
   G_fill_triangle(50, 400,  100,400,  150,475) ;
  
   G_rgb(0, 0, 1) ;  // blue 
   lowleftx = 200 ; lowlefty = 50 ; width = 10 ; height = 30 ;
   G_rectangle (lowleftx, lowlefty, width, height) ;
   lowleftx = 250 ; 
   G_fill_rectangle (lowleftx, lowlefty, width, height) ;


   G_rgb(1, 1, 0) ;  // yellow
   G_triangle (10, 300,  40,300,  60,250) ;
   G_fill_triangle (10,100,  40,100,  60,150) ;

   G_rgb(1, 0.5, 0) ;  // orange
   G_circle (100, 300, 75) ;
   G_fill_circle (370, 200, 50) ;

   // prints text in your graphics window 
   G_rgb(0, 0, 0) ;  // black
   G_draw_string ("hello",300,100) ;



   // draw a polygon 
   x[0] = 100 ;   y[0] = 100 ;
   x[1] = 100 ;   y[1] = 300 ;
   x[2] = 300 ;   y[2] = 300 ;
   x[3] = 300 ;   y[3] = 100 ;
   x[4] = 200 ;   y[4] = 175 ;
   numpoints = 5 ;
   G_polygon (x,y,numpoints) ;


   G_rgb (0.4, 0.2, 0.1) ; // brown
   G_fill_polygon (x,y,numpoints) ;

   G_rgb (0.5, 0.8, 0.4) ;// what color is this?



   int xc,yc ;
   int pixel ;
   int rgbI[3] ;
   double rgb[3] ;

   G_wait_click(p) ;  
   xc = p[0] ; yc = p[1] ;
   while (yc > 20) {

     printf("%d %d\n",xc,yc) ;
     pixel = G_get_pixel(xc,yc) ;
     G_convert_pixel_to_rgbI(pixel, rgbI) ;
     G_convert_rgbI_to_rgb(rgbI, rgb) ;

     printf("pixel = %x\n",pixel) ;
     printf("%3d %3d %3d\n",rgbI[0],rgbI[1],rgbI[2]) ;
     printf("%lf %lf %lf\n",rgb[0],rgb[1],rgb[2]) ;
     printf("\n") ;

     G_wait_click(p) ;  
     xc = p[0] ; yc = p[1] ;
   }





}



