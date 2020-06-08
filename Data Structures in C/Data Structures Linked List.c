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
    struct Friend *next;
} Friend_t;

int call_menu()
{
    int select;

    system("cls");
    printf("Hello! Maintain your friends:\n\n");
    printf("1.) Add a friend.\n");
    printf("2.) Delete a friend.\n");
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

int add_friend(Friend_t **head_ref)
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
        //scanf("%15s", color_enter);
        fgets(color_enter, 15, stdin);

        int len = strlen(color_enter);
        if(color_enter[len-1] == '\n' && len > 1){color_enter[len-1] = 0;}

        strupr(fname_enter);
        strupr(lname_enter);
        strupr(color_enter);

        //Add new node to linked list
        Friend_t *new_node = (Friend_t*) malloc(sizeof(Friend_t));
        Friend_t *last = *head_ref;

        strcpy(new_node->fname, fname_enter);
        strcpy(new_node->lname, lname_enter);
        strcpy(new_node->sex, sex_enter);
        strcpy(new_node->color, color_enter);

        new_node->month = month_enter;
        new_node->day = day_enter;
        new_node->year = year_enter;
        new_node->age = age_enter;
        new_node->next = NULL;

        if (*head_ref == NULL)
        {
            *head_ref = new_node;
        }
        else
        {
            while (last->next != NULL)
                last = last->next;

            last->next = new_node;
        }
        

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

int delete_friend(Friend_t **friends)
{

    bool end_delete = false, result = false;
    char fname[31], lname[41], sex[10], color[16], age[10], del_another[3];
    int index = 0;
    
    while (!end_delete)
    {
        Friend_t *temp = *friends, *prev;
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
 
            fname_result = strcmp(temp->fname, fname);
            lname_result = strcmp(temp->lname, lname);
            sex_result = strcmp(temp->sex, sex);
            color_result = strcmp(temp->color, color);
            
            if( 
                temp != NULL &&
                (fname_result == 0 || fname[0] == '\n') &&
                (lname_result == 0 || lname[0] == '\n') &&
                (temp->age == check_age || age[0] == '\n') &&
                (sex_result == 0 || sex[0] == '\n') &&
                (color_result == 0 || color[0] == '\n')
              )
              {
                  *friends = temp->next;
                  free(temp);
                  result = true;
              }
            else
              {
                while (temp != NULL)
                {
                    fname_result = strcmp(temp->fname, fname);
                    lname_result = strcmp(temp->lname, lname);
                    sex_result = strcmp(temp->sex, sex);
                    color_result = strcmp(temp->color, color);
                    
                    if (
                        (fname_result == 0 || fname[0] == '\n') &&
                        (lname_result == 0 || lname[0] == '\n') &&
                        (temp->age == check_age || age[0] == '\n') &&
                        (sex_result == 0 || sex[0] == '\n') &&
                        (color_result == 0 || color[0] == '\n')
                       )
                    {
                        break;
                    }
                    
                    prev = temp;
                    temp = temp->next;
                }

                if (temp != NULL)
                {
                    prev->next = temp->next;
                    free(temp);
                    result = true;
                }

              }
              
        }
    

        if (result)
        {
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
            if (*friends == NULL)
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

int modify_friend(Friend_t *friends)
{
    bool end_inquire = false, result = false, will_change = false, valid_sex = false;
    char fname[31], lname[41], sex[10], color[16], age[10], inq_another[3];
    int month, day, year, i_age;
    Friend_t *head = friends;
    
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

            while(friends != NULL)
            {
                fname_result = strcmp(friends->fname, fname);
                lname_result = strcmp(friends->lname, lname);
                sex_result = strcmp(friends->sex, sex);
                color_result = strcmp(friends->color, color);

                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (friends->age == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n')
                  )
                {
                    result = true;
                    break;
                }

                friends =  friends->next;
            }
 
        }

        if (result)
        {
            printf("\nRecord found:\n");
            
            printf("\nFirst name: %s\n", friends->fname);
            printf("Last name: %s\n", friends->lname);
            printf("Month: %d\n", friends->month);
            printf("Day: %d\n", friends->day);
            printf("Year: %d\n", friends->year);
            printf("Age: %d\n", friends->age);
            printf("Sex: %s\n", friends->sex);
            printf("Color: %s\n\n", friends->color);

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

            if(fname[0] != '\n'){strcpy(friends->fname, fname);}
            if(lname[0] != '\n'){strcpy(friends->lname, lname);}
            if(sex[0] != '\n'){strcpy(friends->sex, sex);}
            if(color[0] != '\n'){strcpy(friends->color, color);}

            if (will_change)
            {
                friends->month = month;
                friends->day = day;
                friends->year = year;
                friends->age = i_age;
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

        friends = head;
        
    }

    sort_list(friends);

}

int inquire_friend(Friend_t *friends)
{
    bool end_inquire = false, result = false;
    char fname[31], lname[41], sex[10], color[16], age[10], inq_another[3];
    Friend_t *head = friends;
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

            int i = 0;

            while (friends != NULL)
            {
                fname_result = strcmp(friends->fname, fname);
                lname_result = strcmp(friends->lname, lname);
                sex_result = strcmp(friends->sex, sex);
                color_result = strcmp(friends->color, color);

                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (friends->age == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n')
                  )
                {
                    
                    printf("\nRecord found:\n");
                    
                    printf("\nIndex: %d\n", i + 1);
                    printf("First name: %s\n", friends->fname);
                    printf("Last name: %s\n", friends->lname);
                    printf("Month: %d\n", friends->month);
                    printf("Day: %d\n", friends->day);
                    printf("Year: %d\n", friends->year);
                    printf("Age: %d\n", friends->age);
                    printf("Sex: %s\n", friends->sex);
                    printf("Color: %s\n\n", friends->color);
                    result = true;
                    break;
                }
                
                i++;
                friends = friends->next;
            }
 
        }

        if (!result)
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

        friends = head;
    }
}

int print_friend(Friend_t *friends)
{
                    Friend_t *head = friends;
                    int max_lname = strlen("Last name:"), max_fname = strlen("First name:"), max_color = strlen("Color:");
                    while(friends != NULL)
                    {
                        if (strlen(friends->lname) > max_lname){max_lname = strlen(friends->lname);}
                        if (strlen(friends->fname) > max_fname){max_fname = strlen(friends->fname);}
                        if (strlen(friends->color) > max_color){max_color = strlen(friends->color);}
                      
                        friends = friends->next;
                    }
                    friends = head;      
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
                    printf("List of friends:\n\n");

                    int i = 0;
                    while(friends != NULL)
                    {                      
                        char index_buffer[33];
                        char month_buffer[33];
                        char day_buffer[33];
                        char year_buffer[33];
                        char age_buffer[33];
          
                        itoa(i+1, index_buffer, 10);
                        itoa(friends->month, month_buffer, 10);
                        itoa(friends->day, day_buffer, 10);
                        itoa(friends->year, year_buffer, 10);
                        itoa(friends->age, age_buffer, 10);

                        printf("%.*s %.*s %.*s \t%.*s %.*s %.*s \t%.*s \t%.*s \t%.*s\n",
                                10, index_buffer,  
                                max_lname + 1, friends->lname, 
                                max_fname + 1,friends->fname, 
                                10, month_buffer, 
                                10, day_buffer, 
                                10, year_buffer, 
                                10, age_buffer, 
                                10, friends->sex, 
                                max_color + 1, friends->color);
                        
                        i++;
                        friends = friends->next;
                    }

                    printf("\nPress any key to return to menu.");
                    _getch();
}

int sort_list(Friend_t *friends)
{ 
    Friend_t *head = friends;
    Friend_t *next_friend = friends->next;
    char fname_temp[31];
    char lname_temp[41];
    int month_temp;
    int day_temp;
    int year_temp;
    int age_temp;
    char sex_temp[5];
    char color_temp[16];

    while(friends != NULL)//for (int j=0; j < tail-1; j++) 
    { 
        while(next_friend != NULL)//for (int i=j+1; i < tail; i++) 
        { 
            if (strcmp(friends->fname, next_friend->fname) > 0) 
            { 
                //Put to temp variable
                strcpy(lname_temp, friends->lname);
                strcpy(fname_temp, friends->fname); 
                strcpy(sex_temp, friends->sex);
                strcpy(color_temp, friends->color); 
                month_temp = friends->month;
                day_temp = friends->day;
                year_temp = friends->year;
                age_temp = friends->age;

                //Replace value
                strcpy(friends->lname, next_friend->lname);
                strcpy(friends->fname, next_friend->fname); 
                strcpy(friends->sex, next_friend->sex); 
                strcpy(friends->color, next_friend->color);  
                friends->age = next_friend->age;
                friends->month = next_friend->month;
                friends->day = next_friend->day;
                friends->year = next_friend->year;

                //Move temp variable
                strcpy(next_friend->lname, lname_temp); 
                strcpy(next_friend->fname, fname_temp); 
                strcpy(next_friend->sex, sex_temp); 
                strcpy(next_friend->color, color_temp);
                next_friend->age = age_temp;
                next_friend->month = month_temp;
                next_friend->day = day_temp;
                next_friend->year = year_temp; 
            }

            next_friend = next_friend->next;
        }

        friends = friends->next;
        if (friends != NULL){next_friend = friends->next;}
    } 
    
    friends = head;
    next_friend = friends->next;

    while(friends != NULL)//for (int j=0; j < tail-1; j++) 
    { 
        while(next_friend != NULL)//for (int i=j+1; i < tail; i++) 
        { 
            if (strcmp(friends->lname, next_friend->lname) > 0) 
            { 
                //Put to temp variable
                strcpy(lname_temp, friends->lname);
                strcpy(fname_temp, friends->fname); 
                strcpy(sex_temp, friends->sex);
                strcpy(color_temp, friends->color); 
                month_temp = friends->month;
                day_temp = friends->day;
                year_temp = friends->year;
                age_temp = friends->age;

                //Replace value
                strcpy(friends->lname, next_friend->lname);
                strcpy(friends->fname, next_friend->fname); 
                strcpy(friends->sex, next_friend->sex); 
                strcpy(friends->color, next_friend->color);  
                friends->age = next_friend->age;
                friends->month = next_friend->month;
                friends->day = next_friend->day;
                friends->year = next_friend->year;

                //Move temp variable
                strcpy(next_friend->lname, lname_temp); 
                strcpy(next_friend->fname, fname_temp); 
                strcpy(next_friend->sex, sex_temp); 
                strcpy(next_friend->color, color_temp);
                next_friend->age = age_temp;
                next_friend->month = month_temp;
                next_friend->day = day_temp;
                next_friend->year = year_temp;  

            }
            else if (strcmp(friends->lname, next_friend->lname) == 0 &&  strcmp(friends->fname, next_friend->fname) > 0) 
            {
                //Put to temp variable
                strcpy(lname_temp, friends->lname);
                strcpy(fname_temp, friends->fname); 
                strcpy(sex_temp, friends->sex);
                strcpy(color_temp, friends->color); 
                month_temp = friends->month;
                day_temp = friends->day;
                year_temp = friends->year;
                age_temp = friends->age;

                //Replace value
                strcpy(friends->lname, next_friend->lname);
                strcpy(friends->fname, next_friend->fname); 
                strcpy(friends->sex, next_friend->sex); 
                strcpy(friends->color, next_friend->color);  
                friends->age = next_friend->age;
                friends->month = next_friend->month;
                friends->day = next_friend->day;
                friends->year = next_friend->year;

                //Move temp variable
                strcpy(next_friend->lname, lname_temp); 
                strcpy(next_friend->fname, fname_temp); 
                strcpy(next_friend->sex, sex_temp); 
                strcpy(next_friend->color, color_temp);
                next_friend->age = age_temp;
                next_friend->month = month_temp;
                next_friend->day = day_temp;
                next_friend->year = year_temp; 
            }
            
            next_friend = next_friend->next;
        } 
        
        friends = friends->next;
        if (friends != NULL){next_friend = friends->next;}
    } 


}

int main()
{
    bool test = false;
    bool leave = false;
    Friend_t *head = NULL;
    
    // for(int i = 0; i <= 1000000; i++)
    // {
    //     //Add new node to linked list
    //     Friend_t *new_node = (Friend_t*) malloc(sizeof(Friend_t));
    //     Friend_t *last = head;

    //     strcpy(new_node->fname, "GABRIEL");
    //     strcpy(new_node->lname, "POTESTADES");
    //     strcpy(new_node->sex, "M");
    //     strcpy(new_node->color, "RED");

    //     new_node->month = 8;
    //     new_node->day = 31;
    //     new_node->year = 1994;
    //     new_node->age = 25;
    //     new_node->next = NULL;

    //     if (head == NULL)
    //     {
    //         head= new_node;
    //     }
    //     else
    //     {
    //         while (last->next != NULL)
    //             last = last->next;

    //         last->next = new_node;
    //     }
        
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
                add_friend(&head);
                sort_list(head);
            }
            else if (select == 2)
            {

                if (head == NULL)
                {
                    printf("No entries to delete.");
                    _getch();
                }
                else
                {
                    delete_friend(&head);
                }
            
            }
            else if (select == 3)
            {
                if (head == NULL)
                {
                    printf("No entries to edit.");
                    _getch();
                }
                else
                {
                    modify_friend(head);
                    sort_list(head);
                }
                
            }
            else if (select == 4)
            {
                if (head == NULL)
                {
                    printf("No entries to view.");
                    _getch();
                }
                else
                {
                    inquire_friend(head);
                }              
            }
            else if (select == 5)
            {
                if (head == NULL)
                {
                    printf("No records to display.");
                    _getch();
                }
                else
                {
                    print_friend(head);  
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
