//Soyfer_task_2.9

#include <stdio.h>
#include <math.h>

int sign(double x)
{
	int sgn;
	if (x>1e-15) sgn = 1;
	else if (x<-1e-15) sgn = -1;
	else sgn = 0;
	return sgn;
}

int isnat(double x)
{
	int b;
	if ((ceil(x)==floor(x))&&(x>0)) b=1;
	else b=0;
	return b;
}

void sortarr(FILE *f, double *a, int n, int b)
{
	int k,pos,neg,nil; double x;
	
	pos=0; neg=0; nil=0;

	if (b)
	{
		for(k=0;k<n;k++)
		{
			fscanf(f,"%lf",&x);
			if (sign(x)>0) {a[pos]=x; pos++;} //filling 'head' half for positives
			else if (sign(x)<0) {a[neg+n]=x; neg++;} //'tail' half for negatives
			else nil++; //incrementing nil-counter for zeros
		}
	}
	
	else
	{
		rewind(f); //back to the beginning of the file for new data reading
		for(k=0;k<n;k++)
		{
			fscanf(f,"%lf",&x);
			if (sign(x)>0) {a[pos]=x; pos++;} //filling 'head' area for positives
			else if (sign(x)<0) {a[neg+n]=x; neg++;} //'tail' area for negatives
			else nil++;
		}
	}
	
	for (k=0;k<nil;k++) a[pos+k]=0;
	for (k=0;k<neg;k++) a[pos+nil+k]=a[n+k];
	
	fprintf(f, "\n---\nnew sorted array:");
	for (k=0;k<n;k++) fprintf(f, "\n%g", a[k]);
	
	fclose(f);
	return;
}

void main (void)
{
	FILE *f; char *name[1]; int b,n; double x;
	
	printf("file:\t"); scanf("%s", name);
	
	f=fopen(name, "r+");
	if (f==NULL) printf("\nfile error");
	else if ((fscanf(f,"%lf",&x)!=1)||(x==0)) printf("\nempty file or incorrect file data");
	else
	{
		b=isnat(x);

		if (b)
		{
			n=x; //1st number is natural => it is amount of elements in sequence
			double m[2*n]; //double memory for 2 types of numbers: + , - (for 0 only counter)
			sortarr(f,m,n,b);
		}
		else
		{
			n=1; //one element is already read by the 1st 'fscanf' called
			while (fscanf(f,"%lf",&x)==1) n++;
			double m[2*n];
			sortarr(f,m,n,b);
		}	
	}
	return;
}

