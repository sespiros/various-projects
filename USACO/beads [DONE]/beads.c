/*
ID: sespiros
PROG: beads
LANG: C
*/

#include <stdio.h>

int flag1,flag2,n;
char neckl[350];

int checker(int i,int pl,int N,int arg,int arg2){
    char stand;
    //printf ("Checker function in progress...");
    if (arg==0){
       flag1=0;
       if(arg2)stand=neckl[n-1];
       while(i<=N && flag1==0){
            if(neckl[i]==neckl[i-1]||neckl[i]=='w'){
                if(neckl[i]!='w')stand=neckl[i];
                if(neckl[i-1]!='w')stand=neckl[i-1];
                pl++;
                i++;
            }else if(neckl[i]==stand){
                pl++;
                i++;
            }else{
                flag1=i;
            }
        }
    }else{
       flag2=0;
       if(arg2)stand=neckl[0];
       while(i>N && flag2==0){
            if(neckl[i]==neckl[i-1]||neckl[i-1]=='w'){
                if(neckl[i]!='w')stand=neckl[i];
                if(neckl[i-1]!='w')stand=neckl[i-1];
                pl++;
                i--;
            }else if(neckl[i-1]==stand){
                pl++;
                i--;
            }else{
                flag2=i;
            }
        }
    }
    //printf("%d\n",pl);
    return pl;
}

int main(void){
    int maxcut,i,cut[351],j;
    FILE *fin, *fout;

    fin=fopen("beads.in","r");
    fout=fopen("beads.out","w");

    fscanf(fin,"%d\n",&n);

    for(i=0;i<n;i++){neckl[i]=fgetc(fin);}

    for(i=27;i<n;i++){
        cut[i]=2;

        cut[i]=checker(i+2,cut[i],n,0,0);
        cut[i]=checker(i,cut[i],0,1,0);
        if(flag1==n+1 && (neckl[n-1]==neckl[0]||neckl[n-1]=='w'||neckl[0]=='w')){
            cut[i]++;
            cut[i]=checker(n-1,cut[i],flag1,1,1);
        }else if(flag2==n-cut[i] && (neckl[n-1]==neckl[0]||neckl[n-1]=='w'||neckl[0]=='w')){
            cut[i]++;
            cut[i]=checker(1,cut[i],flag2-1,0,1);
        }
        printf("");
    }
    maxcut=cut[0];
    for(i=1;i<n;i++){
        printf("%d\n",cut[i]);
        if(cut[i]>maxcut){
           maxcut=cut[i];
        }
    }
    printf("%d",maxcut);
    fprintf(fout,"%d\n",maxcut);
    fclose(fin);
    fclose(fout);
    return 0;
}
