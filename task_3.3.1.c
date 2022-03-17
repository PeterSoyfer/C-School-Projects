#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRMAX 512

int wordlengths(char*,char*,int*);
int search(const char*,char*);

int main()
{char word[STRMAX],fname[256];

 printf("\nInput name of file with extension: ");
 scanf("%s",fname);

 search(fname,word);

 return 0;
}

int wordlengths(char *str, char *w, int *wlen)
{int i,j,k,wl; char tmp[STRMAX]={0};

 if(strlen(str)>STRMAX)
 {printf("\nError: String is too long!\n"); return -1;}

 for(i=k=0;i<strlen(str);i++) if(str[i]==34) ++k;
 if(k%2==1) {printf("\nError: Odd number of quotes!\n"); return -1;}

 for(i=strlen(str),wl=0;i>=0;i--)
 {
  if(str[i]==34&&str[i-1]==65) // 34 <=> " | 65 <=> A
  {
   for(j=i-1;j>=0&&str[j]!=34;j--)
   {
    if(str[j]<65||str[j]>90) {wl=0; break;}
    tmp[wl++]=str[j];
   }

   if(wl>*wlen)
   {
    *wlen=wl;
    for(k=0;k<wl;k++) w[k]=tmp[wl-k-1];
   }

   for(k=0;k<=wl;k++) tmp[k]='\0';
   wl=0;
  }
 }
 return 0;
}

int search(const char *SInputFile, char *word)
{FILE *f; char *line=NULL;
 size_t len=0; int wordlength=0;

 f=fopen(SInputFile,"r");
 if(f==NULL) {printf("\nError: Cannot open file!\n"); return -1;}

 while(getline(&line,&len,f)!=-1)
  if(wordlengths(line,word,&wordlength)==-1) return 0;

 if(wordlength==0) printf("\nThere is no such word.\n");
 else printf("\nword: %s\n",word);

 fclose(f);
 free(line);
 return 0;
}