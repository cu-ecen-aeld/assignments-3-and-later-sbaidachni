#include <syslog.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv)
{
    openlog(NULL, 0, LOG_USER);
    if (argc!=3)
    {
        syslog(LOG_ERR, "Incorrect number of arguments");
        return 1;
    }
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU  | S_IRGRP | S_IROTH );
    if (fd==-1)
    {
        syslog(LOG_ERR, "Cannot create the file");
        return 1;
    }
    write(fd, argv[2], strlen(argv[2]));
    syslog(LOG_DEBUG , "Writing %s to %s", argv[2], argv[1]);
    return 0;
}