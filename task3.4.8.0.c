//Soyfer_task_3.4
#include <stdio.h>

void into_file(FILE *f, int *a, int n)
{
	int i;
	fprintf(f,"\n");
	for (i=0;i<n;i++) {fprintf(f,"%i ", a[i]);}
	fprintf(f,"\n");
}

void bin_form(int n, int k, int *bit_arr) //binary form (array of 0 and 1) of decimal
{
	int i;
	for(i=n-1;i>=0;i--) {bit_arr[n-(i+1)]=(k&(1<<i))>>i;}
	return;
}

int ones(int n) //number of 1-bits in binary form
{
	int i,c;
	c=0; i=n;
	while(i) {i&=i-1; c++;}
	return c;
}

void k_subsets(FILE *f, char *name, int n, int k)
{
	if ((k>n)||(n<=0)||(k<=0)) {printf("\nincorrect data: k,n must be natural and k<=n\n");}
	
	else
	{
		int i,j,l,m,p,c,set[n],subset[k];
		
		f=fopen(name,"a");
		
		if(f==NULL) {printf("\nCannot open file!\n");}
		
		else
		{
			for(i=0;i<n;i++) {set[i]=i+1;} //filling set as {1 ... N}
			fprintf(f,"\nset:\n");
			into_file(f,set,n);
		
			fprintf(f,"\nsubsets:\n");
			for(l=0,c=0;l<(1<<n);l++)
   		{
   		   p=l^(l>>1);
   		   
				if (ones(p)==k) //finding number witn k 1-bits in its binary form
   		   {
   		   	int b[n];
					bin_form(n,p,b); //getting its binary form as an array
   	      
					for (i=0,j=0;i<n;i++)
					{
						//indexes of 1-bits in binary form are numbers for subset (they don't repeat)
						if (b[i]) {subset[j++] = set[i];}
					}
					into_file(f,subset,k);
					c++; //counting subsets for checking
				}
			}
			fclose(f);
			printf("\nNumber of subsets: %i\nCheck the file, there are all of them\n", c);
		}
	}
	return;
}

int main(void)
{
	FILE *f=NULL; char name[256]; int n,k;
	printf("\nInput N: "); scanf("%i", &n);
	printf("\nInput k: "); scanf("%i", &k);
	printf("\nFile: "); scanf("%s", name);
	k_subsets(f,name,n,k);
	return 0;
}
