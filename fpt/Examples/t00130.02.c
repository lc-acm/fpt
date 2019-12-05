
#include <FPT.h>


int main()
{
  //  analog clock using double buffering...simpler
  double hours,minutes,seconds,x,y,nx,ny,theta,digit ;
  double hx,hy,mx,my,sx,sy,angle ;
  double oldhourtheta,oldminutetheta,oldsecondtheta ;
  char text[3] ;
  double hms[3] ;
 
  G_init_graphics (600,600) ;

  while (0 < 1) {

    // blank the window
    G_rgb(1,1,1) ;
    G_fill_rectangle(0,0, 600,600) ;

    // outer circle of the clock face 
    theta = 0 ; // degrees 
    x = 225*cos(theta*M_PI/180) + 300 ;
    y = 225*sin(theta*M_PI/180) + 300 ;
    G_rgb (1,0,0) ; //red
    while (theta <= 360) {
        theta = theta + 1 ;
        nx = 225*cos(theta*M_PI/180) + 300 ;
        ny = 225*sin(theta*M_PI/180) + 300 ;
        G_line(x,y,nx,ny) ;
        x = nx ;
        y = ny ;
    }


    // digits on the clock face 
    G_rgb (0,0,0) ; //black
    theta = 90 ; // degrees 
    digit = 0 ;
    while (theta > -270) {
        theta = theta - 30 ;
        digit = digit + 1 ;
        nx = 200*cos(theta*M_PI/180) + 300 ;
        ny = 200*sin(theta*M_PI/180) + 300 ;
        if (digit >= 10) { 
                   text[0] = '1' ;
                   text[1] = '0' + digit - 10 ;
                   text[2] = '\0' ;
		 }
        else {
                   text[0] = '0' + digit ;
                   text[1] = '\0' ;
		 }
        G_draw_string(text,nx-5,ny-5) ;
    }

    get_timeD (hms) ;
    hours   = hms[0] ;
    minutes = hms[1] ;
    seconds = hms[2] ;

    G_rgb (1,0,0) ; //red

    // set the second hand 
    theta = 90 - 6*seconds  ;
    angle = theta*M_PI/180 ;
    sx = 175*cos(angle) + 300 ;
    sy = 175*sin(angle) + 300 ;
    G_line(300,300,sx,sy) ;

    // set the minute hand 
    theta = 90 - 6*(minutes + seconds/60.0)  ;
    angle = theta*M_PI/180 ;
    mx = 140*cos(angle) + 300 ;
    my = 140*sin(angle) + 300 ;
    G_line(300,300,mx,my) ;

    // set the hour hand 
    theta = 90 - 30*(hours + minutes/60.0 + seconds/3600.0)  ;
    angle = theta*M_PI/180 ;
    hx = 75*cos(angle) + 300 ;
    hy = 75*sin(angle) + 300 ;
    G_line(300,300,hx,hy) ;

    G_display_image() ;

 } // end while (0 < 1) 

}

