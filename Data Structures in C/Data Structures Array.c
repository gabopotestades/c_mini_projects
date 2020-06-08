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

const int array_size = 17000, fname_size = 31, lname_size = 41, sex_size = 5, color_size = 16;

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

int add_friend(char fname[array_size][fname_size], char lname[array_size][lname_size],
               int *month[], int *day[], int *year[],
               int *age[], char sex[array_size][sex_size], char color[array_size][color_size],
               int *tail)
{
    bool end_add = false, sex_valid = false;
    int l_month, l_day, l_year, l_age;
    char add_another[10];

    while (!end_add)
    {
        system("cls");
        printf("Add a friend:\n\n");

        printf("Enter first name(30 characters): ");
        scanf("%30s", fname[*tail]);

        printf("Enter last name(40 characters): ");
        scanf("%40s",  lname[*tail]);

        //Enter birthday
        get_birthday(&month[*tail], &day[*tail], &year[*tail], &age[*tail], true, false);
        
        //Enter sex
        while(!sex_valid)
        {
            
            printf("Enter sex (M/F): ");
            scanf("%s", sex[*tail]);
            while(getchar() != '\n');
            strupr(sex[*tail]);
            
            int result = 1, result2 = 1;
            result = strcmp(sex[*tail], "M");
            result2 = strcmp(sex[*tail], "F");
            
            if (result == 0 || result2 == 0)
            {
                sex_valid = true;
            }
            else
            { 
                printf("Invalid sex, please try again.\n");
                sex_valid = false;
            }
            
        }

        sex_valid = false;
        printf("Favourite color(15 characters): ");
        //scanf("%s", color[*tail]);
        fgets(color[*tail], 15, stdin);

        int len = strlen(color[*tail]);
        if(color[*tail][len-1] == '\n' && len > 1){color[*tail][len-1] = 0;}

        strupr(fname[*tail]);
        strupr(lname[*tail]);
        strupr(color[*tail]);

        *tail = *tail + 1;

        printf("\nDo you want to add another (Y/N)?");

        scanf("%s", add_another);
        while(getchar() != '\n');
        strupr(add_another);

        if (strcmp(add_another, "Y") == 0)
        {
            if (*tail == array_size)
            {
                printf("Reached limit of entries.\n");
                getch();

                end_add = true;
            }
        }
        else
        {
            end_add = true;
        }
        
    }

    sort_list(fname, lname, month, day, year, age, sex, color, *tail);

}

int delete_friend(char fname[array_size][fname_size], char lname[array_size][lname_size],
               int month[], int day[], int year[],
               int age[], char sex[array_size][sex_size], char color[array_size][color_size],
               int *tail)
{

    bool end_delete = false, result = false;
    char fname_enter[31], lname_enter[41], sex_enter[10], color_enter[16], age_enter[10], del_another[3];
    int index = 0;
    
    while (!end_delete)
    {
        system("cls");
        printf("Delete a friend:\n");
        printf("Leave an entry blank for a filter to disregarded.\n\n");

        printf("Enter first name: ");
        fgets(fname_enter, 31, stdin);

        printf("Enter last name: ");
        fgets(lname_enter, 41, stdin);

        printf("Enter age: ");
        fgets(age_enter, 10, stdin);

        printf("Enter sex: ");
        fgets(sex_enter, 10, stdin);

        //while (getchar() != '\n');

        printf("Enter favorite color: ");
        fgets(color_enter, 16, stdin);

        strupr(fname_enter);
        strupr(lname_enter);
        strupr(sex_enter);
        strupr(color_enter);

        int check_age = atoi(age_enter);
        result = false; 

        if (fname_enter[0] == '\n' && lname_enter[0] == '\n' &&
            age_enter[0] == '\n' && sex_enter[0] == '\n' && color_enter[0] == '\n')
        {
            result = false;
        }
        else
        {
            
            int len = 0, fname_result = 0, lname_result = 0, sex_result = 0, color_result;

            len = strlen(fname_enter);
            if(fname_enter[len-1] == '\n' && len > 1){fname_enter[len-1] = 0;}
            len = strlen(lname_enter);
            if(lname_enter[len-1] == '\n' && len > 1){lname_enter[len-1] = 0;}
            len = strlen(sex_enter);
            if(sex_enter[len-1] == '\n' && len > 1){sex_enter[len-1] = 0;}
            len = strlen(color_enter);
            if(color_enter[len-1] == '\n' && len > 1){color_enter[len-1] = 0;}

            for (int i = 0; i <= *tail - 1; i++)
            {
                fname_result = strcmp(fname[i], fname_enter);
                lname_result = strcmp(lname[i], lname_enter);
                sex_result = strcmp(sex[i], sex_enter);
                color_result = strcmp(color[i], color_enter);

                if(
                   (fname_result == 0 || fname_enter[0] == '\n') &&
                   (lname_result == 0 || lname_enter[0] == '\n') &&
                   (age[i] == check_age || age_enter[0] == '\n') &&
                   (sex_result == 0 || sex_enter[0] == '\n') &&
                   (color_result == 0 || color_enter[0] == '\n')
                  )
                {
                    result = true;
                    index = i;
                    break;
                }
            }
 
        }
             
        if (result)
        {

            for (int c = index; c < *tail - 1; c++)
            {
                strcpy(fname[c], fname[c+1]);
                strcpy(lname[c], lname[c+1]);
                strcpy(sex[c], sex[c+1]);
                strcpy(color[c], color[c+1]);
                month[c] = month[c+1];
                day[c]= day[c+1];
                year[c] = year[c+1];
                age[c] = age[c+1];
            }   

            *fname[*tail-1] = NULL;
            *lname[*tail-1] = NULL;
            age[*tail-1] = NULL;
            month[*tail-1] = NULL;
            day[*tail-1] = NULL;
            year[*tail-1] = NULL;
            *color[*tail-1] = NULL;
            *sex[*tail-1] = NULL;

            *tail = *tail - 1;

            printf("\nRecord deleted.\n");
            
        }
        else
        {
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

int modify_friend(char fname[array_size][fname_size], char lname[array_size][lname_size],
               int month[], int day[], int year[],
               int age[], char sex[array_size][sex_size], char color[array_size][color_size],
               int *tail)
{
    bool end_inquire = false, result = false, will_change = false, valid_sex = false;
    char fname_enter[31], lname_enter[41], sex_enter[10], color_enter[16], age_enter[10], inq_another[3];
    int index = 0, month_enter, day_enter, year_enter, i_age_enter;
    
    while (!end_inquire)
    {
        system("cls");
        printf("Modify a friend:\n");
        printf("Leave an entry blank for a filter to disregarded.\n\n");

        printf("Enter first name: ");
        fgets(fname_enter, 31, stdin);

        printf("Enter last name: ");
        fgets(lname_enter, 41, stdin);

        printf("Enter age: ");
        fgets(age_enter, 10, stdin);

        printf("Enter sex: ");
        fgets(sex_enter, 10, stdin);

        printf("Enter favorite color: ");
        fgets(color_enter, 16, stdin);

        strupr(fname_enter);
        strupr(lname_enter);
        strupr(sex_enter);
        strupr(color_enter);

        int check_age = atoi(age_enter);
        result = false; 

        if (fname_enter[0] == '\n' && lname_enter[0] == '\n' &&
            age_enter[0] == '\n' && sex_enter[0] == '\n' && color_enter[0] == '\n')
        {
            result = false;
        }
        else
        {
            
            int len = 0, fname_result = 0, lname_result = 0, sex_result = 0, color_result;

            len = strlen(fname_enter);
            if(fname_enter[len-1] == '\n' && len > 1){fname_enter[len-1] = 0;}
            len = strlen(lname_enter);
            if(lname_enter[len-1] == '\n' && len > 1){lname_enter[len-1] = 0;}
            len = strlen(sex_enter);
            if(sex_enter[len-1] == '\n' && len > 1){sex_enter[len-1] = 0;}
            len = strlen(color_enter);
            if(color_enter[len-1] == '\n' && len > 1){color_enter[len-1] = 0;}

            for (int i = 0; i <= *tail - 1; i++)
            {
                char color_test[16];
                strcpy(color_test, color[i]);
                fname_result = strcmp(fname[i], fname_enter);
                lname_result = strcmp(lname[i], lname_enter);
                sex_result = strcmp(sex[i], sex_enter);
                color_result = strcmp(color[i], color_enter);
            
                if(
                   (fname_result == 0 || fname_enter[0] == '\n') &&
                   (lname_result == 0 || lname_enter[0] == '\n') &&
                   (age[i] == check_age || age_enter[0] == '\n') &&
                   (sex_result == 0 || sex_enter[0] == '\n') &&
                   (color_result == 0 || color_enter[0] == '\n')
                  )
                {
                    result = true;
                    index = i;
                    break;
                }
            }
 
        }

        if (result)
        {
            printf("\nRecord found:\n");
            
            printf("\nFirst name: %s\n", fname[index]);
            printf("Last name: %s\n", lname[index]);
            printf("Month: %d\n", month[index]);
            printf("Day: %d\n", day[index]);
            printf("Year: %d\n", year[index]);
            printf("Age: %d\n", age[index]);
            printf("Sex: %s\n", sex[index]);
            printf("Color: %s\n\n", color[index]);

            printf("\nLeave an entry blank to disregard edit of the cell:\n");

            printf("Enter first name: ");
            fgets(fname_enter, 31, stdin);

            printf("Enter last name: ");
            fgets(lname_enter, 41, stdin);

            get_birthday(&month_enter, &day_enter, &year_enter, &i_age_enter, false, &will_change);

            valid_sex = false;
            while(!valid_sex)
            {
                
                printf("Enter sex: ");
                fgets(sex_enter, 10, stdin);
                strupr(sex_enter);
                
                int result = 1, result2 = 1, len = strlen(sex_enter);
                if(sex_enter[len-1] == '\n' && len > 1){sex_enter[len-1] = 0;}
                result = strcmp(sex_enter, "M");
                result2 = strcmp(sex_enter, "F");
                
                if (result == 0 || result2 == 0)
                {
                    valid_sex = true;
                }
                else if (sex_enter[0] == '\n')
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
            fgets(color_enter, 16, stdin);

            strupr(fname_enter);
            strupr(lname_enter);
            strupr(sex_enter);
            strupr(color_enter);

            int len = 0, fname_result = 0, lname_result = 0, sex_result = 0, color_result;

            len = strlen(fname_enter);
            if(fname_enter[len-1] == '\n' && len > 1){fname_enter[len-1] = 0;}
            len = strlen(lname_enter);
            if(lname_enter[len-1] == '\n' && len > 1){lname_enter[len-1] = 0;}
            len = strlen(sex_enter);
            if(sex_enter[len-1] == '\n' && len > 1){sex_enter[len-1] = 0;}
            len = strlen(color_enter);
            if(color_enter[len-1] == '\n' && len > 1){color_enter[len-1] = 0;}

            if(fname_enter[0] != '\n'){strcpy(fname[index], fname_enter);}
            if(lname_enter[0] != '\n'){strcpy(lname[index], lname_enter);}
            if(sex_enter[0] != '\n'){strcpy(sex[index], sex_enter);}
            if(color_enter[0] != '\n'){strcpy(color[index], color_enter);}

            if (will_change)
            {
                month[index] = month_enter;
                day[index] = day_enter;
                year[index] = year_enter;
                age[index] = i_age_enter;
            }
            
            printf("\nRecord successfully modified.\n\n");

        }
        else
        {
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

    sort_list(fname, lname, month, day, year, age, sex, color, *tail);

}

int inquire_friend(char fname[array_size][fname_size], char lname[array_size][lname_size],
               int month[], int day[], int year[],
               int age[], char sex[array_size][sex_size], char color[array_size][color_size],
               int *tail)
{
    bool end_inquire = false, result = false;
    char fname_enter[31], lname_enter[41], sex_enter[10], color_enter[16], age_enter[10], inq_another[10];
    int index = 0;
    
    while (!end_inquire)
    {
        system("cls");
        printf("Inquire a friend:\n");
        printf("Leave an entry blank for a filter to disregarded.\n\n");

        printf("Enter first name: ");
        fgets(fname_enter, 31, stdin);
        printf("Enter last name: ");
        fgets(lname_enter, 41, stdin);

        printf("Enter age: ");
        fgets(age_enter, 10, stdin);

        printf("Enter sex: ");
        fgets(sex_enter, 10, stdin);

        printf("Enter favorite color: ");
        fgets(color_enter, 16, stdin);

        strupr(fname_enter);
        strupr(lname_enter);
        strupr(sex_enter);
        strupr(color_enter);

        int check_age = atoi(age_enter);
        result = false; 

        if (fname_enter[0] == '\n' && lname_enter[0] == '\n' &&
            age_enter[0] == '\n' && sex_enter[0] == '\n' && color_enter[0] == '\n')
        {
            result = false;
        }
        else
        {
            
            int len = 0, fname_result = 0, lname_result = 0, sex_result = 0, color_result;

            len = strlen(fname_enter);
            if(fname_enter[len-1] == '\n' && len > 1){fname_enter[len-1] = 0;}
            len = strlen(lname_enter);
            if(lname_enter[len-1] == '\n' && len > 1){lname_enter[len-1] = 0;}
            len = strlen(sex_enter);
            if(sex_enter[len-1] == '\n' && len > 1){sex_enter[len-1] = 0;}
            len = strlen(color_enter);
            if(color_enter[len-1] == '\n' && len > 1){color_enter[len-1] = 0;}

            for (int i = 0; i <= *tail - 1; i++)
            {
                fname_result = strcmp(fname[i], fname_enter);
                lname_result = strcmp(lname[i], lname_enter);
                sex_result = strcmp(sex[i], sex_enter);
                color_result = strcmp(color[i], color_enter);

                if(
                   (fname_result == 0 || fname_enter[0] == '\n') &&
                   (lname_result == 0 || lname_enter[0] == '\n') &&
                   (age[i] == check_age || age_enter[0] == '\n') &&
                   (sex_result == 0 || sex_enter[0] == '\n') &&
                   (color_result == 0 || color_enter[0] == '\n')
                  )
                {
                    result = true;
                    index = i;
                    break;
                }
            }
 
        }

        if (result)
        {
            printf("\nRecord found:\n");
            
            printf("\nIndex: %d\n", index + 1);
            printf("First name: %s\n", fname[index]);
            printf("Last name: %s\n", lname[index]);
            printf("Month: %d\n", month[index]);
            printf("Day: %d\n", day[index]);
            printf("Year: %d\n", year[index]);
            printf("Age: %d\n", age[index]);
            printf("Sex: %s\n", sex[index]);
            printf("Color: %s\n\n", color[index]);

        }
        else
        {
            printf("No record found with filters.\n");
        }
        
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

int print_friend(char fname[array_size][fname_size], char lname[array_size][lname_size],
               int month[], int day[], int year[],
               int age[], char sex[array_size][sex_size], char color[array_size][color_size],
               int *tail)
{
                    int max_lname = strlen("Last name:"), max_fname = strlen("First name:"), max_color = strlen("Color:");
                    for(int i = 0; i < *tail - 1; i++)
                    {
                      if (strlen(lname[i]) > max_lname){max_lname = strlen(lname[i]);}
                      if (strlen(fname[i]) > max_fname){max_fname = strlen(fname[i]);}
                      if (strlen(color[i]) > max_color){max_color = strlen(color[i]);}
                    }
                                           
                    // printf("%.*s %.*s %.*s %.*s %.*s %.*s %.*s %.*s %.*s\n",
                    //         10, "Index:", 
                    //         max_lname + 1, "Last name:", 
                    //         max_fname + 1, "First name:", 
                    //         10, "Month:", 
                    //         10, "Day:", 
                    //         10, "Year:", 
                    //         10, "Age:", 
                    //         10, "Sex:", 
                    //         max_color + 1, "Color:");

                    system("cls");
                    printf("List of friends:\n");

                    for(int i = 0; i < *tail; i++)
                    {                      
                        char index_buffer[33];
                        char month_buffer[33];
                        char day_buffer[33];
                        char year_buffer[33];
                        char age_buffer[33];
          
                        itoa(i+1, index_buffer, 10);
                        itoa(month[i], month_buffer, 10);
                        itoa(day[i], day_buffer, 10);
                        itoa(year[i], year_buffer, 10);
                        itoa(age[i], age_buffer, 10);

                        printf("\n%.*s %.*s %.*s \t%.*s %.*s %.*s \t%.*s \t%.*s \t%s",
                                10, index_buffer,  
                                max_lname + 1, lname[i], 
                                max_fname + 1, fname[i], 
                                10, month_buffer, 
                                10, day_buffer, 
                                10, year_buffer, 
                                10, age_buffer, 
                                10, sex[i], 
                                color[i]);
                    }

                    printf("\nPress any key to return to menu.");
                    _getch();
}

int sort_list(char fname[array_size][fname_size], char lname[array_size][lname_size],
               int *month[], int *day[], int *year[],
               int *age[], char sex[array_size][sex_size], char color[array_size][color_size],
               int tail)
{
    char fname_temp[31];
    char lname_temp[41];
    int month_temp;
    int day_temp;
    int year_temp;
    int age_temp;
    char sex_temp[5];
    char color_temp[16];

    for (int j=0; j < tail-1; j++) 
    { 
        for (int i=j+1; i < tail; i++) 
        { 
            if (strcmp(fname[j], fname[i]) > 0) 
            { 
                //Put to temp variable
                strcpy(lname_temp, lname[j]);
                strcpy(fname_temp, fname[j]); 
                strcpy(sex_temp, sex[j]);
                strcpy(color_temp, color[j]); 
                month_temp = month[j];
                day_temp = day[j];
                year_temp = year[j];
                age_temp = age[j];

                //Replace value
                strcpy(lname[j], lname[i]);
                strcpy(fname[j], fname[i]); 
                strcpy(sex[j], sex[i]); 
                strcpy(color[j], color[i]);  
                age[j] = age[i];
                month[j] = month[i];
                day[j] = day[i];
                year[j] = year[i];

                //Move temp variable
                strcpy(lname[i], lname_temp); 
                strcpy(fname[i], fname_temp); 
                strcpy(sex[i], sex_temp); 
                strcpy(color[i], color_temp);
                age[i] = age_temp;
                month[i] = month_temp;
                day[i] = day_temp;
                year[i] = year_temp; 
            } 
        } 
    } 
 
 
    for (int j=0; j < tail-1; j++) 
    { 
        for (int i=j+1; i < tail; i++) 
        { 
            if (strcmp(lname[j], lname[i]) > 0) 
            { 
                //Put to temp variable
                strcpy(lname_temp, lname[j]);
                strcpy(fname_temp, fname[j]); 
                strcpy(sex_temp, sex[j]);
                strcpy(color_temp, color[j]); 
                month_temp = month[j];
                day_temp = day[j];
                year_temp = year[j];
                age_temp = age[j];

                //Replace value
                strcpy(lname[j], lname[i]);
                strcpy(fname[j], fname[i]); 
                strcpy(sex[j], sex[i]); 
                strcpy(color[j], color[i]);  
                age[j] = age[i];
                month[j] = month[i];
                day[j] = day[i];
                year[j] = year[i];

                //Move temp variable
                strcpy(lname[i], lname_temp); 
                strcpy(fname[i], fname_temp); 
                strcpy(sex[i], sex_temp); 
                strcpy(color[i], color_temp);
                age[i] = age_temp;
                month[i] = month_temp;
                day[i] = day_temp;
                year[i] = year_temp; 
            } 
            else if (strcmp(lname[i], lname[j]) == 0 &&  strcmp(fname[j], fname[i]) > 0) 
            { 
                //Put to temp variable
                strcpy(lname_temp, lname[j]);
                strcpy(fname_temp, fname[j]); 
                strcpy(sex_temp, sex[j]);
                strcpy(color_temp, color[j]); 
                month_temp = month[j];
                day_temp = day[j];
                year_temp = year[j];
                age_temp = age[j];

                //Replace value
                strcpy(lname[j], lname[i]);
                strcpy(fname[j], fname[i]); 
                strcpy(sex[j], sex[i]); 
                strcpy(color[j], color[i]);  
                age[j] = age[i];
                month[j] = month[i];
                day[j] = day[i];
                year[j] = year[i];

                //Move temp variable
                strcpy(lname[i], lname_temp); 
                strcpy(fname[i], fname_temp); 
                strcpy(sex[i], sex_temp); 
                strcpy(color[i], color_temp);
                age[i] = age_temp;
                month[i] = month_temp;
                day[i] = day_temp;
                year[i] = year_temp; 
            } 
            
        } 
        
    } 


}

int main()
{
    bool test = false;
    bool leave = false;
    Friend_t friends[1000];
    int tail = 0;

    char fname[array_size][fname_size];
    char lname[array_size][lname_size];
    int month[array_size];
    int day[array_size];
    int year[array_size];
    int age[array_size];
    char sex[array_size][sex_size];
    char color[array_size][color_size];

    // for (int i = 0; i <= array_size -2; i++)
    // {
    //     strcpy(fname[i], "GABRIEL");
    //     strcpy(lname[i], "POTESTADES");
    //     month[i] = 8;
    //     day[i] = 31;
    //     year[i] = 1994;
    //     age[i] = 24;
    //     strcpy(sex[i], "M");
    //     strcpy(color[i], "YELLOW");
    //     tail += 1;

    // }
            

    // if (test == true)
    // {
        
    //     _getch();
    //     exit(0);    
    // }

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
                if (tail == array_size)
                {
                    printf("Reached limit of entries.");
                    _getch();
                }
                else
                {
                    add_friend(fname, lname, month, day, year, age, sex, color, &tail);
                }              
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
                    delete_friend(fname, lname, month, day, year, age, sex, color, &tail);
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
                    modify_friend(fname, lname, month, day, year, age, sex, color, &tail);
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
                    inquire_friend(fname, lname, month, day, year, age, sex, color, &tail);
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
                    print_friend(fname, lname, month, day, year, age, sex, color, &tail);
                }
            }
            else
            {
                printf("Invalid selection, press any key to try again.\n");
                getch();
            }
            

        }
       

    }

    exit(0);
    
}
