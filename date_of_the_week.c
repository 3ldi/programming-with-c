/*------------------------------------------------------------------------------------
Program file:   day_of_the_week.c
Author:         Eldi Prifti
Email:          eldi_prifti@student.uml.edu
Date:           September 27, 2020
Assignment:     priftiep2.c
Course #:       INFO2120
Objective:      This program prompts the user to enter a date and then displays the
                day of the week it falls on. The user input is required in the format
                mm/dd/yyyy and the date must be in the range 1/1/1701 - 31/12/3000.
-------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>


/* Define structure */

struct date
{
    int month;
    int day;
    int year;
};

/* Function prototypes */

char is_leap_year(struct date);
int  number_of_days(struct date);
char validate_date(struct date);
long calculate_date_number(struct date);
int  calculate_day_number(long);
void display_day_of_week(struct date, int);


/* Begin function main */

int main(void)
{
    /* Variable declarations */

    struct date date_to_check;
    char c, date_flag, answer;
    int day_num;
    long n;

    /* Display initial message and prompt user for date. */
    /*---------------------------------------------------*/

    printf("The program will give the day of the week for any date \nfrom 1/1/1701 to 12/31/3000.\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    // Set up a loop that prompts the user whether to continue with another date or not

    do
    {

        date_flag = 'F';

        /* The following loop will trap the user to enter a correct date by passing the date   */
        /* to function validate_date. If the date is not correct the user will be re-prompted. */
        /*-------------------------------------------------------------------------------------*/
        do
        {
            printf("\nEnter date (mm/dd/yyyy): ");
            scanf("%d/%d/%d", &date_to_check.month, &date_to_check.day, &date_to_check.year);
            while((c = getchar() != '\n') && c != EOF);  // clear input buffer

            date_flag = validate_date(date_to_check);  // function call to validate date

        } while(date_flag == 'F');

        n = calculate_date_number(date_to_check); // function call to calculate number n

        day_num = calculate_day_number(n); // function call to calculate the numeric day of the week

        display_day_of_week(date_to_check, day_num); // function call to display the day of the week in English

        printf("\n"); // empty line

        printf("\nTry another date? [Y- continue] [any other key to Exit]: > "); // user decides to continue or not

        scanf("%c", &answer);
        while((c = getchar() != '\n') && c != EOF);

        printf("----------------------------------------------------\n");

    } while(answer == 'Y' || answer == 'y');

    return 0;

}  /* end function main */


/* Begin function validate_date. The function will return */
/* 'F' for invalid date or 'T' for a good user entry.     */

char validate_date(struct date d)
{
    /* Variable declaration */

    char c;
    char date_flag = 'T';

    if(d.month <= 0 || d.month > 12) // Validate months
    {
        printf("***Invalid month. Try again...\n");
        date_flag = 'F';
        return date_flag;
    }

    if(d.day <= 0 || d.day > number_of_days(d))  // function call to validate number of days
    {
        printf("***Invalid day. Try again...\n");
        date_flag = 'F';
        return date_flag;
    }


    if(d.year < 1701 || d.year > 3000)  /* accepted year range is from 1701 to 3000 */
    {
        printf("***Invalid year. Try again...\n");
        date_flag = 'F';
        return date_flag;
    }

    return date_flag;

} /* end function validate_date */


/* Begin function is_leap_year */

char is_leap_year(struct date d)
{
    /* Variable declaration */

    char flag;

    if((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0)
        flag = 'T';
    else
        flag = 'F';

    return(flag);

} /* end is_leap_year */

/* Begin function days_per_month */

int number_of_days(struct date d)
{
    int days;
    const int days_per_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char leap_year;

    leap_year = is_leap_year(d);  /* function call to determine if it's a leap year */

    if(leap_year == 'T' && d.month == 2)
        days = 29;
    else
        days = days_per_month[d.month - 1];

    return(days);
} /* end function number_of_days */


/* Begin function calculate_date_number */

long calculate_date_number(struct date d)
{
	int f, g, x;
	long n;

	/* Calculate f and g */

	if(d.month <= 2)
	{
		f = d.year - 1;
		g = d.month + 13;
	}
	else
	{
		f = d.year;
		g = d.month + 1;
	}

    /* Calculate the value of "x" based on the month and year. */

    if(d.year == 1700 && d.month >= 2)
        x = 2;
    else if(d.year > 1700 && d.year < 1800)
        x = 2;
    else if(d.year == 1800 && d.month < 2)
        x = 2;
    else if(d.year == 1800 && d.month >= 2)
        x = 1;
    else if(d.year > 1800 && d.year < 1900)
        x = 1;
    else if(d.year == 1900 && d.month < 2)
        x = 1;
    else if(d.year == 1900 && d.month >= 2)
        x = 0;
    else if(d.year > 1900)
        x = 0;

    /* Calculate n */

	n = x + (1461 * f / 4) + (153 * g / 5) + d.day;

	return n; /* return n to calling function */

}  /* end function calculate_date_number */


/* Begin calculate_day_number function. This function will */
/* return a number between 0 and 6, both included.         */

int calculate_day_number(long n)
{
    /* Variable declaration */

    int num;

    num = (n - 621049) % 7;

    return(num);

} /* end function calculate_day_number */


/* Begin display_day_of_week function */

void display_day_of_week(struct date d, int day_number)
{
    printf("%.2d/%.2d/%d falls on a ", d.month, d.day, d.year);

    switch(day_number)
    {
    case 0:
        printf("Sunday!");
        break;
    case 1:
        printf("Monday!");
        break;
    case 2:
        printf("Tuesday!");
        break;
    case 3:
        printf("Wednesday!");
        break;
    case 4:
        printf("Thursday!");
        break;
    case 5:
        printf("Friday!");
        break;
    case 6:
        printf("Saturday!");
        break;
    default:
        printf("\n***Unknown error in calculation!! Restart the program!!\n\n");

    }  /* end switch */

}  /* end display_day_of_week function */
