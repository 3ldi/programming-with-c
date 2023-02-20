/*------------------------------------------------------------------------------
Author:         Eldi Prifti
Course #:       INFO.2120
Objective:      This program prompts the user to enter personal, work related
                information about a desired number(up to 20) of employees. The
                information is stored and then displayed in report style.

                For the purposes of this program, the following restrictions apply:
                - the company was established on 01/01/1995. The last hiring date
                is set to 12/31/2019. So, any dates before or after these borders,
                will not be accepted.
                - min state wage is 15 USD/hour
                - max company wage for FY-2020 is 50 USD/hour
                - max hours worked per week are limited to 60
                - overtime is calculated at 1.5 times the regular rate
                - Tax rate is 21%
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

// Declare structures

struct name
{
    char last_name[15];
    char first_name[15];
    char middle_initial[2];
};

struct date
{
    int mm;
    int dd;
    int yyyy;
};

struct information
{
    struct name fullname;
    struct date hire_date;
    float  pay_rate;
    float  hrs_worked;
    float  ret_percentage;
};

// Function prototypes
int    employees_to_process(void);
int    number_of_days(struct date);
float  get_hours_worked(void);
float  get_payrate(void);
float  get_ret_percentage(void);
struct date  get_date(void);
char   is_leap_year(struct date);
char   validate_date(struct date);
void   safer_gets(char[], int);
void   display_report(struct information[], float[], float[], float[], float[], int);


// Begin function main
int main(void)
{
    int num_employees, i;
    char c, date_flag;
    struct information employee_data[20];
    float gross_pay_array[20];
    float net_pay_array[20];
    float taxes_array[20];
    float amount_401k_array[20];
    const float tax_rate = 0.21;


    printf("Welcome to employee payroll program.\n\n");

    num_employees = employees_to_process(); // function call to get the number of employees to process

    // Loop set up to get data from user for each employee.
    for(i = 0; i < num_employees; i++)
    {
        printf("\n\nEmployee #%d:\n", i+1);

        printf("Enter first name: ");
        safer_gets(employee_data[i].fullname.first_name, 14);  // function calls to get first name

        printf("Enter last name: ");
        safer_gets(employee_data[i].fullname.last_name, 14);   // function calls to get last name

        printf("Enter middle initial: ");
        safer_gets(employee_data[i].fullname.middle_initial, 1);  // function calls to get middle initial

        employee_data[i].hrs_worked = get_hours_worked();  // function call to get hours worked

        employee_data[i].pay_rate = get_payrate();  // function call to get pay rate

        employee_data[i].ret_percentage = get_ret_percentage();  // function call to get 401K percentage

        // The following loop will trap the user to enter a correct date [1/1/1995 - 12/31/2019]
        do
        {
            employee_data[i].hire_date = get_date(); // function call to get the date of hiring

            date_flag = validate_date(employee_data[i].hire_date);  // function call to validate date

        } while(date_flag != 'T');  // end do-while trap loop

        // Calculate gross pay. Hours over 40 are considered overtime.
        if(employee_data[i].hrs_worked <= 40)
            gross_pay_array[i] = employee_data[i].hrs_worked * employee_data[i].pay_rate;
        else
            gross_pay_array[i] = (40 * employee_data[i].pay_rate) + (employee_data[i].hrs_worked - 40) * 1.5 * employee_data[i].pay_rate;

        // Calculate 401k amount
        amount_401k_array[i] = employee_data[i].ret_percentage * gross_pay_array[i];

        // Calculate taxes. 401k amount is considered before taxable income
        taxes_array[i] = tax_rate * (gross_pay_array[i] - amount_401k_array[i]);

        // Calculate net pay
        net_pay_array[i] = (1.0 - tax_rate) * (gross_pay_array[i] - amount_401k_array[i]);

    } // end for loop

    // function call to display report
    display_report(employee_data, gross_pay_array, taxes_array,
                   net_pay_array, amount_401k_array, num_employees);


    return 0;
}  // end function main


// Begin function safer_gets
void safer_gets (char array[], int max_chars)
{
  /* Declare variables. */
  /* ------------------ */

  int i;

  /* Read info from input buffer, character by character,   */
  /* up until the maximum number of possible characters.    */
  /* ------------------------------------------------------ */

  for (i = 0; i < max_chars; i++)
  {
     array[i] = getchar();

     /* If "this" character is the carriage return, exit loop */
     /* ----------------------------------------------------- */

     if (array[i] == '\n')
        break;

   } /* end for */

   /* If we have pulled out the most we can based on the size of array, */
   /* and, if there are more chars in the input buffer,                 */
   /* clear out the remaining chars in the buffer.                      */
   /* ----------------------------------------------------------------  */

   if (i == max_chars )

     if (array[i] != '\n')
       while (getchar() != '\n');

   /* At this point, i is pointing to the element after the last character */
   /* in the string. Terminate the string with the null terminator.        */
   /* -------------------------------------------------------------------- */

   array[i] = '\0';

}  // end function safer_gets


// Begin function employees_to_process to get the total number of employees the user wishes to process
int employees_to_process(void)
{
    // Variable declarations
    int number;
    char c;


    // Trap the user to enter a number between 1 and 20, inclusive.
    do
    {
        printf("How many employees do you wish to process?(1-20) > ");
        scanf("%d", &number);
        while((c = getchar() != '\n') && c != EOF);

        if(number < 1 || number > 20)
        {
            printf("*** Invalid entry ***\n");
            printf("*** Number of employees to process must be between 1 and 20, inclusive.\n");
            printf("*** Please, try again...\n");
        } // end if
    } while(number < 1 || number > 20);  // end do-while trap loop

    return number;
}  // end function employees_to_process


// Begin function get_hours_worked. Min hours is 0 and Max is 60.
float get_hours_worked(void)
{
    // Variable declarations
    float hours;
    char  c;

    // trap user to enter a number between 0 and 60, inclusive.
    do
    {
        printf("Enter hours worked: ");
        scanf("%f", &hours);
        while((c = getchar() != '\n') && c != EOF);

        if(hours < 0.0 || hours > 60.0)
        {
            printf("*** Invalid entry ***\n");
            printf("*** Hours worked must be between 0 and 60, inclusive. Try again...\n");
        } // end if
    } while(hours < 0.0 || hours > 60.0);  // end do-while trap loop

    return hours;
} // end function get_hours_worked


// Begin function get_payrate. Min state rate is 15 USD/hour. Max rate of company is 50 USD/hour.
float get_payrate(void)
{
    // Variable declarations
    float rate;
    char  c;

    // trap user to enter a number between 15 and 50, inclusive.
    do
    {
        printf("Enter pay rate: ");
        scanf("%f", &rate);
        while((c = getchar() != '\n') && c != EOF);

        if(rate < 15.0 || rate > 50.0)
        {
            printf("*** Invalid rate ***\n");
            printf("*** Minimum state wage is 15 USD/hour.\n");
            printf("*** Max company rate for FY 2020 is 50 USD/hour.\n");
            printf("*** Please, try again...\n");
        }
    } while(rate < 15.0 || rate > 50.0);  // end do-while trap loop

    return rate;
} // end function get_hours_worked


// Begin function get_ret_percentage.
float get_ret_percentage(void)
{
    // Variable declarations
    float ret_percent;
    char  c;

    // trap user to enter a number between 15 and 50, inclusive.
    do
    {
        printf("Enter 401K percentage: ");
        scanf("%f", &ret_percent);
        while((c = getchar() != '\n') && c != EOF);

        // in the following comparison I am using ".100001" instead of just ".1"
        // this way the compiler will accept the user entry ".1"
        if(ret_percent < .00 || ret_percent > .100001)
        {
            printf("*** Invalid percentage ***\n");
            printf("*** Minimum percentage is 0.0 while Maximum for FY-2020 is 0.1\n");
            printf("*** Please, try again...\n");
        }
    } while(ret_percent < .00 || ret_percent > .100001);  // end do-while trap loop

    return ret_percent;
} // end function get_ret_percentage


// Begin function is_leap_year
char is_leap_year(struct date d)
{
    // Variable declarations
    char flag;

    if((d.yyyy % 4 == 0 && d.yyyy % 100 != 0) || d.yyyy % 400 == 0)
        flag = 'T';
    else
        flag = 'F';

    return(flag);

} // end function is_leap_year


// Begin function days_per_month

int number_of_days(struct date d)
{
    int days;
    const int days_per_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char leap_year;

    leap_year = is_leap_year(d);  // function call to determine if it's a leap year

    if(leap_year == 'T' && d.mm == 2)
        days = 29;
    else
        days = days_per_month[d.mm - 1];

    return(days);
} // end function number_of_days


// Begin function get_date
struct date get_date(void)
{
    // Variable declarations
    char c;
    struct date hiring;

    printf("Enter hire date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &hiring.mm, &hiring.dd, &hiring.yyyy);
    while((c = getchar() != '\n') && c != EOF);  // clear input buffer

    return hiring;
} // end function get_date


// Begin function validate_date.
// The function will return 'F' for invalid date or 'T' for a good user entry.

char validate_date(struct date d)
{
    /* Variable declaration */

    char c;
    char date_flag = 'T';
    int  num_date, num_max_date = 20201014;  // 10/14/2020 is set as the limit date

    if(d.mm <= 0 || d.mm > 12) // Validate months
    {
        printf("*** Invalid month. Please, try again...\n");
        date_flag = 'F';
        return date_flag;
    }

    if(d.dd <= 0 || d.dd > number_of_days(d))  // function call to validate number of days
    {
        printf("*** Invalid day. Please, try again...\n");
        date_flag = 'F';
        return date_flag;
    }

    if(d.yyyy < 1995 || d.yyyy > 2019)  // accepted year range is from 1995(company est.) to 2020
    {
        printf("*** Invalid year. The company was established 01/01/1995.\n");
        printf("*** Also, due to Covid-19, our last hiring results on 12/31/2019.\n");
        printf("*** Please, try again...\n");
        date_flag = 'F';
        return date_flag;
    }

    return date_flag;

} /* end function validate_date */


// Begin function display_report
void display_report(struct information data[], float gross[], float tax[],
                    float net[], float ret_401k[], int n)
{
    // Variable decalrations
    char  c;
    int   i, max_name_length = 10;
    float total_hours = 0.0, total_rate = 0.0, total_gross = 0.0,
          total_tax = 0.0, total_401k = 0.0, total_net = 0.0;
    char  fullnames[20][35]; // will contain employee's fullname
    char  space[] = " ";


    // Create an array of strings containing full names
    for(i = 0; i < n; i++)
    {
        strcpy(fullnames[i], data[i].fullname.first_name); // copies the first name in the empty fullname:[firstname]
        strcat(fullnames[i], space);  // adds a space: [firstname ]
        strcat(fullnames[i], data[i].fullname.middle_initial); // adds the middle initial: [firstname middle]
        strcat(fullnames[i], space);  // adds a space: [firstname middle ]
        strcat(fullnames[i], data[i].fullname.last_name);  // adds lastname: [firstname middle lastname]
        strcat(fullnames[i], space);  // adds a space to create our desired string:[firstname middle lastname ]
    }


    // Display report

    printf("%78s\n", "Next Tech Employee's Payroll Report - 10/14/2020");
    printf("%78s\n", "------------------------------------------------");
    printf("%-32s %10s %7s %7s %9s %7s %7s %9s", "Name", "Hire Date",
            "Hours", "Rate", "Gross-Pay", "Taxes", "401K", "Net-Pay");
    printf("\n\n");

    // display employee data
    for(i = 0; i < n; i++)
    {
        printf("%-32s %02d/%02d/%4d %7.2f %7.2f %9.2f %7.2f %7.2f %9.2f\n",
               fullnames[i],
               data[i].hire_date.mm, data[i].hire_date.dd, data[i].hire_date.yyyy,
               data[i].hrs_worked, data[i].pay_rate, gross[i], tax[i], ret_401k[i], net[i]);
    } // end for loop

    //compute totals
    for(i = 0; i < n; i++)
    {
        total_hours = total_hours + data[i].hrs_worked;
        total_rate = total_rate + data[i].pay_rate;
        total_gross = total_gross + gross[i];
        total_tax = total_tax + tax[i];
        total_401k = total_401k + ret_401k[i];
        total_net = total_net + net[i];
    } // end for

    printf("\n");  // empty line

    printf("%-43s %7.2f %7.2f %9.2f %7.2f %7.2f %9.2f", "Total Payroll",
           total_hours, total_rate, total_gross, total_tax, total_401k, total_net);

    printf("\n\n");  // empty lines

    getchar();  // wait for user input

} // end function display report





