
#ifndef  X_graphics_a0b1c2d3
#define  X_graphics_a0b1c2d3

// Inspiration :
// Peter Meyers
// Eric Rorem
// Barry Schaudt
// Tony Leclerc
// Mark Vojkovich
// Jeff Ely

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h> 
#include <X11/Xutil.h>// for XComposeStatus
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // for drand48
#include <string.h> // for strlen


int Init_X (double Dswidth, double Dsheight) ;

int Close_Down_X() ;

int Clear_Buffer_X() ; 

int Select_Gray_X (double color) ;




int Copy_Buffer_X() ;

int Flush_X() ;

int Copy_Buffer_And_Flush_X() ;

int Sync_X (int bool_val) ;







int Handle_Events_X (int *px, int *py) ;

int Get_Events_X (int *d) ;
// d needs to point to 2 or more ints
// merely repackages Handle_Events_X

int Get_Events_DX (double *d) ;
// d needs to point to 2 or more doubles
// merely repackages Handle_Events_X






int Set_Color_Rgb_X (int r, int g, int b) ;
// assumes r,g,b are ints in [0,255]

int Set_Color_Rgb_DX (double dr, double dg, double db) ;
// assumes r,g,b are doubles in [0, 1]

int Point_X (double Dx, double Dy) ; 

int Safe_Point_X (double Dx, double Dy) ;

int Line_X (double Dxs, double Dys, double Dxe, double Dye) ;

int Safe_Line_X (double Dxs, double Dys, double Dxe, double Dye) ;

int Rectangle_X (double Dxlow, double Dylow, double Dwidth, double Dheight) ; 

int Fill_Rectangle_X (double Dxlow, double Dylow, double Dwidth, double Dheight) ;


int Triangle_X (double Dx1, double Dy1, 
                double Dx2, double Dy2,
                double Dx3, double Dy3) ;


int Fill_Triangle_X (double Dx1, double Dy1, 
                     double Dx2, double Dy2,
                     double Dx3, double Dy3) ;

int Polygon_X (int *x, int *y, int npts) ;

int Polygon_DX (double *x, double *y, double Dnpts) ;

int Fill_Polygon_X (int *x, int *y, int npts) ;

int Fill_Polygon_DX (double *x, double *y, double Dnpts) ;

int Horizontal_Single_Pixel_Line_X (double Dx0, double Dx1, double Dy) ;

int Circle_X (double Da, double Db, double Dr) ;

int Fill_Circle_X (double Da, double Db, double Dr) ;

int Font_Pixel_Height_X () ;
// Returns the height of the font in pixels. 




// the void * declarations below allow for the passing
// of a character array (usual usage) but also, for instance,
// a double array of packed characters


int String_Pixel_Width_X (const void *s) ;
// Returns the length, in pixels, of the string s 

int Draw_String_X (const void *s, double Dx, double Dy) ;
// Draw the string s, with the lower left hand corner at (x,y)


int Get_Current_Dimensions_X (int dimensions[2]) ;

int Get_Current_Dimensions_DX (double dimensions[2]) ;

int Change_Pen_Dimensions_X (double Dw, double Dh) ;

int Draw_Text_X (
               int num_lines_of_text,
               const void  *lines_of_text,  // an aray of pointers
               double startx, 
               double starty,
               double height,
               double x_over_y_ratio,
               double extra_space_between_letters_fraction,
               double extra_space_between_lines_fraction)  ;


int Save_Image_To_File_X (const void *filename) ;


int Get_Image_From_File_X (const void *filename, double Dx, double Dy) ;
// Put lower left corner of file into the graphics window at (x,y).
// return 1 if successful else 0


int Get_Image_Dimensions_From_File_X (int d[2], void *filename) ;
// return 1 if successful else 0
// You do NOT need to have initialized the graphics environment 
// before you call this function


int Get_Pixel_X (double Dx, double Dy) ;
// return the 32 bit pixel value...assumes x,y are legal
// i.e. it is NOT safe

int Get_Pixel_SAFE_X (double Dx, double Dy, int pixel[1]) ;
// return 1 if successful, else 0

int Convert_Pixel_To_rgbI_X (int pixel, int rgbI[3]) ;
// rgbI[] values in 0-255
// return 1 if successful, else 0

int Convert_rgbI_To_rgb_X (int rgbI[3], double rgb[3]) ;
// convert rgbI[] in 0-255 to rgb[] in 0.0 - 1.0
// return 1 if successful, else 0


int XImage_to_Display (XImage *pxim, double Dx, double Dy) ;
// Put lower left corner of file into the graphics window at (x,y).
// return 1 if successful else 0
#endif

