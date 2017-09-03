#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <vector>

#include <iostream>

#include <thread>

#include <algorithm>
#include <iterator>
#include <numeric>


#include "pars_line.h"

const int PORT = 54321;
