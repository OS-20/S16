#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

void make_toks(char *s,char *tok[])
{
    int i=0;
    char *p;
    p=strtok(s," ");
    while(p!=NULL)
    {
        tok[i++]=p;
        p=strtok(NULL," ");
    }
    tok[i]=NULL;
}

void count(char *fn,char op)
{
    int fh,cc=0,wc=0,lc=0;
    char c;
    fh=open(fn,O_RDONLY);
    if(fh==-1)
    {
        printf("\nfile %s not found\n",fn);
        return;
    }

    while(read(fh,&c,1)>0)
    {
        
        if(c==' ')
            wc++;
        if(c=='\n')
            {
            wc++;
            lc++;
            }
            cc++;
    }

    close(fh);

    switch(op)
    {
        case 'c':
            printf("\nNo. of Characters : %d\n",cc);
            break;

        case 'w':
            printf("\nNo. of Words : %d\n",wc + 1);
            break;

        case 'l':
            printf("\nNo. of lines : %d\n",lc);
            break;

        default:
            printf("\nInvalid option. Use c, w, or l.\n");
    }
}

int main()
{
    char buff[80],*args[10];
    int pid;
    while(1)
    {
        printf("Myshell$");
        fflush(stdin);
        fgets(buff,80,stdin);
        buff[strlen(buff)-1]='\0';
        make_toks(buff,args);
        if(strcmp(args[0],"count")==0)
            count(args[2],args[1][0]);
        else
        {
            pid=fork();
            if(pid>0)
                wait(NULL);
            else
            {
                if((execvp(args[0],args)==-1))
                    printf("Bad Command\n");
            }
        }
    }
    return 0;
    }


