/*
ID: sespiros
PROG: gift1
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int np,i=0,check=0,many[10],j=0,check2=0,c=1,a;
	char *names[10],from[14],to[14];
	int amount[10],amou;
	FILE *fin, *fout;

	fin=fopen("gift1.in","r");
	fout=fopen("gift1.out","w");

	fscanf(fin,"%d",&np);

	for (i=0;i<np;i++){
		amount[i]=0;
	}

	for (i=0;i<np;i++){
		names[i]=malloc(14*sizeof(char));
		fscanf(fin,"%s",names[i]);
	}

	while(check2<np){
		fscanf(fin,"%s",from);
		i=0;
		c=1;
		while(i<np && c){
			if(!strcmp(from,names[i])){
				check=i;
				c=0;
			}
			i++;
		}
		fscanf(fin,"%d",&amou);
		fscanf(fin,"%d",&many[check]);
		a=many[check];
		if(a!=0){
		amount[check]-=a*(amou/a);}

		for(i=0;i<many[check];i++){
			fscanf(fin,"%s",to);
			j=0;
			c=1;
			while(j<np && c){
				if(!strcmp(to,names[j])){
					amount[j]+=amou/many[check];
					c=0;
				}
				j++;
			}
		}
		check2+=1;
	}

	for(i=0;i<np;i++){
		fprintf(fout,"%s %d\n",names[i],amount[i]);
	}

	fclose(fin);
	fclose(fout);
}
