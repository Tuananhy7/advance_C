#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fp=NULL;
char buff[255];

void sig_handler(int signo)
{
        if(signo==2)
                raise(9);
}

void sig_handler1(int signo)
{
        if(signo==10)
        {
                printf("\nrecived message:\n");
                fp=fopen("output.txt","r+");
                fgets(buff,255,(FILE*)fp);
                fclose(fp);
                printf("%s\n",buff);
        }
}
int main()
{
        //FILE *fp=NULL;
        int id=0;
        pid_t idmask=0;
        fp=fopen("output.txt","w+");
        //char *buff=(char*)malloc(sizeof(char)*255);
        printf("%d\n",getpid());
        do
        {
                printf("enter pid:");
                scanf("%d",&id);
                idmask=(pid_t)id;
        }while(abs(kill(idmask,SIGCHLD)));
        printf("connected\n");
        signal(SIGINT,sig_handler);
        signal(10,sig_handler1); //revice
        //signal(12,sig_handler2); //send
        while(1)
        {
                        fp=fopen("output.txt","r+");
                        printf("typing message:");
                        scanf("%s",buff);
                        fputs(buff,fp);
                        fclose(fp);
                        printf("sent message:\n");
                        kill(id,10);

        }
        return 0;
}
