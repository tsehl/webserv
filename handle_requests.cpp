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
            while (getline(ifs, line))
                response << line << std::endl;
            ifs.close();
        }
    }
    //std::cout << "response : \n" << response.str() << std::endl;
    ssize_t bytes_sent = send(client_socket, response.str().c_str(), response.str().size(), 0);
    if (bytes_sent < 0)
        std::cerr << "Erreur lors de l'envoi de données au client" << std::endl;
    return 1;
}

int SearchLocation(std::string path, std::vector<Location> locations)
{
    for (size_t i = 0; i < locations.size(); i++)
    {
        size_t foundPos = path.find(locations[i].getPath());
        if (foundPos == 0) 
        { // Vérifiez si le chemin commence par locationPath
            size_t endPos = locations[i].getPath().size();
            if (endPos == path.size() || (endPos < path.size() && path[endPos] == '/')) 
                return i;  // Vérifiez que le chemin est à la fin ou suivi par '/'
        }
    }
    return (-1);
}

int handle_requests(std::vector<std::string> data, int client_fd, std::vector<Location> locations)
{
    //std::cout << data[1] << std::endl;
    int i = SearchLocation(data[1], locations);
    std::cout << "index = " << i << std::endl;
    if (i != -1)
    {
        data[1].replace(data[1].find(locations[i].getPath()), locations[i].getPath().length(), locations[i].getRoot());
        data[1].insert(0, "/");
    }
    std::cout << "data[1] = " << data[1] << std::endl;
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