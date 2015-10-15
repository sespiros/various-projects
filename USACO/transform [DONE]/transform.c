/*
ID: sespiros
PROG: transform
LANG: C
*/


#include	<stdio.h>
#include	<stdlib.h>
#define max 10

int check,n;
char a[max][max],b[max][max],c[max][max];

  void
checker90 (int n  )
{
  int i1=0,j1,i2,j2=n-1;
  check=1;

  while(i1<n && j2>=0 && check){
    j1=0;
    i2=0;
    while(j1<n && i2<n && check){
      if(a[i1][j1]==b[i2][j2]){
        check=1;
      }else{
        check=0;
      }
      j1++;
      i2++;
    }
    i1++;
    j2--;
  }
}


  void
checker180 (int n  )
{
  int i=0,j=0;
  check=1;

  while(i<n && check){
    j=0;
    while(j<n && check){
      if(a[i][j]==b[n-i-1][n-j-1]){
        check=2;
      }else{
        check=0;
      }
      j++;
    }
    i++;
  }
}


  void
checker270 (int n  )
{
  int i1=0,j1=0,i2=0,j2=n-1;
  check=1;

  while(i1<n && i2<n && check){
    j1=0;
    j2=n-1;
    while(j1<n && j2>=0 && check){
      if(a[i1][j1]==b[j2][i2]){
        check=3;
      }else{
        check=0;
      }
      j1++;
      j2--;
    }
    i1++;
    i2++;
  }
}


  void
checkermirror (int n  )
{
  int i=0,j=0;
  check=1;

  while(i<=(n-1)/2 && check){
    j=0;
    while(j<=(n-1)/2 && check){
      if(a[i][j]==b[i][n-j-1] && a[i][n-j-1]==b[i][j]){
        check=4;
      }else{
        check=0;
      }
      j++;
    }
    i++;
  }
}

  void
checkercomb (int n  )
{
  int i1=0,j1=0,i2,j2=n-1;
  check=1;
  //90 degrees
  while(i1<n && j2>=0 && check){
    j1=0;
    i2=0;
    while(j1<n && i2<n && check){
      b[i1][j1]=c[i2][j2];
      j1++;
      i2++;
    }
    i1++;
    j2--;
  }
  checkermirror(n);
  //270 degrees
  if(check==0){
    i1=0;
    i2=n-1;
   while(i1<n && i2>=0 && check){
    j1=0;
    j2=n-1;
    while(j1<n && j2>=0 && check){
      b[i1][j1]=c[i2][j2];
      j1++;
      j2--;
    }
    i1++;
    i2--;
  }
  checkermirror(n);
  }
  //180 degrees
  if(check==0){
    for(i1=0;i1<n;i1++){
      for(j1=0;j1<n;j1++){
        b[i1][j1]=c[n-1-i1][n-1-j1];
      }
    }
    checkermirror(n);
  }
  if(check==4)check=5;
}


  void
checkerequal (int n  )
{
  int i,j;
  check=1;

  for(i=0;i<n && check;i++){
   for(j=0;j<n && check;j++){
     if(a[i][j]==b[i][j]){
       check=6;
     }else{
       check=0;
     }
   }
  }
}


  void
btoc (void  )
{
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      b[i][j]=c[i][j];
    }
  }
}		/* -----  end of function btoc  ----- */


  int
main ( int argc, char *argv[] )
{
  FILE *fin,*fout;

  int i,j;

  fin=fopen("transform.in","r");
  fout=fopen("transform.out","w");

  fscanf(fin,"%d",&n);
  fgetc(fin);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      a[i][j]=fgetc(fin);
      //printf("%c",a[i][j]);
    }
    fgetc(fin);
    //printf("\n");
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      c[i][j]=fgetc(fin);
      //printf("%c",b[i][j]);
    }
    fgetc(fin);
    //printf("\n");
  }
  btoc();
  checker90(n);
  if(check==0)checker180(n);
  if(check==0)checker270(n);
  if(check==0)checkermirror(n);
  if(check==0)checkercomb(n);
  btoc();
  if(check==0)checkerequal(n);
  if(check==0)check=7;
  //printf("%d\n",check);
  fprintf(fout,"%d\n",check);
  fclose(fin);
  fclose(fout);

  return 0;
}
