
#include <stdio.h>
#include <string.h>
#include "view.h"
#include "types.h"

/* Color macros for terminal output */
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"

/*
    Function Name : read_validate_argument

    Description:
    This function validates the command line argument
    and checks whether the given file is an mp3 file.
*/
Status read_validate_argument(char *argv[], View *view)
{
    /* Check whether file name is entered */
    if(argv[2] == NULL)
    {
        printf(RED "Invalid command\n" RESET);
        return failure;
    }

    /* Check .mp3 extension */
    if(strstr(argv[2],".mp3") != NULL)
    {
        view->mp3_file_name = argv[2];
        return success;
    }
    else
    {
        printf(RED "File must be .mp3\n" RESET);
        return failure;
    }
}

/*
    Function Name : viewing

    Description:
    This function performs the complete
    viewing operation of mp3 tags.
*/
Status viewing(View *view)
{
    /* Open mp3 file */
    if(open_files(view) != success)
    {
        printf(RED "File opening unsuccessful\n" RESET);
        return failure;
    }

    printf(GREEN "File open successful\n" RESET);

    /* Skip ID3 header */
    skiping_header(view);

    printf(GREEN "Skipping header successful\n" RESET);

    /* Read and display tag data */
    return read_data(view);
}

/*
    Function Name : open_files

    Description:
    This function opens the mp3 file
    in read mode.
*/
Status open_files(View *view)
{
    view->fptr_mp3 = fopen(view->mp3_file_name,"r");

    return view->fptr_mp3 == NULL;
}

/*
    Function Name : skiping_header

    Description:
    This function skips the first
    10 bytes of ID3 header.
*/
Status skiping_header(View *view)
{
    fseek(view->fptr_mp3,10,SEEK_SET);

    return success;
}

/*
    Function Name : read_data

    Description:
    This function reads the mp3 tag frames,
    extracts tag information and displays it.
*/
Status read_data(View *view)
{
    int count = 0;

    /* Display table header */
    printf(YELLOW "-----------------------------------------------------\n" RESET);

    printf(YELLOW "| TAG NAME     |     DATA                           |\n" RESET);

    printf(YELLOW "-----------------------------------------------------\n" RESET);

    /* Loop until all required tags are displayed */
    while(count < 6)
    {
        char tag[5] = {0};
        int size;

        /* Read frame tag */
        fread(tag, 4, 1, view->fptr_mp3);

        /* Read frame size */
        fread(&size, 4, 1, view->fptr_mp3);

        /* Convert big endian to little endian */
        char *p = (char *)&size;

        for(int i = 0; i < 2; i++)
        {
            char t = p[i];
            p[i] = p[3 - i];
            p[3 - i] = t;
        }

        /* Skip flags and encoding bytes */
        fseek(view->fptr_mp3, 3, SEEK_CUR);

        /* Read actual tag data */
        char name[size];
        // size-1 beacouse  1 bytes is for encoding 
        fread(name, size - 1, 1, view->fptr_mp3);

        name[size - 1] = '\0';

        /* Display tag details */
        if(display(name, tag, size - 1) == 0)
            count++;
    }

    printf(YELLOW "-----------------------------------------------------\n" RESET);

    return success;
}

/*
    Function Name : display

    Description:
    This function compares tag names
    and displays corresponding mp3 data.
*/
Status display(char *data, char *tag, int size)
{
    data[size] = '\0';

    /* Display title */
    if(strcmp(tag, "TIT2") == 0)
        printf(BLUE "| Title        | %-35s|\n" RESET,data);

    /* Display year */
    else if(strcmp(tag, "TYER") == 0)
        printf(BLUE "| Year         | %-35s|\n" RESET,data);

    /* Display album */
    else if(strcmp(tag, "TALB") == 0)
        printf(BLUE "| Album        | %-35s|\n" RESET,data);

    /* Display comment */
    else if(strcmp(tag, "COMM") == 0)
        printf(BLUE "| Comments     | %-35s|\n" RESET,data);

    /* Display artist */
    else if(strcmp(tag, "TPE1") == 0)
        printf(BLUE "| Artist       | %-35s|\n" RESET,data);

    /* Display content type */
    else if(strcmp(tag, "TCON") == 0)
        printf(BLUE "| Content      | %-35s|\n" RESET,data);

    else
        return failure;

    return success;
}

