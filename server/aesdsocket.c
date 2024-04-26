#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <arpa/inet.h>


static char is_exit = 0;
static const char file_path[] = "/var/tmp/aesdsocketdata";
static const size_t buf_size = 64;

static void signal_handler(int signo) {
    is_exit=1;   
}

int main(int argc, char** argv)
{
    struct sigaction action = {};
    action.sa_handler = &signal_handler;

    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);

    openlog(NULL, 0, LOG_USER);

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    struct addrinfo *result;

    struct sockaddr_in  peer_addr = {};
    socklen_t peer_addr_size;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int s_id = socket(PF_INET, SOCK_STREAM, 0);
    if (s_id == -1)
    {
        fprintf(stderr, "Cannot open socket.\n");
        exit(EXIT_FAILURE);        
    }

    int s = getaddrinfo(NULL, "9000", &hints, &result);
    if (s != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    int bind_res = bind(s_id, result->ai_addr, result->ai_addrlen);
    if (bind_res==-1)
    {
        fprintf(stderr, "Error in binding.\n");
        close(s_id);
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    if ((argc > 1) && (strcmp(argv[1],"-d") == 0)) 
    {
        int pid = fork();
        if (pid!=0)
        {
            exit(EXIT_SUCCESS);
        }
    }

    if (listen(s_id, 1)==-1)
    {
            fprintf(stderr, "Error in listening.\n");
            close(s_id);
            exit(EXIT_FAILURE);
    }

    printf("Listening\n");

    int fd = open(file_path, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU  | S_IRGRP | S_IROTH);

    while(is_exit==0) 
    {
        peer_addr_size = sizeof(peer_addr);
        int cfd = accept(s_id, (struct sockaddr*)&peer_addr, &peer_addr_size);
        if (cfd==-1)
        {
            fprintf(stderr, "Error in accepting.\n");
            close(s_id);
            exit(EXIT_FAILURE);
        }
        char addrs[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &peer_addr.sin_addr, addrs, INET_ADDRSTRLEN);
        syslog(LOG_INFO, "Accepted connection from %s", addrs);

        for(;;) 
        {
            char buf[buf_size]; 

            int recv_len = recv(cfd, buf, sizeof(buf), 0);
            if (recv_len <= 0) {
                break;
            }

            int i=0;
            int end = 0;
            for (i=0; i < recv_len; i++) {
                if (buf[i] == '\n') {
                    i += 1;
                    end = 1;
                    break;
                }
            }

            write(fd, buf, i);

            if (end==1) {
                int rfd = open(file_path, O_RDONLY, 0);
                while (1) {
                    int read_len = read(rfd, buf, sizeof(buf));
                    if (read_len == 0) {
                        break;
                    }

                    send(cfd, buf, read_len, 0);
                }
                close(rfd);
            }
        }
        close(cfd);
        syslog(LOG_INFO, "Closed connection from %s", addrs);
    }

    syslog(LOG_INFO, "Caught signal, exiting");
    close(fd);
    close(s_id);
    unlink(file_path);
    return 0;
}