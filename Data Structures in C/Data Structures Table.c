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

int add_friend(Friend_t friends[], int *tail, int *array_size)
{
    bool end_add = false, sex = false;
    int month, day, year, age;
    char add_another[10];

    while (!end_add)
    {
        system("cls");
        printf("Add a friend:\n\n");

        printf("Enter first name(30 characters): ");
        scanf("%30s", friends[*tail].fname);

        printf("Enter last name(40 characters): ");
        scanf("%40s", friends[*tail].lname);

        //Enter birthday
        get_birthday(&friends[*tail].month, &friends[*tail].day, &friends[*tail].year, &friends[*tail].age, true, false);
        
        //Enter sex
        while(!sex)
        {
            
            printf("Enter sex (M/F): ");
            scanf("%s", friends[*tail].sex);
            while(getchar() != '\n');
            strupr(friends[*tail].sex);
            
            int result = 1, result2 = 1;
            result = strcmp(friends[*tail].sex, "M");
            result2 = strcmp(friends[*tail].sex, "F");
            
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
        //scanf("%s", color[*tail]);
        fgets(friends[*tail].color, 15, stdin);

        int len = strlen(friends[*tail].color);
        if(friends[*tail].color[len-1] == '\n' && len > 1){friends[*tail].color[len-1] = 0;}

        strupr(friends[*tail].fname);
        strupr(friends[*tail].lname);
        strupr(friends[*tail].color);

        *tail = *tail + 1;

        printf("\nDo you want to add another (Y/N)?");

        scanf("%s", add_another);
        while(getchar() != '\n');
        strupr(add_another);

        if (strcmp(add_another, "Y") == 0)
        {
            if (*tail == *array_size)
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

    sort_list(friends, *tail);

}

int delete_friend(Friend_t friends[], int *tail, int *array_size)
{

    bool end_delete = false, result = false;
    char fname[31], lname[41], sex[10], color[16], age[10], del_another[3];
    int index = 0;
    
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
        result = false; 

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

            for (int i = 0; i <= *tail - 1; i++)
            {
                fname_result = strcmp(friends[i].fname, fname);
                lname_result = strcmp(friends[i].lname, lname);
                sex_result = strcmp(friends[i].sex, sex);
                color_result = strcmp(friends[i].color, color);

                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (friends[i].age == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n')
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
                strcpy(friends[c].fname, friends[c+1].fname);
                strcpy(friends[c].lname, friends[c+1].lname);
                strcpy(friends[c].sex, friends[c+1].sex);
                strcpy(friends[c].color, friends[c+1].color);
                friends[c].month = friends[c+1].month;
                friends[c].day = friends[c+1].day;
                friends[c].year = friends[c+1].year;
                friends[c].age = friends[c+1].age;
            }   

            *friends[*tail-1].fname = NULL;
            *friends[*tail-1].lname = NULL;
            friends[*tail-1].age = NULL;
            friends[*tail-1].month = NULL;
            friends[*tail-1].day = NULL;
            friends[*tail-1].year = NULL;
            *friends[*tail-1].color = NULL;
            *friends[*tail-1].sex = NULL;

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

int modify_friend(Friend_t friends[], int *tail)
{
    bool end_inquire = false, result = false, will_change = false, valid_sex = false;
    char fname[31], lname[41], sex[10], color[16], age[10], inq_another[3];
    int index = 0, month, day, year, i_age;
    
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

            for (int i = 0; i <= *tail - 1; i++)
            {
                fname_result = strcmp(friends[i].fname, fname);
                lname_result = strcmp(friends[i].lname, lname);
                sex_result = strcmp(friends[i].sex, sex);
                color_result = strcmp(friends[i].color, color);

                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (friends[i].age == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n')
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
            
            printf("\nFirst name: %s\n", friends[index].fname);
            printf("Last name: %s\n", friends[index].lname);
            printf("Month: %d\n", friends[index].month);
            printf("Day: %d\n", friends[index].day);
            printf("Year: %d\n", friends[index].year);
            printf("Age: %d\n", friends[index].age);
            printf("Sex: %s\n", friends[index].sex);
            printf("Color: %s\n\n", friends[index].color);

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

            int len = 0, fname_result = 0, lname_result = 0, sex_result = 0, color_result;

            len = strlen(fname);
            if(fname[len-1] == '\n' && len > 1){fname[len-1] = 0;}
            len = strlen(lname);
            if(lname[len-1] == '\n' && len > 1){lname[len-1] = 0;}
            len = strlen(sex);
            if(sex[len-1] == '\n' && len > 1){sex[len-1] = 0;}
            len = strlen(color);
            if(color[len-1] == '\n' && len > 1){color[len-1] = 0;}

            if(fname[0] != '\n'){strcpy(friends[index].fname, fname);}
            if(lname[0] != '\n'){strcpy(friends[index].lname, lname);}
            if(sex[0] != '\n'){strcpy(friends[index].sex, sex);}
            if(color[0] != '\n'){strcpy(friends[index].color, color);}

            if (will_change)
            {
                friends[index].month = month;
                friends[index].day = day;
                friends[index].year = year;
                friends[index].age = i_age;
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

    sort_list(friends, *tail);

}

int inquire_friend(Friend_t friends[], int *tail)
{
    bool end_inquire = false, result = false;
    char fname[31], lname[41], sex[10], color[16], age[10], inq_another[3];
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

            for (int i = 0; i <= *tail - 1; i++)
            {
                fname_result = strcmp(friends[i].fname, fname);
                lname_result = strcmp(friends[i].lname, lname);
                sex_result = strcmp(friends[i].sex, sex);
                color_result = strcmp(friends[i].color, color);

                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (friends[i].age == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n')
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
            printf("First name: %s\n", friends[index].fname);
            printf("Last name: %s\n", friends[index].lname);
            printf("Month: %d\n", friends[index].month);
            printf("Day: %d\n", friends[index].day);
            printf("Year: %d\n", friends[index].year);
            printf("Age: %d\n", friends[index].age);
            printf("Sex: %s\n", friends[index].sex);
            printf("Color: %s\n\n", friends[index].color);

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

int print_friend(Friend_t friends[], int tail)
{
                    int max_lname = strlen("Last name:"), max_fname = strlen("First name:"), max_color = strlen("Color:");
                    for(int i = 0; i < tail - 1; i++)
                    {
                      if (strlen(friends[i].lname) > max_lname){max_lname = strlen(friends[i].lname);}
                      if (strlen(friends[i].fname) > max_fname){max_fname = strlen(friends[i].fname);}
                      if (strlen(friends[i].color) > max_color){max_color = strlen(friends[i].color);}
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

                    for(int i = 0; i < tail; i++)
                    {                      
                        char index_buffer[33];
                        char month_buffer[33];
                        char day_buffer[33];
                        char year_buffer[33];
                        char age_buffer[33];
          
                        itoa(i+1, index_buffer, 10);
                        itoa(friends[i].month, month_buffer, 10);
                        itoa(friends[i].day, day_buffer, 10);
                        itoa(friends[i].year, year_buffer, 10);
                        itoa(friends[i].age, age_buffer, 10);

                        printf("\n%.*s %.*s %.*s \t%.*s %.*s %.*s \t%.*s \t%.*s \t%s",
                                10, index_buffer,  
                                max_lname + 1, friends[i].lname, 
                                max_fname + 1, friends[i].fname, 
                                10, month_buffer, 
                                10, day_buffer, 
                                10, year_buffer, 
                                10, age_buffer, 
                                10, friends[i].sex, 
                                friends[i].color);
                    }

                    printf("\nPress any key to return to menu.");
                    _getch();
}

int sort_list(Friend_t friends[], int tail)
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


}

int main()
{
    bool test = false;
    bool leave = false;
    Friend_t friends[18300];
    int tail = 0, array_size = sizeof(friends)/sizeof(friends[0]);

    // for (int i = 0; i <=  18300-1; i++)
    // {
    //     strcpy(friends[i].fname, "GABRIEL");
    //     strcpy(friends[i].lname, "POTESTADES");
    //     strcpy(friends[i].sex, "M");
    //     strcpy(friends[i].color, "CRIMSON RED");
    //     friends[i].age = 24;
    //     friends[i].month = 8;
    //     friends[i].day = 31;
    //     friends[i].year = 1994;
    //     tail += 1;
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
                    add_friend(friends, &tail, &array_size);
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
                    delete_friend(friends, &tail, &array_size);
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
                    modify_friend(friends, &tail);
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
                    inquire_friend(friends, &tail);
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
                    print_friend(friends, tail);
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
