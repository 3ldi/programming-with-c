/*--------------------------------------------------------------------------------------
Program file:   people_report.c
Author:         Eldi Prifti
Date:           November 7, 2020
Course #:       INFO.2120
Objective:      This program takes data from a file and loads a structure of up to
                100 items. Then, the program will prompt the user to select from
                either report or label. Based on the user choice, the program will
                do either a sort by name, or by zip code. The program will then output
                both, on the screen and on a file: report5.txt or label5.txt, based
                on the user's choice.
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <time.h>

/* Define structures */
struct date
{
    int year;
    int month;
    int day;
}; // end date

struct name
{
    char last[15];
    char first[15];
    char middle_initial;
}; // end name

struct information
{
    struct name full_name;
    char   address[20];
    char   city[15];
    char   state[3];
    long   zip;
    struct date fdate;
}; // end information


/* Function prototypes */
int get_choice(void);
int sort(struct information *, int, char);


/* Begin function main */
int main(void)
{
    /* variable declarations */

    struct information people[100];  // Maximum of a 100 records
    struct information *people_ptr = people;
    FILE    *in_file_ptr, *out_file_ptr;
    time_t  rawtime;
    struct  tm *timeptr;
    int     i, num_friends = 0;
    char    c, user_choice;
    char    fullnames[100][35]; // will contain friends' fullnames
    char    mid_init[3]; // will contain the middle initial and a space
    char    filename[30], space[] = " ", comma_space[] = ", ";


    /* Greet the user and prompt for a file name. */
    printf("Welcome to the friends program!\n\n");
    printf("Enter the name of the file to open: ");
    scanf("%29s", filename);
    while((c = getchar() != '\n') && c != EOF);  /* clear input buffer */

    /* Open input file for reading.                    */
    /* If error, display message and exit the program. */
    in_file_ptr = fopen(filename, "r");
    if(in_file_ptr == NULL)
    {
        printf("\nError. Could not open the file %s for reading.\n", filename);
        getchar(); // wait for user input
        return 1;
    }  // end if


    /* Obtain inforamtion from input data file and store in structure */
    for( i = 0; !feof(in_file_ptr) && i < 100; i++)
    {
        fscanf(in_file_ptr, "%[^\n]\n", people[i].full_name.last);
        fscanf(in_file_ptr, "%[^\n]\n", people[i].full_name.first);
        fscanf(in_file_ptr, "%c\n", &people[i].full_name.middle_initial);
        fscanf(in_file_ptr, "%[^\n]\n", people[i].address);
        fscanf(in_file_ptr, "%[^\n]\n", people[i].city);
        fscanf(in_file_ptr, "%[^\n]\n", people[i].state);
        fscanf(in_file_ptr, "%ld", &people[i].zip);
        /* when reading the date from file we will skip the '/' character */
        fscanf(in_file_ptr, "%d%*c%d%*c%d\n", &people[i].fdate.month,
                                              &people[i].fdate.day,
                                              &people[i].fdate.year);

        /* Count the number of friends in data file */
        num_friends++;
    } // end for loop

    /* Display the number of friends to user */
    printf("You have %i friends.\n", num_friends);

    /* function call to prompt user for their choice. */
    user_choice = get_choice();

    if(user_choice == 1)
    {
        /* Sort by last name */
        people_ptr = people;
        sort(people_ptr, num_friends, 'N');

        /* Open file for writing. */
		/* If error, display message and exit the program. */
    	out_file_ptr = fopen("report5.txt", "w");
   		if(out_file_ptr == NULL)
    	{
    		printf("\nError. Could not open the file 'report5.txt' for writing.\n");
        	getchar(); // wait for user input
        	return 1;
		}  // end if
       	time(&rawtime);
       	timeptr = localtime(&rawtime);
        /* Display header on screen */
        printf("\n\n");
        printf("               Your freinds' report %30s", asctime(timeptr));
		printf("               --------------------\n\n");
        printf("%-25s %-20s %-15s %-2s %5s %-10s\n\n",
               "Name", "Address", "City", "St", "Zip", "Friended");

	    /* Write header to file */
        fprintf(out_file_ptr,"\n");
        fprintf(out_file_ptr,"Your freinds' report - The current date and time:  %-s", asctime(timeptr));
		fprintf(out_file_ptr,"-------------------------------------------------\n\n");
        fprintf(out_file_ptr,"%-25s %-20s %-15s %-2s %5s %-10s\n\n",
                             "Name", "Address", "City", "St", "Zip", "Friended");

        for(i = 0; i < num_friends; i++)
        {
        	// Concatenate last and first name with a comma in the middle
         	strcpy(fullnames[i], people[i].full_name.last);
            strcat(fullnames[i], comma_space);
            strcat(fullnames[i], people[i].full_name.first);
            strcat(fullnames[i], space);
            mid_init[0] = people[i].full_name.middle_initial;
            mid_init[1] = '\0';
            strcat(fullnames[i], mid_init);
            strcat(fullnames[i], space);

            // Display the full name on screen
            printf("%-26s",fullnames[i]);
            // Display the rest of the data on the screen
            printf("%-20s ", people[i].address);
            printf("%-15s ", people[i].city);
            printf("%-2s ", people[i].state);
            printf("%.5ld ", people[i].zip);
            printf("%.2d/%.2d/%.4d", people[i].fdate.month, people[i].fdate.day, people[i].fdate.year);
            printf("\n");

            /* Write report to file */
            // Display the full name on screen
            fprintf(out_file_ptr,"%-26s",fullnames[i]);
            // Display the rest of the data on the screen
            fprintf(out_file_ptr,"%-20s ", people[i].address);
            fprintf(out_file_ptr,"%-15s ", people[i].city);
            fprintf(out_file_ptr,"%-2s ", people[i].state);
            fprintf(out_file_ptr,"%.5ld ", people[i].zip);
            fprintf(out_file_ptr,"%.2d/%.2d/%.4d", people[i].fdate.month, people[i].fdate.day, people[i].fdate.year);
            fprintf(out_file_ptr,"\n");
		} // end for
  		printf("\n\n%60s", "(Report has been sent to 'report5.txt')\n\n");
    } // end if
    else if(user_choice == 2)
    {
        // sort by zip code
        people_ptr = people;
        sort(people_ptr, num_friends, 'Z');

        /* Open file for writing. */
    	/* If error, display message and exit the program. */
    	out_file_ptr = fopen("label5.txt", "w");
   		if(out_file_ptr == NULL)
    	{
    		printf("\nError. Could not open the file 'label5.txt' for writing.\n");
        	getchar(); // wait for user input
        	return 1;
    	}  // end if

    	// Write time stamp to file
		time(&rawtime);
       	timeptr = localtime(&rawtime);
		fprintf(out_file_ptr,"Your freinds' labels ordered by zip code.    %-s", asctime(timeptr));
		fprintf(out_file_ptr,"-----------------------------------------\n\n");
        for(i = 0; i < num_friends; i++)
        {
        	printf("\n\n");
            // Display name on screen
            printf("%s %c %s\n", people[i].full_name.first,
                                 people[i].full_name.middle_initial,
                                 people[i].full_name.last);
            /* Display the address */
            printf("%s\n", people[i].address);
            /* Display city, state and zip code */
            printf("%s, %s %.5ld\n", people[i].city, people[i].state, people[i].zip);

   			/* Print labels to file label5.txt*/
			fprintf(out_file_ptr,"\n");
		    fprintf(out_file_ptr,"%s %c %s\n", people[i].full_name.first,
                                               people[i].full_name.middle_initial,
                                               people[i].full_name.last);
            fprintf(out_file_ptr,"%s\n", people[i].address);
            fprintf(out_file_ptr,"%s, %s %.5ld\n", people[i].city, people[i].state, people[i].zip);

    	} // end for
    	printf("\n%60s", "(Labels have been sent to 'label5.txt')\n\n");

    } // end else-if
    else if(user_choice == 3)
    {
        printf("\nProgram terminated by user!\n\n");
        return 0;
    } // end else-if
	// Close open files
    fclose(in_file_ptr);
	fclose(out_file_ptr);

	return 0;
}  // end function main


/* Begin function get_choice */
int get_choice(void)
{
    /* Declare variables */
    int c, choice;

    /* Trap user to enter an accepted character */
    while(1)
    {
        printf("\n\n(1) Print Report\n");
        printf("(2) Print Labels\n");
        printf("(3) Exit the program\n");
        printf("\nEnter your choice: ");

        /* Get character from user and test if the entry is a number between 1 and 3*/
        if(scanf("%i", &choice)!= 1)
            {
                while((c = getchar() != '\n') && c != EOF); //clear input buffer
                printf("Error on input. Try again...\n");
                continue;
            }
        else if(choice < 1 || choice > 3)
            {
                printf("Error on input. Try again...\n");
                continue;
            }
        else
            break;
    } // end while loop
    return choice;
}  // end get_choice


/* Begin function sort */
int sort(struct information *friends, int entries, char sort_by)
{
    /* Decalre variables */
    int  i,j;
    char not_done = 'y';
    struct information *t_ptr = friends;
    struct information *t_ptr2 = t_ptr + 1;
    struct information temp, *temp2;

    temp2 = &temp;

    while(not_done == 'y')
    {
        not_done = 'n';

        t_ptr = friends;
        t_ptr2 = t_ptr + 1;

        for(i = 0; i < entries - 1; i++)
        {
            if(   (sort_by == 'N' && strcmp(t_ptr->full_name.last, t_ptr2->full_name.last) > 0)
               || (sort_by == 'Z' && (t_ptr->zip > t_ptr2->zip)))
            {
                *temp2 = *t_ptr;
                *t_ptr = *t_ptr2;
                *t_ptr2 = *temp2;

                not_done = 'y';
            } // end if

            t_ptr++;
            t_ptr2++;
        } // end for loop

    } // end while loop

    return 0;
} // end function sort
