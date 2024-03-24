#include "webserv.hpp"

int handle_get(std::string path, int client_socket)
{
    std::stringstream response;
    std::ifstream ifs;
    std::string line;
    int is_file = 0;
    DIR * dir = NULL;
    if (path == "/")
        path = "html/default.html";
    else
        path = path.substr(1);
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    ifs.open (path, std::ifstream::in);
    if(ifs.is_open())
    {
       while (getline(ifs, line))
        {
            response << line << std::endl;
            is_file = 1;
        }
        ifs.close();
    }
    if (is_file == 0)
    {
        dir = opendir(path.c_str());
        if (dir != NULL) 
        {
            dirent* entry;
            while ((entry = readdir(dir)) != NULL) 
                    response << "<li><a href='" << path << "/" << entry->d_name << "'>" << entry->d_name << "</a></li>";
             closedir(dir);
        }
        else
        {
            ifs.open ("html/404.html", std::ifstream::in);
            if(!ifs.is_open())
                throw HttpErrorException();
        }
    }
    //std::cout << "response : \n" << response.str() << std::endl;
    ssize_t bytes_sent = send(client_socket, response.str().c_str(), response.str().size(), 0);
    if (bytes_sent < 0)
        std::cerr << "Erreur lors de l'envoi de données au client" << std::endl;
    return 1;
}

int handle_requests(std::vector<std::string> data, int client_fd)
{
    
    if (data[0] == "GET") {
        handle_get(data[1], client_fd);
    /*} else if (data[0] == "POST") {
        std::cout << "Vous avez choisi 2" << std::endl;
    } else if (data[0] == "DELETE") {
        std::cout << "Vous avez choisi 3" << std::endl;*/
    } else {
        return (0);
    }
    return (1);
}