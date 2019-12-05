
// Inspiration :
// Peter Meyers
// Eric Rorem
// Barry Schaudt
// Tony Leclerc
// Mark Vojkovich
// Jeff Ely

#include <X_graphics.h>

static int	 The_Win_width ;
static int       The_Win_height ;

static int	 The_Pix_width ;
static int       The_Pix_height ;

static int	 The_Tmp_width ;
static int       The_Tmp_height ;

static int	 TheDepth;



static Display	*TheDisplay;
static Window    TheRootWindow;
static int	 TheScreenNumber;
static Window	 TheWindow;
static Pixmap	 ThePixmap;
static Pixmap	 TheTmpPixmap;
static XID	 TheDrawable;
static GC	 TheWindowContext;
static GC	 ThePixmapContext;
static GC	 TheTmpContext;


//static char         *TheFont = "9x15" ;
//static char         *TheFont = "8x13" ;
//static char         *TheFont = "9x15bold" ;
//static char         *TheFont = "6x9" ;
static char         *TheFont = "10x20" ;
//static char         *TheFont = "12x24" ;


static XFontStruct  *TheFontInfo;


static int Current_Red_Int ;
static int Current_Green_Int ;
static int Current_Blue_Int ;
static unsigned long int Current_Color_Pixel ;
static unsigned long int Last_Clear_Buffer_Pixel ;



int Clear_Buffer_X() 
{
   unsigned long int p ;

   //   XSetForeground(TheDisplay, ThePixmapContext, 0);

   //   p = 0xffffff ; // white
   //   XSetForeground(TheDisplay, ThePixmapContext, p);

   // have decided that it is best for this to simply
   // use the color that was last instantiated
   // you want to avoid having a call to this inadvertently
   // also changing the "last" color and either of the codes
   // that is commented out above clearly did this


   XFillRectangle(TheDisplay, TheDrawable, ThePixmapContext, 
                                           0, 0, The_Pix_width, The_Pix_height);
   XFlush(TheDisplay);  
   Last_Clear_Buffer_Pixel = Current_Color_Pixel ;
}



int Init_X (double Dswidth, double Dsheight)
{
  int swidth = (int)Dswidth ;
  int sheight = (int)Dsheight ;

    XGCValues vals;
    Colormap TheColormap;
    XColor TheColor;
    int i;


    
    TheDisplay = XOpenDisplay("\0");
    TheRootWindow = DefaultRootWindow(TheDisplay);
    TheScreenNumber = DefaultScreen(TheDisplay); 
    TheDepth = DefaultDepth(TheDisplay, TheScreenNumber);
    if (TheDepth != 24) {
      printf("24 bit color not supported.\n") ;
      printf("Color function not likely to work.\n") ;
      return 0 ;
    }


    ///////////////////////////////////////////////////////////////////

    The_Pix_width = swidth ;
    The_Pix_height = sheight ;

    The_Win_width = swidth ;   // initial belief
    The_Win_height = sheight ; // initial belief

    int maxwidth,maxheight ;
    maxwidth = XDisplayWidth(TheDisplay,TheScreenNumber) ;
    maxheight = XDisplayHeight(TheDisplay,TheScreenNumber) ;

    if (swidth > maxwidth) {
      printf("Requested width of %d exceeds max allowable of %d.\n",
	     swidth,maxwidth) ;

      printf("The display window width truncated\n") ;
      printf("BUT the back buffer IS as specified.\n") ;
      The_Win_width = maxwidth ;
    } 


    if (sheight > maxheight) {
      printf("Requested height of %d exceeds max allowable of %d.\n",
	     sheight,maxheight) ;

      printf("The display window width truncated\n") ;
      printf("BUT the back buffer IS as specified.\n") ;
      The_Win_height = maxheight ;
    } 

    ///////////////////////////////////////////////////////////////////


    TheWindow = XCreateSimpleWindow(TheDisplay, TheRootWindow,
                        0, 0, The_Win_width, The_Win_height, 0, 0, 0);

    if (!TheWindow) return 0 ;



    ThePixmap = XCreatePixmap(TheDisplay, TheRootWindow,
                              The_Pix_width, The_Pix_height, TheDepth);

    if (!ThePixmap) return 0 ;

    TheDrawable = ThePixmap;


    XMapWindow(TheDisplay, TheWindow);
    XSelectInput(TheDisplay, TheWindow, ExposureMask |
					StructureNotifyMask |
					PointerMotionMask | 
					ButtonPressMask |
					KeyPressMask );




    vals.graphics_exposures = 0; // False
    TheWindowContext = XCreateGC(TheDisplay, TheWindow,
                                 GCGraphicsExposures, &vals);
    if (!TheWindowContext) return 0;



    ThePixmapContext = XCreateGC(TheDisplay, ThePixmap, 0, 0);
    if (!ThePixmapContext) return 0;


    TheColormap = DefaultColormap(TheDisplay, TheScreenNumber);


    TheFontInfo = XLoadQueryFont(TheDisplay, TheFont) ;
    //    XSetFont(TheDisplay, TheWindowContext, TheFontInfo->fid) ;
    XSetFont(TheDisplay, ThePixmapContext, TheFontInfo->fid) ;



    XClearArea(TheDisplay, TheWindow, 0,0,0,0,True); 


    // most people expect a white piece of paper
    // with a black pencil
    Set_Color_Rgb_X (255,255,255) ; // white
    Clear_Buffer_X() ; // otherwise you can inherit garbage
    // from the parent window

    Copy_Buffer_X() ;


    XFlush(TheDisplay);  


    Set_Color_Rgb_X (0,0,0) ; // black pencil
    return 1 ;
}



int Close_Down_X()
{
    XDestroyWindow(TheDisplay, TheWindow);
    XFreeGC(TheDisplay, TheWindowContext);
    XFreeGC(TheDisplay, ThePixmapContext);
    XFreePixmap(TheDisplay, ThePixmap);
    XCloseDisplay(TheDisplay);
}








int Copy_Buffer_X()
{

  /*
   XCopyArea(TheDisplay, ThePixmap, TheWindow, TheWindowContext,
	     0, 0, The_Win_width, The_Win_height, 0,0) ;
  */

   // assumes that Pixmap is >= window on both dimensions
   // which will normally be the case
   // unless temporarily while resizing occurs
   XCopyArea(TheDisplay, ThePixmap, TheWindow, TheWindowContext,
	     0, The_Pix_height - The_Win_height,
             The_Win_width, The_Win_height,
             0,0) ;
			
}



int Flush_X()
{
   XFlush(TheDisplay) ;
}


int Copy_Buffer_And_Flush_X()
{
   Copy_Buffer_X() ;

   XFlush(TheDisplay) ;
}



int Send_Expose_Event()
{
  XExposeEvent e ;

  //  XEvent e ;
  // doesn't look like you have to actually fill in any
  // of the subfields of e

  e.type = Expose ;
  //e.serial
  e.send_event = 1 ;
  e.display = TheDisplay ;
  //  e.window = TheWindow ;
  e.window = PointerWindow ;
  //  e.window = InputFocus ;
  //e.x
  //e.y
  //e.width
  //e.height
  e.count = 1 ;

  // XSendEvent (TheDisplay, TheWindow, 0, 0 , (XEvent *)&e) ;
  XSendEvent (TheDisplay, TheWindow, 0, ExposureMask, (XEvent *)&e) ;
  // XSendEvent (TheDisplay, TheWindow, 1, ExposureMask, &e) ;

}



int Handle_Events_X(int *px, int *py)
{
    int DummyInt;
    Window DummyWindow;
    XEvent event;
    int x,y ;
    KeySym keysym ;
    char buffer[10] ;
    int bufsize = 10 ;
    XComposeStatus compose ;
    int ww,hh ;
    int retval ;

    // printf("enter Handle_Events_X\n") ;


 MORE_EVENTS : 

    if ( !(XPending(TheDisplay)) ) {
      retval = -3000 ;
      goto LLL ;
    } 

    XNextEvent(TheDisplay, &event);
      // if the event queue is empty, XNextEvent flushes the
      // output buffer and blocks until an event is received
      // Since we don't want it to block when the queue is empty
      // we check beforehand with XPending to see if there
      // is anything in the queue

    // printf("event.type == %d\n",event.type) ;

    switch(event.type) {


    case Expose:
      // printf("Expose\n") ;

        Copy_Buffer_And_Flush_X() ;
             // this is new ... when the window is uncovered
	     // this will regenerate it from the buffer

	*px = 0 ; *py = 0 ;

        retval = -1 ; 
        goto LLL ;
	break;	


    case MotionNotify:
      // printf("MotionNotify\n") ;
        // while this gives coords relative to the upper left
        // of the window being displayed...so, for example,
        // suppose we target mouse movement around the center
        // of the window that is being displayed.  this will give
        // a certain (x,y). suppose we drag the window and 
        // then again target mouse movement near the center of
        // the moved window.  this will give the same (x,y).

	x = event.xmotion.x ;
	y = event.xmotion.y ;
	// this will also give "correct" values if the motion
	// of the mouse carries it off the window

        y = The_Pix_height-1 - y ;

	if(event.xmotion.state & Button3Mask) {
	    *px = x ;	    *py = y ;
	} else 
	if(event.xmotion.state & Button1Mask) {
	    *px = x ;	    *py = y ;
	} else {
	    goto MORE_EVENTS;
	}

        retval = -2 ; 
        goto LLL ;
	break;


    case ButtonPress:
      // printf("ButtonPress\n") ;
        // while this gives coords relative to the upper left
        // of the window being displayed...so, for example,
        // suppose we click the mouse at the center
        // of the window that is being displayed.  this will give
        // a certain (x,y). suppose we drag the window and 
        // then again click the mouse at the center of
        // the moved window.  this will give the same (x,y).
        x = event.xbutton.x ;
        y = event.xbutton.y ;
        y = The_Win_height-1 - y ;
        *px = x ; *py = y ;

        retval = -3 ; 
        goto LLL ;
	break;



    case ConfigureNotify:
      // printf("ConfigureNotify\n") ;
        // check for window resizing

	ww = event.xconfigure.width;
	hh = event.xconfigure.height;

        // motion or resizing ?
	if((ww == The_Win_width) && (hh == The_Win_height)){ break; }


        // if get here, then resizing

	// new if stmnt
        if ((ww > The_Pix_width)||
            (hh > The_Pix_height)) {

	  // at least one of the dimensions of the new window
	  // is larger than the current pixmap
  // printf("at least one dimension of new win is larger than pixmaxp\n") ;

	  // create a tmp pixmap and copy current pixmap to it
          The_Tmp_width = The_Pix_width ;
          The_Tmp_height = The_Pix_height ;
	  TheTmpPixmap = XCreatePixmap(TheDisplay, TheRootWindow,
                                    The_Tmp_width, The_Tmp_height, TheDepth);
          TheTmpContext = XCreateGC(TheDisplay, TheTmpPixmap, 0, 0);

          XCopyArea(TheDisplay, ThePixmap, TheTmpPixmap, TheTmpContext,
		    0, 0,
                    The_Pix_width, The_Pix_height,
                    0,0) ;



	  // free up the old pixmap
          XFreeGC(TheDisplay, ThePixmapContext);
	  XFreePixmap(TheDisplay, ThePixmap);

	  // construct new pixmap
	  // don't make either dimension smaller
          if (ww > The_Pix_width)  The_Pix_width = ww ;
          if (hh > The_Pix_height) The_Pix_height = hh ;


	  ThePixmap = XCreatePixmap(TheDisplay, TheRootWindow,
                                    The_Pix_width, The_Pix_height, TheDepth);
          ThePixmapContext = XCreateGC(TheDisplay, ThePixmap, 0, 0);



	  // clear it out.
	  // We use the same color as was last used to clear the buffer
	  // but make sure to restore the current color when done clearing.
          XSetForeground(TheDisplay,ThePixmapContext, Last_Clear_Buffer_Pixel) ;
          XFillRectangle(TheDisplay,ThePixmap, ThePixmapContext, 
                                           0, 0, The_Pix_width, The_Pix_height);

          XSetForeground(TheDisplay,ThePixmapContext, Current_Color_Pixel) ;







	  // copy the data back
          int yy ;
          if (The_Pix_height >= The_Tmp_height) {

            yy = The_Pix_height - The_Tmp_height ;

            XCopyArea(TheDisplay, TheTmpPixmap, ThePixmap, ThePixmapContext,
	              0,0,
                      The_Tmp_width, The_Tmp_height,
                      0,yy) ;
	  } else {

            yy = The_Pix_height - The_Tmp_height ;

            XCopyArea(TheDisplay, TheTmpPixmap, ThePixmap, ThePixmapContext,
	              0,-yy,
                      The_Tmp_width, The_Tmp_height,
                      0,0) ;
	  }



	  ////////////////////////////////////
          TheDrawable = ThePixmap;

          XSetFont(TheDisplay, ThePixmapContext, TheFontInfo->fid) ;
	}


	// XClearWindow(TheDisplay, TheWindow);

        The_Win_width = ww ;
        The_Win_height = hh ;

	*px = The_Win_width ; *py = The_Win_height ;

        retval = -4 ; 
        goto LLL ;
	break;		


    case KeyPress:
      // printf("KeyPress\n") ;
        XLookupString (&(event.xkey), buffer, bufsize, &keysym, &compose) ;
	*px = 0 ; *py = 0 ;

        retval = keysym ;
        goto LLL ;
	break;


    default:
      // printf("default\n") ;
	*px = 0 ; *py = 0 ;

        retval = -1000 ;
        goto LLL ;
	break;

    }



    // printf("none of the above\n") ;
    *px = 0 ; *py = 0 ;
    retval = -2000 ;
    goto LLL ;
    // This actually does happen
    //e.g when you move the window.
    // I think the reason the default doesn't pick
    // that case up is that such an action isn't
    // placed on the display event queue because
    // of the way Init_X has set things up with
    // XSelectInput(...



 LLL : ;

    // printf("exit Handle_Events_X\n") ;
    return retval ;
}







int Get_Events_X (int *d)
// d needs to point to 2 or more ints
// merely repackages Handle_Events_X
{
  int s,x,y ;

  s = Handle_Events_X (&x,&y) ;
  d[0] = x ; 
  d[1] = y ;
  return s ;
}


int Get_Events_DX (double *d)
// d needs to point to 2 or more doubles
// merely repackages Handle_Events_X
{
  int s,x,y ;

  s = Handle_Events_X (&x,&y) ;
  d[0] = x ; 
  d[1] = y ;
  return s ;
}



////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////







int Point_X (double Dx, double Dy) 
{
  int x,y ;
  x = (int)Dx ; 
  y = (int)Dy ;

    XDrawPoint(TheDisplay, TheDrawable, ThePixmapContext, 
               x, The_Pix_height - 1 - y) ;
}




int Safe_Point_X (double Dx, double Dy)
{
  int x = (int)Dx ;
  int y = (int)Dy ;

    if ((x < 0) || (y < 0) || (x >= The_Pix_width) || (y >= The_Pix_height)) {return 0 ;}
    XDrawPoint(TheDisplay, TheDrawable, ThePixmapContext,
               x,  The_Pix_height - 1 - y) ;
    return 1 ;
}





int Line_X (double Dxs, double Dys, double Dxe, double Dye)
{
  int xs = (int)Dxs ;
  int ys = (int)Dys ;
  int xe = (int)Dxe ;
  int ye = (int)Dye ;


    XDrawLine (TheDisplay, TheDrawable, ThePixmapContext,
               xs, The_Pix_height-1-ys,
               xe, The_Pix_height-1-ye);
}






int Safe_Line_X (double Dxs, double Dys, double Dxe, double Dye)
{
  int ixs = (int)Dxs ;
  int iys = (int)Dys ;
  int ixe = (int)Dxe ;
  int iye = (int)Dye ;

  double xs, ys, xe, ye ; // doubles for accuracy in clipping 
  double t, xedge, yedge ;


  if (  (ixs >= 0 ) && (ixs < The_Pix_width)  
     && (ixe >= 0 ) && (ixe < The_Pix_width)  
     && (iys >= 0 ) && (iys < The_Pix_height)  
     && (iye >= 0 ) && (iye < The_Pix_height)  ) {

    XDrawLine (TheDisplay, TheDrawable, ThePixmapContext,
               ixs, The_Pix_height-1-iys,
               ixe, The_Pix_height-1-iye );

    return 1 ;

  }



  xs = ixs ; ys = iys ; xe = ixe ; ye = iye ;

// start to end 
// in       in      leave line alone...draw it all 
// in      out      replace end 
// out      in      replace start 
// out     out      don't draw the line 


// clip against all 4 sides of screen 



// first clip against y = 0 

 yedge = 0 ;
 if (ys >= yedge) {
     if (ye >= yedge) {
         // start is in, end is in , leave alone...next test 
     }
     else {
         // start is in, end is out, replace end...next test 
         t = (yedge - ys)/(ye - ys) ; 
             // ye cannot be ys .. no div by 0 worry 
         xe = xs + t*(xe - xs) ;
         ye = yedge ;
     }
 } else {
     if (ye >= yedge) {
         //start is out, end is in, replace start...next test 
         t = (yedge - ys)/(ye - ys) ; 
             // ye cannot be ys .. no div by 0 worry 
         xs = xs + t*(xe - xs) ;
         ys = yedge ;

     }
     else {
         // both are out...don't draw line at all 
         goto CLend ;
     }
 }

// second, clip against y = The_Pix_height - 1 

 yedge = The_Pix_height - 1 ;
 if (ys <= yedge) {
     if (ye <= yedge) {
         // start is in, end is in , leave alone...next test 
     }
     else {
         // start is in, end is out, replace end...next test 
         t = (yedge - ys)/(ye - ys) ; 
             // ye cannot be ys .. no div by 0 worry 
         xe = xs + t*(xe - xs) ;
         ye = yedge ;
     }
 } else {
     if (ye <= yedge) {
         //start is out, end is in, replace start...next test 
         t = (yedge - ys)/(ye - ys) ; 
             // ye cannot be ys .. no div by 0 worry 
         xs = xs + t*(xe - xs) ;
         ys = yedge ;

     }
     else {
         // both are out...don't draw line at all 
         goto CLend ;
     }
 }


// third, clip against x = 0 

 xedge = 0 ;
 if (xs >= xedge) {
     if (xe >= xedge) {
         // start is in, end is in , leave alone...next test 
     }
     else {
         // start is in, end is out, replace end...next test 
         t = (xedge - xs)/(xe - xs) ; 
             // xe cannot be xs .. no div by 0 worry 
         ye = ys + t*(ye - ys) ;
         xe = xedge ;
     }
 } else {
     if (xe >= xedge) {
         //start is out, end is in, replace start...next test 
         t = (xedge - xs)/(xe - xs) ; 
             // xe cannot be xs .. no div by 0 worry 
         ys = ys + t*(ye - ys) ;
         xs = xedge ;

     }
     else {
         // both are out...don't draw line at all 
         goto CLend ;
     }
 }

// finally, clip against x = The_Pix_width - 1 

 xedge = The_Pix_width - 1 ;
 if (xs <= xedge) {
     if (xe <= xedge) {
         // start is in, end is in , leave alone...next test 
     }
     else {
         // start is in, end is out, replace end...next test 
         t = (xedge - xs)/(xe - xs) ; 
             // xe cannot be xs .. no div by 0 worry 
         ye = ys + t*(ye - ys) ;
         xe = xedge ;
     }
 } else {
     if (xe <= xedge) {
         //start is out, end is in, replace start...next test 
         t = (xedge - xs)/(xe - xs) ; 
             // xe cannot be xs .. no div by 0 worry 
         ys = ys + t*(ye - ys) ;
         xs = xedge ;

     }
     else {
         // both are out...don't draw line at all 
         goto CLend ;
     }
 }


    XDrawLine (TheDisplay, TheDrawable, ThePixmapContext,
               (int)xs, (int)(The_Pix_height-1-ys),
               (int)xe, (int)(The_Pix_height-1-ye) );


 CLend : 

    return 1 ;

}





int Rectangle_X (double Dxlow, double Dylow, double Dwidth, double Dheight) 
{

  int xlow = (int)Dxlow ;
  int ylow = (int)Dylow ;
  int width = (int)Dwidth ;
  int height = (int)Dheight ; 

  /*
    XDrawRectangle(TheDisplay, TheDrawable, ThePixmapContext,
                   xlow,  The_Pix_height-1-ylow-height,
                   width,height);
  */
  // interesting that this bug could have been around for so long


    XDrawRectangle(TheDisplay, TheDrawable, ThePixmapContext,
                   xlow,  The_Pix_height - ylow - height,
                   width,height);
}




int Fill_Rectangle_X (double Dxlow, double Dylow, double Dwidth, double Dheight) 
{
  int xlow = (int)Dxlow ;
  int ylow = (int)Dylow ;
  int width = (int)Dwidth ;
  int height = (int)Dheight ; 

  /*
    XFillRectangle(TheDisplay, TheDrawable, ThePixmapContext,
                   xlow, The_Pix_height-1-ylow-height,
                   width, height);
  */

    XFillRectangle(TheDisplay, TheDrawable, ThePixmapContext,
                   xlow, The_Pix_height - ylow - height,
                   width, height);
}



int Triangle_X (double Dx1, double Dy1, 
                double Dx2, double Dy2,
                double Dx3, double Dy3)
{
  int x1 = (int)Dx1 ;
  int y1 = (int)Dy1 ;
  int x2 = (int)Dx2 ;
  int y2 = (int)Dy2 ;
  int x3 = (int)Dx3 ;
  int y3 = (int)Dy3 ;

  XPoint Points[4];

  // you DO want the height-1  here though

  Points[0].x = (x1);
  Points[0].y = (The_Pix_height-1-y1);
  Points[1].x = (x2);
  Points[1].y = (The_Pix_height-1-y2);
  Points[2].x = (x3);
  Points[2].y = (The_Pix_height-1-y3);
  Points[3].x = Points[0].x;
  Points[3].y = Points[0].y;

  XDrawLines(TheDisplay, TheDrawable,ThePixmapContext,
                               Points, 4, CoordModeOrigin);
}





int Fill_Triangle_X (double Dx1, double Dy1, 
                     double Dx2, double Dy2,
                     double Dx3, double Dy3)
{
  int x1 = (int)Dx1 ;
  int y1 = (int)Dy1 ;
  int x2 = (int)Dx2 ;
  int y2 = (int)Dy2 ;
  int x3 = (int)Dx3 ;
  int y3 = (int)Dy3 ;

  XPoint Points[3];

  Points[0].x = (x1);
  Points[0].y = (The_Pix_height-1-y1);
  Points[1].x = (x2);
  Points[1].y = (The_Pix_height-1-y2);
  Points[2].x = (x3);
  Points[2].y = (The_Pix_height-1-y3);


  XFillPolygon(TheDisplay, TheDrawable, ThePixmapContext,
                Points, 3, Convex, CoordModeOrigin);
}





int Polygon_X (int *x, int *y, int npts)
{
   XPoint xpoint[1000] ;
   int k ;

   if (npts <= 0) return 0 ;

   if (npts > 1000) {
      printf("\nPolygon+X has been asked to deal with %d points.\n",
             npts) ;
      printf("Points past first 1000 ignored.\n") ;
      npts = 1000 ;
   }

   for (k = 0 ; k < npts ; k++) {
        xpoint[k].x = x[k] ; 
        xpoint[k].y = The_Pix_height -1 - y[k] ;
   }

   XDrawLines(TheDisplay,TheDrawable,ThePixmapContext,
                       xpoint,npts,  CoordModeOrigin);
   XDrawLine(TheDisplay,TheDrawable,ThePixmapContext,
                    xpoint[0].x, xpoint[0].y,
                         xpoint[npts-1].x, xpoint[npts-1].y ) ;

   return 1 ;
}



int Polygon_DX (double *x, double *y, double Dnpts)
{
  int npts = (int)Dnpts ;
   XPoint xpoint[1000] ;
   int k ;

   if (npts <= 0) return 0 ;

   if (npts > 1000) {
      printf("\nPolygon+X has been asked to deal with %d points.\n",
             npts) ;
      printf("Points past first 1000 ignored.\n") ;
      npts = 1000 ;
   }

   for (k = 0 ; k < npts ; k++) {
        xpoint[k].x = (int)x[k] ;
        xpoint[k].y = (int)(The_Pix_height -1 - y[k]) ;
   }

   XDrawLines(TheDisplay,TheDrawable,ThePixmapContext,
                       xpoint,npts,  CoordModeOrigin);
   XDrawLine(TheDisplay,TheDrawable,ThePixmapContext,
                    xpoint[0].x, xpoint[0].y,
                         xpoint[npts-1].x, xpoint[npts-1].y ) ;

   return 1 ;
}



int Fill_Polygon_X (int *x, int *y, int npts)
{
   XPoint xpoint[1000] ;
   int k ;

   if (npts <= 0) return 0 ;

   if (npts > 1000) {
      printf("\nFill_Polygon_X has been asked to deal with %d points.\n",
             npts) ;
      printf("Points past first 1000 ignored.\n") ;
      npts = 1000 ;
   }

   for (k = 0 ; k < npts ; k++) {
        xpoint[k].x = x[k] ; 
        xpoint[k].y = The_Pix_height -1 - y[k] ;
   }


   XFillPolygon(TheDisplay,TheDrawable,ThePixmapContext,
                xpoint,npts,Nonconvex,CoordModeOrigin);   

   return 1 ;

}



int Fill_Polygon_DX (double *x, double *y, double Dnpts)
{
  int npts = (int)Dnpts ;
   XPoint xpoint[1000] ;
   int k ;

   if (npts <= 0) return 0 ;

   if (npts > 1000) {
      printf("\nFill_Polygon_X has been asked to deal with %d points.\n",
             npts) ;
      printf("Points past first 1000 ignored.\n") ;
      npts = 1000 ;
   }

   for (k = 0 ; k < npts ; k++) {
        xpoint[k].x = (int)x[k] ; 
        xpoint[k].y = (int)(The_Pix_height -1 - y[k]) ;
   }


   XFillPolygon(TheDisplay,TheDrawable,ThePixmapContext,
                xpoint,npts,Nonconvex,CoordModeOrigin);   


   return 1 ;
}




int Horizontal_Single_Pixel_Line_X (double Dx0, double Dx1, double Dy)
{
  int x0 = (int)Dx0 ;
  int x1 = (int)Dx1 ;
  int y = (int)Dy ;

   int t,x ;
   int j,n ;

   // protect against an offscreen line
   if (y < 0) return 0 ;
   if (y >= The_Pix_height) return 0 ;

   if (x0 < 0) x0 = 0 ;
   else if (x0 >= The_Pix_width) x0 = (The_Pix_width - 1) ;
   if (x1 < 0) x1 = 0 ;
   else if (x1 >= The_Pix_width)  x1 = (The_Pix_width - 1) ;
   // end protection code


   if (x1 < x0) { t = x1 ; x1 = x0 ; x0 = t ; }

   //   for (x = x0 ; x <= x1 ; x++) { Point(x,y) ;   }
   Line_X (x0,y, x1,y) ;

   return 1 ;
} 






int Circle_X (double Da, double Db, double Dr)
{
 int a = (int)Da ;
 int b = (int)Db ;
 int r = (int)Dr ;

 int x,y,e,e1,e2 ;

 x = r ;
 y = 0 ;
 e = 0;

 while (x >= y) {

       Safe_Point_X( a+x,b+y) ;   Safe_Point_X( a-x,b+y) ;
       Safe_Point_X( a+x,b-y) ;   Safe_Point_X( a-x,b-y) ;

       Safe_Point_X( a+y,b+x) ;   Safe_Point_X( a-y,b+x) ;
       Safe_Point_X( a+y,b-x) ;   Safe_Point_X( a-y,b-x) ;

       e1 =  e + y + y + 1 ;
       e2 = e1 - x - x + 1 ;
       y  =  y + 1 ;

       if ( abs(e2) < abs(e1) ) {
              x = x - 1 ;
              e = e2 ;
       } else e = e1 ;

     } 

} 







int Fill_Circle_X (double Da, double Db, double Dr)
{
 int a = (int)Da ;
 int b = (int)Db ;
 int r = (int)Dr ;

 int x,y,e,e1,e2 ;

 x = r ;
 y = 0 ;
 e = 0;

 while (x >= y) {

       Horizontal_Single_Pixel_Line_X (a-x, a+x, b+y) ;
       Horizontal_Single_Pixel_Line_X (a-x, a+x, b-y) ;

       Horizontal_Single_Pixel_Line_X (a-y, a+y, b+x) ;
       Horizontal_Single_Pixel_Line_X (a-y, a+y, b-x) ;

       e1 =  e + y + y + 1 ;
       e2 = e1 - x - x + 1 ;
       y  =  y + 1 ;

       if ( abs(e2) < abs(e1) ) {
              x = x - 1 ;
              e = e2 ;
       } else e = e1 ;

     } 

} 





int Font_Pixel_Height_X ()
// Returns the height of the font in pixels. 
{
     return TheFontInfo->max_bounds.ascent + TheFontInfo->max_bounds.descent;
}



// the void * delcarations below allow for the passing of
// arrays of characters (usual usage) but also, for instance,
// an array of doubles that is composed of packed characters


int String_Pixel_Width_X (const void *s)
// Returns the length, in pixels, of the string s 
{
     int len;

     len = strlen((char *)s);

     return XTextWidth(TheFontInfo, (char *)s, len);
}





int Draw_String_X (const void *s, double Dx, double Dy)
// Draw the string s, with the lower left hand corner at (x,y)
{
  int x = (int)Dx ;
  int y = (int)Dy ;

     int len;

     len = strlen((const char *)s);

     XDrawString(TheDisplay,TheDrawable,ThePixmapContext,
                                         x,The_Pix_height-1-y,
                                         (char *)s, len);
}




int Get_Current_Dimensions_X (int dimensions[2])
{
  dimensions[0] = The_Pix_width ;
  dimensions[1] = The_Pix_height ;
}


int Get_Current_Dimensions_DX (double dimensions[2]) 
{
  dimensions[0] = The_Pix_width ;
  dimensions[1] = The_Pix_height ;
}


int Change_Pen_Dimensions_X (double Dw, double Dh)
{
  printf("Change_Pen_Dimensions_X  not implemented\n") ;
  return 0 ;
}



int Draw_Text_X (
               int num_lines_of_text,
               const void *lines_of_text, // an array of pointers
               double startx, 
               double starty,
               double height,
               double x_over_y_ratio,
               double extra_space_between_letters_fraction,
               double extra_space_between_lines_fraction) 
{
  printf("Draw_Text_X  not implemented\n") ;
  return 0 ;
}



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


void fputintB (int x, FILE *fp)
{
   char *p ;
   int c[4],i ;

   p = (char *) &x ;

   for (i = 0 ; i < 4 ; i++) {
        c[i] = *p ;
        p++ ;
   }

   for (i = 3 ; i >= 0 ; i--) {
        fputc(c[i], fp) ;
   }

}




int fgetintB (FILE *fp)
{
   char *p ;
   int c[4],i ;
   int x ;
   char q ;

   for (i = 3 ; i >= 0 ; i--) {
        c[i] = fgetc(fp) ;
   }



   p = (char *) &x ;

   for (i = 0 ; i < 4 ; i++) {
        q = c[i] ;
        *p = q ;;
        p++ ;
   }

   return x ;
}







void  XImage_To_XWD_File (XImage *pxim,  FILE *fp)
{
  // assumes full color but uses full 32 bits per pixel
 int header_size, file_version, format, depth ;
 int xoffset, byte_order, bitmap_unit, bitmap_order, bitmap_pad ;
 int bits_per_pixel, bytes_per_line, visual_class ;
 int redmask, greenmask, bluemask ;
 int bitsperrgb, numentriesincolormap, numcolorstructures ;
 int windowwidth, windowheight, windowx, windowy, windowborderwidth ;
 int numbytestowrite ;
 int width,height ;

 header_size = 104 ;
 fputintB(header_size,fp) ;

 file_version = 7 ;
 fputintB(file_version,fp) ; 

 format = 2 ; // ZPixmap
 fputintB(format,fp) ;

 depth = 24 ;
 fputintB(depth,fp) ;

 width = pxim->width ;
 fputintB(width,fp) ;

 height = pxim->height ;
 fputintB(height,fp) ;

 xoffset = 0 ;
 fputintB(xoffset,fp) ;

 byte_order = 0 ;
 fputintB(byte_order,fp) ;

 bitmap_unit = 32 ;
 fputintB(bitmap_unit,fp) ;

 bitmap_order = 0 ;
 fputintB(bitmap_order,fp) ;

 bitmap_pad = 32  ;
 fputintB(bitmap_pad,fp) ;

 bits_per_pixel = 32 ;
 fputintB(bits_per_pixel,fp) ;

 bytes_per_line = width * 4 ;
 fputintB(bytes_per_line,fp) ;

 visual_class = 5 ; // more than one sample per pixel
 fputintB(visual_class,fp) ;

 redmask = 0x00ff0000 ;
 fputintB(redmask,fp) ;

 greenmask = 0x0000ff00 ;
 fputintB(greenmask,fp) ;

 bluemask = 0x000000ff ;
 fputintB(bluemask,fp) ;

 // bitsperrgb = 8 ; // hard to believe
 bitsperrgb = 24 ; 
 fputintB(bitsperrgb,fp) ;

 numentriesincolormap = 0 ; // not used :
 fputintB(numentriesincolormap,fp) ;

 numcolorstructures = 0 ;
 fputintB(numcolorstructures,fp) ;

 windowwidth = width ;
 fputintB(windowwidth,fp) ;

 windowheight = height ;
 fputintB(windowheight,fp) ;

 windowx = 0 ; // how crucial is this ?
 fputintB(windowx,fp) ;

 windowy = 0 ; // how crucial is this ?
 fputintB(windowy,fp) ;

 windowborderwidth = 0 ;
 fputintB(windowborderwidth,fp) ;


 // null terminated window name fleshed out to multiple of 4 bytes
 fputc('\0',fp) ;
 fputc('\0',fp) ;
 fputc('\0',fp) ;
 fputc('\0',fp) ;


 numbytestowrite =   bytes_per_line * height ;

 fwrite( pxim->data, numbytestowrite, 1, fp) ;

}











void XImage_From_XWD_File (XImage *pxim, FILE *fp)
{
  // assumes full color but uses full 32 bits per pixel

 int header_size, file_version, format, depth ;
 int xoffset, byte_order, bitmap_unit, bitmap_order, bitmap_pad ;
 int bits_per_pixel, bytes_per_line, visual_class ;
 int redmask, greenmask, bluemask ;
 int bitsperrgb, numentriesincolormap, numcolorstructures ;
 int windowwidth, windowheight, windowx, windowy, windowborderwidth ;
 int numbytestowrite ;

 int width,height ;

 int c, numbytestoread ;


 header_size = fgetintB(fp) ;
 file_version = fgetintB(fp) ;
 format = fgetintB(fp) ;
 depth = fgetintB(fp) ;
 width =  fgetintB(fp) ;
 height =  fgetintB(fp) ;
 xoffset = fgetintB(fp) ;
 byte_order = fgetintB(fp) ;
 bitmap_unit = fgetintB(fp) ;
 bitmap_order = fgetintB(fp) ;
 bitmap_pad = fgetintB(fp) ;
 bits_per_pixel = fgetintB(fp) ;
 bytes_per_line = fgetintB(fp) ;
 visual_class = fgetintB(fp) ;
 redmask = fgetintB(fp) ;
 greenmask = fgetintB(fp) ;
 bluemask = fgetintB(fp) ;
 bitsperrgb = fgetintB(fp) ;
 numentriesincolormap = fgetintB(fp) ;
 numcolorstructures = fgetintB(fp) ;
 windowwidth = fgetintB(fp) ;
 windowheight = fgetintB(fp) ;
 windowx = fgetintB(fp) ;
 windowy = fgetintB(fp) ;
 windowborderwidth = fgetintB(fp) ;

 // null terminated window name fleshed out to multiple of 4 bytes
 c = fgetc(fp) ; c = fgetc(fp) ; c = fgetc(fp) ; c = fgetc(fp) ;

 /* ++++++++++++++++++++++++ */
 
 pxim->width = width ;
 pxim->height = height ;
 pxim->depth = depth ;
 pxim->xoffset = xoffset ;
 pxim->format = format ;
 pxim->bitmap_unit = bitmap_unit ;
 pxim->bitmap_pad = bitmap_pad ;
 pxim->bytes_per_line = bytes_per_line ;
 pxim->bits_per_pixel = bits_per_pixel ;
 pxim->byte_order = byte_order ;
 pxim->bitmap_bit_order = bitmap_order ;



 /* on users head to have freed up any previous memory that pxim->data
    might have pointed to...trying to free it up here will cause faults
    if not already pointing to something sane */


 numbytestoread =   pxim->bytes_per_line * pxim->height  ;
 pxim->data = (char *)malloc(numbytestoread) ;
 if (pxim->data == NULL) {
      printf("ERROR: XImage_From_XWD_File : can't malloc space needed\n") ;
      printf("Program terminating\n\n") ;
      exit(1) ;
 }

 fread (pxim->data, numbytestoread, 1, fp) ;

 rewind(fp) ;

}





int Save_Image_To_File_X (const void *filename)
// return 1 if successful else 0
{
  FILE *fp ;
  XImage *pxim ;

  fp = fopen ((char *)filename,"w") ;
  if (fp == NULL) {
    printf("Save_Image_To_File_X cannot open file %s\n",(char *)filename) ;
    return 0 ;
  }

  //  pxim = XGetImage (TheDisplay, TheWindow,0,0, The_Pix_width, The_Pix_height) ;
  pxim = XGetImage (TheDisplay, TheDrawable, 0,0, The_Pix_width, The_Pix_height,
                      AllPlanes, ZPixmap) ;

  XImage_To_XWD_File (pxim,  fp) ;

  XDestroyImage(pxim) ; // lack of this was causing mem leaks when
  // many images were being saved for movies

  fclose(fp) ;

  return 1 ;
}





int Get_Image_From_File_X (const void *filename, double Dx, double Dy)
// Put lower left corner of file into the graphics window at (x,y).
// return 1 if successful else 0
{
  int x = (int)Dx ;
  int y = (int)Dy ;

  FILE *fp ;
  XImage xim[1] ;
  int srcx,srcy,destx,desty ;
  int image_width, image_height ;
  int transfer_width, transfer_height ;

  fp = fopen ((char *)filename,"r") ;
  if (fp == NULL) {
    printf("Get_Image_From_File_X cannot open file %s\n",(char *)filename) ;
    return 0 ;
  }

  XImage_From_XWD_File (&xim[0], fp) ;
  image_width = xim[0].width ;
  image_height = xim[0].height ;
  //  printf("%d %d\n",image_width,image_height) ;

  if (image_height <= The_Pix_height - y) {

    transfer_height = image_height ;
    srcx = 0 ;
    srcy = 0 ;
    destx = x ;
    desty = The_Pix_height - y - image_height ;
    if (image_width <= The_Pix_width - x) { transfer_width = image_width ; }
    else { transfer_width = The_Pix_width - x ;}

  } else {

    transfer_height = The_Pix_height - y ;
    srcx = 0 ;
    srcy = image_height - (The_Pix_height - y) ;
    destx = x ;
    desty = 0 ;
    if (image_width <= The_Pix_width - x) { transfer_width = image_width ; }
    else { transfer_width = The_Pix_width - x ;}

  }


  XPutImage (TheDisplay, TheDrawable, ThePixmapContext, &xim[0],
             srcx, srcy, destx, desty,
             transfer_width, transfer_height) ;
	     //	     The_Pix_width, The_Pix_height) ;


  fclose(fp) ;

  return 1 ;
}




int Get_Image_Dimensions_From_File_X (int d[2], void *filename)
// return 1 if successful else 0
// You do NOT need to have initialized the graphics environment 
// before you call this function
{
 FILE *fp ;

 fp = fopen ((char *)filename,"r") ;
 if (fp == NULL) {
   printf("Get_Image_Dimensions_From_File_X cannot open file %s\n",
                                                     (char *)filename) ;
   return 0 ;
 }

 // assumes full color but uses full 32 bits per pixel
 int header_size, file_version, format, depth ;
 int width,height ;

 header_size = fgetintB(fp) ;
 file_version = fgetintB(fp) ;
 format = fgetintB(fp) ;
 depth = fgetintB(fp) ;
 width =  fgetintB(fp) ;
 height =  fgetintB(fp) ;

 d[0] = width ;
 d[1] = height ;

 fclose(fp) ;

 return 1 ;
}





int Get_Pixel_X (double Dx, double Dy)
// return the 32 bit pixel value...assumes x,y are legal
// i.e. it is NOT safe
{
  int x = (int)Dx ;
  int y = (int)Dy ;

  XImage *pxim ;
  int p ;

  pxim = XGetImage (TheDisplay, TheDrawable, 0,0, The_Pix_width, The_Pix_height,
                      AllPlanes, ZPixmap) ;
  p = XGetPixel(pxim,x, The_Pix_height - 1 - y) ;

  XDestroyImage(pxim) ; // lack of this was causing mem leaks when
  // many images were being saved for movies

  return p ;
}



int Get_Pixel_SAFE_X (double Dx, double Dy, int pixel[1]) 
// return 1 if successful, else 0
{
  int x = (int)Dx ;
  int y = (int)Dy ;
  XImage *pxim ;

  if ((x < 0) || (x >= The_Pix_width) || (y < 0) || (y >= The_Pix_height))
    return 0 ;

  pxim = XGetImage (TheDisplay, TheDrawable, 0,0, The_Pix_width, The_Pix_height,
                      AllPlanes, ZPixmap) ;

  pixel[0] = XGetPixel(pxim,x, The_Pix_height - 1 - y) ;

  XDestroyImage(pxim) ; // lack of this was causing mem leaks when
  // many images were being saved for movies

  return 1 ;
}




/////////////////////////////////////////////////////////////////
// suppose there were just 4 colors, 0,1,2,3
// [0.00, 0.25) -> 0
// [0.25, 0.50) -> 1
// [0.50, 0.75) -> 2
// [0.75, 1.00] -> 3
// 0 -> middle of [0.00, 0.25)
// 1 -> middle of [0.25, 0.50)
// 2 -> middle of [0.50, 0.75)
// 3 -> middle of [0.75, 1.00)



int Set_Color_Rgb_X (int r, int g, int b)
{
  unsigned long int p ;

  if (r < 0) r = 0 ; else if (r > 255) r = 255 ;
  if (g < 0) g = 0 ; else if (g > 255) g = 255 ;
  if (b < 0) b = 0 ; else if (b > 255) b = 255 ;

  p = (r << 16) | (g  << 8) | (b) ;
  XSetForeground(TheDisplay, ThePixmapContext, p) ;

  // new
  Current_Red_Int   = r ;
  Current_Green_Int = g ;
  Current_Blue_Int  = b ;
  Current_Color_Pixel = p ;

}



int Set_Color_Rgb_DX (double dr, double dg, double db)
{
  int r,g,b ;

  if (dr < 0.0) dr = 0.0 ; else if (dr > 1.0) dr = 1.0 ;
  if (dg < 0.0) dg = 0.0 ; else if (dg > 1.0) dg = 1.0 ;
  if (db < 0.0) db = 0.0 ; else if (db > 1.0) db = 1.0 ;

  r = (int)(256*dr) ;
  g = (int)(256*dg) ;
  b = (int)(256*db) ;

  Set_Color_Rgb_X (r,g,b) ;

}




int Convert_Pixel_To_rgbI_X (int pixel, int rgbI[3]) 
// rgbI[] values in 0-255
// return 1 if successful, else 0
{
  rgbI[2] = pixel & 0xff ;
  rgbI[1] = (pixel >> 8) & 0xff ;
  rgbI[0] = (pixel >> 16) & 0xff ;
  return 1 ;
}


int Convert_rgbI_To_rgb_X (int rgbI[3], double rgb[3]) 
// convert rgbI[] in 0-255 to rgb[] in 0.0 - 1.0
// return 1 if successful, else 0
{
  double d ;
  d = 0.5/256.0 ;
  // see above discussion of middle of intervals for purpose of d
  rgb[0] = rgbI[0] / 256.0 + d ;
  rgb[1] = rgbI[1] / 256.0 + d ;
  rgb[2] = rgbI[2] / 256.0 + d ;
}



int XImage_to_Display (XImage *pxim, double Dx, double Dy)
// Put lower left corner of file into the graphics window at (x,y).
// return 1 if successful else 0
{
  int x = (int)Dx ;
  int y = (int)Dy ;

  int image_width, image_height ;
  int srcx,srcy,destx,desty ;
  int transfer_width, transfer_height ;

  image_width = pxim->width ;
  image_height = pxim->height ;
  //  printf("%d %d\n",image_width,image_height) ;

  if (image_height <= The_Pix_height - y) {

    transfer_height = image_height ;
    srcx = 0 ;
    srcy = 0 ;
    destx = x ;
    desty = The_Pix_height - y - image_height ;
    if (image_width <= The_Pix_width - x) { transfer_width = image_width ; }
    else { transfer_width = The_Pix_width - x ;}

  } else {

    transfer_height = The_Pix_height - y ;
    srcx = 0 ;
    srcy = image_height - (The_Pix_height - y) ;
    destx = x ;
    desty = 0 ;
    if (image_width <= The_Pix_width - x) { transfer_width = image_width ; }
    else { transfer_width = The_Pix_width - x ;}

  }


  XPutImage (TheDisplay, TheDrawable, ThePixmapContext, pxim,
             srcx, srcy, destx, desty,
             transfer_width, transfer_height) ;
	     //	     The_Pix_width, The_Pix_height) ;

  return 1 ;
}

