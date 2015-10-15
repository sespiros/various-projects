/*
ID: sespiros
PROG: milk
LANG: C
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

int farm[5000][2];

  void
qsortt (int farmers  )
{
  int i,j,min=1001,temp,pos;

  for(i=0;i<farmers;i++){
    min=1001;
    for(j=i;j<farmers;j++){
      if(farm[j][0]<min){
        min=farm[j][0];
        pos=j;
      }
    }
    temp=farm[i][0];
    farm[i][0]=farm[pos][0];
    farm[pos][0]=temp;
    temp=farm[i][1];
    farm[i][1]=farm[pos][1];
    farm[pos][1]=temp;
  }
}		/* -----  end of function qsortt  ----- */

  int
main ( int argc, char *argv[] )
{
  FILE *fin,*fout;
  int i,limit,cur=0, amount=0,farmers,min=0;


  fin=fopen("milk.in","r");
  fout=fopen("milk.out","w");

  fscanf(fin,"%d%d",&limit,&farmers);

  for(i=0;i<farmers;i++){
    fscanf(fin,"%d%d",&farm[i][0],&farm[i][1]);
  }
  i=0;
  qsortt(farmers);

  while(amount<limit){
    cur=0;
    if(farm[i][1]<=limit-amount){
      cur=farm[i][1];
      min+=cur*farm[i][0];
    }else{
      cur=limit-amount;
      farm[i][1]-=cur;
      min+=cur*farm[i][0];
    }
    amount+=cur;
    i++;
  }

  fprintf(fout,"%d\n",min);

  fclose(fin);
  fclose(fout);
  return 0;
}				/* ----------  end of function main  ---------- */
