
#include <stdio.h>
#include <stdlib.h>




int main(int argc, char **argv)
{
  FILE *fin, *fout ;

 
  if (argc != 3) {
    printf("Usage : pgm   input_C_file   output_C_file_name\n") ;
    exit(0) ;
  }


  fin = fopen (argv[1],"r") ;
  if (fin == NULL) {
    printf("can't open file %s\n",argv[1]) ;
    exit(0) ;
  }


  fout = fopen (argv[2],"w") ;
  if (fout == NULL) {
    printf("can't open file %s\n",argv[2]) ;
    exit(0) ;
  }

  make_double_indices_legal(fin, fout) ;
}



