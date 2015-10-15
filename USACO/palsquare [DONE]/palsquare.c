/*
ID: sespiros
PROG: palsquare
LANG: C
*/


#include	<stdio.h>
#include	<math.h>
#include	<stdlib.h>
#include	<string.h>
#define maxsq 100

  void
converter (int base,long int number_to_convert, char ret[100])
{
  char base_digits[20] =
       {'0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J'};

  int converted_number[64];
  int index=0,i;

   /* convert to the indicated base */
  while (number_to_convert != 0)
  {
     converted_number[index] = number_to_convert % base;
     number_to_convert = number_to_convert / base;
     ++index;
  }
   /* now print the result in reverse order */
  --index;  /* back up to last entry in the array */

  for(i=0; index>=0; index--) /* go backward through array */
  {
     ret[i++]= base_digits[converted_number[index]];
  }
  ret[i]='\0';
}		/* -----  end of function converter  ----- */


  int
checker (char con[maxsq])
{
  int fl=0,i;

  if(strlen(con)==1)return 1;
  for(i=0;i<strlen(con)/2;i++){
    if(con[i]==con[strlen(con)-1-i]){
      fl++;
    }
  }
  if(fl==strlen(con)/2){
    return 1;
  }else{
    return 0;
  }
}		/* -----  end of function checker  ----- */

  int
main ( int argc, char *argv[] )
{
  FILE *fin,*fout;
  int n,i,a;
  long int sq;
  char con[maxsq],con2[maxsq];

  fin=fopen("palsquare.in","r");
  fout=fopen("palsquare.out","w");

  fscanf(fin,"%d",&n);

  for(i=1;i<=300;i++){
    sq=pow(i,2);
    converter(n,sq,con);
    converter(n,i,con2);
//    printf("%ld %s\n",i,con);
    a=checker(con);
   if(a)fprintf(fout,"%s %s\n",con2,con);
  }
  fclose(fin);
  fclose(fout);
  return 0;
}				/* ----------  end of function main  ---------- */
