/*
ID: sespiros
PROG: barn1
LANG: C
*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#define min(a,b) (a<b)?a:b

int
cmp (const void *arg1,const void *arg2 )
{
  return (*(int *)arg2)-(*(int *)arg1);
}		/* -----  end of function cmp  ----- */

  int
cmp2 (const void *arg1,const void *arg2 )
{
  return (*(int *)arg1)-(*(int *)arg2);
}		/* -----  end of function cmp  ----- */


  int
main ( int argc, char *argv[] )
{
  int i,maxn,maxst,full,s[200],df[200],ret,m;

  freopen("barn1.in","r",stdin);
  freopen("barn1.out","w",stdout);

  scanf("%d %d %d",&maxn,&maxst,&full);

  for(i=0;i<full;i++){//anti gia maxn full gia lysh horis map
    scanf("%d",&s[i]);
  }
  qsort(s,full,sizeof(int),cmp2);

  for(i=0;i<full-1;i++){
    df[i]=s[i+1]-s[i];
  }
  qsort(df, full-1, sizeof(int),cmp);

  ret=s[full-1]-s[0]+1;
  m=min(maxn-1,full-1);
  for(i=0;i<m;i++){
    ret-=(df[i]-1);
  }
  printf("%d\n",ret);
  return 0;
}				/* ----------  end of function main  ---------- */
