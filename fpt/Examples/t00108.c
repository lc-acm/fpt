
#include <FPT.h>

 
int main()
{
 double s ;
 double suncx,suncy,sunradius ;
 double earthcx,earthcy,earthradius ;
 double mooncx,mooncy,moonradius ;
 double sunTOearth, earthTOmoon ;
 double earth_angle, earth_delta ;
 double moon_angle, moon_delta ;
 double day ;
 char q ;

 s = 800 ;
 G_init_graphics (s+1,s+1) ;

 suncx = 0.5*s ; suncy = 0.5*s ; sunradius = 0.1*s ;
 earthradius = 0.25*sunradius ;      // not astronimically correct 
 moonradius  = 0.4*earthradius ;     // not astronomically correct 
 sunTOearth  = 4.0*sunradius ;       // not astronomically correct 
 earthTOmoon = 3.0*earthradius ;     // not astronomically correct 

 // blank out the right half of the window
 G_rgb (0,0,0) ; // black
 G_fill_rectangle(suncx, 0,  suncx,s) ;
 G_rectangle(0,0, s,s) ;

 G_rgb (1,1,0) ; // yellow
 G_fill_circle (suncx, suncy, sunradius) ; ;

 earth_angle = 0.0 ;
 moon_angle = 0.0 ;

 day = 0.0 ;
 while (day < 2.0*365.0) {
   // run loop for 2 years 

      earthcx = sunTOearth*cos(earth_angle) + suncx ;
      earthcy = sunTOearth*sin(earth_angle) + suncy ;

      mooncx = earthTOmoon*cos(moon_angle) + earthcx ;
      mooncy = earthTOmoon*sin(moon_angle) + earthcy ;

      G_rgb (0,0,1) ; // blue
      G_fill_circle (earthcx, earthcy, earthradius) ;
      G_rgb (0.5, 0.5, 0.5) ; // grey
      G_fill_circle (mooncx, mooncy, moonradius) ;      

      //      flushgraphics() ;
      //      q = G_wait_key() ;
      G_display_image() ;
      usleep(2000) ;

      // erase the earth and the moon
      G_rgb (0,0,0) ; // black
      G_fill_circle (earthcx, earthcy, earthradius) ;
      G_fill_circle (mooncx, mooncy, moonradius) ;

      day = day + 1.0 ;
      earth_angle = earth_angle + 2.0*M_PI/365.0 ;
      moon_angle  = moon_angle  + 2.0*M_PI/28.0 ;
 }

 // outputstring("Strike a key in the graphics window to continue\n") ;
 q = G_wait_key() ;

}




