//Soyfer_task_4.5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ffindN(FILE *f, char *name)
{
	int N,x;
	f=fopen(name,"r");
	if (f==NULL) N=-1;
	else if (fscanf(f,"%i",&x)!=1) N=0;
	else
	{
		N=1;
		while (fscanf(f,"%i",&x)==1) N++;
	}
	fclose(f);
	return N;
}

int issort(int *a, int n)
{
	int i,b;
	for (i=1;i<n;i++) if (a[i-1]>a[i]) {b=0; break;}
	if (i==n) b=1;
	return b;
}

void rand_arr(int *a, int n)
{
	int i;
	srand(time(NULL));
	for (i=0;i<n;i++) a[i]=rand();
	return;
}

void fget_arr(FILE *f, char *name, int *a, int n)
{
	int i,x;
	f=fopen(name,"r");
	for(i=0;i<n;i++) fscanf(f,"%i",&a[i]);
	fclose(f);
	return;
}

void insert_bin_sort(int *a, int n)
{
	int i,j,k,l,m,tmp; //lo == j ,  hi == k ,  mid == l ;
	
	for (i=0;i<n;i++)
	{
		tmp=a[i]; j=0; k=i;
		
		while (j<k)
		{
			l=j+(k-j)/2;
			
			if (tmp<a[l]) k=l;
			else j=l+1;
		}
	
		for (m=i;m>=j;m--) a[m]=a[m-1];
		
		a[j]=tmp;
	}
	printf("\nUr array:\n");
	for (i=0;i<n;i++) printf("\na[%i] = %i\n", i, a[i]);
	return;
}

int main(void)
{
	FILE *f=NULL; char name[256]; int i,b,n; clock_t t1,t2;
	
	printf("\nChoose array filling\n\t1)Random integer-numbers array of size n");
	printf("\n\t2)Filling array from file\nInput 1 or 2:\t");
	scanf("%i", &b);
	
	switch(b)
	{
		case 1: printf("\nInput size of array: "); scanf("%i", &n); break;
		case 2: printf("\nName of file: "); scanf("%s", name); n=ffindN(f,name); break;
		default: printf("\nIncorrect input. Try again"); n=-1; break;
	}
	
	if (n>=1)
	{
		int a[n];
		switch(b)
		{
			case 1: rand_arr(a,n); break;
			case 2: fget_arr(f,name,a,n); break;
			default: break;
		}
		printf("\nUnsorted array:\n");
		for (i=0;i<n;i++) printf("\na[%i] = %i\n", i, a[i]);
		if (issort(a,n)!=1)
		{
			t1=clock();
			insert_bin_sort(a,n);
			t2=clock();
			printf("\n\nsorting time: %g sec", (double)(t2-t1)/CLOCKS_PER_SEC);
		}
		else printf("\n\nOh, it's already sorted.");
	}
	else printf("\nError: Array cannot be created");
	return 0;
}