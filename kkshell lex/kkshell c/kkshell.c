/*KKSHELL*/
#define CMDLEN 50
#define ARGLEN 25
#define PATH_LENGTH 100

/*HEADER FILES*/
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<dirent.h>
#include<sys/utsname.h>
#include<wait.h>
#include<fcntl.h>
#include<ctype.h>
#include<pwd.h>
#include<stdlib.h>
#include<unistd.h>

/*GLOBAL VARIABLES*/
char cmd[CMDLEN];
char arg1[ARGLEN],arg2[ARGLEN];

/*FUNCTION DECLARATION*/
void kexit();
void klogin();
void getcmd(char cmdname[]);
void getargs();
void kdate();
void kmd();
void krd();
void kren();
void kcat();
void kcatp();
void kls();
void klsp();
void kclear();
void kpwd();
void kwc();
void khead();
void ktail();
void kwhoami();
void kuname();
void kcp();
void kcd();
void kabout();
void kman();

/*MAIN FUNCTIONS*/
int main()
{
	char cmdname[10];
	kclear();
	klogin();
	do
	{
	printf("\n[KKshell]@");
	gets(cmd);
	getcmd(cmdname);
	getargs();
	if(strcmp(cmdname,"kls")==0 && strcmp(arg1,"-p")==0)
		klsp();
	else if(strcmp(cmdname,"kls")==0)
		kls();
	else if(strcmp(cmdname,"kren")==0)
		kren();
	else if(strcmp(cmdname,"kdate")==0)
		kdate();
	else if(strcmp(cmdname,"kcd")==0)
		kcd();
	else if(strcmp(cmdname,"khead")==0)
		khead();
	else if(strcmp(cmdname,"ktail")==0)
		ktail();
	else if(strcmp(cmdname,"kcat")==0 && strcmp(arg1,"-p")==0)
		kcatp();
	else if(strcmp(cmdname,"kcat")==0)
		kcat();
	else if(strcmp(cmdname,"kclear")==0)
		kclear();
	else if(strcmp(cmdname,"kmd")==0)
		kmd();
	else if(strcmp(cmdname,"krd")==0)
		krd();
	else if(strcmp(cmdname,"kpwd")==0)
		kpwd();
	else if(strcmp(cmdname,"kwc")==0)
		kwc();
	else if(strcmp(cmdname,"kwhoami")==0)
		kwhoami();
	else if(strcmp(cmdname,"kuname")==0)
		kuname();
	else if(strcmp(cmdname,"kcp")==0)
		kcp();
	else if(strcmp(cmdname,"kman")==0)
		kman();
	else if(strcmp(cmdname,"about")==0)
		kabout();
	else if(strcmp(cmdname,"exit")==0)
		kexit();
	else if(cmdname[0]!=0)
		printf("\n\a\a\aKERROR:COMMAND NOT FOUND");
	}while(strcmp(cmdname,"exit")!=0);
	return;
}

/*Function to check login and password*/
void klogin()
{
	char login[20];
	char pass[20];
	while(1)
	{
		printf("\nLOGIN NAME:");
		scanf("%s",login);
		printf("PASSWORD");
		scanf("%s",pass);
		if(strcmp(pass,"kkshell")==0)
		{
			printf("\nLOGIN SUCESSFULL\nWELCOME TO KKSHELL");
			return;
		}
		else
			printf("\n\a\a\aKERROR:WRONG PASSWORD\nENTER AGAIN");
	}
}

/*FUNCTION TO EXIT KKSHELL*/
void kexit()
{
	printf("\n\a\aTERMINATING KKSHELL........\n");
	exit(0);
}

/*FUNCTION TO GET THE COMMAND NO*/
void getcmd(char cmdname[])
{
	int i;
	for(i=0;cmd[i]!=' ' && cmd[i]!=0;i++)
		cmdname[i]=cmd[i];
		cmdname[i]=0;
	return;
}

/*FUNCTION TO GET ARGUMENTS*/
void getargs()
{

 	arg1[0]=0;
	arg2[0]=0;
	int i,k;
	for(i=0;cmd[i]!=' '&& cmd[i]!=0;i++);
	if(cmd[i]!=0)
	{
		i++;
	}	
	for(k=0;cmd[i]!=' ' && cmd[i]!=0;i++,k++)
	{
		arg1[k]=cmd[i];
	}
	arg1[k]=0;
	if(cmd[i]!=0)
	{
		i++;
	}	

	for(k=0;cmd[i]!=' ' && cmd[i]!='\0';i++,k++)
	{
		arg2[k]=cmd[i];
	}
		arg2[k]=0;
	
	return;
}

/*FUNCTION TO DISPLAY DATE AND TIME*/
void kdate()
{
	time_t tvar=time(0);
	printf("\n%s",ctime(&tvar));
	return;
}

/*FUNCTION TO CREATE NEW DIRECTORY*/
void kmd()
{
	getargs();
	if(mkdir(arg1,000)!=0)
		printf("\n\a\a\aKERROR:UNABLE TO CREATE DIRECTORY");
	else
		printf("\nDIRECTORY CREATED SUCCESSFULLY");
	return;
}

/*FUNCTION TO DELETE DIRECTORY*/
void krd()
{
	getargs();
	if(rmdir(arg1)!=0)
		printf("\n\a\a\aKERROR:DIRECTORY NOT FOUND");
	else
		printf("\nDIRECTORY DELETED SUCCESSFULLY");
	return;
}

/*FUNCTION TO RENAME DIRECTORY AND FILES*/
void kren()
{
	getargs();
	if(rename(arg1,arg2)!=0)
		printf("\n\a\a\aKERROR:UNABLE TO RENAME");
	else
		printf("\nRENAMED SUCCESSFULLY");
	return;
}

/*FUNCTION TO DISPLAY CONTENTS OF A FILE*/
void kcat()
{
	char ch;
	FILE *fp;
	getargs();
	if((fp=fopen(arg1,"r"))==NULL)
		printf("\n\a\a\aKERROR:UNABLE TO OPEN FILE");
	else
	{
		ch=fgetc(fp);
		while(ch!=EOF)
		{
			printf("%c",ch);
			ch=fgetc(fp);
		}
	fclose(fp);
	}
	return;

}

/*FUNCTION TO DISPLAY CONTENTS OF A FILE PAGEWISE*/
void kcatp()
{
	char ch,flag;
	FILE *fp;
	int i;
	getargs();
	if((fp=fopen(arg2,"r"))==NULL)
		printf("\n\a\a\aKERROR:UNABLE TO OPEN FILE");
	else
	{
		ch=fgetc(fp);
		for(i=0;ch!=EOF;)
		{
			if(ch=='\n')
				i++;
			printf("%c",ch);
			ch=fgetc(fp);
			if(i%34==33)
			{
				printf("\nPRESS ENTER TO CONTINUE");
				getchar();
				i++;
			}
		}	
	fclose(fp);
	}
	return;

}


/*FUNCTION TO LIST ALL FILES AND DIRECTORIES*/
void kls()
{
	DIR *dir_fdesc;
	struct dirent *dp;
	int i;
	getargs();
	if(arg1[0]==0)
		strcpy(arg1,".");
	if((dir_fdesc=opendir(arg1))==NULL)
		printf("\n\a\a\aKERROR:DIRECTORY DOES NOT EXIST");
	else
	{
		printf("\nNO.\tNAME");
		for(i=1;(dp=readdir(dir_fdesc))!=NULL;i++)
		{
			printf("\n%d.\t%s",i,dp->d_name);
		}
	}
	return;
}

/*FUNCTION TO LIST ALL FILES AND DIRECTORIES PAGE WISE*/
void klsp()
{
	DIR *dir_fdesc;
	struct dirent *dp;
	int i;
	getargs();
	if(arg2[0]==0)
		strcpy(arg2,".");
	if((dir_fdesc=opendir(arg2))==NULL)
		printf("\n\a\a\aKERROR:DIRECTORY DOES NOT EXIST");
	else
	{
		printf("\nNO.\tNAME");
		for(i=1;(dp=readdir(dir_fdesc))!=NULL;i++)
		{
			printf("\n%d.\t%s",i,dp->d_name);
			if(i%34==33)
			{
				printf("\nPRESS ENTER TO CONTINUE");
				getchar();
			}
		}
	}
	return;
}

	

/*FUNCTION TO CLEAR THE SCREEN*/
void kclear()
{
	system("clear");
	return;
}

/*FUNCTION TO GET PRESENT WORKING DIRECTORY*/
void kpwd()
{
	char curdir[PATH_LENGTH];
	getcwd(curdir,PATH_LENGTH);
	printf("\nPRESENT WORKING DIRECTORY: %s",curdir);
	return;
}

/*FUNCTION TO COUNT LINES,WORDS CHARACTERS*/
void kwc()
{
	int lines=0,words=0,chars=0,flag=0;
	char ch,prev;
	FILE *fp;
	getargs();
	if((fp=fopen(arg1,"r"))==NULL)
		printf("\n\a\a\aKERROR:UNABLE TO OPEN FILE");
	else
	{
		ch=fgetc(fp);
		prev=ch;
		while(ch!=EOF)
		{
			if(ch=='\n')
			{
				lines++;
				chars++;
				if(prev!='\n' && prev!=' ')words++;
			}
			else if(ch==' ' && prev!=' ' &&prev!='\n')
			{
				words++;
				chars++;
			}
			else
			{
				chars++;
			}
			prev=ch;
			ch=fgetc(fp);
			
		}
		printf("\nLINES:%d\tWORDS:%d\tCHARACTERS:%d",lines,words,chars);
	fclose(fp);
	}
	return;
}

/*FUNCTION TO DISPLAY LINES FROM BEGINNING*/
void khead()
{
	FILE *fp;
	int lines=0,i,j;
	char ch;
	getargs();
	if(arg2[0]==0)
		lines=10;	
	else
	{
		for(i=0,j=1;arg2[i]!='\0';i++,j=j*10)
		{
			lines=lines*10;
			lines=lines+arg2[i]-'0';
		}
	}	
	if((fp=fopen(arg1,"r"))==NULL)
		printf("\n\a\a\aKERROR:UNABLE TO OPEN FILE");
	else
	{
		for(i=0;i<lines && ch!=EOF;)
		{
			ch=fgetc(fp);
			printf("%c",ch);
			if(ch=='\n')
				i++;
		}
	fclose(fp);
	}	
	return;
}

/*FUNCTION TO DISPLAY LINES FROM END*/
void ktail()
{
	FILE *fp;
	int lines=0,i,j,ln=0;
	char ch;
	getargs();
	if(arg2[0]==0)
		lines=10;	
	else
	{
		for(i=0,j=1;arg2[i]!='\0';i++,j=j*10)
		{
			lines=lines*10;
			lines=lines+arg2[i]-'0';
		}
	}
	if((fp=fopen(arg1,"r"))==NULL)
		printf("\n\a\a\aKERROR:UNABLE TO OPEN FILE");
	else
	{
		ch=fgetc(fp);
		while(ch!=EOF)
		{
			if(ch=='\n')
				ln++;
			ch=fgetc(fp);
		}
		ln=ln-lines;
		if(ln<0)
		{
			printf("\nKERROR:GIVE LESS LINES");
			return;
		}
		fclose(fp);
		fp=fopen(arg1,"r");
		for(i=0;i<ln;)
		{
			ch=fgetc(fp);
			if(ch=='\n')
				i++;
		}
		ch=fgetc(fp);			
		for(i=0;i<lines && ch!=EOF;)
		{
			printf("%c",ch);
			if(ch=='\n')
				i++;
			ch=fgetc(fp);
		}

		fclose(fp);
	}	
	return;
}

/*FUNCTION FOR WHO AM I*/
void kwhoami()
{
	struct passwd *pw;
	pw=getpwuid(getuid());
        printf("\nLogin Name:%s",pw->pw_name);
        return;
}

/*FUNCTION TO DISPLAY,OS VERSION AND MACHINE*/
void kuname()
{
	struct utsname sys;
	uname(&sys);
	printf("\nOS:%s",sys.sysname);
	printf("\nOS release:%s",sys.release);
	printf("\nVersion of Release:%s",sys.version);
	printf("\nHardware Type:%s\n",sys.machine);
	return;
}

/*FUNCTION TO COPY CONTENTS OF FILE*/
void kcp()
{
	char ch;
	FILE *fp1,*fp2;
	getargs();
	if((fp1=fopen(arg1,"r"))==NULL)
		printf("\n\a\a\aKERROR:UNABLE TO OPEN SOURCE FILE");
	
	else if((fp2=fopen(arg2,"w"))==NULL)
		printf("\n\a\a\aKERROR:UNABLE TO CREATE DESTINATION FILE");
	
	else
	{
		ch=fgetc(fp1);
		while(ch!=EOF)
		{
			fputc(ch,fp2);
			ch=fgetc(fp1);
		}
	printf("\nFILE COPIED SUCCESSFULLY");
	fclose(fp1);
	fclose(fp2);
	}
	return;
}

/*FUNCTION TO CHANGE DIRECTORY*/
void kcd()
{
	char newdir[PATH_LENGTH];
	struct passwd *pw;
	char olddir[PATH_LENGTH];
	getargs();
	getcwd(olddir,PATH_LENGTH);
	printf("\nPRESENT WORKING DIRECTORY:%s",olddir);
   	if(arg1[0]=='\0')
	{
		pw=getpwuid(getuid());
		strcpy(arg1,pw->pw_dir);
	}
	if(chdir(arg1)==-1)
	{
		printf("\n\a\a\aKERROR:ERROR IN CHANGING DIRECTORY");	
		return;     		
	}
	else
	{
		printf("\nDIRECTORY CHANGED TO:%s SUCESSFULLY",arg1);
		getcwd(newdir,PATH_LENGTH);
		printf("\nPRESENT WORKING DIRECTORY:%s",newdir);
	}	
	return;
}


/*COMMAND MANUAL*/
void kman()
{
	kclear();
        strcpy(cmd," manual.kk");
	printf("%s",arg1);
	kcat();
	return;
}

/*ABOUT US*/
void kabout()
{
	kclear();
	strcpy(cmd," aboutus.kk");
	kcat();
	return;
}
