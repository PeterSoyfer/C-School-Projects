#include "2.5_funcs.h"

int is_delim(int c)
{register int i;
 for (i=0;i<n_delim;i++)
 if(c==delim[i]||c=='\n'||c=='\r') return 1;
 return 0;
}

void wordmaxmin(char *str, int *maxmin)
{int i,wordlen;
 for(i=wordlen=0;i<strlen(str);i++)
 {
  if(is_delim(str[i])==0)
  {
   ++wordlen;
   if(i==strlen(str)-1)
   {
    if (wordlen>maxmin[0]) maxmin[0]=wordlen;
    if (wordlen<maxmin[1]&&wordlen>0) maxmin[1]=wordlen;
   }
  }
  else
  {
   if(maxmin[0]==0) maxmin[1]=wordlen;
   if (wordlen>maxmin[0]) maxmin[0]=wordlen;
   if (wordlen<maxmin[1]&&wordlen>0) maxmin[1]=wordlen;
   wordlen=0;
  }
 }
 return; 
}

void wordlengths(char *str, int *wl, int *sym)
{int i,wordlen;

 for(i=wordlen=0;i<strlen(str);i++)
 {
  sym[str[i]]++;
  if(is_delim(str[i])==0)
  {++wordlen;
   if(i==strlen(str)-1) wl[wordlen]++;
  }
  else
  {wl[0]++;
   if(wordlen>0) wl[wordlen]++;
   wordlen=0;
  }
 }
 return;
}

double wordarithm(int *wl, int size)
{int i,ws; double ans;
 for(i=1,ws=0;i<size;i++) ws+=wl[i];
 for(i=ans=0;i<size;i++) ans+=i*wl[i];
 if(ws!=0) ans/=ws;
 return ans;
}

double symbolfreq(int *sym, int ch)
{int i,symsum; double ans;
 for(i=symsum=0;i<NSYM;i++) symsum+=sym[i];
 ans=sym[ch];
 ans/=symsum;
 return ans;
}

void symbolprint(FILE *fp, int *sym)
{int i;
 for(i=0;i<NSYM;i++)
 {
  if(sym[i]!=0)
  {
   if(i==10) fprintf(fp,"\nSymbol: \\n \tFrequency: %g\n",symbolfreq(sym,i));
   if(i==13) fprintf(fp,"\nSymbol: \\r \tFrequency: %g\n",symbolfreq(sym,i));
   if(i==32) fprintf(fp,"\nSymbol: space\tFrequency: %g\n",symbolfreq(sym,i));
   if(i!=10&&i!=13&&i!=32) fprintf(fp,"\nSymbol: %c\tFrequency: %g\n",i,symbolfreq(sym,i));
  }
 }
 return;
}

void general()
{FILE *f; char *line=NULL; char fname[256];
 size_t len=0; int i,maxlen,p[2],c[NSYM];

 printf("\nInput name of file with extension: ");
 scanf("%s",fname);

 f=fopen(fname,"r");
 if(f==NULL) {printf("\nError: Cannot open file!\n"); return;}

 for(i=0;i<NSYM;i++) c[i]=0;
 for(i=0;i<2;i++) p[i]=0; //array with maximum and minimum wordlength

 while(getline(&line,&len,f)!=-1) wordmaxmin(line,p);

 maxlen=p[0]+1;
 int w[maxlen];
 for(i=0;i<maxlen;i++) w[i]=0;

 rewind(f);
 while(getline(&line,&len,f)!=-1) wordlengths(line,w,c);
 free(line);
 fclose(f);

 f=fopen("result.txt","a");
 if(f==NULL) {printf("\nError: Cannot open file!\n"); return;}
 fprintf(f,"\n\tResults from file %s :\n",fname);
 fprintf(f,"\nMaximum word length: %i\n",p[0]);
 fprintf(f,"\nMinimum word length: %i\n",p[1]);
 fprintf(f,"\nAverage word length: %g\n",wordarithm(w,maxlen));
 symbolprint(f,c);
 fclose(f);
 printf("\nYou may see the results in the file result.txt\n");
 return;
}