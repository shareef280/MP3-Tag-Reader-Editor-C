
/*
    DESCRIPTION

    NAME: shareef sab
    BATCH: 26001B
    PROJECT TITLE: MP3 TAG READER and editor
    DATE: 7 jun 2026

    This program is used to:
    1. View MP3 tag details
    2. Edit MP3 tag details
    3. Display help menu

    Supported ID3 Tags:
    - Title
    - Artist
    - Album
    - Year
    - Content
    - Comment
*/

#include <stdio.h>
#include <string.h>
#include "view.h"
#include "edit.h"
#include"types.h"

 

/* Function declaration */
OperationType check_operation_type(char *argv[]);

Status main(int argc, char *argv[])
{
    /* Structure variable for viewing operation */
    View view;
    
    /* Check whether user selected view operation */
    if(check_operation_type(argv) == p_view)
    {
        printf(CYAN "----- YOU CHOOSED TO VIEW MP3 TAG -----\n" RESET);

        /* Validate command line arguments */
        if(read_validate_argument(argv, &view) == success)
        {
            printf(GREEN "Validation is successful\n" RESET);

            /* Call viewing function */
            if(viewing(&view) == success)
                printf(GREEN "---------- DETAILS DISPLAYED SUCCESSFULLY -----------\n" RESET);
            else
            {
                printf(RED "------------ VIEWING DETAILS UN-SUCCESSFULL--------- ---\n" RESET);
                return failure;
            }
        }
        else
        {
            printf(RED "Validation is unsuccessful\n" RESET);
            return failure;
        }
    }

    /* Check whether user selected edit operation */
    else if(check_operation_type(argv) == p_edit)
    {
        /* Structure variable for editing operation */
        Edit edit;

        printf(CYAN "------------- YOU CHOOSED TO EDIT MP3 TAG ------------\n" RESET);

        /* Validate edit operation arguments */
        if(read_validate_argument_of_edit(argv, &edit) == success)
        {
            printf(GREEN "Read validate argument is successful\n" RESET);

            /* Call editing function */
            if(lets_edit_the_data(&edit) == 0)
                printf(GREEN "----------- EDITING IS SUCCESSFULL ----------\n" RESET);
            else
                printf(RED "------------ EDITING IS UN-SUCCESSFULL---------\n" RESET);
        }
        else
        {
            printf(RED "Read validate argument is unsuccessful\n" RESET);

            /* Display help menu if validation fails */
            help();
            help_function();

            return failure;
        }
        
    }

    /* Check whether user selected help option */
    else if(check_operation_type(argv) == p_help)
    {
        printf(YELLOW "---------- HELP MENU ----------\n" RESET);

        help_function();
    }

    /* Invalid argument handling */
    else
    {
        printf(RED "ERROR: INVALID ARGUMENTS\n" RESET);

        help();
    }
    return success;
}

/*
    Function Name : check_operation_type

    Description:
    This function checks which operation
    the user selected using command line arguments.

    Return Values:
    0 -> View
    1 -> Edit
    2 -> Help
    3 -> Invalid argument
*/
OperationType check_operation_type(char *argv[])
{
    /* Check whether argument is present */
    if(argv[1] == NULL)
        return p_unsupported;

    /* Compare operation arguments */
    if(strcmp(argv[1],"-v") == 0)
        return p_view;
    else if(strcmp(argv[1],"-e") == 0)
        return p_edit;
    else if(strcmp(argv[1],"--help") == 0)
        return p_help;
    else
        return p_unsupported;
}

/*
    Function Name : help_function

    Description:
    This function displays all supported
    commands and editing options.
*/
void help_function()
{
    printf(YELLOW "-----------------------------------------------------\n" RESET);

    printf(BLUE "1. -v -> to view mp3 file contents\n" RESET);

    printf(BLUE "2. -e -> to edit mp3 file contents\n" RESET);

    printf(BLUE "         2.1 -t -> to edit song title\n" RESET);

    printf(BLUE "         2.2 -a -> to edit artist name\n" RESET);

    printf(BLUE "         2.3 -A -> to edit album name\n" RESET);

    printf(BLUE "         2.4 -y -> to edit year\n" RESET);

    printf(BLUE "         2.5 -m -> to edit content\n" RESET);

    printf(BLUE "         2.6 -c -> to edit comment\n" RESET);

    printf(YELLOW "-----------------------------------------------------\n" RESET);
}

/*
    Function Name : help

    Description:
    This function displays the correct
    command format to run the program.
*/
void help()
{
    printf(CYAN "For viewing: ./a.out -v mp3filename\n" RESET);

    printf(CYAN "For editing: ./a.out -e -t/-a/-A/-m/-y/-c data mp3filename\n" RESET);

    printf(CYAN "For help: ./a.out --help\n" RESET);
}

