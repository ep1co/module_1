#include <stdio.h>
#include <string.h>

int main()
{
    struct animal
    {
        char *name;
        char *size;
    };

    struct animal dog = {"ki", "medium"};
    printf("%s\n", dog.name);
    
    return 0;
}