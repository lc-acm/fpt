
#include <FPT.h>

// Pascal's triangle mod 2

int main()
{
  int size,x,y,row,r,p[1000],q ;

  printf("Enter screen size <= 1000 ") ;
  scanf("%d",&size) ;
  
  G_init_graphics (size, size) ;

  row = 0 ;
  while (row < size) {

        p[row] = 1 ;
        r = row - 1 ;
        while (r > 0) {
            p[r] = (p[r] + p[r-1]) %  2  ;
            r = r - 1 ;
        }
     
        y = row ;
        x = 0 ;
        while (x <= row) {
            if (p[x] == 0) {
                G_rgb(0.7, 1.0 , 0.0) ;
	    } else {
                G_rgb(0.0, 0.0 , 1.0) ;
	    }

            G_point(x,y) ;
            x = x + 1 ;
        }

        row = row + 1 ;
  }

  q = G_wait_key() ;

}

  
