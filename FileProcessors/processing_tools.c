
#include <stdio.h>
#include <stdlib.h>



int make_double_indices_legal(FILE *fin, FILE *fout)
// process a "C" program, looking for all non-comment
// occurrences of [...] and replace them with 
//   [(int)(  ...  ) + 0.5]

// test cases should include things like
// var[x+3]
// var[x][y-7]
// var[[a+b]], although this wouldn't actually be a legal item in "C"
{
  int c ;
  int q, err ;
  int prevc ;
  int inside_a_string ;
  int inside_C_comment ;
  int inside_Cpp_comment ;


  inside_C_comment = 0 ;
  inside_Cpp_comment = 0 ;
  inside_a_string = 0 ; // no, we are not yet inside a string

  prevc = 0 ;
  c = fgetc(fin) ;

  while (c != EOF) {


    if (inside_C_comment == 1) {

         if ( (prevc == '*') && (c == '/') ) { inside_C_comment = 0 ; }
         fputc(c,fout) ;

    } else if (inside_Cpp_comment == 1) {

         if ( (prevc != '\\') && (c == '\n') ) { inside_Cpp_comment = 0 ; }
         fputc(c,fout) ;

    } else if (inside_a_string == 1) {

         if (c == '"') { inside_a_string = 0 ; }
         fputc(c,fout) ;

    } else if ((prevc == '/') && (c == '*')) {

         inside_C_comment = 1 ;
         fputc(c,fout) ;
         c = 0 ; // this eliminates the possibility that
        	 // the next pair might be */
	         // it turns out that /*/ is NOT a legit comment

    } else if ((prevc == '/') && (c == '/')) {

         inside_Cpp_comment = 1 ;
         fputc(c,fout) ;


    } else if (c == '"') {

         inside_a_string = 1 ;
         fputc(c,fout) ;


    } else if (c == '[') {

       fputc('[',fout) ;
       fputc('(',fout) ;
       fputc('i',fout) ;
       fputc('n',fout) ;
       fputc('t',fout) ;
       fputc(')',fout) ;
       fputc('(',fout) ;
       fputc('(',fout) ;

    } else if (c == ']') {

       fputc(')',fout) ;
       fputc('+',fout) ;
       fputc('0',fout) ;
       fputc('.',fout) ;
       fputc('5',fout) ;
       fputc(')',fout) ;
       fputc(']',fout) ;

    } else {

       fputc(c,fout) ;

    }





    prevc = c ;    
    c = fgetc(fin) ;
  }


}








int before_and_after (FILE *fin, FILE *fout,
                      char *before,  char *after)
{
  int i ;
  int c ;


  // copy the before string into the outputs stream
  i = 0 ;
  while (before[i] != 0) {
    c = before[i] ;
    fputc(c,fout) ;
    i++ ;
  }



  // copy the file into the output stream
  c = fgetc(fin) ;
  while (c != EOF) {

    fputc(c,fout) ;
    c = fgetc(fin) ;
  }





  // copy the after string into the outputs stream
  i = 0 ;
  while (after[i] != 0) {
    c = after[i] ;
    fputc(c,fout) ;
    i++ ;
  }

}








int convert_int_constants_to_doubles(FILE *fin, FILE *fout)
// process a "C" program, looking for all integer constants
// and appends a ".0"  to it

// test cases should include things like
// x+3  =>  x+3.0
// -3*x =>  -3.0*x
// a-23 + 4.5  =>  a-23.0 + 4.5  
// a75 -23 + 4.5  =>  a75 -23.0 + 4.5 
// double x[10] => double x[10.0]   (this will be ok with other processing)

{
  int c ;
  int q, err ;
  int prevc ;
  int inside_a_string ;
  int inside_a_character_constant ;
  int inside_C_comment ;
  int inside_Cpp_comment ;
  int inside_a_number ; 
  int inside_a_name ;
  int e_seen ;
  int period_seen ;


  inside_C_comment = 0 ;
  inside_Cpp_comment = 0 ;
  inside_a_string = 0 ; // no, we are not yet inside a string
  inside_a_character_constant = 0 ;
  inside_a_number = 0 ;
  inside_a_name = 0 ;
  e_seen = 0 ;
  period_seen = 0 ;

  prevc = 0 ;
  c = fgetc(fin) ;

  while (c != EOF) {


    if (inside_C_comment == 1) {

         if ( (prevc == '*') && (c == '/') ) { inside_C_comment = 0 ; }
         fputc(c,fout) ;

    } else if (inside_Cpp_comment == 1) {

         if ( (prevc != '\\') && (c == '\n') ) { inside_Cpp_comment = 0 ; }
         fputc(c,fout) ;

    } else if (inside_a_string == 1) {

         if (c == '"') { inside_a_string = 0 ; }
         fputc(c,fout) ;

    } else if (inside_a_character_constant == 1) {

         if (c == '\'') { inside_a_character_constant = 0 ; }
         fputc(c,fout) ;






    } else if ((prevc == '/') && (c == '*')) {

         inside_C_comment = 1 ;
         fputc(c,fout) ;
         c = 0 ; // this eliminates the possibility that
        	 // the next pair might be */
	         // it turns out that /*/ is NOT a legit comment

    } else if ((prevc == '/') && (c == '/')) {

         inside_Cpp_comment = 1 ;
         fputc(c,fout) ;


    } else if (c == '"') {

         inside_a_string = 1 ;
         fputc(c,fout) ;

    } else if (c == '\'') {

         inside_a_character_constant = 1 ;
         fputc(c,fout) ;





    } else if ((!inside_a_number) && (!inside_a_name) && isalpha(c)) {

         // we know we are starting a name
         inside_a_name = 1 ;
         fputc(c,fout) ;

    } else if (inside_a_name && (! isalnum(c))) {

         // we know we are ending a name
         inside_a_name = 0 ;
         fputc(c,fout) ;



    } else if ((!inside_a_number) && (!inside_a_name) &&
                isdigit(c) && (prevc != '.')) {

         // we know we are starting an int
         inside_a_number = 1 ;
         period_seen = 0 ;
         e_seen = 0 ;
         fputc(c,fout) ;


    } else if (inside_a_number) {

      if (isdigit(c)) {
         fputc(c,fout) ;
      } else if ((c == 'e') || (c == 'E')) {
         e_seen = 1 ;
         fputc(c,fout) ;
      } else if (c == '.') {
         period_seen = 1 ;
         fputc(c,fout) ;
      } else if (   ((prevc == 'e') || (prevc == 'E')) &&
		    ((c == '+') || (c == '-')) ) {
         fputc(c,fout) ;
      } else {

	if (( ! e_seen) && (! period_seen)) {
	   fputc('.',fout) ;
	   fputc('0',fout) ;
	}
        fputc(c,fout) ;
        inside_a_number = 0 ;
      }


    } else {

       fputc(c,fout) ;

    }





    prevc = c ;    
    c = fgetc(fin) ;
  }


}

