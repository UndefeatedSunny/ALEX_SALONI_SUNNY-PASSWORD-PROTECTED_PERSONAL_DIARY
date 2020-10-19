#include<stdio.h>                               // Adding Libraries.
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define ll long long int

struct record                                   // Declare a Structure used to strore or write Data.
{
    char date[15];
    char day[10];
    char time[10];
    char note[500];
};


int password()
{
    char pass[15]={0};                          // For taking i/p (password) from User for verification Purpose.
    char check[15]={0};                         // For fetching Original Password From the password File Store in the Disk.
    char ch;
    int j=0,i=0;

    printf("\t\tPLEASE! ENTER THE PASSWORD\n\n");
    printf("\t\tONLY 3 CHANCES WILL BE GIVEN\n");

    for(i=0;i<=2;i++)                           // Loop Run 3 Times(Maximum).
    {
        j=0;
        printf("\n\n\nEnter the Password-> ");

        pass[0]=getch();                        // Main purpose is to Check, There is no Carriage Return (Enter) will be given by the user.
        while(pass[j]!='\r')                    // Checking Carriage Return.
        {
            if(pass[j]=='\b')                   // -->> Removes the Problem of removal of (*) from Screen while Typing the Password and enter backspace, then now with that the (*) all removed.
            {
                j--;
                printf("\b");                   // Backspace(For moving one Step Back).
                printf(" ");                    // Replace the * with Blank Space.
                printf("\b");                   // Then again, move One Step Back, & now we can move further (PROBLEM SOLVED).
                pass[j]=getch();                // Most Impotant Concept -->> To take cursor one step back and ready to take continious Input.
            }
            else
            {
                printf("*");                    // Shows like that we Enter Password on the Screen in the HIDDEN format i.e (*) Format.
                j++;
                pass[j]=getch();                // Storing Pasword from User Side For Comparision Purpose.
            }
        }
        pass[j]='\0';                           // Adding NULL at the Last helps to Check Termination point of the CHARACTER ARRAY i.e. (String).

        FILE *fp;                               // file pointer to the password file.
        fp = fopen("password","r");             // Opening in the Read Mode.
        if(fp==NULL)                            // Checking the presence of password File.
        {
            printf(" [FILE MISSING]");
            getch();
            return 1;
        }
        else
        {
            j=0;
            while(1)
            {
                ch=fgetc(fp);                   // Taking i/p Character by Character.
                if(ch==EOF)
                {
                    check[j]='\0';              // Adding NULL at the Last helps to Check Termination point of the CHARACTER ARRAY i.e. (String).
                    break;
                }
                check[j]=ch-5;                  // Decrypting Technique.
                j++;
            }
        }
        if(strcmp(pass,check)==0)               // Compare the User Password with Original Password.
        {
            printf("\n\t\t\tACCESS GRANTED \n");
            return 0;
        }
        else
        {
            printf("\n\t\t\tWRONG PASSWORD \n");
        }
        fclose(fp);                             // Close the password file.
    }
    printf("YOU ARE NOT ALLOWED TO ENTER");
    getch();
    return 1;
}




void edit_password()
{
    system("cls");

    char pass[15]={0}, verify[15]={0};
    char ch;
    int match,i=0,choice;

    printf("\n\n");
    FILE *fp;                                                       // File Pointer to password file.
    fp=fopen("password","rb");                                      // Read Binary Mode
    if(fp==NULL)
    {
        fp=fopen("password","wb");
        if(fp==NULL)                                                // Write Binary Mode
        {
            printf("SYSTEM ISSUE -_-");
            getch();
            return ;
        }
        fclose(fp);
        printf("\nYOUR PASSWORD IS 'ENTER'\n PRESS ENTER TO CHANGE PASSWORD\n\n");
        getch();
    }
    fclose(fp);
    match=password();                                               // PROCESS is SAME as PASSWORD , instead only we take confirmation Step in the end to rewrite the PASSWORD (Verification Purpose).
    if(match==1)
    {
        return;
    }
    do
    {
        if(match==0)
        {
            printf("\nEnter the NEW password -> ");                 // If matches ENTER the NEW PASSWORD.
            fflush(stdin);
            pass[0]=getch();
            while(pass[i]!='\r')
            {
                if(pass[i]=='\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    pass[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    pass[i]=getch();
                }
            }
            pass[i]='\0';
            i=0;
            printf("\nConfirm Password -> ");
            verify[0]=getch();
            while(verify[i]!='\r')
            {
                if(verify[i]=='\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    verify[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    verify[i]=getch();
                }
            }
            verify[i]='\0';                                         // ADDing NULL Character in the END.
            if(strcmp(pass,verify)==0)
            {
                fp=fopen("password","wb");
                if(fp==NULL)
                {
                    printf("SYSTEM ERROR -_-");
                    getch();
                    return;
                }
                i=0;
                while(pass[i]!='\0')
                {
                    ch=pass[i];
                    putc(ch+5,fp);
                    i++;
                }
                putc(EOF,fp);
                fclose(fp);
            }
            else
            {
                printf("\nWRONG PASSWORD");
                choice=1;
            }
        }
    }
    while(choice==1);
    printf("\n\n\t\tPassword Changed (-_-)");
    getch();
}

void add_record()
{
    system("cls");                                                  // For Clearing Console.
    if(password()!=0)                                               // Password Protection. (-_-)
    {
        return;
    }
    char enter='Y';
    int choice;
    FILE *fp;
    struct record add;
    char date[15];                                                  // For Creating Filename (Name is SAME as Date).
    char time[15];                                                  // Whether Note already Exists or not (Based on Time).
    printf("\n\n\t\t\t***************************\n");
    printf("\t\t\t* WELCOME TO THE ADD MENU *");
    printf("\n\t\t\t***************************\n\n");
    printf("\n\n\t\tENTER DATE OF YOUR RECORD:[yyyy-mm-dd]: ");
    fflush(stdin);
    gets(date);
    fp=fopen(date,"ab+");                                           // Append Data + ((Read + Write) Permissions), only if file is present.
    if(fp==NULL)                                                    // Means File is NOT Present.
    {
        fp=fopen(date,"wb+");                                       // Creation of FILE if not present on that DATE.
        if(fp==NULL)
        {
            printf("\nSYSTEM ERROR -_-");
            printf("\nEnter any KEY to exit");
            getch();
            return;
        }
    }
    while(enter=='Y'||enter=='y')
    {
        choice=0;
        fflush(stdin);
        printf("\n\t\tENTER TIME:[hh:mm]: ");
        scanf("%s",time);
        rewind(fp);                                                 // Back pointer to the Initial Position For READ Data.
        while(fread(&add,sizeof(add),1,fp)==1)
        {
            if(strcmp(add.time,time)==0)                            // Whether Note already Exists or not ? (Based on Time).
            {
                printf("\n Already Exists");
                choice=1;
            }
        }
        if(choice==0)
        {
            strcpy(add.time,time);                                  // Taking Input from user for all fields like Date, Day, Time, Note.
            printf("\n\t\tEnter the Date: ");
            fflush(stdin);
            gets(add.date);
            fflush(stdin);
            printf("\n\t\tEnter the Day: ");
            gets(add.day);
            fflush(stdin);
            printf("\n\t\tStart Type the NOTE: ");
            gets(add.note);
            fwrite(&add, sizeof(add),1,fp) ;
            printf("\n\t\tYOUR RECORD IS ADDED...\n");
        }
        printf("\n\t ADD another NOTE .... (Y/N) ");
        fflush(stdin);
        enter=getch();                                              // Checking whether user wanted another note on same day.
    }
    fclose(fp);
    printf("Enter any KEY to Exit");
    getch();

}



void view_record()
{
    system("cls");
    FILE *fp;
    struct record owner;
    char date_verif[15];
    char time[10];
    int option;
    char choice;
    printf("\n\n\t\t*******************************\n");
    printf("\t\t* HERE IS THE VIEWING MENU *");
    printf("\n\t\t*******************************\n\n");
    if(password()!=0)
    {
        return;
    }

    do                                                                              // RUN 1 time minimum (Thats what we need for Verification Purpose).
    {
        printf("\n\t\tENTER THE DATE OF RECORD TO BE VIEWED:[yyyy-mm-dd]: ");
        fflush(stdin);
        gets(date_verif);

        fp=fopen(date_verif,"rb");
        if(fp==NULL)                                                                // Checking Whether Record is Present or NOT.
        {
            printf("THE RECORD NOT EXISTS -_-\nPlease Enter any KEY to EXIT\n");
            getch();
            return;
        }
        system("cls");
        printf("\n\tPLEASE CHOOSE THE VIEW TYPE (-_-):\n");
        printf("\n\t1.RECORD OF WHOLE DAY.");
        printf("\n\t2.RECORD OF PARTICULAR TIME.");
        printf("\n\n\tPLEASE ENTER YOUR CHOICE: ");
        scanf("%d",&option);

        switch(option)                                                              // Whether the user wanted the Whole Day Record or Particular Time.
        {
            case 1:
                printf("\n\tRECORD OF WHOLE DAY [%s] IS -->> \n",date_verif);       // WHOLE DAY RECORD.
                while(fread(&owner,sizeof(owner),1,fp)==1)
                {
                    printf("\nDATE : %s",owner.date);
                    printf("\nTIME : %s",owner.time);
                    printf("\nDAY  : %s",owner.day);
                    printf("\nNOTE : %s",owner.note);
                    printf("\n");
                }
                break;

            case 2:                                                                 // PARTICULAR TIME RECORD.
                fflush(stdin);
                printf("\nENTER TIME:[hh:mm]:");
                gets(time);
                while(fread(&owner,sizeof(owner),1,fp)==1)
                {
                    if(strcmp(time,owner.time)==0)
                    {
                        printf("\nHERE IS YOUR RECORD SIR (-_-)");
                        printf("\nDATE : %s",owner.date);
                        printf("\nTIME : %s",owner.time);
                        printf("\nDAY  : %s",owner.day);
                        printf("\nNOTE : %s",owner.note);
                        printf("\n");
                    }
                }
                break;

            default:
                printf("\nPLEASE ENTER THE CORRECTION OPTION");
                break;
        }
        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING...(Y/N):");
        fflush(stdin);
        scanf("%c",&choice);
    }
    while(choice=='Y'||choice=='y');

    fclose(fp);
    return;

}


void delete_record()
{
    system("cls");
    FILE *fp;
    FILE *fptemp;
    struct record info;
    char date[15],time[15],another='Y';
    int option;
    printf("\n\n\t\t\t*************************\n");
    printf("\t\t\t* WELCOME TO DELETE MENU*");
    printf("\n\t\t\t*************************\n\n");
    if(password()!=0)
    {
        return;
    }

    while(another=='Y' || another=='y')                                                 // Continious Asking from user, wanted another record to delete or not.
    {
        printf("\n\n\tPLEASE SELECT ANY METHOD FOR DELETION.");
        printf("\n\n\t{1} DELETE WHOLE RECORD\t\t\t[1]");
        printf("\n\n\t{2} DELETE A PARTICULAR RECORD BY TIME\t[2]");

        do
        {
            printf("\n \t\t\t\t\t\tENTER THE OPTION : ");                               // Providing 2 Options whether he want to delete whole Day record or Particular Timing.
            scanf("%d",&option);

            switch(option)
            {
                case 1:
                    printf("\n\t\t\t\t\t\tENTER THE DATE OF RECORD TO BE DELETED [yyyy-mm-dd] : ");
                    fflush(stdin);
                    gets(date);
                    fp=fopen(date,"wb");
                    if(fp==NULL)                                                        // Is fine present or not , if not create it.
                    {
                        printf("\n\t\t\tFILE NOT EXISTS");
                        printf("ENTER ANY KEY TO EXIT");
                        getch();
                        return;
                    }
                    fclose(fp);
                    remove(date);                                                       // Remove/Delete the file from the System.
                    printf("\n\t\t\t\t\tFILE DELETED SUCCESSFULLY.... (-_-)\n");
                    break;

                case 2:
                    printf("\n\t\t\t\t\t\tENTER THE DATE OF RECORD TO BE DELETED [yyyy-mm-dd] : ");
                    fflush(stdin);
                    gets(date);
                    fp=fopen(date,"rb");
                    if(fp==NULL)                                                        // Is fine present or not ?
                    {
                        printf("\n\t\t\tFILE NOT EXISTS");
                        printf("ENTER ANY KEY TO EXIT");
                        getch();
                        return;
                    }

                    fptemp=fopen("temp","wb");                                          // Temporary File Creation, for copying data from the original file, wat we need not to delete.
                    if(fptemp==NULL)
                    {
                        printf("\n\t\t\tSYSTEM ERROR (-_-)");
                        printf("ENTER ANY KEY TO EXIT");
                        getch();
                        return;
                    }

                    printf("\n\t\t\t\t\t\tENTER THE TIME OF RECORD TO BE DELETED:[hh:mm]:");
                    fflush(stdin);
                    gets(time);

                    while(fread(&info,sizeof(info),1,fp)==1)
                    {
                        if(strcmp(time,info.time)!=0)
                        {
                            fwrite(&info,sizeof(info),1,fptemp);                        // Copy data from the original file to the Temporary File.
                        }
                    }
                    fclose(fptemp);
                    fclose(fp);
                    remove(date);
                    rename("temp",date);                                                // Rename the Temporary file to Original file and Delete the original File.
                    printf("\n\t\t\t\tFILE DELETED SUCCESSFULLY.... (-_-)");
                    break;

                default:
                    printf("\n\t\t\tPLEASE! ENTER THE CORRECT OPTION ");
                    break;
            }
        }
        while(option<1||option>2);

        printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD.(Y/N):");
        fflush(stdin);
        scanf("%c",&another);
    }
    printf("\n\n\tPRESS ANY KEY TO EXIT...");
    getch();
}

int main()
{
    int option;
    printf("\n\n\t\t\t#########################################################");      // For Design Purpose Only.
    printf("\n\t\t\t#\t\t\t\t\t\t\t#\n\t\t\t# \t   PASSWORD PROTECTED PERSONAL DIARY\t\t#");
    printf("\n\t\t\t#\t\t\t\t\t\t\t#\t\t\t\t\t\t\t# \t       (ALEX_SALONI_SUNNY) \t\t\t#\n\t\t\t#\t\t\t\t\t\t\t#\n");
    printf("\t\t\t#########################################################");

    while(1)
    {
        printf("\n\n\n\t\t\t{ MAIN MENU }\t    { OPTIONS }");
        printf("\n\n\t\t\tADD RECORD\t\t[1]");
        printf("\n\t\t\tVIEW RECORD\t\t[2]");
        printf("\n\t\t\tDELETE RECORD\t\t[3]");
        printf("\n\t\t\tEDIT PASSWORD\t\t[4]");
        printf("\n\t\t\tEXIT\t\t\t[5]");
        printf("\n\n\t\t\tPlease! Enter the Option: ");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
                add_record();                                                       // Add Record in the Diary.
                break;
            case 2:
                view_record();                                                      // View the Record (Based on Day and Timing).
                break;
            case 3:
                delete_record();                                                    // Delete the Record (Based on Day and Timing).
                break;
            case 4:
                edit_password();                                                    // PASSWORD Change.
                break;
            case 5:
                printf("\n\t\t\tTHANK YOU\t [-_-]\n");                              // Closing the application.
                getch();
                return 0;
                break;
        }
        system("cls");
    }
    return 0;
}
