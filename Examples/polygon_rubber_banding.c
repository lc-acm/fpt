#include <FPT.h>




void draw_line_segment_sequence (double *x, double *y, int n)
{
  int i ;
  for (i = 0 ; i < n-1 ; i++) {
    G_line(x[i],y[i], x[i+1],y[i+1]) ;
  }
}




int click_polygon_rubber_band_style (double min_y_value, double *x, double *y)
// allows "rubber banding"
// return size of the polygon
// routine finishes when a point is clicked under the y = min_y_value line
// clicking the points alone will not have them register....
// each must be clicked AND draggged into place
{
  int s ;
  double E[2] ;
  double old[2] ;
  int n ;

  n = 0 ;

  G_wait_click(E) ; 
  x[n] = E[0] ; y[n] = E[1] ; n++ ;
  G_rgb(0,0,0) ;
  G_fill_circle(E[0],E[1],2) ;
  G_display_image() ;
    

  while (1) {

    do { s = Get_Events_DX (E) ; } while (s != -2) ;
                    // the -2 code is the mouse drag
                    // -3 is the mouse click
    while (s == -2) {

      G_rgb(1,1,1) ;
      G_clear() ;
      G_rgb(0,0,0) ;
      draw_line_segment_sequence(x,y,n) ;
        // to do this right, you really need to have either multiple layers
        // or to save and restore the underlying image


      G_line(x[n-1],y[n-1],E[0],E[1]) ;
      G_display_image() ;
      old[0] = E[0] ; old[1] = E[1] ;
      s = Get_Events_DX (E) ;
    }

    x[n] = old[0] ; y[n] = old[1] ; n++ ;
    
    if (E[1] < min_y_value) break ;

  }

  return n ;
}





int main()
{
  double x[1000],y[1000] ;
  int n ;
  int q ;

  G_init_graphics(800,600) ;
  G_rgb(1,1,1) ;
  G_clear() ;
  G_rgb(0,0,0) ;
  n = click_polygon_rubber_band_style (10, x,y) ;
  G_rgb(1,0,0) ;
  G_fill_polygon(x,y,n) ;
  q = G_wait_key() ;
}
