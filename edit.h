
#ifndef EDIT_H
#define EDIT_H
#include "types.h"
/*
    Structure Name : Edit

    Description:
    This structure stores all information
    required for mp3 tag editing operation.
*/
typedef struct _Edit
{
    /* Original mp3 file name */
    char *edit_file_name;

    /* File pointer for original mp3 file */
    FILE *fptr_edit_file;

    /* Temporary file name */
    char *temp_file_name;

    /* File pointer for temp file */
    FILE *fptr_temp_file;

    /* New data to be updated */
    char *change_data;

    /* ID3 tag to edit */
    char *Tag;

}Edit;

/*
    Function Declarations
*/

/* Validate edit operation arguments */
Status read_validate_argument_of_edit(char *argv[], Edit *edit);

/* Check selected tag option */
Status tag_checking(char *argv[], Edit *edit);

/* Perform complete editing operation */
Status lets_edit_the_data(Edit *edit);

/* Open source and temp files */
Status open_edit_files(Edit *edit);

/* Copy ID3 header */
Status copy_header_file(Edit *edit);

/* Copy and modify frame data */
Status copying_the_data(Edit *edit);

/* Copy remaining mp3 data */
Status copy_remaining_data(Edit *edit);

/* Rename temp file to original file */
Status renameing_temp_file(Edit *edit);

/* Convert endian format */
void convert_endian(char *q);

#endif

