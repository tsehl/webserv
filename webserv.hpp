#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <exception>
# include <netinet/in.h>
# include <sys/socket.h> 
# include <cstring>
# include <string>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fstream>
# include <sstream>
# include <cctype>
# include <fcntl.h>
# include <vector>
# include <dirent.h>
# include "Server.hpp"
#include <map>

class Server;

int handle_requests(std::vector<std::string> data, int client_fd);
int parsing_request(std::string request, int client_fd);
std::vector<std::string> split(const std::string &s, char delim);
int parserConfig(std::vector<Server>& server, std::string path_configfile);
std::string parseMultipartFormData(const std::string& formData);


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

class ExecFailedException : public std::exception
{
    const char * what () const throw () {return ("execve failed") ;}
};

class InvalidFormDataException : public std::exception
{
    const char * what () const throw () {return ("Invalid form data") ;}
};

class AcceptFailedException : public std::exception
{
    const char * what () const throw () {return ("Accept failed") ;}
};

class ForkfailedException : public std::exception
{
    const char * what () const throw () {return ("Fork error") ;}
};

class RecvFailedException : public std::exception
{
    const char * what () const throw () {return ("Recv failed") ;}
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

/*# include <iostream>
# include <exception>
# include <netinet/in.h>
# include <sys/socket.h> 
# include <cstring>

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