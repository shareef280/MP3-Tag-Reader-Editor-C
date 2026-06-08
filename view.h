
#ifndef VIEW_H
#define VIEW_H
#include"types.h"
/*
    Structure Name : View

    Description:
    This structure stores information
    required for viewing mp3 tag details.
*/
typedef struct _View
{
    /* Mp3 file name */
    char *mp3_file_name;

    /* File pointer for mp3 file */
    FILE *fptr_mp3;

}View;

/*
    Function Declarations
*/

/* Display usage instructions */
void help();

/* Validate command line arguments */
Status read_validate_argument(char *argv[], View *view);

/* Display help menu */
void help_function();

/* Perform complete viewing operation */
Status viewing(View *view);

/* Open mp3 file */
Status open_files(View *view);

/* Skip ID3 header */
Status skiping_header(View *view);

/* Read tag data */
Status read_data(View *view);

/* Display tag details */
Status display(char *data, char *tag, int size);

#endif

