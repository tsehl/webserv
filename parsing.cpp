#include "webserv.hpp"

bool is_cgi_script(const std::string& path) 
{
    static const std::string cgi_extension = ".cgi";

    if (path.size() >= cgi_extension.size() &&
        path.compare(path.size() - cgi_extension.size(), cgi_extension.size(), cgi_extension) == 0) {
        return true;
    }

    return false;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Structure pour stocker les données d'un champ de formulaire
struct FormData {
    std::string name;
    std::string filename;
    std::string contentType;
    std::string data;
};




void handle_cgi_script(int client_socket, std::string script_path, std::string request) {

    parse_upload(request, client_socket);
    pid_t pid = fork();
    if (pid < 0) {
        throw ForkFailedException();
    } else if (pid == 0) {
        script_path.insert(0, "/Users/thsehl/Documents/webserv");
        std::cout << "script : " << script_path << std::endl;
        dup2(client_socket, STDOUT_FILENO);
        dup2(client_socket, STDIN_FILENO);
        
        execve(script_path.c_str(), NULL, NULL);

        throw ExecFailedException();
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}


int parsing_request(std::string request, int client_fd)
{
    if(isspace(request[0]))
        return 0;
    std::vector<std::string> data = split(request, ' ');
    /*std::cout << data[0] << std::endl;
    std::cout << data[1] << std::endl;*/
    if (is_cgi_script(data[1]))
        handle_cgi_script(client_fd, data[1], request);
    else
        handle_requests(data, client_fd);
    return 1;
}

std::vector<std::string> split(const std::string &s, char delim) 
{
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string token;

    while (std::getline(iss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

