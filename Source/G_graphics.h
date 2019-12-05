
#ifndef GENERIC_GRAPHICS_DEF
#define GENERIC_GRAPHICS_DEF


#include <X_graphics.h> 


/////////////////////////////////////////////////////////////////////
// the G_ routines are graphics related and should
// not be called unless G_init_graphics has been called first
/////////////////////////////////////////////////////////////////////
// The following are merely pointers
// which are initialized by G_Init
// The actual space for the pointers is declared IN G_graphics.c
// The header file has these pointers declared as "extern"
/////////////////////////////////////////////////////////////////////


extern int (* G_close) () ;
// terminate the graphics


extern int (* G_display_image) () ;
// make drawing visible if it already isn't
// in some environments, this might not do anything
// in others it might copy a buffer and/or do other
// synchronizing tasks


extern int (* Gi_events) (int *d) ;

extern int (* G_events) (double *d) ;


extern int (* G_change_pen_dimensions) (double w, double h) ;
// return 0 if illegal w,h specified, otherwise 1


extern int (* Gi_get_current_window_dimensions) (int *dimentsions) ;
// return 1 if successful
// needs to be passed an array of two ints


extern int (* G_get_current_window_dimensions) (double *dimentsions) ;
// return 1 if successful
// needs to be passed an array of two doubles


extern int (* Gi_rgb) (int r, int g, int b) ;
// assumes r,g,b are ints in [0,255]

extern int (* G_rgb) (double r, double g, double b) ;
// assumes r,g,b are doubles in [0, 1]


/////////////////////////////////////////////////////////////////////
// The next batch are based on the ability to repeatedly
//  plot a single pixel
/////////////////////////////////////////////////////////////////////

extern int (* G_pixel) (double x, double y) ;
// return 1 always
// This is not guaranteed to be safe


extern int (* G_point) (double x, double y) ;
// return 1 always
// This is SAFE.
// Draws a thick point whose dimensions are controlled by
// int G_change_pen_dimensions (double w, double h).

extern int (* G_circle) (double a, double b, double r) ;
// always return 1
// capable of drawing a circle with thick outline

extern int (* G_unclipped_line) (double ixs, double iys, double ixe, double iye) ;
// return 1 always
// This is SAFE.
// Capable of drawing a thick line.
// This is safe because it depends on G_point (which is SAFE)
// but because it is unclipped, this code could waste a great
// deal of time trying to plot lots of points outside the window.


extern int (* G_line) (double ixs, double iys, double ixe, double iye) ;
// return 0 if line clipped away entirely, else return 1
// This is SAFE.
// Capable of drawing a thick line.
// This also clips
// Note that the clipping occurs only for a thin, "perfect"
// line, not for a possibly thick line, but the safety feature
// of G_point that will actually plot a thick point, keeps the
// entire code safe.


extern int (* Gi_polygon) (int *x, int *y, int numpts) ; 
// return 1 always
// capable of drawing a polygon with thick outline

extern int (* G_polygon) (double *x, double *y, double numpts) ;
// provided as an alternative for passing arrays of doubles
// return 1 always
// capable of drawing a polygon with thick outline


extern int (* G_triangle) (double x0, double y0, double x1, double y1, double x2, double y2) ; 
// return value it inherits from G_polygon
// capable of drawing a triangle with thick outline


extern int (* G_rectangle) (double xleft, double yleft, double width, double height) ; 
// return value it inherits from G_polygon
// capable of drawing a rectangle with thick outline



/////////////////////////////////////////////////////////////////////
// This batch are based on the ability to repeatedly
// draw single pixel horizontal lines
/////////////////////////////////////////////////////////////////////


extern int (* G_single_pixel_horizontal_line) (double x0, double x1, double y) ;
// return 1 always
// This is not guaranteed to be safe


extern int (* G_clear) () ; 
// return 1 always


extern int (* G_fill_circle) (double a, double b, double r) ;
// always return 1


extern int (* G_unclipped_fill_polygon) (double *xx, double *yy, double n) ;
// return 0 if size needs to be truncated (unusual), else 1 
// This is SAFE


extern int (* Gi_fill_polygon) (int *xx, int *yy, int n) ;
// return 0 if size needs to be truncated (unusual), 
// or if clipping is used,  otherwise return 1
// This is SAFE
// AND it clips


extern int (* G_fill_polygon) (double *xx, double *yy, double n) ;
// provided as an alternative for passing arrays of doubles
// return 0 if size needs to be truncated (unusual), 
// or if clipping is used,  otherwise return 1
// This is SAFE
// AND it clips


extern int (* G_fill_triangle) (double x0, double y0, double x1, double y1, double x2, double y2) ; 
// return value it inherits from G_fill_polygon


extern int (* G_fill_rectangle) (double xleft, double yleft, double width, double height) ;
// return value it inherits from G_fill_polygon


extern int (* G_font_pixel_height) () ;
// return the font height in pixels






// the void * pointers below allow for passing in 
// either an array of characters (usual usage)
// but also, perhaps, an double array of packed 
// characters

extern int (* G_string_pixel_width) (const void *s) ;
// return the length in pixles of the string s

extern int (* G_draw_string) (const void *one_line_of_text, double LLx, double LLy) ;
// draw a single line of text beginning at (LLx,LLy) wihc specifies
// the coordinates of the lower left corner of the bounding box
// of the text


extern int (* G_draw_text) (
               int num_lines_of_text,
               const void  *lines_of_text, // an array of pointers
               double startx, 
               double starty,
               double height,
               double x_over_y_ratio,
               double extra_space_between_letters_fraction,
               double extra_space_between_lines_fraction) ;


extern int (* G_save_image_to_file) (const void *filename) ;
// return 1 if successful, else 0

extern int (* G_get_image_from_file) (const void *filename, double x, double y) ;
// return 1 if successful, else 0



extern int (* G_get_pixel) (double x, double y) ;
// return the 32 bit pixel value...assumes x,y are legal
// i.e. it is NOT safe

extern int (* G_get_pixel_SAFE) (double x, double y, int pixel[1]) ;
// return 1 if successful, else 0

extern int (* G_convert_pixel_to_rgbI) (int pixel, int rgbI[3]) ;
// rgbI[] values in 0-255
// return 1 if successful, else 0

extern int (* G_convert_rgbI_to_rgb) (int rgbI[3], double rgb[3]) ;
// convert rgbI[] in 0-255 to rgb[] in 0.0 - 1.0
// return 1 if successful, else 0


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
// Below are actual function interfaces
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


int  G_init_graphics (double w, double h) ;
// G_init_graphics has the task of connecting this interface
// with actual routines that can do the work in a
// specific environment, e.g. X11 or Windows or whatever



////////////////////////////////////////////////////////////////////
// The following functions are built on top of G
// not directly on top of the underlying
// video system
////////////////////////////////////////////////////////////////////

int Gi_wait_click(int p[2]) ;

int G_wait_click(double p[2]) ;

int G_wait_key() ;





/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// Added Aug 28, 2012

int G_sector(double xcenter, double ycenter, double radius, 
             double start_radians, double end_radians) ;

int G_fill_sector(double xcenter, double ycenter, double radius, 
                  double start_radians, double end_radians) ;

int G_wait_mouse() ;
// save off mouse click in reserved variables

double G_x_mouse() ;
// return x coordinate of last G_wait_mouse

double G_y_mouse() ;
// return y coordinate of last G_wait_mouse

  


#endif
