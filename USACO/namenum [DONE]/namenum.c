/*
ID: sespiros
PROG: namenum
LANG: C
*/


#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#define N 8
#define max 14


FILE *fin,*fout;
char s[max];
int c=0,i[max],n[max],pl=0;
char a[N][3]={{'A','B','C'},{'D','E','F'},{'G','H','I'},{'J','K','L'},{'M','N','O'},{'P','R','S'},{'T','U','V'},{'W','X','Y'}};

  int
main ( int argc, char *argv[] )
{
  FILE *dict;
  int i=0,j=0,len,fl=0;
  char temp[max];

  fin=fopen("namenum.in","r");
  fout=fopen("namenum.out","w");
  dict=fopen("dict.txt","r");

  while((n[c++]=fgetc(fin))!=EOF){
    if(n[c-1]==10){
      n[c-1]='\0';
    }else{
    n[c-1]-='0';
    }
  }
  c-=2;
  for(i=0;i<4616;i++){
    fgets(temp,max,dict);
    len=(int)strlen(temp);
    if(c==len-1){
      temp[c+1]='\0';
      for(j=0;j<c && (temp[j]==a[n[j]-2][0] || temp[j]==a[n[j]-2][1] || temp[j]==a[n[j]-2][2]);j++){
      }
      if(j==c){
        fprintf(fout,"%s",temp);
        fl++;
      }
    }
  }

  if(fl==0)fprintf(fout,"NONE\n");

  fclose(fin);
  fclose(fout);
  return 0;
}				/* ----------  end of function main  ---------- */
