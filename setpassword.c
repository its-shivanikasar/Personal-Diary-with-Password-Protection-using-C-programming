#include<stdio.h>
#include<conio.h>

//set password by default
void setPassword()
{
	FILE *fp;
	char pass[10]="12345";
	fp=fopen("password.bin","wb");
	
	if(fp==NULL)
	{
		printf("\nError in opening file...");
		return;
	}
	else
	{
		fwrite(pass,sizeof(char),5,fp);
	}
	fclose(fp);
}

int main()
{
	setPassword();
	
	FILE *rl=NULL;
	rl=fopen("record_list.bin","wb");
	
	if(rl==NULL)
	{
	    printf("\nError while opening file");
	    return 1;
	}
	else
	{
	    fprintf(rl,"Record_name\t\tDate\t\tTime\t\tName\t\tPlace");
	    fclose(rl);
	}
	return 0;
}
