/*---------------------------------------------------------------------------------------
Author:         Eldi Prifti
Date:           July 26, 2020
Course #:       INFO2110
Objective:      This program allows the user to enter an initial state of a stock
                portfolio. Then, the user is allowed to make a desired number of
                transactions(buy - sell) with the stocks in the portfolio. Number of
                transactions will be limited to 10 each(buy - sell).
                After all transactions are completed, the final state of the portfolio,
                and all transactions are displayed along with a financial advice.
---------------------------------------------------------------------------------------*/

#include <stdio.h>

/* Function prototypes */
/*---------------------*/

void get_company_name(char []);
void get_stock_name(char []);
int  get_starting_balance(char []);
int  get_transactions_number(char [], char []);
int  validate_buy_amount(int);
int  validate_sell_amount(int, int);
void display_recap(char [], int, int, int, int [], int, int []);

/***********************
 * Begin function main *
 ***********************/

int main(void)
{
    /* Variable declarations */
    /*-----------------------*/

    int  i, how_many_buy, how_many_sell, initial_balance, stock_balance, amount_buy, amount_sell;
    int  buys[10], sells[10];
    char c, stock_name[20], company_name[40];
    char op1[] = "buys", op2[] = "sells", transaction_mode[6];

    /* Displaying initial greeting and prompting the user for company name and stock name */
    /*------------------------------------------------------------------------------------*/

    printf("******************************************************************************\n");
    printf("*  Welcome! This program allows you to buy and sell stocks from a portfolio. *\n");
    printf("*  You can conduct up to 10 transactions for each(buying-selling).           *\n");
    printf("*  To begin, please enter the company name and the stock name.               *\n");
    printf("******************************************************************************\n\n");

    /* Call function to get company name */
    /*-----------------------------------*/

    get_company_name(company_name);

    /* Call function to get stock name */
    /*---------------------------------*/

    get_stock_name(stock_name);

    printf("\n\n\t\t***Welcome to %s stock system!***\n\n", company_name);

    /* Call function to get initial balance. The returned value is stored */
    /* in a local variable in function main for later use.                */
    /*--------------------------------------------------------------------*/

    initial_balance = get_starting_balance(stock_name);

    printf("\n");  /* Empty line for nicer output */

    /* Set transaction_mode to 'buys' */
    /*--------------------------------*/

    for(i=0; i<6; i++)
        transaction_mode[i] = op1[i];

    /* Call function to get the number of buying transactions.
    /* The returned value is stored in a local variable in function main for later use. */
    /*----------------------------------------------------------------------------------*/

    how_many_buy = get_transactions_number(transaction_mode, stock_name);

    /* Set transaction_mode to 'sells' */
    /*---------------------------------*/

    for(i=0; i<6; i++)
        transaction_mode[i] = op2[i];

    /* Call function to get the number of selling transactions.
    /* The returned value is stored in a local variable in function main for later use. */
    /*----------------------------------------------------------------------------------*/

    how_many_sell = get_transactions_number(transaction_mode, stock_name);

    printf("\n");  /* empty line for nicer output */

    stock_balance = initial_balance; /* stock_balance will be used for all calculations */

    /* The following for loop will require the user to enter */
    /* the amount of stocks for each buying transaction.     */
    /*-------------------------------------------------------*/

    for(i = 1; i <= how_many_buy; i++)
    {
        /* Call function to validate amount of stocks to buy. The returned value */
        /* is stored in a local variable in function main for later use.         */
        /*-----------------------------------------------------------------------*/

        amount_buy = validate_buy_amount(i);

        /* After validation, the amount is added to the stock balance. */
        /* Then, the amount is stored in the array buys.               */
        /*-------------------------------------------------------------*/

        buys[i-1] = amount_buy;
        stock_balance += amount_buy;

    } /* end for loop */

    printf("\n");  /* Empty line for nicer output */

    /* The following for loop will require the user to enter the amount of stocks to sell   */
    /* for each selling transactions. A function checks each entry and the balance in order */
    /* to make sure that there are enough stocks to perform the transaction.                */
    /*--------------------------------------------------------------------------------------*/

    for( i = 1; i <= how_many_sell; i++)
    {
        /* Call function to validate amount of stocks to sell. The returned value */
        /* is stored in a local variable in function main for later use.          */
        /*------------------------------------------------------------------------*/

        amount_sell = validate_sell_amount(i, stock_balance);

        /* After validation, the amount is deducted from the stock balance. */
        /* Then, the entry is added in the array sells.                     */
        /*------------------------------------------------------------------*/

        stock_balance -= amount_sell;
        sells[i-1] = amount_sell;

        /* The balance is checked to make sure it is greater than 0 in order to allow the */
        /* next transaction (if any). If the balance reaches 0, the loop will break.      */
        /*--------------------------------------------------------------------------------*/

        if(stock_balance == 0)
        {
            printf("***Remaining stock balance reached 0. No more selling transactions allowed!\n");
            how_many_sell = i; /* Updating with the actual number of sell transactions that took place. */
            break;
        }  /* end if block */
    } /* end for loop */

    printf("\n\n");  /* Empty lines for nicer output */

    /* Function call to display a recap of all the transactions with financial advice. */
    /*---------------------------------------------------------------------------------*/

    display_recap(stock_name, initial_balance, stock_balance,
                    how_many_buy, buys, how_many_sell, sells);

    getchar();  /* Wait for user input */

    return 0;

}  /** end main function */


/* Begin get_company_name */
/*------------------------*/

void get_company_name(char name[])
{
    char c;

    printf("Enter the company name: ");
    scanf("%40[^\n]", name);
    while((c = getchar() != '\n') && c != EOF);  /* clear input buffer */
} /* end get_company_name */


/* Begin get_stock_name function */
/*-------------------------------*/

void get_stock_name(char name[])
{
    char c;

    printf("Enter the stock name: ");
    scanf("%20[^\n]", name);
    while((c = getchar() != '\n') && c != EOF);  /* clear input buffer */
} /* end get_stock_name */


/* Begin get_starting_balance function */
/*-------------------------------------*/

int get_starting_balance(char name[])
{
   char c;
   int  balance;

    /* The following do-while loop will trap the user to enter a current balance at least 0 */
    /*--------------------------------------------------------------------------------------*/

    do
    {
        printf("Enter the current number in %s stock portfolio: ", name);
        scanf("%i", &balance);
        while((c = getchar() != '\n') && c != EOF);  /* clear input buffer */

        if(balance < 0)
            printf("***Invalid entry! Current balance must be at least 0 or greater. Try again...\n");

    } while(balance < 0);  /* end do-while trap loop */

   return (balance);
} /* end get_starting_balance */


/* Begin get_transactions_number. This function will be used */
/* to get the number for both: buying and selling.           */
/*-----------------------------------------------------------*/

int get_transactions_number(char mode[], char name[])
{
    char c;
    int  number;

    /* The following do-while loop will trap the user to enter a number of buys */
    /* in the specified range [0..10] both included.                            */
    /*--------------------------------------------------------------------------*/

    do
    {
        printf("Enter the number of %s of %s stock(0-10): ", mode, name);
        scanf("%i", &number);
        while((c = getchar() != '\n') && c != EOF); /* Clear input buffer */

        if(number < 0 || number > 10)
            printf("***Error! Your entry must be between 0 and 10. Try again...\n");

    } while(number < 0 || number > 10);  /* end do-while trap loop */

    return(number);
} /* end get_transactions_number */


/* Begin validate_buy_amount */
/*---------------------------*/

int validate_buy_amount(int i)
{
    char c;
    int  amount;

    /* The following loop will trap the user to enter an amount greater than 0. */
    /*--------------------------------------------------------------------------*/

    do
    {
        printf("Enter the buy #%i: ", i);
        scanf("%i", &amount);
        while((c = getchar() != '\n') && c != EOF);  /* Clear input buffer */

        if(amount <= 0)
            printf("***Error! Amount to buy must be greater than 0. Try again...\n");

    } while(amount <= 0);  /* end do-while trap loop */

    return(amount);
} /* end validate_buy_amount */


/* Begin validate_sell_amount */
/*----------------------------*/

int validate_sell_amount(int i, int balance)
{
    char c;
    int  amount;

    /* The following loop will trap the user to enter an amount */
    /* in the range [1...current stock balance].                */
    /*----------------------------------------------------------*/

    do
    {
        printf("Enter the sell #%i: ", i);
        scanf("%i", &amount);
        while((c = getchar() != '\n') && c != EOF);  /* clear input buffer */

        if(amount > balance || amount < 1)
            printf("***Error! Amount to sell must be between 1 and %i. Try again...\n", balance);

    } while(amount < 1 || amount > balance);  /* end do-while trap loop */

    return(amount);
} /* end validate_sell_amount */


/* Begin display_recap */
/*---------------------*/

void display_recap(char name[], int start_balance, int current_balance,
                   int buys_nr, int buys[], int sells_nr, int sells[])
{
    char c;
    int  i;

    printf("\t\t***%s Stock Portfolio Recap***\n\n", name);
    printf("Starting number of %s stocks: %6i\n\n", name, start_balance);

    /* Displaying all buying transactions */
    /*------------------------------------*/
    for(i = 0; i < buys_nr; i++)
        printf("Buy  #%i:%29i\n", i+1, buys[i]);

    printf("\n");  /* Empty line for nicer output */

    /* Displaying all selling transcations */
    /*-------------------------------------*/

    for(i = 0; i < sells_nr; i++)
        printf("Sell #%i:%29i\n", i+1, sells[i]);

    printf("\nEnding number of %s stocks:  %7i\t\n", name, current_balance);

    /* Selecting and displaying the financial advice based on the ending state of the portfolio. */
    /*-------------------------------------------------------------------------------------------*/

    if(current_balance < 100)
        printf("\"Time to buy more %s stocks!\"\n", name);

    else if(current_balance >= 100 && current_balance < 1000)
        printf("\"%s stocks are at an adequate level!\"\n", name);

    else
        printf("\"You are overstocked with %s stocks. Do not buy more!\"\n", name);
} /* end display_recap */
