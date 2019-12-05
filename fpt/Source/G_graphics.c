


#include <G_graphics.h>

#include <X_graphics.h> 


/////////////////////////////////////////////////////////////////////
// the G_ routines are graphics related and should
// not be called unless G_init_graphics has been called first
/////////////////////////////////////////////////////////////////////
// The following are merely pointers
// which are initialized by G_Init
// The actual space for the pointers is declared here
// The header file has these pointers declared as "extern"
/////////////////////////////////////////////////////////////////////

int (* G_close) () ;
// terminate the graphics


int (* G_display_image) () ;
// make drawing visible if it already isn't
// in some environments, this might not do anything
// in others it might copy a buffer and/or do other
// synchronizing tasks


int (* Gi_events) (int *d) ;

int (* G_events) (double *d) ;


int (* G_change_pen_dimensions) (double w, double h) ;
// return 0 if illegal w,h specified, otherwise 1


int (* Gi_get_current_window_dimensions) (int *dimentsions) ;
// return 1 if successful
// needs to be passed an array of two ints


int (* G_get_current_window_dimensions) (double *dimentsions) ;
// return 1 if successful
// needs to be passed an array of two doubles


int (* Gi_rgb) (int r, int g, int b) ;
// assumes r,g,b are ints in [0,255]

int (* G_rgb) (double r, double g, double b) ;
// assumes r,g,b are doubles in [0, 1]


/////////////////////////////////////////////////////////////////////
// The next batch are based on the ability to repeatedly
//  plot a single pixel
/////////////////////////////////////////////////////////////////////

int (* G_pixel) (double x, double y) ;
// return 1 always
// This is not guaranteed to be safe


int (* G_point) (double x, double y) ;
// return 1 always
// This is SAFE.
// Draws a thick point whose dimensions are controlled by
// int G_change_pen_dimensions (double w, double h).

int (* G_circle) (double a, double b, double r) ;
// always return 1
// capable of drawing a circle with thick outline

int (* G_unclipped_line) (double ixs, double iys, double ixe, double iye) ;
// return 1 always
// This is SAFE.
// Capable of drawing a thick line.
// This is safe because it depends on G_point (which is SAFE)
// but because it is unclipped, this code could waste a great
// deal of time trying to plot lots of points outside the window.


int (* G_line) (double ixs, double iys, double ixe, double iye) ;
// return 0 if line clipped away entirely, else return 1
// This is SAFE.
// Capable of drawing a thick line.
// This also clips
// Note that the clipping occurs only for a thin, "perfect"
// line, not for a possibly thick line, but the safety feature
// of G_point that will actually plot a thick point, keeps the
// entire code safe.


int (* Gi_polygon) (int *x, int *y, int numpts) ; 
// return 1 always
// capable of drawing a polygon with thick outline

int (* G_polygon) (double *x, double *y, double numpts) ;
// provided as an alternative for passing arrays of doubles
// return 1 always
// capable of drawing a polygon with thick outline


int (* G_triangle) (double x0, double y0, double x1, double y1, double x2, double y2) ; 
// return value it inherits from G_polygon
// capable of drawing a triangle with thick outline


int (* G_rectangle) (double xleft, double yleft, double width, double height) ; 
// return value it inherits from G_polygon
// capable of drawing a rectangle with thick outline



/////////////////////////////////////////////////////////////////////
// This batch are based on the ability to repeatedly
// draw single pixel horizontal lines
/////////////////////////////////////////////////////////////////////


int (* G_single_pixel_horizontal_line) (double x0, double x1, double y) ;
// return 1 always
// This is not guaranteed to be safe


int (* G_clear) () ; 
// return 1 always


int (* G_fill_circle) (double a, double b, double r) ;
// always return 1


int (* G_unclipped_fill_polygon) (double *xx, double *yy, double n) ;
// return 0 if size needs to be truncated (unusual), else 1 
// This is SAFE


int (* Gi_fill_polygon) (int *xx, int *yy, int n) ;
// return 0 if size needs to be truncated (unusual), 
// or if clipping is used,  otherwise return 1
// This is SAFE
// AND it clips


int (* G_fill_polygon) (double *xx, double *yy, double n) ;
// provided as an alternative for passing arrays of doubles
// return 0 if size needs to be truncated (unusual), 
// or if clipping is used,  otherwise return 1
// This is SAFE
// AND it clips


int (* G_fill_triangle) (double x0, double y0, double x1, double y1, double x2, double y2) ; 
// return value it inherits from G_fill_polygon


int (* G_fill_rectangle) (double xleft, double yleft, double width, double height) ;
// return value it inherits from G_fill_polygon


int (* G_font_pixel_height) () ;
// return the font height in pixels






// the void * pointers below allow for passing in 
// either an array of characters (usual usage)
// but also, perhaps, an double array of packed 
// characters

int (* G_string_pixel_width) (const void *s) ;
// return the length in pixles of the string s

int (* G_draw_string) (const void *one_line_of_text, double LLx, double LLy) ;
// draw a single line of text beginning at (LLx,LLy) which specifies
// the coordinates of the lower left corner of the bounding box
// of the text


int (* G_draw_text) (
               int num_lines_of_text,
               const void  *lines_of_text, // an array of pointers
               double startx, 
               double starty,
               double height,
               double x_over_y_ratio,
               double extra_space_between_letters_fraction,
               double extra_space_between_lines_fraction) ;


int (* G_save_image_to_file) (const void *filename) ;
// return 1 if successful, else 0

int (* G_get_image_from_file) (const void *filename, double x, double y) ;
// return 1 if successful, else 0



int (* G_get_pixel) (double x, double y) ;
// return the 32 bit pixel value...assumes x,y are legal
// i.e. it is NOT safe

int (* G_get_pixel_SAFE) (double x, double y, int pixel[1]) ;
// return 1 if successful, else 0

int (* G_convert_pixel_to_rgbI) (int pixel, int rgbI[3]) ;
// rgbI[] values in 0-255
// return 1 if successful, else 0

int (* G_convert_rgbI_to_rgb) (int rgbI[3], double rgb[3]) ;
// convert rgbI[] in 0-255 to rgb[] in 0.0 - 1.0
// return 1 if successful, else 0



///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
// Below are actual functions
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


int  G_init_graphics (double w, double h)
// G_init_graphics has the task of connecting this interface
// with actual routines that can do the work in a
// specific environment, e.g. X11 or Windows or whatever
{
 int s ;

 G_close = Close_Down_X ;

 // G_display_image = Copy_Buffer_X ;
 G_display_image = Copy_Buffer_And_Flush_X ;

 Gi_events = Get_Events_X ;

 G_events = Get_Events_DX ;

 G_change_pen_dimensions =  Change_Pen_Dimensions_X ;

 Gi_get_current_window_dimensions = Get_Current_Dimensions_X ;

 G_get_current_window_dimensions = Get_Current_Dimensions_DX ;

 Gi_rgb = Set_Color_Rgb_X ;

 G_rgb = Set_Color_Rgb_DX ;

 G_pixel = Point_X ;

 G_point = Safe_Point_X ;

 G_circle = Circle_X ;

 G_unclipped_line = Line_X ;

 // G_line = Line_X ;
 G_line = Safe_Line_X ;

 Gi_polygon = Polygon_X ; 

 G_polygon = Polygon_DX ;

 G_triangle = Triangle_X ; 

 G_rectangle = Rectangle_X ; 

 G_single_pixel_horizontal_line = Horizontal_Single_Pixel_Line_X ;

 G_clear = Clear_Buffer_X ;

 G_fill_circle =  Fill_Circle_X ;

 G_unclipped_fill_polygon =  Fill_Polygon_DX ; 

 Gi_fill_polygon = Fill_Polygon_X ; 

 G_fill_polygon = Fill_Polygon_DX ; 

 G_fill_triangle = Fill_Triangle_X ;

 G_fill_rectangle = Fill_Rectangle_X ;

 G_font_pixel_height = Font_Pixel_Height_X ;

 G_string_pixel_width = String_Pixel_Width_X ;

 G_draw_string = Draw_String_X ;

 G_draw_text = Draw_Text_X ;

 G_save_image_to_file = Save_Image_To_File_X ;

 G_get_image_from_file = Get_Image_From_File_X ;

 G_get_pixel = Get_Pixel_X ;

 G_get_pixel_SAFE = Get_Pixel_SAFE_X ;

 G_convert_pixel_to_rgbI = Convert_Pixel_To_rgbI_X ;

 G_convert_rgbI_to_rgb = Convert_rgbI_To_rgb_X ;

 s = Init_X(w,h) ;

 return s ;
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


// The following functions are built on top of G
// not directly on top of the underlying
// video system


int Gi_wait_click(int p[2])
{
  int sig ;

  G_display_image();  
  do {
    sig = Gi_events(p) ;
  }  while (sig != -3) ;

  return sig ;
}



int G_wait_click(double p[2])
{
  int sig ;
  int pi[2] ;

  sig = Gi_wait_click(pi) ;
  p[0] = pi[0] ;
  p[1] = pi[1] ;
  
  return sig ;
}



int G_wait_key()
{
  int p[2] ;
  int sig ;

  G_display_image();  
  do {
    sig = Gi_events(p) ;
  }  while (sig < 0) ;

  return sig ;
}










/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// Added Aug 28, 2012



static int sector(double xcenter, double ycenter, double radius, 
                  double start_radians, double end_radians,
                  double *x, double *y,
	          int num_pts_in_full_circle) 
{
  int num,j ;
  double theta,delta ;

  //  printf("start = %lf  end = %lf\n",start_radians,end_radians) ;

  delta = end_radians - start_radians ;
  if (delta < 0) return 0 ;
  if (delta > 2*M_PI) return 0 ;

  num = (int)(num_pts_in_full_circle*delta/(2*M_PI)) ;

  //  printf("delta = %lf  num = %d\n",delta,num) ;

  if (num < 1) { num = 1 ; }
  else if (num > 500) { num = 500 ; }

  //  printf("new num = %d\n",num) ;

  j = 0 ; 
  while (j <= num) {
    theta = start_radians + j*delta/num;

    // printf("j = %d  theta = %lf\n",j,theta) ;

    x[j] = xcenter + radius*cos(theta) ;
    y[j] = ycenter + radius*sin(theta) ;

    j++ ;
  }
  x[j] = xcenter ;y[j] = ycenter ; j++ ;

  return j ;
}



int G_sector(double xcenter, double ycenter, double radius, 
             double start_radians, double end_radians)
{
  int num_pts_in_full_circle, n ;
  double x[500+3],y[500+3] ;

  num_pts_in_full_circle = 500 ;

  n = sector(xcenter,ycenter,radius,start_radians,end_radians,
             x,y,num_pts_in_full_circle) ;

  // normally, n == num_pts_in_full_circle + 1 

  if (n <= 0) {
    printf("Sector flaw\n") ;
  } else {
    G_polygon(x,y,n) ;
  }

  return 1 ;
}




int G_fill_sector(double xcenter, double ycenter, double radius, 
                  double start_radians, double end_radians)
{
  int num_pts_in_full_circle, n ;
  double x[500+3],y[500+3] ;

  num_pts_in_full_circle = 500 ;

  n = sector(xcenter,ycenter,radius,start_radians,end_radians,
             x,y,num_pts_in_full_circle) ;

  // normally, n == num_pts_in_full_circle + 1 

  if (n <= 0) {
    printf("Sector flaw\n") ;
  } else {
    G_fill_polygon(x,y,n) ;
  }

  return 1 ;
}



/////////////////////////////////////////////////////////////////

static double mouse_values[2] ;


int G_wait_mouse()
// save off mouse click in reserved variables
{
  G_wait_click(mouse_values) ;
}



double G_x_mouse()
// return x coordinate of last G_wait_mouse
{
  return mouse_values[0] ;
}



double G_y_mouse()
// return y coordinate of last G_wait_mouse
{
  return mouse_values[1] ;
}



  

