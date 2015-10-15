/*
ID: sespiros
PROG: friday
LANG: C
*/
#include <stdio.h>

int main(void){
    int d=0,date=1,month=0,year=1900,np,i;
    int array[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int final[7];
    FILE *fin,*fout;

    fin=fopen("friday.in","r");
    fout=fopen("friday.out","w");

    fscanf(fin,"%d",&np);

    for(i=0;i<7;i++)final[i]=0;
    while(year<1900+np){
        if(d==7)d=0;

        if(year%400 ==0 || (year%100 != 0 && year%4 == 0)){
            array[1]=29;
        }else{
            array[1]=28;}

        if(date==array[month]){
            date=1;
            month++;
            if(month==12){
                month=0;
                year++;
            }
        }else{date++;}


        if(date==13){
           final[d]+=1;}


        d++;
    }

    for(i=4;i<7;i++){
        fprintf(fout,"%d ",final[i]);
    }
    for(i=0;i<3;i++){
        fprintf(fout,"%d ",final[i]);
    }
    fprintf(fout,"%d\n",final[3]);
    fclose(fin);
    fclose(fout);
}
