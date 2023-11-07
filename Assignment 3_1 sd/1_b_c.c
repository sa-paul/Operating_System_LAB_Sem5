#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    struct stat st;

    // Get the current permissions of the file
    if (stat("test.c", &st) != 0)
    {
        perror("stat");
        exit(1);
    }

    // Modify the permissions using bitwise operations
    st.st_mode |= S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    // To make executable
    // st.st_mode |= S_IXUSR | S_IXGRP | S_IXOTH;

    // Set the new permissions of the file
    if (chmod("test.c", st.st_mode) != 0)
    {
        perror("chmod");
        exit(1);
    }

    return 0;
}
