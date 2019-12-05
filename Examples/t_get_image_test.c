
#include <FPT.h>   

int main(int argc, char **argv)
{
   int swidth, sheight, q, s ; 
   int llx, lly ;

   if (argc != 5) {
     printf("Usage : pgm  width height lowleftx lowlefty\n") ;
     exit(0) ;
   }

   // must do this before you do 'almost' any other graphical tasks 
   swidth = atoi(argv[1]) ;  sheight = atoi(argv[2]) ;
   llx = atoi(argv[3]) ; lly = atoi(argv[4]) ;

   G_init_graphics (swidth, sheight) ;
   G_rgb(0.5, 0.5 , 0.5) ; G_clear() ;

   s = G_get_image_from_file("t01e.xwd", llx, lly) ;
   if (s == 0) printf("unsuccessful\n") ;

   q = G_wait_key() ; // pause to look ...any key to continue

   G_close() ; // terminate graphics...probably not fatal if forgotten
}



