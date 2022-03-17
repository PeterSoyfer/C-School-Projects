//Soyfer_task_5.3

#include <stdio.h>
#include <math.h>

int ffindN(FILE *f, char *name) //number of pairs
{
	int N; double x[2];
	f=fopen(name,"r");
	if (f==NULL) N=-1;
	else if (fscanf(f,"%lf\t%lf\n",&x[0],&x[1])!=2) N=0;
	else
	{
		N=1;
		while (fscanf(f,"%lf\t%lf\n",&x[0],&x[1])==2) N++;
	}
	fclose(f);
	return N;
}

void fget_pts(FILE *f, char *name, double pts[][2], int n)
{
	int i;
	f=fopen(name,"r");
	if (f==NULL) printf("\nError");
	else
	{
		for(i=0;i<n;i++)
		{
			fscanf(f,"%lf\t%lf\n",&pts[i][0],&pts[i][1]);
		}
	}
	fclose(f);
	return;
}

int signum(double x)
{
	int sign;
	if (x>1e-15) sign=1;
	else if (x<-1e-15) sign=-1;
	else sign=0;
	return sign;
}

int i_min(double a[], int n)
{
	int i,result; double min;
	min=a[0]; result=0;
	for(i=0;i<n;i++)
	{
		if (a[i]<min) {min=a[i]; result=i;}
		//else if (fabs(a[i]-min)<1e-15)
	}
	return result;
}

double scalar(double a[2], double b[2]) //scalar multiplication of vectors
{
	double c;
	c=a[0]*b[0]+a[1]*b[1];
	return c;
}

double l(double a[2]) //vector length
{
	double vl;
	vl=sqrt(scalar(a,a));
	return vl;
}

double s_or(double a[2], double b[2]) //determinant 2*2 matrix for oriented square
{
	double s;
	s=a[0]*b[1]-a[1]*b[0];
	return s;
}

double h_or(double a[2], double b[2], double c[2])
{
	double height;
	height=s_or(a,b)/l(c);
	return height;
}

int min_dist(double pts[][2], double vpt[2], int n)
{
	int i,j,k,sum,p[2],sgn[2]; double min,q,ht[n],a[2][2],c[2][2];
	
	for (i=0;i<n;i++)
	{
		for (j=0;j<2;j++) //a[0]==AB, a[1]==BA, c[0]==AM, c[1]==BM;
		{
			q=pts[(i+1)%n][j]-pts[i][j]; a[0][j]=q; a[1][j]=-q;
			c[0][j]=vpt[j]-pts[i][j]; c[1][j]=vpt[j]-pts[(i+1)%n][j];
		}
	
		sum=0;
		for (k=0;k<2;k++)
		{
			sgn[k]=signum(scalar(a[k],c[k]));
			switch(sgn[k])
			{
				case 1: p[k]=1; break;
				case 0: p[k]=0; ht[i]=l(c[k]); break;
				case -1: p[k]=-1; ht[i]=l(c[k]); break;
				default: break;
			}
			sum+=p[k];
		}
		
		if (sum==2) {ht[i]=fabs(h_or(c[0],c[1],a[0]));}
	}
	k=i_min(ht,n);
	return k;
}

int foo(double pts[][2], double vpt[2], int n) //pts - polygon points, vpt - unknown point
{
	double AB[2],MA[2],MB[2];
	int i,j,r,t,ans;
	
	switch(n)
	{
		case 1:
			{
				for (j=0;j<2;j++) {AB[j]=pts[0][j]-vpt[j];}	
				
				if(l(AB)<1e-15) ans=0;
				else ans=1;
				break;
			}
		case 2:
			{
				for (j=0;j<2;j++)
				{AB[j]=pts[1][j]-pts[0][j]; MA[j]=pts[0][j]-vpt[j]; MB[j]=pts[1][j]-vpt[j];}
		
				t=signum(h_or(MA,MB,AB));
	
				if(t!=0) ans=t;
				else
				{
					if (((l(MA)/l(AB))>1)||(scalar(MA,AB)>0)) ans=-1;
					else ans=0;
				}
				break;
			}
		default:
			{
				r=min_dist(pts,vpt,n); //1st point of the nearest section number

				for (j=0;j<2;j++)
				{
					AB[j]=pts[(r+1)%n][j]-pts[r][j];
					MA[j]=pts[r][j]-vpt[j];
					MB[j]=pts[(r+1)%n][j]-vpt[j];
				}
			
				t=signum(h_or(MA,MB,AB));
			
				if(t!=0) {ans=t;}
				else if ((l(MA)>l(AB))||(scalar(MA,AB)>0)) {ans=-1;}
				else {ans=0;}
				break;
			}
	}
	return ans;
}

void main(void)
{
	FILE *f=NULL; char name[256]; int n;
	printf("\nName of file: "); scanf("%s", name);
	n=ffindN(f,name);
	if(n>0)
	{
		double ps[n][2],pt[2]; fget_pts(f,name,ps,n);
		printf("\nInput coordinates of important point: "); scanf("%lf %lf",&pt[0],&pt[1]);
		switch(foo(ps,pt,n))
		{
			case -1: printf("\nOutside\n"); break;
			case 0: printf("\nBoundary\n"); break;
			case 1: printf("\nInside\n"); break;
			default: printf("\nError\n"); break;
		}
	}
	else printf("\nError\n");
	return;
}