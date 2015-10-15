/*
ID: sespiros
PROG: milk2
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXN 5000
#define DMAXN 2*MAXN


int start[MAXN],end[MAXN],n,b;

  int
checker (int c)
{
  int i=0,a=0;
  while(i<n&& a==0)
  {
    if(c>=start[i] && c<end[i])
    {
      a=1;
      b=i;
    }
    i++;
  }
  return a;
}

int main(void){

  int i,c,max=-1,min=100000,check=1,pre=0,milk=0,idle=0,maxmilk=0,maxidle=0;

	FILE *fin, *fout;

	fin=fopen("milk2.in","r");
	fout=fopen("milk2.out","w");

  fscanf(fin,"%d\n",&n);
	for(i=0;i<n;i++){
		fscanf(fin,"%d\n",&start[i]);
		fscanf(fin,"%d\n",&end[i]);
    if(end[i]>max){
      max=end[i];
     }
    if(start[i]<min){
      min=start[i];
    }
  }
  c=min;
  while(c<=max){
    check=checker(c);

    if(milk==913){
      printf("*");}

    if(check)
    {
      if(idle>=maxidle){
        maxidle=idle;
       }
      if(!pre){
        idle=0;
       }

      milk++;
    }else
    {
      if(milk>=maxmilk){
        maxmilk=milk;
      }
      if(pre){
        milk=0;
      }

      idle++;
    }
    pre=check;
    c++;
  }
  if(milk>maxmilk){
    fprintf(fout,"%d %d\n",milk,idle);}
  else{
    fprintf(fout,"%d %d\n",maxmilk,maxidle);}
  fclose(fin);
  fclose(fout);
  return 0;
}
