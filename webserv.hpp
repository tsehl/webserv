#ifndef WEBSERV_HPP
# define WEBSERV_HPP

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
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include "Server.hpp"

using namespace std;


int handle_requests(std::vector<std::string> data, int client_fd);
int parsing_request(std::string buffer, int client_fd);
int parserConfig(std::vector<Server> server, std::string path_configfile);
std::vector<std::string> split(const std::string &s, char delim);

class ErrorConfigFileException : public std::exception
{
    const char * what () const throw () {return ("Error configuration file") ;}
};

class ErrorParserConfigException : public std::exception
{
    const char * what () const throw () {return ("Error parsing configuration file") ;}
};

class SocketFailedException : public std::exception
{
    const char * what () const throw () {return ("Socket creation failed") ;}
};

class ConnectFailedException : public std::exception
{
    const char * what () const throw () {return ("Connect failure") ;}
};

class HttpErrorException : public std::exception
{
    const char * what () const throw () {return ("open http error file failed") ;}
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

#endif