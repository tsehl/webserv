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
    std::cout << "response : \n" << response.str() << std::endl;
    ssize_t bytes_sent = send(client_socket, response.str().c_str(), response.str().size(), 0);
    //std::cout << response.str() << std::endl;
    if (bytes_sent < 0)
        std::cerr << "Erreur lors de l'envoi de données au client" << std::endl;
    return 1;
}

void handle_delete(std::string path, int client_socket)
{
    std::stringstream response;
    std::string line;
    int is_file = 0;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    //std::cout << "path = " << path << std::endl;
    path.insert(0, ".");
    if (remove(path.c_str()) != 0)
    {
        response << "Error deleting file\n";
        is_file = 1;
    }
    if (is_file == 0)
        response << "File deleted\n";
    ssize_t bytes_sent = send(client_socket, response.str().c_str(), response.str().size(), 0);
    if (bytes_sent < 0)
        std::cerr << "Erreur lors de l'envoi de données au client" << std::endl;
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

int handle_requests(std::vector<std::string> data, int client_fd, std::vector<Location> locations, Server server)
{
    //std::cout << data[1] << std::endl;
    server.setVecLocation(locations);
    int i = SearchLocation(data[1], locations);
    if (i != -1)
    {
        data[1].replace(data[1].find(locations[i].getPath()), locations[i].getPath().length(), locations[i].getRoot());
        data[1].insert(0, "/");
    }
    if (data[0] == "GET" && i != -1)
    {
        if (locations[i].getAllowGet())
            handle_get(data[1], client_fd);
    }
    else if (data[0] == "DELETE" && i != -1)
    {   
        if (locations[i].getAllowDelete())
            handle_delete(data[1], client_fd);
    }
    if (i == -1 && data[0] == "GET" && server.getAllowGet())
        handle_get(data[1], client_fd);
    else if (i == -1 && data[0] == "DELETE" && server.getAllowDelete())
        handle_delete(data[1], client_fd);
    else
        return (0);
    return (1);
}