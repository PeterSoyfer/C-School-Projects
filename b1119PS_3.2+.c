//b1119PS_3.2.1

#include <math.h>
#include <stdio.h>

int mp (int x)
{
	return x*(x-1)/2; //triangle number - max amount of points
}

int cp(double y1[2], double y2[2], double pt[2]) //checking parallelity and calculating crosspoints
{
	if (y1[0]==y2[0]) 
	{
		return 0; //case of parallelity or similarity
	}
	else
	{
		pt[0] = (y2[1] - y1[1])/(y1[0] - y2[0]);
		pt[1] = (y2[1]*y1[0] - y1[1]*y2[0])/(y1[0] - y2[0]);
		return 1; //case of cross and calculation of point coordinates
	}
}	

int sp(double p1[2], double p2[2]) //comparison of pts coordinates 
{
	if (fabs(p1[0]-p2[0])<=1e-13 && fabs(p1[1]-p2[1])<=1e-13) 
	//condition of pts coincidence regarding to accuracy of double
	{
		return 1; //case of similarity
	}
	else
	{
		return 0; //case of difference
	}
}

void main ()
{

int ml;

FILE *f0;
	if ((f0=fopen("lines.txt", "r")) == NULL)
	{  
		printf("FILE_ERROR");
		return;
	}
	fscanf(f0,"%i", &ml); //getting amount of lines from file (1st symbol)

double ls[ml][2], pts[mp(ml)][2]; //initializing 2d-massives for lines and points

/*int u;
for (u=0;u<=mp(ml)-1;u++)
{
	pts[u][0]=1e-14;//filling massive with impossible quantities for choosing right elements
}*/

int i;
	for (i=0; i<=ml-1;i++)  //getting coefficients of each line from file
	{
		fscanf(f0,"%lf%lf", &ls[i][0], &ls[i][1]);
	}

fclose(f0);

printf("crossing points:\n");

int j,k,q; //counters for internal loops
int n=0; //counter for crossing points
int r=1; //counter of appropriate element from pts massive to rewrite
double p1[2]; //disposable massive for loop

	for (j=1; j<=ml-1; j++) //main loop in which all conditions and function operations are done
	{
		for (k=0; k<=j-1; k++) //subloop
		{
     	   if (cp(ls[j], ls[k], p1)==1) //calculation of crossing points with overlaps
			{
				n++; //first counting of crossings with overlaps
				if (j==1) //writing the first element independently to others
				{
					pts[0][0]=p1[0];
					pts[0][1]=p1[1];
				}
				else
            {
               int c=0; //controller of difference between all points
					for (q=0; q<=r-1; q++) //comparing all the pts
					{
						c+=sp(pts[q], p1);
					}

               if (c==0) //controller shows that all pts are different
					   {
					    r++;
					    pts[q][0]=p1[0]; //rewriting the elements
					    pts[q][1]=p1[1];
					   }
               else
               {
                  n--; //decreasing the number of pts regarding to overlaps
               }
				}
			}
		}
	}
int s;
	for (s=0; s<=r-1; s++) //loop for printing the outcome
	{
     	printf("%lf %lf\n", pts[s][0], pts[s][1]);
   }
printf("total amount of crossings: %i\n", n);

/*for (j=1; j<=ml-1; j++) //main loop in which all conditions and function operations are done
	{
		for (k=0; k<=j-1; k++) //subloop
		{
		   if (cp(ls[j], ls[k], p1)==0)
		   {
		      printf("those are parallel: %i %i\n", j, k);
         }
      //printf("value of cp for the last line: %i\n", cp(ls[j], ls[k], p1));
      }
   }*/
}
