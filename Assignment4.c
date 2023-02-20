/*------------------------------------------------------------------------------
Program file:   student_report.c
Author:         Eldi Prifti
Email:          eldi_prifti@student.uml.edu
Date:           October 25, 2020
Assignment:     priftiep4.c
Course #:       INFO.2120
Objective:      This program uses pointer notation and pointer math to calculate
                the averages of a maximum of 20 student records. The data is provided
                to the program through a structure variable and is already filled out.
                Everything is then displayed in a report style. Finally, the program
                will calculate and display the averages for each exam as the last
                row of the report.
---------------------------------------------------------------------------------------*/

#include <stdio.h>


// Declare structures
struct univ
{
	char name[15];
	int	 grade[6];

}; // end struct univ


// Begin function main
int main(void)
{
    // Declare variables

    struct univ student_array[20] =
	{	{"Jim Sears",87,43,98,77,69,0 } ,
    	{"Joe Bob",35,21,89,57,77,0 } ,
    	{"Joy Pop",78,89,98,78,99,0 } ,
    	{"Jop Lyn",55,66,77,88,99,0 } ,
    	{"Jon Doe",65,71,79,87,76,0 } ,
    	{"Jon Doe",79,89,98,48,91,0 } ,
    	{"Jones Dob",54,66,79,88,92,0 } ,
    	{"Jan Gloe",39,81,69,67,73,0 } ,
    	{"Jack Sims",68,85,98,77,94,0 } ,
    	{"Jonnee Doz",89,69,77,68,96,0  }
	};

	struct univ *student_array_ptr = student_array;
    int         *student_grade_ptr = student_array_ptr->grade;

    int   col, row, i;
    int   num_grades = sizeof(student_array[0].grade)/sizeof(student_array[0].grade[0]);
    int   num_students = 10;
    int   total_grades = 0;
    float avg_student = 0.0, avg_exam = 0.0;


    student_array_ptr = student_array;
    // Iterate through student_array's elements using pointer notation.
    for( row = 0; row < num_students; row++, student_array_ptr++)
    {
        // Have the student_grade_ptr point to the first element of array grade
        student_grade_ptr = student_array_ptr->grade;

        for(col = 0; col < num_grades - 1; col++, student_grade_ptr++)
            total_grades += *student_grade_ptr;

        // Calculate student's average and assign it to the last element of array grade
        avg_student = (float)total_grades / (num_grades - 1);

        student_grade_ptr = student_array_ptr->grade;  // point at the first element again
        for(i = 0; i < num_grades; i++, student_grade_ptr++)
            if(*student_grade_ptr == 0)
                *student_grade_ptr = (int)avg_student;

        // Reset total_grades to 0 before moving to the next element of student_array.
        total_grades = 0;

    }  // end for loop


     // Format and display the header of the report

	printf("\n\n");
	printf("                       University Student Report \n");
	printf("                       ------------------------- \n\n");

	printf("%-15s %9s %7s %7s %7s %7s %9s\n",
           "Student Name", "Exam 1", "Exam 2", "Exam 3", "Exam 4", "Exam 5", "Average");
	printf("===================================================================\n");
    printf("\n");

    // Have the student_array_ptr point at the beginning of the structure
	student_array_ptr = student_array;

    for( row = 0; row < num_students; row++, student_array_ptr++)
    {
        // Display student's name
        printf("%-15s", student_array_ptr->name);

        student_grade_ptr = student_array_ptr->grade;  // point at the first element of grade again
        for( col = 0; col < num_grades; col++, student_grade_ptr++)
            // Display each grade and average
            printf(" %7i", *student_grade_ptr);

            printf("\n");
    }  // end for loop


    // Calculate and display averages for each exam and the average of student averages.
    printf("===================================================================\n");
    printf("%-15s", "Test averages");

    total_grades = 0;

    for(col = 0; col < num_grades; col++)
    {
        // Point to the beginning of the structure
        student_array_ptr = student_array;

        // Iterate through each student record
        for(row = 0; row < num_students; row++, student_array_ptr++)
        {
			// Point at the first element in array grade
			student_grade_ptr = student_array_ptr->grade;

            // After this loop the pointer will point at the element
            // at the 'col'-th position of array grade of the current student record
		 	for(i = 0; i < col; i++)
 		 		student_grade_ptr++;

			total_grades += *student_grade_ptr;

		}  // end nested for loop

        // Calculate and display exam average
        avg_exam = (float)total_grades / num_students;
        printf("%8.0f", avg_exam);

        // Reset total_grades to 0 before moving to the next element
        total_grades = 0;

    }  // end outer for loop

    printf("\n\n");
    getchar();  // wait for user input

    return 0;
} // end main
