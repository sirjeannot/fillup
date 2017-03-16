#include <stdio.h>
#include <time.h>

int mt[624];
int mt_index=0;


void mt_init(int seed)
{
	int i;
	mt[0]=seed;
	for(i=0; i<624; i++)
		mt[i]=(1812433253*(mt[i-1]^(mt[i-1]>>30)) + i)&0xFFFFFFFF;
}


// Generate an array of 624 untempered numbers
void mt_gennum()
{
	int i,y;
	for(i=0; i<624; i++)
	{
		y=(mt[i]>>31)&1+(mt[i+1]%624)&0x7FFFFFFF;
		mt[i]=mt[(i+397)%624]^(y>>1);
         if ((y % 2)==1)
             mt[i]=mt[i]^0x9908b0df;
     }
 }

int mt_extrnum()
{
	if(!mt_index)
		mt_gennum();
	int y=mt[mt_index];
	y^=(y>>11);
	y^=(y<<7&0x9d2c5680);
	y^=(y<<15&0xefc60000);
	y^=(y>>18);
	mt_index=(mt_index+1)%624;
	return y;
}

int main()
{
 	FILE *fp;
 	mt_init((int)time(NULL));
 	
 	fp=fopen("junk.txt", "w");
 	while(1)
	 		fprintf(fp, "%d", mt_extrnum());
 	fclose(fp);
 	return 0;
}
