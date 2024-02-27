#include "webserv.hpp"

int parsing_request(std::string buffer, int client_fd)
{
    if(isspace(buffer[0]))
        return 0;
    std::vector<std::string> data = split(buffer, ' ');
    /*std::cout << data[0] << std::endl;
    std::cout << data[1] << std::endl;*/
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