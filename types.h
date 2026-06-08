#ifndef TYPES_H
#define TYPES_H

/* Typedef for creating the alias to unsigned int data type */
typedef unsigned int uint;
/* Color macros for terminal output */
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define BLUE    "\033[1;34m"
#define YELLOW  "\033[1;33m"

/* Status will be used as Function return type */
typedef enum
{
    success,
    failure
} Status;

typedef enum
{
    p_view,
    p_edit,
    p_help,
    p_unsupported
} OperationType;

#endif
