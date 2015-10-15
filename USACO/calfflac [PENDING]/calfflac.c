/*
ID: sespiros
PROG: calfflac
LANG: C
*/

#include <stdio.h>
#include <ctype.h>
#define N 20000

int main(void){

	FILE *in=fopen("calfflac.in","r");
	FILE *out=fopen("calfflac.out","w");

	char buf[N];
	int C[N],I[N],L[N],max,fl;
	int n=0,i,j,c=0,k=0,u;
	int t;

	while(!feof(in)){buf[n++]=fgetc(in);}
	fclose(in);
	buf[--n]='\0';

	//printf("%s",buf);

	for(i=0;i<n;i++){
		t=i;
		if((buf[i]>='a' && buf[i]<='z')||(buf[i]>='A' && buf[i]<='Z')){
			for(j=n;j>=t;j--){
				if((buf[j]>='a' && buf[j]<='z')||(buf[j]>='A' && buf[j]<='Z')){
					if(tolower(buf[t])==tolower(buf[j])){
						if(c==0)u=j;
						if(j==t){c++;}else{c+=2;}
						t++;
						while(!((buf[t]>='a' && buf[t]<='z')||(buf[t]>='A' && buf[t]<='Z'))&&t<=j)t++;
					}else{
						if(c!=0){
							C[k]=c;
							I[k]=i;
							L[k++]=u;
						}
						c=0;
						t=i;
					}
				}
			}
			if(c!=0){
				C[k]=c;
				I[k]=i;
				L[k++]=u;
			}
			c=0;
		}
	}
	max=C[0];
	fl=0;
	for(i=1;i<k;i++){
		if(C[i]>max){
			max=C[i];
			fl=i;
		}
	}

//	fprintf(out,"%d\n",max);
	i=I[fl];
	while(i<=L[fl]){
		fprintf(out,"%c",buf[i++]);
	}
	//fprintf(out,"\n");
	fclose(out);
	return 0;
}
