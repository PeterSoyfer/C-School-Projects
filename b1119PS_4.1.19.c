//b1119PS_4.1.15
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h> /*for fmax*/

typedef struct isotope_data
{
	int z, a; //charge (p) and mass (p+n) of a nucleus
	char el[3]; //symbol of an element
	double m, ab; //mass and abundance of an isotope
}
isot;

void load(isot I, FILE *f0, isot Is[]) //loading data from file to structure massive
{
	int i;
	//isot I, Is[280];
	//FILE *f0;
	for (i=0; i<280; i++)
    {
		fscanf (f0, "%i\t%i\t%s\t%lf\t%lf\n", &I.z, &I.a, &I.el, &I.m, &I.ab);
  		Is[i]=I;
	}
	fclose(f0);
}

int del_(char *st) //erasing spaces in string
{
	int i,j=0;
	for (i=0;i<=(strlen(st)-1);i++) //strlen - length of a string before space
	{
		if (isspace(st[i])==0) 
		/*isspace returns nonzero value (probably index of the symbol, logical 'True')
		of first appearing spacing symbol in string*/
		{
			j++;
		}
		return j; //returning length of string before the first space
	}
}

int at,k; //external variables for multiple functions

int query(char *st, int *at , int *k) /*distributing query; 'at' instead of 'massnumber' for shortness*/
{
	if (strchr(st, '*')!=0)
   /*searching function strchr returns pointer (memory address?)
   of selected symbol if it's found or NULL (0) if it's not*/
	{
		char s[3];
		s[0]=st[2]; //recognizing value of massnumber (maximum 238, 3-numerical)
		s[1]=st[3];
		s[2]=st[4];
		*at=atoi(s); //reading and converting massnumber of isotope from str to int
		return 4; //appropriate case is sent as a value of query function
	}
	
	if (strchr(st,'[')==0) return 1;	
	
	char s1[2], s2[2];
	strcat(s1,&(st[3])); //strcat writes symbols from st[4th] in the end of s1
	strcat(s2,&(st[2]));
	(*k)=fmax(atoi(s1),atoi(s2));
	/*fmax - searching for the greatest value of 2 parameters; atoi converts string to int*/
	if (*k) return 2;
	else return 3;
}

void search1(char *s, isot Is[])
{
	int i;
	for (i=0;i<280;i++)
	{
		if (strcmp(s,(Is[i].el))==0) //strcmp returns 0 if strings are identical
		{
			if(Is[i].ab<0.1)
			{
				printf("%i\t%i\t%s\t%lf\t%.1e\n", (Is[i]).z, (Is[i]).a, (Is[i]).el, (Is[i]).m, (Is[i]).ab);
			}
			else
			{
				printf("%i\t%i\t%s\t%lf\t%lf\n", (Is[i]).z, (Is[i]).a, (Is[i]).el, (Is[i]).m, (Is[i]).ab);
			}
		}
	}
}

void search2(char *s, isot Is[], int *k)
{
	int i=0;
	char ss[2];
	while (isalpha(s[i]))
   /*isalpha recognizes letters of alphabet in string without register division
   (if letter - returns nonzero (l.True), if not - returns NULL)*/
	{
		ss[i]=s[i];
		i++;
	}
	for (i=0;i<280;i++)
	{
		if (*k==(Is[i]).a && strcmp(ss,(Is[i].el))==0) //strcmp - string coincidence checking
		{
			if(Is[i].ab<0.1)
			{
				printf("%i\t%i\t%s\t%lf\t%.1e\n", (Is[i]).z, (Is[i]).a, (Is[i]).el, (Is[i]).m, (Is[i]).ab);
			}
			else
			{
				printf("%i\t%i\t%s\t%lf\t%lf\n", (Is[i]).z, (Is[i]).a, (Is[i]).el, (Is[i]).m, (Is[i]).ab);
			}
		}
	}
}

void search3(char *s, isot Is[])
{
	int i=0;
	char ss[2];
	isot cmp;
	double n;
	while (isalpha(s[i]))
	{
		ss[i]=s[i];
		i++;
	}
	for (i=0;i<280;i++)
	{
		if (strcmp(ss,(Is[i].el))==0 && (Is[i]).ab > n)
		cmp=Is[i];
		n=(Is[i]).ab;
	}
		if(n<0.1)
		{
			printf("%i\t%i\t%s\t%lf\t%.1e\n", cmp.z, cmp.a, cmp.el, cmp.m, cmp.ab);
		}
		else
		{
			printf("%i\t%i\t%s\t%lf\t%lf\n", cmp.z, cmp.a, cmp.el, cmp.m, cmp.ab);
		}
}

void search4(isot Is[], int *at)
{
	int i;
	for (i=0;i<280;i++)
	{
		if (*at==(Is[i]).a)
			if(Is[i].ab<0.1)
			{
				printf("%i\t%i\t%s\t%lf\t%.1e\n", (Is[i]).z, (Is[i]).a, (Is[i]).el, (Is[i]).m, (Is[i]).ab);
			}
			else
			{
				printf("%i\t%i\t%s\t%lf\t%lf\n", (Is[i]).z, (Is[i]).a, (Is[i]).el, (Is[i]).m, (Is[i]).ab);
			}
	}
}

void main()
{
	char s[0];	//string of user's request expanding in dependence with length of input data
	int mass;	//variable for mass number from user
	FILE *f0;
	static isot Is[279];
	isot I;
	int i;
	
	if ((f0=fopen("atom.txt", "r")) == NULL)
	{  
		printf("FILE_ERROR");
		return;
	}

	load(I, f0, Is);	//getting table of isotopes from file - try to change calling of arguments (not void)

	for (;;)
	{
		printf("lookin' for sumthin', huh? ");
		scanf("%s", &s);
		if (!(del_(s))) break;

    	switch (query(s, &at , &k))
		{
			case 1:
				search1(s, Is);
				break;
			case 2:
				search2(s, Is, &k);
				break;
			case 3:
				search3(s, Is);
				break;
			case 4:
				search4(Is, &at);
				break;
			default:
				printf("u mad? don't play the ape, man\n");
        	if (getch()==13) break; //breaking if "Enter" button pressed (13=="Enter")
		}
   }	// ending of requesting loop
}
