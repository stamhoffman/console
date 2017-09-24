#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <thread>

#include "pars_line.h"

const int PORT = 54321;
