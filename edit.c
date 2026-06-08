
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "edit.h"
#include "types.h"

 

/*
    Function Name : read_validate_argument_of_edit

    Description:
    This function validates command line arguments
    required for edit operation.
*/
Status read_validate_argument_of_edit(char *argv[], Edit *edit)
{
    /* Check edit option */
    if(argv[2] == NULL)
        return failure;

    /* Validate tag option */
    if(tag_checking(argv, edit) != 0)
        return failure;

    /* Check new data */
    if(argv[3] == NULL)
        return failure;
    else
        edit->change_data = argv[3];

    /* Check mp3 file */
    if(argv[4] == NULL)
        return failure;

    /* Validate .mp3 extension */
    if(strstr(argv[4], ".mp3") != NULL)
        edit->edit_file_name = argv[4];
    else
        return failure;

    /* Store temp file name */
    if(argv[5] == NULL)
        edit->temp_file_name = "temp.mp3";
    else
        edit->temp_file_name = argv[5];

    return success;
}

/*
    Function Name : tag_checking

    Description:
    This function checks which tag
    the user wants to edit.
*/
Status tag_checking(char *argv[], Edit *edit)
{
    /* Song title tag */
    if(strcmp(argv[2], "-t") == 0)
    {
        edit->Tag = "TIT2";
        return success;
    }

    /* Artist tag */
    else if(strcmp(argv[2], "-a") == 0)
    {
        edit->Tag = "TPE1";
        return success;
    }

    /* Album tag */
    else if(strcmp(argv[2], "-A") == 0)
    {
        edit->Tag = "TALB";
        return success;
    }

    /* Year tag */
    else if(strcmp(argv[2], "-y") == 0)
    {
        edit->Tag = "TYER";
        return success;
    }

    /* Content tag */
    else if(strcmp(argv[2], "-m") == 0)
    {
        edit->Tag = "TCON";
        return success;
    }

    /* Comment tag */
    else if(strcmp(argv[2], "-c") == 0)
    {
        edit->Tag = "COMM";
        return success;
    }

    else
        return failure;
}

/*
    Function Name : lets_edit_the_data

    Description:
    This function performs complete
    mp3 tag editing operation.
*/
Status lets_edit_the_data(Edit *edit)
{
    /* Open source and temp files */
    if(open_edit_files(edit) != success)
    {
        printf(RED "File open failed\n" RESET);
        return failure;
    }

    printf(GREEN "Files opened successfully\n" RESET);

    /* Copy ID3 header */
    copy_header_file(edit);

    /* Copy and modify tag data */
    copying_the_data(edit);

    /* Copy remaining file data */
    copy_remaining_data(edit);

    /* Rename temp file */
    renameing_temp_file(edit);

    printf(CYAN "Tag edited successfully\n" RESET);

    return success;
}

/*
    Function Name : open_edit_files

    Description:
    This function opens original mp3 file
    and temporary file.
*/
Status open_edit_files(Edit *edit)
{
    /* Open original mp3 file */
    edit->fptr_edit_file = fopen(edit->edit_file_name, "r");

    if(edit->fptr_edit_file == NULL)
        return failure;

    /* Open temp file */
    edit->fptr_temp_file = fopen(edit->temp_file_name, "w");

    if(edit->fptr_temp_file == NULL)
        return failure;

    return success;
}

/*
    Function Name : copy_header_file

    Description:
    This function copies first 10 bytes
    of ID3 header into temp file.
*/
Status copy_header_file(Edit *edit)
{
    char buff[10];

    fread(buff, 10, 1, edit->fptr_edit_file);

    fwrite(buff, 10, 1, edit->fptr_temp_file);

    return success;
}

/*
    Function Name : copying_the_data

    Description:
    This function reads all tag frames,
    modifies required tag and copies
    remaining data into temp file.
*/
Status copying_the_data(Edit *edit)
{
    int found = 0;

    while(!found)
    {
        char tag[5] = {0};
        int size;
        char flag[2];
        char encoding;

        /* Read frame tag */
        if(fread(tag, 4, 1, edit->fptr_edit_file) != 1)
            return failure;

        /* Read frame size */
        if(fread(&size, 4, 1, edit->fptr_edit_file) != 1)
            return failure;

        /* Convert endian format */
        convert_endian((char *)&size);

        int original_size = size;

        /* Allocate memory for frame data */
        char *data = malloc(size);

        /* Read frame information */
        fread(flag, 2, 1, edit->fptr_edit_file);

        fread(&encoding, 1, 1, edit->fptr_edit_file);

        fread(data, size - 1, 1, edit->fptr_edit_file);

        /* Check matching tag */
        if(strcmp(edit->Tag, tag) == 0)
        {
            /* Update new data size */
            size = 1 + strlen(edit->change_data);

            convert_endian((char *)&size);

            /* Write updated frame */
            fwrite(tag, 4, 1, edit->fptr_temp_file);

            fwrite(&size, 4, 1, edit->fptr_temp_file);

            fwrite(flag, 2, 1, edit->fptr_temp_file);

            fwrite(&encoding, 1, 1, edit->fptr_temp_file);

            fwrite(edit->change_data, strlen(edit->change_data), 1, edit->fptr_temp_file);

            found = 1;
        }
        else
        {
            /* Write original frame */
            convert_endian((char *)&original_size);

            fwrite(tag, 4, 1, edit->fptr_temp_file);

            fwrite(&original_size, 4, 1, edit->fptr_temp_file);

            fwrite(flag, 2, 1, edit->fptr_temp_file);

            fwrite(&encoding, 1, 1, edit->fptr_temp_file);

            fwrite(data, size - 1, 1, edit->fptr_temp_file);
        }

        /* Free allocated memory */
        free(data);
    }

    return success;
}

/*
    Function Name : copy_remaining_data

    Description:
    This function copies remaining mp3 data
    into temp file after editing.
*/
Status copy_remaining_data(Edit *edit)
{
    char ch;

    while(fread(&ch, 1, 1, edit->fptr_edit_file))
    {
        fwrite(&ch, 1, 1, edit->fptr_temp_file);
    }

    return success;
}

/*
    Function Name : renameing_temp_file

    Description:
    If user gives output file name,
    edited data will be stored in new file.

    If user does not give output file name,
    original mp3 file will be replaced.
*/
Status renameing_temp_file(Edit *edit)
{
    fclose(edit->fptr_edit_file);

    fclose(edit->fptr_temp_file);

    /* Check whether user provided output file */
    if(strcmp(edit->temp_file_name, "temp.mp3") == 0)
    {
        /* Replace original file */
        remove(edit->edit_file_name);

        rename(edit->temp_file_name, edit->edit_file_name);
    }

    return success;
}



/*
    Function Name : convert_endian

    Description:
    This function converts endian format
    of integer data.
*/
void convert_endian(char *q)
{
    for(int i = 0; i < 2; i++)
    {
        char t = q[i];

        q[i] = q[3 - i];

        q[3 - i] = t;
    }
}

