/*
ID: sespiros
PROG: dualpal
LANG: C
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#define max 100

  void
converter (int base,long int number_to_convert, char ret[100])
{
  char base_digits[20] =
          {'0', '1', '2', '3', '4', '5', '6', '7',
           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J'};
  int converted_number[64];
  int index=0,i;

  /*convert to the indicated base */
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
}   /* -----  end of function converter  ----- */

  int
checker (char con[max])
{
  int fl=0,i,c=0;

  if(strlen(con)==1)return 1;
  for(i=0;i<strlen(con)/2;i++){
    if(con[i]==con[strlen(con)-1-i]){
      if(con[i]==0 && c==0){
        fl--;
      }else{
        c=1;
      }
      fl++;
    }
  }
  if(fl==strlen(con)/2){
    return 1;
  }else{
    return 0;
  }
}   /* -----  end of function checker  ----- */


  int
main ( int argc, char *argv[] )
{
  FILE *fin,*fout;
  int fl,i, n, s, pl=0, base,two=0;
  char con[max];

  fin=fopen("dualpal.in","r");
  fout=fopen("dualpal.out","w");

  fscanf(fin,"%d",&n);
  fscanf(fin,"%d",&s);

  for(i=s+1;pl<n;i++){
    two=0;
    for(base=2;base<=10;base++){
      converter(base,i,con);
      fl=checker(con);
      if(fl)two++;
    }
    if(two>=2){
      fprintf(fout,"%d\n",i);
      pl++;
    }
  }

  fclose(fin);
  fclose(fout);

  return 0;
}				/* ----------  end of function main  ---------- */
