#include <iostream>
#include <exception>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <cstring>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

class SocketFailedException : public std::exception
{
    const char * what () const throw () {return ("Socket creation failed") ;}
};

class ConnectFailedException : public std::exception
{
    const char * what () const throw () {return ("Connect failure") ;}
};


class SelectFailedException : public std::exception
{
    const char * what () const throw () {return ("Select failed") ;}
};

class BindFailedException : public std::exception
{
    const char * what () const throw () {return ("Binding failed") ;}
};

class ListenFailedException : public std::exception
{
    const char * what () const throw () {return ("Listen failed") ;}
};

class AcceptFailedException : public std::exception
{
    const char * what () const throw () {return ("Accept failed") ;}
};

class ReadFailedException : public std::exception
{
    const char * what () const throw () {return ("Read failed") ;}
};

class ForkFailedException : public std::exception
{
    const char * what () const throw () {return ("Forkfailed") ;}
};

class PipeFailedException : public std::exception
{
    const char * what () const throw () {return ("Pipe failed") ;}
};

/*#include <iostream>
#include <exception>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <cstring>

class SocketFailedException : public std::exception
{
    const char * what () const throw () {return ("Socket failed") ;}
};

class BindFailedException : public std::exception
{
    const char * what () const throw () {return ("Binding failed") ;}
};

class ListenFailedException : public std::exception
{
    const char * what () const throw () {return ("Listen failed") ;}
};

class AcceptFailedException : public std::exception
{
    const char * what () const throw () {return ("Accept failed") ;}
};*/