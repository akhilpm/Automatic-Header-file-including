#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<strings.h>
#include<errno.h>

char header[20][40],blacklist[10][20];
int h=0,bindex=0;

void initialize_lists()
{
//put stdio.h in the include list
strcpy(header[h++],"#include <stdio.h>");
//initialize black list
strcpy(blacklist[bindex++],"#include <stdarg.h>");
}


int header_included(char head[])
{
int i;
for(i=0;i<h;i++)
 {
 if(strcmp(header[i],head)==0)
    return 1;
 }
return 0;
}


int blacklisted(char head[])
{
int i;
for(i=0;i<bindex;i++)
 {
  if(strcmp(blacklist[i],head)==0)
    return 1;
 }
return 0;
}


int execute_command(char command[])
{
return system(command);
}

void find_includer(char func[])
{
FILE *tmp;
int i,j,ind,l;
int flag=0;
char add[]=" > output.txt";
char lin[150],copy[20],cmd[50];
strcpy(cmd,func);
strcat(cmd,add);
//puts(func);
//puts(cmd);
if(execute_command(cmd)==4096)
 {
  memset(cmd,'\0',strlen(cmd)+2);
  return;
 }
else
{
tmp=fopen("output.txt","r");
fgets(lin,150,tmp);
l=strlen(lin)-1;
lin[l]='\0';
  while(!feof(tmp))
  {
  fgets(lin,150,tmp);
  ind=0;
  if(strncmp(lin,"DESCRIPTION",10)!=0)
    {
    for(i=0;i<strlen(lin)-1;i++)
      {
       while(isspace(lin[i]))
          i++;
       if(lin[i]=='#')
        {
         for(j=i;j<strlen(lin)-1;j++)
           {
           if(lin[j]=='<')
               flag==1;
           if(flag==1 && lin[j]==' ')
               break;
           else
               copy[ind++]=lin[j];
           }
         copy[ind]='\0';
         if(!header_included(copy))
           {
            if(!blacklisted(copy))
               strcpy(header[h++],copy);
           }
         bzero(copy,20);
         break;
        }
        else
          break;
      }
    }
  else
    {
    fclose(tmp);
    system("rm output.txt");
    memset(cmd,'\0',strlen(cmd)+2);
    return;
    }
  }
}
}


int main(int argc,char *argv[])
{
FILE *ptr,*copy;
char line[250],linecopy[50];
int i=0,ind=0,index=0,line_count=0;
char key[]="man ";
char cmd[100];

initialize_lists();
ptr=fopen(argv[1],"r");
copy=fopen("backup.c","w");
while(!feof(ptr))
  {
  fgets(line,250,ptr);
  line_count++;
  }
rewind(ptr);
while(!feof(ptr) && i<line_count-1)
  {
  i++;
  fgets(line,250,ptr);
  fputs(line,copy);
  }
fclose(copy);
fclose(ptr);
ptr=fopen(argv[1],"r");
while(!feof(ptr))
  {
  fgets(line,250,ptr);
  ind=0;
  for(i=0;i<strlen(line)-1;i++)
     {
      while(line[i]!='(' && i<strlen(line)-1)
         {
         if(isalpha(line[i]))
            {
             //printf("%c",line[i]);
             linecopy[ind++]=line[i++];
            }
         else
           {
               i++;
               ind=0;
	       bzero(linecopy,50);
           }
         }
      linecopy[ind]=='\0';
      //puts(linecopy);
      //i++;
      //execute the man command
      strcpy(cmd,key);
      strcat(cmd,linecopy);
      if(strlen(linecopy)>2)
        {
         find_includer(cmd);
         bzero(linecopy,50);
        }
      ind=0;
      bzero(cmd,50);
     }
  }
fclose(ptr);

//restore the original file with headers included
ptr=fopen(argv[1],"w");
copy=fopen("backup.c","r");
for(i=0;i<h;i++)
  {
  fputs(header[i],ptr);
  fprintf(ptr,"\n");
  }
fprintf(ptr,"\n");
i=0;
while(!feof(copy) && i<line_count-1)
  {
  i++;
  fgets(line,250,copy);
  fputs(line,ptr);  
  }
fclose(ptr);
fclose(copy);
if(system("rm backup.c")==-1)
  {
  printf("\nerror occured\n");
  exit(-1);
  }
return 0;
}

