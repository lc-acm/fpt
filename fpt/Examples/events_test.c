#include <FPT.h>

int main()
{
  int s, e[2] ;

  G_init_graphics(600,400) ;

  while (1) {

   s = Get_Events_X(e) ;

   if (s >= 0) {

    printf("key pressed\n") ;
    if (s == 'q') break ;

   } else if (s == -1) {
     printf("window exposed\n") ;
   } else if (s == -2) {
     printf("mouse dragged\n") ;
   } else if (s == -3) {
     printf("mouse clicked\n") ;
   } else if (s == -4) {
     printf("window resized\n") ;
   } else if (s == -1000) {
     printf("unspecified event\n") ;
   } else if (s == -2000) {
     printf("window in motion\n") ;
   } else {
     printf("this should never happen\n") ;
   }

  }

}
