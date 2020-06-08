#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#pragma (__pack__)


char long_month[12][10] = { "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", 
                           "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };
char short_month[12][4] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", 
                             "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
int days_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 

typedef struct Friend
{
    char fname[31];
    char lname[41];
    int month;
    int day;
    int year;
    int age;
    char sex[5];
    char color[16];
} Friend_t;

int call_menu()
{
    int select;

    system("cls");
    printf("Hello! Maintain your friends:\n\n");
    printf("1.) Add a friend.\n");
    printf("2.) Delete  a friend.\n");
    printf("3.) Edit a friend.\n");
    printf("4.) View a friend.\n");
    printf("5.) View friend list.\n");
    printf("6.) Exit\n\n");

    printf("What do you want to do (Enter 1-5): ");
    scanf("%d", &select);
    while(getchar() != '\n');

    return select;

}

void get_birthday(int *month, int *day, int *year, int *age, bool is_add, bool *will_change)
{

    bool date_checker = false, not_valid = false, valid_month = false;
    char i_month[40], whole_month[30];

    i_month[0] = '\n';  

    while (!date_checker)
    {
        *day = 0, *year = 0;
        printf("Enter birthday (MM dd yyyy): ");

        if(is_add)
        {
           scanf("%s %d %d", i_month, day, year);
        }
        else
        {
            fgets(whole_month, sizeof(whole_month), stdin);
            sscanf(whole_month, "%s %d %d", i_month, day, year);
        }
        
                
//Check_year
        if (*year > 2019 || *year <= 0) { not_valid = true; } 


#pragma region Check_month

        int check_month = atoi(i_month);

        strupr(i_month);
        if(check_month == 0  && i_month[0] != '0')
        {
            
            for(int i=0; i < 12; i++)
            {
                int long_result = 0, short_result = 0;
                long_result = strcmp(long_month[i], i_month);
                short_result = strcmp(short_month[i], i_month);

                if (long_result == 0 || short_result == 0)
                {
                    *month = i + 1;
                    valid_month = true;
                    break;
                }
            
            }

            if (!valid_month) {not_valid = true;}
        }
        else
        {

            if (check_month > 0 && check_month < 13 && strlen(i_month) < 3)
            {
                *month = check_month;
            }
            else
            {
                not_valid = true;
            }
            
        }
        
#pragma endregion Check_month

#pragma region Check_day

        if (*month == 2)
        { 

            int local_year = year;

            if (local_year % 4 == 0)
            {   
              if (local_year % 100 == 0)
              {
                 if (local_year % 400 == 0 && *day > 29)
                 {
                     not_valid = true;
                 }
              }
              else if (*day > 29)
              {
                not_valid = true;
              }
            
            }
        }
        else if (*month < 13 && *month > 0)
        {
            if (*day > days_month[*month-1])
            {
                not_valid = true;
            }
        }
        else if (*month > 12)
        {
            not_valid = true;
        }    

#pragma endregion Check_day

        if (!not_valid)
        {
            date_checker = true;

            //Compute age
            int current_month = 0, current_year = 2019;
            time_t now;
            time(&now);

            struct tm *local = localtime(&now);

            current_month = local->tm_mon + 1;

            if (*month > current_month) { current_year = current_year - 1; } 

            *age = current_year - *year; 

            if(!is_add){*will_change = true;}

        }
        else
        {
            
           if(!is_add && i_month[0] == '\n')
           {
               *will_change = false;
                date_checker = true;
           }
           else
           {
                printf("Invalid date, try again.\n");
                //_getch();
           }
           
           
        }
        
        not_valid = false;
               
    }

}

int add_friend(char *file_name, int *tail)
{

    bool end_add = false, sex = false;
    char fname_enter[31], lname_enter[41], sex_enter[3], color_enter[16], add_another[10];
    int month_enter, day_enter, year_enter, age_enter;
                   
    while (!end_add)
    {
        system("cls");
        printf("Add a friend:\n\n");

        printf("Enter first name(30 characters): ");
        scanf("%30s", fname_enter);

        printf("Enter last name(40 characters): ");
        scanf("%40s", lname_enter);

        //Enter birthday
        get_birthday(&month_enter, &day_enter, &year_enter, &age_enter, true, false);
        
        //Enter sex
        while(!sex)
        {
            
            printf("Enter sex (M/F): ");
            scanf("%s", sex_enter);
            while(getchar() != '\n');
            strupr(sex_enter);
            
            int result = 1, result2 = 1;
            result = strcmp(sex_enter, "M");
            result2 = strcmp(sex_enter, "F");
            
            if (result == 0 || result2 == 0)
            {
                sex = true;
            }
            else
            { 
                printf("Invalid sex, please try again.\n");
                sex = false;
            }
            
        }

        sex = false;
        printf("Favourite color(15 characters): ");
        fgets(color_enter, 15, stdin);

        int len = strlen(color_enter);
        if(color_enter[len-1] == '\n' && len > 1){color_enter[len-1] = 0;}

        strupr(fname_enter);
        strupr(lname_enter);
        strupr(color_enter);

        FILE *fileptr = fopen(file_name, "a");
        char buffer[1000] = "\0";

        char month_buffer[33];
        char day_buffer[33];
        char year_buffer[33];
        char age_buffer[33];

        itoa(month_enter, month_buffer, 10);
        itoa(day_enter, day_buffer, 10);
        itoa(year_enter, year_buffer, 10);
        itoa(age_enter, age_buffer, 10);

        if(*tail > 0){strcat(buffer, "\n");}
        strcat(buffer, lname_enter);
        strcat(buffer, " ");
        strcat(buffer, fname_enter);
        strcat(buffer, "\t");
        strcat(buffer, month_buffer);
        strcat(buffer, " ");
        strcat(buffer, day_buffer);
        strcat(buffer, " ");
        strcat(buffer, year_buffer);
        strcat(buffer, "\t");
        strcat(buffer, age_buffer);
        strcat(buffer, "\t");
        strcat(buffer, sex_enter);
        strcat(buffer, "\t");
        strcat(buffer, color_enter);

        fputs(buffer, fileptr);

        fileptr = freopen(file_name, "r", fileptr);
    
        fclose(fileptr);

        *tail = *tail + 1;
        printf("\nDo you want to add another (Y/N)?");

        scanf("%s", add_another);
        while(getchar() != '\n');
        strupr(add_another);

        if (strcmp(add_another, "Y") != 0)
        {
            end_add = true;
        }
        
    }
}

int delete_friend(char *file_name, int *tail)
{

    bool end_delete = false, result = false;
    char fname[31], lname[41], sex[10], color[16], age[10], del_another[3];
    char fname_enter[31], lname_enter[41], sex_enter[10], color_enter[16];
    int month_enter, day_enter, year_enter, age_enter;
    
    while (!end_delete)
    {
        system("cls");
        printf("Delete a friend:\n");
        printf("Leave an entry blank for a filter to disregarded.\n\n");

        printf("Enter first name: ");
        fgets(fname, 31, stdin);
        printf("Enter last name: ");
        fgets(lname, 41, stdin);

        printf("Enter age: ");
        fgets(age, 10, stdin);

        printf("Enter sex: ");
        fgets(sex, 10, stdin);

        printf("Enter favorite color: ");
        fgets(color, 16, stdin);

        strupr(fname);
        strupr(lname);
        strupr(sex);
        strupr(color);

        int check_age = atoi(age);
        int index = 0;
        result = false; 
        FILE *fileptr = fopen(file_name, "r");

        if (fname[0] == '\n' && lname[0] == '\n' &&
            age[0] == '\n' && sex[0] == '\n' && color[0] == '\n')
        {
            result = false;
        }
        else
        {
            
            int len = 0, fname_result = 0, lname_result = 0, sex_result = 0, color_result;

            len = strlen(fname);
            if(fname[len-1] == '\n' && len > 1){fname[len-1] = 0;}
            len = strlen(lname);
            if(lname[len-1] == '\n' && len > 1){lname[len-1] = 0;}
            len = strlen(sex);
            if(sex[len-1] == '\n' && len > 1){sex[len-1] = 0;}
            len = strlen(color);
            if(color[len-1] == '\n' && len > 1){color[len-1] = 0;}
            
            char line[200] = "\0";
            
            while (fgets(line, sizeof(line), fileptr) != NULL)
            {
                
                sscanf(line, "%s %s\t%d %d %d\t%d\t%s\t%[^\n]s",
                              lname_enter, fname_enter, &month_enter, &day_enter, &year_enter,
                              &age_enter, sex_enter, color_enter);

                fname_result = strcmp(fname_enter, fname);
                lname_result = strcmp(lname_enter, lname);
                sex_result = strcmp(sex_enter, sex);
                color_result = strcmp(color_enter, color);

                index++;
                
                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (age_enter == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n')
                  )
                {
                    result = true;
                    break;

                }
            }

        }
           
        rewind(fileptr);  

        if (result)
        {
            //fclose(fileptr);
            //fileptr = open(file_name, "r", fileptr);

            FILE *tempFile = fopen("delete-line.tmp", "w");
            char buffer[1000];
            int count = 1;

            while(fgets(buffer, 1000, fileptr) != NULL)
            {
                if(index != count)
                {
                    fputs(buffer, tempFile);
                }
                count++;
            }

            fclose(fileptr);
            fclose(tempFile);

            remove(file_name);
            rename("delete-line.tmp", file_name);
            
            *tail = *tail - 1;

            printf("\nRecord deleted.\n");
            
        }
        else
        {
            fclose(fileptr);
            printf("No record found with filters.\n");
        }
        
        printf("\nDo you want to delete another (Y/N)?");

        scanf("%s", del_another);
        while(getchar() != '\n');
        strupr(del_another);

        if (strcmp(del_another, "Y") == 0)
        {
            if (*tail == 0)
            {
                printf("No more records to delete.\n");
                getch();

                end_delete = true;
            }
        }
        else
        {
            end_delete = true;
        }

    }
}

int modify_friend(char *file_name, int *tail)
{
    bool end_inquire = false, result = false, will_change = false, valid_sex = false;
    char fname[31], lname[41], sex[10], color[16], age[10], inq_another[3];
    int index = 0, month, day, year, i_age;
    char fname_enter[31], lname_enter[41], sex_enter[10], color_enter[16];
    int month_enter, day_enter, year_enter, age_enter;
    
    while (!end_inquire)
    {
        system("cls");
        printf("Modify a friend:\n");
        printf("Leave an entry blank for a filter to disregarded.\n\n");

        printf("Enter first name: ");
        fgets(fname, 31, stdin);

        printf("Enter last name: ");
        fgets(lname, 41, stdin);

        printf("Enter age: ");
        fgets(age, 10, stdin);

        printf("Enter sex: ");
        fgets(sex, 10, stdin);

        printf("Enter favorite color: ");
        fgets(color, 16, stdin);

        strupr(fname);
        strupr(lname);
        strupr(sex);
        strupr(color);

        int check_age = atoi(age);
        result = false; 
        
        FILE *fileptr = fopen(file_name, "r");

        if (fname[0] == '\n' && lname[0] == '\n' &&
            age[0] == '\n' && sex[0] == '\n' && color[0] == '\n')
        {
            result = false;
        }
        else
        {
            
            int len = 0, fname_result = 0, lname_result = 0, sex_result = 0, color_result;

            len = strlen(fname);
            if(fname[len-1] == '\n' && len > 1){fname[len-1] = 0;}
            len = strlen(lname);
            if(lname[len-1] == '\n' && len > 1){lname[len-1] = 0;}
            len = strlen(sex);
            if(sex[len-1] == '\n' && len > 1){sex[len-1] = 0;}
            len = strlen(color);
            if(color[len-1] == '\n' && len > 1){color[len-1] = 0;}

            char line[200] = "\0";
            index = 0;

            while (fgets(line, sizeof(line), fileptr) != NULL)
            {
                
                sscanf(line, "%s %s\t%d %d %d\t%d\t%s\t%[^\n]s",
                              lname_enter, fname_enter, &month_enter, &day_enter, &year_enter,
                              &age_enter, sex_enter, color_enter);

                fname_result = strcmp(fname_enter, fname);
                lname_result = strcmp(lname_enter, lname);
                sex_result = strcmp(sex_enter, sex);
                color_result = strcmp(color_enter, color);

                index++;
                
                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (age_enter == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n')
                  )
                {
                    result = true;
                    break;
                }
            }
 
        }

        rewind(fileptr);

        if (result)
        {
            printf("\nRecord found:\n");
            
            printf("\nFirst name: %s\n", fname_enter);
            printf("Last name: %s\n", lname_enter);
            printf("Month: %d\n", month_enter);
            printf("Day: %d\n", day_enter);
            printf("Year: %d\n", year_enter);
            printf("Age: %d\n", age_enter);
            printf("Sex: %s\n", sex_enter);
            printf("Color: %s\n\n", color_enter);

            printf("\nLeave an entry blank to disregard edit of the cell:\n");

            printf("Enter first name: ");
            fgets(fname, 31, stdin);

            printf("Enter last name: ");
            fgets(lname, 41, stdin);

            get_birthday(&month, &day, &year, &i_age, false, &will_change);

            valid_sex = false;
            while(!valid_sex)
            {
                
                printf("Enter sex: ");
                fgets(sex, 10, stdin);
                strupr(sex);
                
                int result = 1, result2 = 1, len = strlen(sex);
                if(sex[len-1] == '\n' && len > 1){sex[len-1] = 0;}
                result = strcmp(sex, "M");
                result2 = strcmp(sex, "F");
                
                if (result == 0 || result2 == 0)
                {
                    valid_sex = true;
                }
                else if (sex[0] == '\n')
                {
                    valid_sex = true;
                }          
                else
                { 
                    printf("Invalid sex, please try again.\n");
                    valid_sex = false;
                }
                
            }

            printf("Enter favorite color: ");
            fgets(color, 16, stdin);

            strupr(fname);
            strupr(lname);
            strupr(sex);
            strupr(color);

            int len = 0;

            len = strlen(fname);
            if(fname[len-1] == '\n' && len > 1){fname[len-1] = 0;}
            len = strlen(lname);
            if(lname[len-1] == '\n' && len > 1){lname[len-1] = 0;}
            len = strlen(sex);
            if(sex[len-1] == '\n' && len > 1){sex[len-1] = 0;}
            len = strlen(color);
            if(color[len-1] == '\n' && len > 1){color[len-1] = 0;}

            FILE *tempFile = fopen("delete-line.tmp", "w");
            char buffer[1000] = "\0", line_insert[1000];
            int count = 1;

            char month_buffer[33];
            char day_buffer[33];
            char year_buffer[33];
            char age_buffer[33];

            if (will_change)
            {
                itoa(month, month_buffer, 10);
                itoa(day, day_buffer, 10);
                itoa(year, year_buffer, 10);
                itoa(i_age, age_buffer, 10);
            }
            else
            {
                itoa(month_enter, month_buffer, 10);
                itoa(day_enter, day_buffer, 10);
                itoa(year_enter, year_buffer, 10);
                itoa(age_enter, age_buffer, 10);
            }
            if(lname[0] != '\n'){strcat(buffer, lname);} else{strcat(buffer,lname_enter);}
            strcat(buffer, " ");
            if(fname[0] != '\n'){strcat(buffer, fname);} else{strcat(buffer,fname_enter);}
            strcat(buffer, "\t");
            strcat(buffer, month_buffer);
            strcat(buffer, " ");
            strcat(buffer, day_buffer);
            strcat(buffer, " ");
            strcat(buffer, year_buffer);
            strcat(buffer, "\t");
            strcat(buffer, age_buffer);
            strcat(buffer, "\t");
            if(sex[0] != '\n'){strcat(buffer, sex);} else{strcat(buffer,sex_enter);}
            strcat(buffer, "\t");
            if(color[0] != '\n'){strcat(buffer, color);} else{strcat(buffer,color_enter);}
            if(index < *tail){strcat(buffer, "\n");}

            while(fgets(line_insert, 1000, fileptr) != NULL)
            {
                if(index != count)
                {
                    fputs(line_insert, tempFile);
                }
                else
                {
                    fputs(buffer, tempFile);
                }
                
                count++;
            }

            fclose(fileptr);
            fclose(tempFile);

            remove(file_name);
            rename("delete-line.tmp", file_name);

            printf("\nRecord successfully modified.\n\n");

        }
        else
        {
            fclose(fileptr);
            printf("No record found with filters.\n");
        }
        
        printf("\nDo you want to modify again (Y/N)?");

        scanf("%s", inq_another);
        while(getchar() != '\n');
        strupr(inq_another);

        if (strcmp(inq_another, "Y") == 0)
        {
            end_inquire = false;
        }
        else
        {
            end_inquire = true;
        }
    }


}

int inquire_friend(char *file_name, int *tail)
{
    bool end_inquire = false, result = false;
    char fname[31], lname[41], sex[10], color[16], age[10], inq_another[3];
    char fname_enter[31], lname_enter[41], sex_enter[10], color_enter[16];
    int month_enter, day_enter, year_enter, age_enter;
    int index = 0;
    
    while (!end_inquire)
    {
        system("cls");
        printf("Inquire a friend:\n");
        printf("Leave an entry blank for a filter to disregarded.\n\n");

        printf("Enter first name: ");
        fgets(fname, 31, stdin);
        printf("Enter last name: ");
        fgets(lname, 41, stdin);

        printf("Enter age: ");
        fgets(age, 10, stdin);

        printf("Enter sex: ");
        fgets(sex, 10, stdin);

        printf("Enter favorite color: ");
        fgets(color, 16, stdin);

        strupr(fname);
        strupr(lname);
        strupr(sex);
        strupr(color);

        int check_age = atoi(age);
        result = false; 

        FILE *fileptr = fopen(file_name, "r");

        if (fname[0] == '\n' && lname[0] == '\n' &&
            age[0] == '\n' && sex[0] == '\n' && color[0] == '\n')
        {
            result = false;
        }
        else
        {
            
            int len = 0, fname_result = 0, lname_result = 0, sex_result = 0, color_result;

            len = strlen(fname);
            if(fname[len-1] == '\n' && len > 1){fname[len-1] = 0;}
            len = strlen(lname);
            if(lname[len-1] == '\n' && len > 1){lname[len-1] = 0;}
            len = strlen(sex);
            if(sex[len-1] == '\n' && len > 1){sex[len-1] = 0;}
            len = strlen(color);
            if(color[len-1] == '\n' && len > 1){color[len-1] = 0;}

            char line[200] = "\0";
            index = 0;
            
            while (fgets(line, sizeof(line), fileptr) != NULL)
            {
                
                sscanf(line, "%s %s\t%d %d %d\t%d\t%s\t%[^\n]s",
                              lname_enter, fname_enter, &month_enter, &day_enter, &year_enter,
                              &age_enter, sex_enter, color_enter);

                fname_result = strcmp(fname_enter, fname);
                lname_result = strcmp(lname_enter, lname);
                sex_result = strcmp(sex_enter, sex);
                color_result = strcmp(color_enter, color);

                index++;

                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (age_enter == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n')
                  )
                {
                    result = true;
                            
                    printf("\nRecord found:\n");
                    
                    printf("\nIndex: %d\n", index);
                    printf("First name: %s\n", fname_enter);
                    printf("Last name: %s\n", lname_enter);
                    printf("Month: %d\n", month_enter);
                    printf("Day: %d\n", day_enter);
                    printf("Year: %d\n", year_enter);
                    printf("Age: %d\n", age_enter);
                    printf("Sex: %s\n", sex_enter);
                    printf("Color: %s\n\n", color_enter);

                    break;
                }

            }
 
        }

        if (!result)
        {
            printf("No record found with filters.\n");
        }
        
        fclose(fileptr);

        printf("\nDo you want to inquire again (Y/N)?");

        scanf("%s", inq_another);
        while(getchar() != '\n');
        strupr(inq_another);

        if (strcmp(inq_another, "Y") == 0)
        {
            end_inquire = false;
        }
        else
        {
            end_inquire = true;
        }
    }
}

int print_friend(char *file_name, int tail)
{                
    int  index = 1;
    char line[256];
                   
    FILE *fileptr = fopen(file_name, "r");

    system("cls");
    printf("List of friends:\n\n");

    while(fgets(line, sizeof(line), fileptr) != NULL) 
    {
        printf("%d %s", index, line);
        index++;
    }

    fclose(fileptr);

    printf("\n\nPress any key to return to menu.");
    _getch();
}

int sort_list(char *file_name, int tail)
{
    
    Friend_t friends[tail];

    int month_temp, day_temp, year_temp, age_temp, index = 0;
    char line[1000];
    char fname_temp[31];
    char lname_temp[41];
    char sex_temp[5];
    char color_temp[16];
    
    char fname_enter[31], lname_enter[41], sex_enter[3], color_enter[16];
    int month_enter, day_enter, year_enter, age_enter;

    FILE *fileptr = fopen(file_name, "r");

    while (fgets(line, sizeof(line), fileptr) != NULL)
    {
                
        sscanf(line, "%s %s\t%d %d %d\t%d\t%s\t%[^\n]s",
               lname_enter, fname_enter, &month_enter, &day_enter, &year_enter,
              &age_enter, sex_enter, color_enter);

        strcpy(friends[index].lname, lname_enter);
        strcpy(friends[index].fname, fname_enter);
        strcpy(friends[index].sex, sex_enter);
        strcpy(friends[index].color, color_enter);
        friends[index].month = month_enter;
        friends[index].day = day_enter;
        friends[index].year = year_enter;
        friends[index].age = age_enter;

        index++;
    }

    for (int j=0; j < tail-1; j++) 
    { 
        for (int i=j+1; i < tail; i++) 
        { 
            if (strcmp(friends[j].fname, friends[i].fname) > 0) 
            { 
                //Put to temp variable
                strcpy(lname_temp, friends[j].lname);
                strcpy(fname_temp, friends[j].fname); 
                strcpy(sex_temp, friends[j].sex);
                strcpy(color_temp, friends[j].color); 
                month_temp = friends[j].month;
                day_temp = friends[j].day;
                year_temp = friends[j].year;
                age_temp = friends[j].age;

                //Replace value
                strcpy(friends[j].lname, friends[i].lname);
                strcpy(friends[j].fname, friends[i].fname); 
                strcpy(friends[j].sex, friends[i].sex); 
                strcpy(friends[j].color, friends[i].color);  
                friends[j].age = friends[i].age;
                friends[j].month = friends[i].month;
                friends[j].day = friends[i].day;
                friends[j].year = friends[i].year;

                //Move temp variable
                strcpy(friends[i].lname, lname_temp); 
                strcpy(friends[i].fname, fname_temp); 
                strcpy(friends[i].sex, sex_temp); 
                strcpy(friends[i].color, color_temp);
                friends[i].age = age_temp;
                friends[i].month = month_temp;
                friends[i].day = day_temp;
                friends[i].year = year_temp; 
            } 
        } 
    } 
 
 
    for (int j=0; j < tail-1; j++) 
    { 
        for (int i=j+1; i < tail; i++) 
        { 
            if (strcmp(friends[j].lname, friends[i].lname) > 0) 
            { 
                //Put to temp variable
                strcpy(lname_temp, friends[j].lname);
                strcpy(fname_temp, friends[j].fname); 
                strcpy(sex_temp, friends[j].sex);
                strcpy(color_temp, friends[j].color); 
                month_temp = friends[j].month;
                day_temp = friends[j].day;
                year_temp = friends[j].year;
                age_temp = friends[j].age;

                //Replace value
                strcpy(friends[j].lname, friends[i].lname);
                strcpy(friends[j].fname, friends[i].fname); 
                strcpy(friends[j].sex, friends[i].sex); 
                strcpy(friends[j].color, friends[i].color);  
                friends[j].age = friends[i].age;
                friends[j].month = friends[i].month;
                friends[j].day = friends[i].day;
                friends[j].year = friends[i].year;

                //Move temp variable
                strcpy(friends[i].lname, lname_temp); 
                strcpy(friends[i].fname, fname_temp); 
                strcpy(friends[i].sex, sex_temp); 
                strcpy(friends[i].color, color_temp);
                friends[i].age = age_temp;
                friends[i].month = month_temp;
                friends[i].day = day_temp;
                friends[i].year = year_temp; 

            }
            else if (strcmp(friends[j].lname, friends[i].lname) == 0 &&  strcmp(friends[j].fname, friends[i].fname) > 0) 
            {
                //Put to temp variable
                strcpy(lname_temp, friends[j].lname);
                strcpy(fname_temp, friends[j].fname); 
                strcpy(sex_temp, friends[j].sex);
                strcpy(color_temp, friends[j].color); 
                month_temp = friends[j].month;
                day_temp = friends[j].day;
                year_temp = friends[j].year;
                age_temp = friends[j].age;

                //Replace value
                strcpy(friends[j].lname, friends[i].lname);
                strcpy(friends[j].fname, friends[i].fname); 
                strcpy(friends[j].sex, friends[i].sex); 
                strcpy(friends[j].color, friends[i].color);  
                friends[j].age = friends[i].age;
                friends[j].month = friends[i].month;
                friends[j].day = friends[i].day;
                friends[j].year = friends[i].year;

                //Move temp variable
                strcpy(friends[i].lname, lname_temp); 
                strcpy(friends[i].fname, fname_temp); 
                strcpy(friends[i].sex, sex_temp); 
                strcpy(friends[i].color, color_temp);
                friends[i].age = age_temp;
                friends[i].month = month_temp;
                friends[i].day = day_temp;
                friends[i].year = year_temp; 
            }
            
        } 
        
    } 

    fclose(fileptr);

    FILE *fileptr2 = fopen("Text.tmp", "w");

    char month_buffer[33];
    char day_buffer[33];
    char year_buffer[33];
    char age_buffer[33];      

        for(int i = 0; i < tail; i++)
    {

        char buffer[1000] = "\0";

        itoa(friends[i].month, month_buffer, 10);
        itoa(friends[i].day, day_buffer, 10);
        itoa(friends[i].year, year_buffer, 10);
        itoa(friends[i].age, age_buffer, 10);

        if (i > 0){strcat(buffer, "\n");}
        strcat(buffer, friends[i].lname);
        strcat(buffer, " ");
        strcat(buffer, friends[i].fname);
        strcat(buffer, "\t");
        strcat(buffer, month_buffer);
        strcat(buffer, " ");
        strcat(buffer, day_buffer);
        strcat(buffer, " ");
        strcat(buffer, year_buffer);
        strcat(buffer, "\t");
        strcat(buffer, age_buffer);
        strcat(buffer, "\t");
        strcat(buffer, friends[i].sex);
        strcat(buffer, "\t");
        strcat(buffer, friends[i].color);

        fputs(buffer, fileptr2);
        
    }
    
    fclose(fileptr2);

    remove(file_name);
    rename("Text.tmp", file_name);

}

int main()
{
    FILE *fileptr;
    char file_name[] = "Text File.txt";
    bool test = false;
    bool leave = false;
    int tail = 0, triedCreating = 0;

    OPEN:
    fileptr = fopen(file_name, "r+");

    if (!fileptr)
    {
        // try to create the file
        if (!triedCreating)
        {
            triedCreating = 1;
            fclose(fopen("Text File.txt", "w"));
            goto OPEN;
        }
        fprintf(stderr, "Error opening file %i. Message: %s", errno, strerror(errno));
        _getch();
        exit(EXIT_FAILURE);
    }
    else
    {
        char chr;
        chr = getc(fileptr);
        while (chr != EOF)
        {
            if(chr == '\n'){tail = tail + 1;}
            chr = getc(fileptr);
        }
        tail = tail + 1;

    }
    
    fclose(fileptr);

    while (!leave)
    {

        int select = call_menu();

        if (select == 6)
        {
            leave = true;
        }
        else
        {
            if (select == 1)
            {
                add_friend(file_name, &tail);
                if(tail > 1){sort_list(file_name, tail);};
                         
            }
            else if (select == 2)
            {

                if (tail == 0)
                {
                    printf("No entries to delete.");
                    _getch();
                }
                else
                {
                    delete_friend(file_name, &tail);
                }
            
            }
            else if (select == 3)
            {
                if (tail == 0)
                {
                    printf("No entries to edit.");
                    _getch();
                }
                else
                {
                    modify_friend(file_name, &tail);
                    if(tail > 1){sort_list(file_name, tail);};
                }
            }
            else if (select == 4)
            {
                if (tail == 0)
                {
                    printf("No entries to view.");
                    _getch();
                }
                else
                {
                    inquire_friend(file_name, &tail);
                }
            }
            else if (select == 5)
            {
                if (tail == 0)
                {
                    printf("No records to display.");
                    _getch();
                }
                else
                {
                    if(tail > 1){sort_list(file_name, tail);};
                    print_friend(file_name, tail);
                }
            }
            else
            {
                printf("Invalid selection, press any key to try again.\n");
                getch();
            }
            

        }
       

    }

    fclose(fileptr);
    exit(0);
    
}
