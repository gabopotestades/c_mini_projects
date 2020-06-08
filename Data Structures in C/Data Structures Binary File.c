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

struct Friend
{
    char fname[30];
    char lname[40];
    int month;
    int day;
    int year;
    int age;
    char sex[5];
    char color[15];
    int is_deleted;
} new_friend;

struct Friender
{
    char fname[30];
    char lname[40];
    int month;
    int day;
    int year;
    int age;
    char sex[5];
    char color[15];
    int is_deleted;
} next_friend;

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

int add_friend(int *tail, int *total_count)
{
    bool end_add = false, sex = false;
    int month, day, year, age;
    char add_another[10];

    FILE *fileptr  = fopen("BinaryFile.bin", "ab");

    while (!end_add)
    {
        
        system("cls");
        printf("Add a friend:\n\n");

        printf("Enter first name(30 characters): ");
        scanf("%30s", new_friend.fname);

        printf("Enter last name(40 characters): ");
        scanf("%40s", new_friend.lname);

        //Enter birthday
        get_birthday(&new_friend.month, &new_friend.day, &new_friend.year, &new_friend.age, true, false);
        
        //Enter sex
        while(!sex)
        {
            
            printf("Enter sex (M/F): ");
            scanf("%5s", new_friend.sex);
            while(getchar() != '\n');
            strupr(new_friend.sex);
            
            int result = 1, result2 = 1;
            result = strcmp(new_friend.sex, "M");
            result2 = strcmp(new_friend.sex, "F");
            
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
        fgets(new_friend.color, 15, stdin);

        int len = strlen(new_friend.color);
        if(new_friend.color[len-1] == '\n' && len > 1){new_friend.color[len-1] = 0;}

        strupr(new_friend.fname);
        strupr(new_friend.lname);
        strupr(new_friend.color);
        new_friend.is_deleted = 0;

        fwrite(&new_friend, sizeof(new_friend), 1, fileptr);

        *tail = *tail + 1;
        *total_count = *total_count + 1;

        printf("\nDo you want to add another (Y/N)?");

        scanf("%s", add_another);
        while(getchar() != '\n');
        strupr(add_another);

        if (strcmp(add_another, "Y") == 0)
        {
            // if (*tail == *array_size)
            // {
            //     printf("Reached limit of entries.\n");
            //     getch();
            end_add = false;
            //}
        }
        else
        {
            end_add = true;
        }
        
    }

    fflush(fileptr);
    //fclose("BinaryFile.bin");

    return 0;

    //sort_list(friends, *tail);

}

int delete_friend(int *tail)
{

    bool end_delete = false, result = false;
    char fname[31], lname[41], sex[10], color[16], age[10], del_another[3];
    char fname_enter[31], lname_enter[41], sex_enter[10], color_enter[16];
    int month_enter, day_enter, year_enter, age_enter, index = 0;
    
    while (!end_delete)
    {
        FILE *fileptr = fopen("BinaryFile.bin", "r+b");
        //FILE *tempFile = fopen("delete-line.dat", "wb");

        system("cls");
        printf("Delete a friend:\n");
        printf("Leave an entry blank for a filter to disregarded.\n\n");

        printf("Enter first name: ");
        fgets(fname, 30, stdin);
        printf("Enter last name: ");
        fgets(lname, 40, stdin);

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

            while(fread(&new_friend, sizeof(new_friend), 1, fileptr) != 0)
            {

                fname_result = strcmp(new_friend.fname, fname);
                lname_result = strcmp(new_friend.lname, lname);
                sex_result = strcmp(new_friend.sex, sex);
                color_result = strcmp(new_friend.color, color);

                index++;
                
                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (new_friend.age == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n') &&
                   (new_friend.is_deleted == 0)
                  )
                {
                        new_friend.is_deleted = 1;
                        fseek(fileptr, ftell(fileptr) - sizeof(new_friend), SEEK_SET);
                        fwrite(&new_friend, sizeof(new_friend), 1, fileptr);
                        //fwrite(&new_friend, sizeof(new_friend), 1, tempFile);

                        *tail = *tail - 1;
                        result = true;
                        break;
                    
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
               
        fclose(fileptr);
        
        //remove("BinaryFile.bin");
        //rename("delete-line.dat", "BinaryFile.bin");

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

int modify_friend(int *tail)
{
    bool end_inquire = false, result = false, will_change = false, valid_sex = false;
    char fname[31], lname[41], sex[5], color[16], age[3], inq_another[3];
    int index = 0, month, day, year, i_age;
    
    while (!end_inquire)
    {
        FILE *fileptr = fopen("BinaryFile.bin", "r+b");
        
        system("cls");
        printf("Modify a friend:\n");
        printf("Leave an entry blank for a filter to disregarded.\n\n");

        printf("Enter first name: ");
        fgets(fname, 30, stdin);

        printf("Enter last name: ");
        fgets(lname, 40, stdin);

        printf("Enter age: ");
        fgets(age, 10, stdin);

        printf("Enter sex: ");
        fgets(sex, 10, stdin);

        printf("Enter favorite color: ");
        fgets(color, 15, stdin);

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

            while(fread(&new_friend, sizeof(new_friend), 1, fileptr) != 0)
            {
                fname_result = strcmp(new_friend.fname, fname);
                lname_result = strcmp(new_friend.lname, lname);
                sex_result = strcmp(new_friend.sex, sex);
                color_result = strcmp(new_friend.color, color);

                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (new_friend.age == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n') &&
                   (!new_friend.is_deleted)
                  )
                {
                    printf("\nRecord found:\n");
            
                    printf("\nFirst name: %s\n", new_friend.fname);
                    printf("Last name: %s\n", new_friend.lname);
                    printf("Month: %d\n", new_friend.month);
                    printf("Day: %d\n", new_friend.day);
                    printf("Year: %d\n", new_friend.year);
                    printf("Age: %d\n", new_friend.age);
                    printf("Sex: %s\n", new_friend.sex);
                    printf("Color: %s\n\n", new_friend.color);

                    printf("\nLeave an entry blank to disregard edit of the cell:\n");

                    printf("Enter first name: ");
                    fgets(fname, 30, stdin);

                    printf("Enter last name: ");
                    fgets(lname, 40, stdin);

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
                    fgets(color, 15, stdin);

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

                    if(fname[0] != '\n'){strcpy(new_friend.fname, fname);}
                    if(lname[0] != '\n'){strcpy(new_friend.lname, lname);}
                    if(sex[0] != '\n'){strcpy(new_friend.sex, sex);}
                    if(color[0] != '\n'){strcpy(new_friend.color, color);}

                    if (will_change)
                    {
                        new_friend.month = month;
                        new_friend.day = day;
                        new_friend.year = year;
                        new_friend.age = i_age;
                    }

                    fseek(fileptr, ftell(fileptr) - sizeof(new_friend), SEEK_SET);
                    fwrite(&new_friend, sizeof(new_friend), 1, fileptr);

                    result = true;
                    break;
                }
            }
 
        }

        if (result)
        {      
            printf("\nRecord successfully modified.\n\n");
        }
        else
        {
            printf("No record found with filters.\n");
        }
        
        fclose(fileptr);

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

    //sort_list(friends, *tail);

}

int inquire_friend()
{
    bool end_inquire = false, result = false;
    char fname[31], lname[41], sex[10], color[16], age[10], inq_another[3];
    int index = 0;
    
    FILE *fileptr = fopen("BinaryFile.bin", "rb");

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

            int index = 1;

            rewind(fileptr);

            while(fread(&new_friend, sizeof(new_friend), 1, fileptr) != 0)
            {
                fname_result = strcmp(new_friend.fname, fname);
                lname_result = strcmp(new_friend.lname, lname);
                sex_result = strcmp(new_friend.sex, sex);
                color_result = strcmp(new_friend.color, color);

                if(
                   (fname_result == 0 || fname[0] == '\n') &&
                   (lname_result == 0 || lname[0] == '\n') &&
                   (new_friend.age == check_age || age[0] == '\n') &&
                   (sex_result == 0 || sex[0] == '\n') &&
                   (color_result == 0 || color[0] == '\n') &&
                   (new_friend.is_deleted == 0)
                  )
                {
                    result = true;
                    
                    printf("\nRecord found:\n");
                    
                    printf("\nIndex: %d\n", index);
                    printf("First name: %s\n", new_friend.fname);
                    printf("Last name: %s\n", new_friend.lname);
                    printf("Month: %d\n", new_friend.month);
                    printf("Day: %d\n", new_friend.day);
                    printf("Year: %d\n", new_friend.year);
                    printf("Age: %d\n", new_friend.age);
                    printf("Sex: %s\n", new_friend.sex);
                    printf("Color: %s\n\n", new_friend.color);

                    break;
                }

                index++;
                
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
    }
    
    //fflush(fileptr);
    fclose(fileptr);

}

int print_friend()
{
                  
    system("cls");
    printf("List of friends:\n");

    FILE *fileptr = fopen("BinaryFile.bin", "rb");
    int index = 1;

    rewind(fileptr);

    while(fread(&new_friend, sizeof(new_friend), 1, fileptr) != 0)
    {    
        if(!new_friend.is_deleted)   
        {
            printf("\n%d %10s %10s \t%d %d %d \t%d \t%5s \t%s",
            index,  
            new_friend.lname, 
            new_friend.fname, 
            new_friend.month, 
            new_friend.day, 
            new_friend.year, 
            new_friend.age, 
            new_friend.sex, 
            new_friend.color);
            index++;    
        }

    }

    fclose(fileptr);

    printf("\nPress any key to return to menu.");
    _getch();
}

int sort_list(int total_count)
{
    FILE *fileptr = fopen("BinaryFile.bin", "r+b");

    char fname_temp[30];
    char lname_temp[40];
    int month_temp;
    int day_temp;
    int year_temp;
    int age_temp;
    char sex_temp[5];
    char color_temp[15];
    long ptrindex;

    for (int j=0; j < total_count-1; j++) 
    { 

        fseek(fileptr, sizeof(new_friend) * j, SEEK_SET);
        fread(&new_friend, sizeof(new_friend), 1, fileptr);

        for (int i=j+1; i < total_count; i++) 
        {
            fseek(fileptr, sizeof(new_friend) * i, SEEK_SET);
            fread(&next_friend, sizeof(new_friend), 1, fileptr);

            if (strcmp(new_friend.fname, next_friend.fname) > 0) 
            { 
                //Put to temp variable
                // strcpy(lname_temp, new_friend.lname);
                // strcpy(fname_temp, new_friend.fname); 
                // strcpy(sex_temp, new_friend.sex);
                // strcpy(color_temp, new_friend.color); 
                // month_temp = new_friend.month;
                // day_temp = new_friend.day;
                // year_temp = new_friend.year;
                // age_temp = new_friend.age;

                // //Replace value
                // strcpy(new_friend.lname, next_friend.lname);
                // strcpy(new_friend.fname, next_friend.fname); 
                // strcpy(new_friend.sex, next_friend.sex); 
                // strcpy(new_friend.color, next_friend.color);  
                // new_friend.age = next_friend.age;
                // new_friend.month = next_friend.month;
                // new_friend.day = next_friend.day;
                // new_friend.year = next_friend.year;

                // //Move temp variable
                // strcpy(new_friend.lname, lname_temp); 
                // strcpy(new_friend.fname, fname_temp); 
                // strcpy(new_friend.sex, sex_temp); 
                // strcpy(new_friend.color, color_temp);
                // new_friend.age = age_temp;
                // new_friend.month = month_temp;
                // new_friend.day = day_temp;
                // new_friend.year = year_temp;
              
                fseek(fileptr, sizeof(new_friend) * j, SEEK_SET);
                fwrite(&next_friend, sizeof(new_friend), 1, fileptr);
                
                fseek(fileptr, sizeof(new_friend) * i, SEEK_SET);
                fwrite(&new_friend, sizeof(new_friend), 1, fileptr);
                
            } 
            
            fseek(fileptr, sizeof(new_friend) * j, SEEK_SET);
            fread(&new_friend, sizeof(new_friend), 1, fileptr);
        } 
    } 
 
    for (int j=0; j < total_count-1; j++) 
    { 
        fseek(fileptr, sizeof(new_friend) * j, SEEK_SET);
        fread(&new_friend, sizeof(new_friend), 1, fileptr);

        for (int i=j+1; i < total_count; i++) 
        { 
            fseek(fileptr, sizeof(new_friend) * i, SEEK_SET);
            fread(&next_friend, sizeof(new_friend), 1, fileptr);

            if (strcmp(new_friend.lname, next_friend.lname) > 0) 
            { 
                fseek(fileptr, sizeof(new_friend) * j, SEEK_SET);
                fwrite(&next_friend, sizeof(new_friend), 1, fileptr);
                
                fseek(fileptr, sizeof(new_friend) * i, SEEK_SET);
                fwrite(&new_friend, sizeof(new_friend), 1, fileptr);
            }
            else if (strcmp(new_friend.lname, next_friend.lname) == 0 &&  strcmp(new_friend.fname, next_friend.fname) > 0) 
            {
                fseek(fileptr, sizeof(new_friend) * j, SEEK_SET);
                fwrite(&next_friend, sizeof(new_friend), 1, fileptr);
                
                fseek(fileptr, sizeof(new_friend) * i, SEEK_SET);
                fwrite(&new_friend, sizeof(new_friend), 1, fileptr);
            }
            
            fseek(fileptr, sizeof(new_friend) * j, SEEK_SET);
            fread(&new_friend, sizeof(new_friend), 1, fileptr);
        } 
        
    }

    fclose(fileptr);

}

int main()
{
    bool test = false;
    bool leave = false;
    int triedCreating = 0;
    int index = 0, tail = 0, total_count = 0;

    FILE *fileptr;

    OPEN:
    fileptr = fopen("BinaryFile.bin", "rb");

    if (!fileptr)
    {
        // try to create the file
        if (!triedCreating)
        {
            triedCreating = 1;
            fclose(fopen("BinaryFile.bin", "wb"));
            goto OPEN;
        }
        fprintf(stderr, "Error opening file %i. Message: %s", errno, strerror(errno));
        _getch();
        exit(EXIT_FAILURE);
    }
    else
    {
        while (fread(&new_friend, sizeof(new_friend), 1, fileptr) == 1)
        { 
            total_count++;

            if(!new_friend.is_deleted)   
            {
                tail++;
            }
        }
    }

    fclose(fileptr);
    //fflush(fileptr);

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
                add_friend(&tail, &total_count);    
                sort_list(total_count);         
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
                    delete_friend(&tail);
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
                    modify_friend(&tail);
                    sort_list(total_count);
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
                    inquire_friend();
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
                    print_friend();
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
