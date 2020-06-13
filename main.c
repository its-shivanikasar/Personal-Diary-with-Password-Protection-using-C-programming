/*----------------------------------------------------------------------------------------------------------------------------
                Name                  : Shivani Sanjay Kasar
                Code                  : C Miniproject
                Details               : Personal Diary With Password Protection
                Operations Performed  : 1) Can change password
                                        2) Add record
                                        3) View record (by record_name / date / time / Author's name / place / All records)
                                        4) Delete record (by record_name / date / time / Author's name / place)
                                        5) Modify record (by record_name / date / time / Author's name / place)
----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------
                                                Header Files
----------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------------------------------------------------------
                                                Global definitions
----------------------------------------------------------------------------------------------------------------------------*/

char date[10],tim[10],name[20],place[20],note[50],f_name[20];

/*----------------------------------------------------------------------------------------------------------------------------
                                                    Function Declarations
----------------------------------------------------------------------------------------------------------------------------*/

void initialize();

void validatePassword();

void editPassword();

void addRecord();

void viewRecord();

void deleteRecord();

void modifyRecord();

/*----------------------------------------------------------------------------------------------------------------------------
                                                        Main Method
----------------------------------------------------------------------------------------------------------------------------*/

int main()
{
    int ch;
	
	//if entered password is matched then only it will get access
	validatePassword();
		
    printf("\n------------------------------------------------------------------------------\n");
    printf("\t\tPersonal Diary with password protection by SK");
    printf("\n------------------------------------------------------------------------------\n");

    do
    {
		//main menu
        printf("\nMain Menu : \n");
        printf("1.Add Record\n");
        printf("2.View Record\n");
        printf("3.Modify Record\n");
        printf("4.Delete Record\n");
        printf("5.Change Password\n");
        printf("6.Exit\n");

        printf("\nEnter your choice : ");
        scanf("%d",&ch);

        switch(ch)
        {
			case 1:		addRecord();
						break;
						
			case 2:		viewRecord();
						break;
						
			case 3:		modifyRecord();
						break;
						
			case 4:		deleteRecord();
						break;
						
			case 5:		editPassword();
						break;
						
			case 6: 	//exit from diary
			            printf("\n\n\t\tThankyou for using Personal Diary!!! \t Visit Again! ");
						
						getch();
						exit(0);
						
			default:	printf("\nInvalid choice...");
			
        }		
    }while(1);
	
    return 0;
}

/*----------------------------------------------------------------------------------------------------------------------------
                                    function to initilize all global variables to NULL
----------------------------------------------------------------------------------------------------------------------------*/

void initialize()
{
    
    strcpy(f_name,"NULL");
    strcpy(date,"NULL");
    strcpy(tim,"NULL");
    strcpy(name,"NULL");
    strcpy(place,"NULL");
    strcpy(note,"NULL");
}

/*----------------------------------------------------------------------------------------------------------------------------
                                                function to validate password
----------------------------------------------------------------------------------------------------------------------------*/

void validatePassword()
{
	int count=1,flag=0;
	char password[18],pass[10];
	FILE *fp=NULL;
	
	//read password from file
	fp=fopen("password.bin","rb");
	fread(pass,sizeof(char),5,fp);
	fclose(fp);
	
	do
	{
		flag=0;
		
		//accept password from user
		printf("\nEnter password to open Personal Diary : ");
		scanf("%s",password);
		
		if(strcmp(password,pass)!=0)
		{
			printf("\nWrong Password !!!\t\t remaining trials %d\n",(3-(count++)));	//only 3 trials are available
			flag=1;
		}
		if(count==4)
		{
			printf("\nSorry...");
			getch();
			exit(0);
		}
	}while(flag);
}


/*----------------------------------------------------------------------------------------------------------------------------
                                                function to add record in a file
----------------------------------------------------------------------------------------------------------------------------*/

void addRecord( )
{
	char fname[20],temp[20];
	FILE *fp=NULL,*RL=NULL;

    //accept file name
	printf("\nEnter Record name : ");
	fflush(stdin);
	scanf("%s",fname);
	
	//open it
	fp=fopen(fname,"ab");
	RL=fopen("record_list.bin","ab");
	
	if(fp==NULL || RL==NULL)
	{
	    printf("\n----------------------------------------------------\n");
		printf("\nError in opening file...");
		printf("\n----------------------------------------------------\n");
		return;
	}
	else
	{
	    //accept details
	    
	    fprintf(RL,"%s\t\t\t",fname);
	    
	    printf("\n---------------------------------------------------\n");
	    printf("\t\tAccepting details of record\n\n");
	    
		printf("\nEnter date : ");
		fflush(stdin);
		scanf("%s",date);
		fprintf(RL,"%s\t",date);
	
		printf("\nEnter time : ");
		scanf("%s",tim);
		fprintf(RL,"%s\t\t",tim);
		
		printf("\nEnter name : ");
		scanf("%s",name);
		fprintf(RL,"%s\t\t\t",name);
		
		printf("\nEnter place : ");
		scanf("%s",place);
		fprintf(RL,"%s\n",place);
		
		int flag=1;
		strcpy(note," ");
		
		printf("\nEnter note (enter 'end' to exit) : ");
		do
		{
		        fflush(stdin);
    		    scanf("%s",note);
    		    
    		    if(strcmp(note,"end")!=0)
    		    {
    		        fprintf(fp,"%s ",note);
    		    }
    		    else
    		        flag=0;
    		
		}while(flag);

        printf("\n---------------------------------------------------\n");
        printf("\nRecord inserted successfully !!!");
        printf("\n---------------------------------------------------\n\n");
        
		fclose(fp);
		fclose(RL);
	}
}
        
/*----------------------------------------------------------------------------------------------------------------------------
                                            function to View record from file
----------------------------------------------------------------------------------------------------------------------------*/

void viewRecord()
{
    int ch;
	char temp[20];
	FILE *fp=NULL;
	FILE *rl=NULL;

    initialize();
    
        //view menu
		printf("\n\nView Record by : 1) Record_name  2) Date  3) Time  4) Author's_name  5) Place  6) All records  7) Exit\n");
		printf("\nEnter your choice : ");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
					{
						//accept file name
						printf("\nEnter Record name : ");
						scanf("%s",temp);
				        
				        rl=fopen("record_list.bin","rb");
    
                        if(rl==NULL)
                        {
                            printf("\nError while opening file");
                            return;
                        }
                        else
                        {
                            //read from file
    				        fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);
    						while(!feof(rl))
    						{	
    							if(strcmp(f_name,temp)==0)  //find record name from record_list
    							    break;
    							fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);
    						}
    						
    						if(feof(rl))    //reach end of file
    						{
    						    initialize();
    						    printf("\n----------------------------------------------------\n");
		                        printf("\nRecord not exits...\n");
		                        printf("\n----------------------------------------------------\n");
    						}
    						fclose(rl);
    						break;
                        }
					}
		   case 2:
					{
						printf("\nEnter date : ");
						scanf("%s",temp);
						
						rl=fopen("record_list.bin","rb");
    
                        if(rl==NULL)
                        {
                            printf("\nError while opening file");
                            return;
                        }
                        else
                        {
    						fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);
    						while(!feof(rl))
    						{
    							if(strcmp(date,temp)==0)
    								break;
    							fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);		  
    						}
    						if(feof(rl))
    						{
    						    initialize();
    						    printf("\n----------------------------------------------------\n");
		                        printf("\nRecord not exits...\n");
		                        printf("\n----------------------------------------------------\n");
    						}
    						fclose(rl);
    						break;
                        }
					}
		   case 3:
					{
						printf("\nEnter time : ");
						scanf("%s",temp);
						
						rl=fopen("record_list.bin","rb");
    
                        if(rl==NULL)
                        {
                            printf("\nError while opening file");
                            return;
                        }
                        else
                        {
    						fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);
    						while(!feof(rl))
    						{
    							if(strcmp(tim,temp)==0)
    								break;
    							fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);		  
    						}
    						if(feof(rl))
    						{
    						    initialize();
    						    printf("\n----------------------------------------------------\n");
		                        printf("\nRecord not exits...\n");
		                        printf("\n----------------------------------------------------\n");
    						}
    						fclose(rl);
    						break;
                        }
					}
		   case 4:
					{
						printf("\nEnter author's name : ");
						scanf("%s",temp);
						
						rl=fopen("record_list.bin","rb");
    
                        if(rl==NULL)
                        {
                            printf("\nError while opening file");
                            return;
                        }
                        else
                        {
    						fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);
    						while(!feof(rl))
    						{
    							if(strcmp(name,temp)==0)
    								break;
    							fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);		  
    						}
    						
    						if(feof(rl))
    						{
    						    initialize();
    						    printf("\n----------------------------------------------------\n");
		                        printf("\nRecord not exits...\n");
		                        printf("\n----------------------------------------------------\n");
    						}
    						fclose(rl);
    						break;
                        }
					}
		   case 5:
					{
						printf("\nEnter place : ");
						scanf("%s",temp);
						
						rl=fopen("record_list.bin","rb");
    
                        if(rl==NULL)
                        {
                            printf("\nError while opening file");
                            return;
                        }
                        else
                        {
    						fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);
    						while(!feof(rl))
    						{
    							if(strcmp(place,temp)==0)
    								break;
    						    fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);			  
    						}
    						
    						if(feof(rl))
    						{
    						    initialize();
    						    printf("\n----------------------------------------------------\n");
		                        printf("\nRecord not exits...\n");
		                        printf("\n----------------------------------------------------\n");
    						}
    						fclose(rl);
    						break;
                        }
					}
					
			case 6: {
						rl=fopen("record_list.bin","rb");
    
                        if(rl==NULL)
                        {
                            printf("\nError while opening file");
                            return;
                        }
                        else
                        {
                            printf("\n----------------------------------------------------\n");
		                    printf("\nRecord_name\tDate\tTime\tAuthor's_name\tPlace\n");
		                    printf("\n----------------------------------------------------\n");
		                        
    						fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);
    						fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);
    						while(!feof(rl))
    						{
                                printf("%s \t %s \t %s \t %s \t %s\n",f_name,date,tim,name,place);
                        		
    						    fscanf(rl,"%s%s%s%s%s",f_name,date,tim,name,place);			  
    						}
    						
    						if(feof(rl))
    						{
    						    initialize();
    						}
    						fclose(rl);
    						break;
                        }
					}
			case 7:
			        return;
		    default:
					printf("\nInvalid choice");
		}
	
	if(strcmp(f_name,"NULL")!=0)    //if record exits
	{
    	//open it
    	fp=fopen(f_name,"r");
    	
    	if(fp==NULL)
    	{
    	    printf("\n----------------------------------------------------\n");
    		printf("\nError in opening file...\n");
    		printf("\n----------------------------------------------------\n");
    		return;
    	}
    	else
    	{
    	    //print details
    		printf("\n---------------------------------------------------\n");
    		
    		printf("Record name : %s\n",f_name);
    		printf("Record date : %s\n",date);
    		printf("Record time : %s\n",tim);
    		printf("Author name : %s\n",name);
    		printf("Record place : %s\n",place);
    		
    		printf("Record note : ");
    		while(fscanf(fp,"%s ",note)==1)
    		    printf("%s ",note);
    		    
    		printf("\n----------------------------------------------------\n");
    		fclose(fp);
    	}
	}
}

/*----------------------------------------------------------------------------------------------------------------------------
                                                function to delete record
----------------------------------------------------------------------------------------------------------------------------*/

void deleteRecord()
{
    int ch;
	char temp[20];
	FILE *fp=NULL,*temp1=NULL;
	
	//delete menu
	printf("\n\nDelete Record by : 1) Record_name  2) Date  3) Time  4) Author's_name  5) Place  6) Exit\n");
	printf("\nEnter your choice : ");
	scanf("%d",&ch);
	
	switch(ch)
	{
	    case 1:
	            {
	                //accept file name
                	printf("\nEnter Record name to be delete : ");
                	scanf("%s",temp);
                	
                	fp=fopen("record_list.bin","rb");
                    temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
                        //read record details from record_list file
            	        fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        
                        while(!feof(fp))
                        {
                            if(strcmp(temp,f_name)!=0) //write record to temp file except record to be delete
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                //delete record
                                if(remove(f_name))   //returns '0' on succcess 
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\tRecord is not deleted\n");
                                    printf("\n----------------------------------------------------\n");
                                }
                                else
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\t%s record deleted successfully...\n",f_name);
                                    printf("\n----------------------------------------------------\n");
                                }    
                            }
                            
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        if(feof(fp))
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
	                break;
	            }
	   case 2:
	            {
	                printf("\nEnter date of record which is to be delete : ");
	                scanf("%s",temp);
	                
	                fp=fopen("record_list.bin","rb");
                    temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
            	        fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        while(!feof(fp))
                        {
                            if(strcmp(temp,date)!=0)
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                if(remove(f_name))   //returns '0' on succcess 
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\tRecord is not deleted\n");
                                    printf("\n----------------------------------------------------\n");
                                }
                                else
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\t%s record deleted successfully...\n",f_name);
                                    printf("\n----------------------------------------------------\n");
                                }    
                            }
                            
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        if(feof(fp))
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
	                break;
	            }
	   case 3:
	            {
	                printf("\nEnter time of record which is to be delete : ");
	                scanf("%s",temp);
	                
	                fp=fopen("record_list.bin","rb");
                    temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
            	        fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        while(!feof(fp))
                        {
                            if(strcmp(temp,tim)!=0)
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                if(remove(f_name))   //returns '0' on succcess 
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\tRecord is not deleted\n");
                                    printf("\n----------------------------------------------------\n");
                                }
                                else
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\t%s record deleted successfully...\n",f_name);
                                    printf("\n----------------------------------------------------\n");
                                }    
                            }
                            
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        
                        if(feof(fp))
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
	                break;
	            }
	   case 4:
	            {
	                printf("\nEnter author's name of record to be delete : ");
	                scanf("%s",temp);
	                
	                fp=fopen("record_list.bin","rb");
                    temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
            	        fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        while(!feof(fp))
                        {
                            if(strcmp(temp,name)!=0)
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                if(remove(f_name))   //returns '0' on succcess 
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\tRecord is not deleted\n");
                                    printf("\n----------------------------------------------------\n");
                                }
                                else
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\t%s record deleted successfully...\n",f_name);
                                    printf("\n----------------------------------------------------\n");
                                }    
                            }
                            
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        if(feof(fp))
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
	                break;
	            }
	   case 5:
	            {
	                printf("\nEnter place of record to be delete : ");
	                scanf("%s",temp);
	                
	                fp=fopen("record_list.bin","rb");
                    temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
            	        fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        while(!feof(fp))
                        {
                            if(strcmp(temp,place)!=0)
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                if(remove(f_name))   //returns '0' on succcess 
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\tRecord is not deleted\n");
                                    printf("\n----------------------------------------------------\n");
                                }
                                else
                                {
                                    printf("\n----------------------------------------------------\n");
                                    printf("\n\t\t%s record deleted successfully...\n",f_name);
                                    printf("\n----------------------------------------------------\n");
                                }    
                            }
                            
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        if(feof(fp))
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
	                break;
	            }
	   case 6:
	            return;
	   default:
	            printf("\nInvalid choice");
	}
	
	//if all records are written into temp file except record to be delete successfully then
	if(strcmp(f_name,"NULL")==0)
	{
	    remove("record_list.bin");
	    rename("temp.bin","record_list.bin");
	}
}

/*----------------------------------------------------------------------------------------------------------------------------
                                            function to modify record in a file
----------------------------------------------------------------------------------------------------------------------------*/

void modifyRecord( )
{
    int ch,flag=0;
	char temp[20],fname[20];
	FILE *fp=NULL,*temp1=NULL;
    
    //accept record name to be modify
    printf("\nEnter record name to be modify : ");
    scanf("%s",fname);

    //modify menu        	
    printf("\n\nModify Record by : 1) Record_name  2) Date  3) Time  4) Author's_name  5) Place  6) Exit\n");
    printf("\nEnter your choice : ");
    scanf("%d",&ch);
        	
    switch(ch)
    {
        case 1:
                {
                    
                    //accept file name
                    printf("\nEnter new record name : ");
                    scanf("%s",temp);
                        	
                    fp=fopen("record_list.bin","rb");
                    temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
                        flag=0;
                        
                        //read from record_list file
                    	fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);

                    	while(!feof(fp))
                        {
                            if(strcmp(fname,f_name)!=0) //write records to temp file except record to be modify
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                flag=1;
                                
                                //change record file name
                                rename(f_name,temp);
                                
                                //write modified record into temp file
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",temp,date,tim,name,place);
                            }            
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        
                        if(feof(fp))    //reach end of file
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
                    break;
        	    }
        case 2:
                {
        	       printf("\nEnter new date : ");
        	       scanf("%s",temp);
        	                
        	       fp=fopen("record_list.bin","rb");
                   temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
                        flag=0;
                        
            	        fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        while(!feof(fp))
                        {
                            if(strcmp(fname,f_name)!=0)
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                flag=1;
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,temp,tim,name,place);
                            }    
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        if(feof(fp))
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
                    break;
        	   }
        case 3:
        	   {
        	        printf("\nEnter new time : ");
        	        scanf("%s",temp);
        	                
        	        fp=fopen("record_list.bin","rb");
                    temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
                        flag=0;
                        
            	        fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        while(!feof(fp))
                        {
                            if(strcmp(fname,f_name)!=0)
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                flag=1;
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,temp,name,place);
                            }    
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        if(feof(fp))
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
                    break;
        	    }
        case 4:
        	   {
        	        printf("\nEnter new author's name : ");
        	        scanf("%s",temp);
        	                
        	        fp=fopen("record_list.bin","rb");
                    temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
                        flag=0;
                        
            	        fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        while(!feof(fp))
                        {
                            if(strcmp(fname,f_name)!=0)
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                flag=1;
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,temp,place);
                            }    
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        if(feof(fp))
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
                    break;
        	   }
        case 5:
        	   {
        	       printf("\nEnter new place : ");
        	       scanf("%s",temp);
        	                
        	        fp=fopen("record_list.bin","rb");
                    temp1=fopen("temp.bin","ab");
                        
                    if(fp==NULL || temp1==NULL)
                    {
                        printf("\nError in opening file");
                        return;
                    }
                    else
                    {
                        flag=0;
                        
            	        fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        while(!feof(fp))
                        {
                            if(strcmp(fname,f_name)!=0)
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,place);
                            else
                            {
                                flag=1;
                                fprintf(temp1,"%s\t\t%s\t\t%s\t\t%s\t\t%s\n",f_name,date,tim,name,temp);
                            }
                            fscanf(fp,"%s%s%s%s%s",f_name,date,tim,name,place);
                        }
                        if(feof(fp))
    					{
    					    initialize();
    					}
                        fclose(fp);
                        fclose(temp1);
                    }
                    break;
        	   }
        case 6:
                return;
        default:
        	    printf("\nInvalid choice");
    }
    
    if(flag==1)
    {
        remove("record_list.bin");
        rename("temp.bin","record_list.bin");
    
        printf("\n----------------------------------------------------\n");
        printf("\n\t\t%s record modified successfully...\n",fname);
        printf("\n----------------------------------------------------\n");
    }
    else
    {
        printf("\n----------------------------------------------------\n");
        printf("\n\t\tRecord does not exits...\n");
        printf("\n----------------------------------------------------\n");
    }
}

/*----------------------------------------------------------------------------------------------------------------------------
                                            function to change password of diary
----------------------------------------------------------------------------------------------------------------------------*/

void editPassword()
{
	char password[20],rpassword[20];
	int flag=0;
	FILE *fp=NULL;
	
	//accept new password
	printf("\nEnter new password : ");
	scanf("%s",password);
	
	//check for new password
	do
	{
		printf("\nRe-enter new password : ");
		scanf("%s",rpassword);
		
		flag=0;
		
		if(strcmp(password,rpassword)!=0)
		{
			printf("\nPasswords are not match !!!\n\n");
			flag=1;
		}
	}while(flag);
	
	printf("\n---------------------------------------------------\n");
	printf("\n\n\t\tPassword is changed successfully !!!\n\n");
	printf("\n---------------------------------------------------\n");
	
	//write new password to file
	fp=fopen("password.bin","wb");
	fwrite(password,sizeof(char),strlen(password),fp);
	fclose(fp);
}

/*----------------------------------------------------------------------------------------------------------------------------
                                                End of Program
----------------------------------------------------------------------------------------------------------------------------*/
