#ifndef Status_H
#define Status_H

typedef enum
{
    ERR_SUCCESS,
    ERR_BAD_ARGS,
    ERR_STOP,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_LAST,
    ERR_UNDERFLOW

}Status_t;

typedef enum{EMPTY, BEFORE, CURRENT, AFTER, SORTED} Op_t;


#endif
