#include "webserv.hpp"

bool is_cgi_script(const std::string& path) 
{
    // Vérifier si le chemin se termine par l'extension .cgi
    static const std::string cgi_extension = ".cgi";

    if (path.size() >= cgi_extension.size() &&
        path.compare(path.size() - cgi_extension.size(), cgi_extension.size(), cgi_extension) == 0) {
        return true;
    }

    return false;
}

void handle_cgi_script(int client_socket, std::string script_path) {
    // Créer un processus fils pour exécuter le script CGI
    //std::cout << "CGI script detected" << std::endl;
    pid_t pid = fork();
    if (pid < 0) {
        throw ForkFailedException();
    } else if (pid == 0) {
        script_path.insert(0, "/Users/thsehl/Documents/webserv");
        //std::cout << script_path << std::endl;
        dup2(client_socket, STDOUT_FILENO);
        dup2(client_socket, STDIN_FILENO);
        
        
        execve(script_path.c_str(), NULL, NULL);

        throw ExecFailedException();
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}


int parsing_request(std::string buffer, int client_fd)
{
    if(isspace(buffer[0]))
        return 0;
    std::vector<std::string> data = split(buffer, ' ');
    /*std::cout << data[0] << std::endl;
    std::cout << data[1] << std::endl;*/
    if (is_cgi_script(data[1]))
        handle_cgi_script(client_fd, data[1]);
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

