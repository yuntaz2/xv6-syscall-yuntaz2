#include "kernel/types.h" // something is wrong in the user.h that has to be declared later than types.h
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(-1);
    }
    int guess = atoi(argv[1]);
    int result = pidguess(guess);
    switch (result)
    {
    case 1:
    {
        printf("Guess %d is correct.\n", guess);
        break;
    }
    case -1:
    {
        printf("Error in exec pidguess().\n");
        break;
    }
    case 0:
    {
        printf("Guess %d is incorrect; The correct answer is %d.\n", guess, getpid());
        break;
    }
    default:
    {
        printf("something is wrong...\n");
    }
    }
    exit(0);
}