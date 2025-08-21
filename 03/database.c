#include "database.h"
#include "contacts.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

extern Contact contacts[ARR_SIZE];

int openDB(char *filename)
{
    int fd = open(filename, O_RDWR | O_CREAT);
    int i = 0;
    ssize_t data;
    while (i < ARR_SIZE)
    {
        Contact c;
        data = read(fd, &c, sizeof(Contact));
        if (data <= 0)
        {
            break;
        }
        if (data != sizeof(Contact))
        {
            break;
        }
        contacts[i++] = c;
    }
    return fd;
}

void closeDB(int fd)
{
    long bytes_written = write(fd, contacts, ARR_SIZE * sizeof(Contact));
    close(fd);
}
