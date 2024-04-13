#include "Server.hpp"
#define BUFFER_SIZE 512

void handle_client(size_t max_body_size, int client_socket, std::vector<Location> locations) 
{
    char buffer[BUFFER_SIZE];
    long long bytes_received = 0;
    std::string request = "";
    //const int max_body_size = 10000; // Exemple de taille maximale.

    do
    {
        usleep(100);
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
        //std::cout << "bytes_received : " << bytes_received << std::endl;
        if (bytes_received > 0) 
        {
            buffer[bytes_received] = '\0';
            request.append(buffer);
            if (request.length() > max_body_size) 
            {
                std::cout << "La taille de la requête dépasse la limite autorisée.\n";
                request = "GET /html/400.html HTTP/1.1";
                break;
            }
        }
        else if (bytes_received < 0) 
        {
            close(client_socket);
            throw RecvFailedException();
        }
    } while (static_cast<unsigned long>(bytes_received) >= sizeof(buffer) - 1);
    
    //std::cout << "Request:\n" << request << std::endl << request.size() << std::endl;
    parsing_request(request, client_socket, locations);
}

std::string check_configfile(std::string path_configfile)
{
    std::string ext(5, 'a');
    int index = 0;
    for (size_t i = path_configfile.length() - 5; i < path_configfile.length(); i++)
    {
        ext[index] = path_configfile[i];
        index++;
    }
    if (ext.compare(".conf") == 0 && path_configfile.length() > 5)
        return (path_configfile);
    return ("");
}

int main(int ac, char **ar)
{
    int client_fd = -1;
    try
    {
        std::string path_configfile;
        if (ac > 2)
            throw ErrorConfigFileException();
        if (ac == 1)
            path_configfile = "config/default.conf";
        else
            path_configfile = check_configfile(ar[1]);
        if (path_configfile == "")
            throw ErrorConfigFileException();
        int max_fd = -1;
        std::vector<Server> server;
        fd_set read_fds, master_fds;
        int nb_server = parserConfig(server, path_configfile);
        if (nb_server < 1)
            throw ErrorParserConfigException();;
        for (size_t i = 0; i < server.size(); i++)
        {
            //std::cout << server[i].getBodySize() << std::endl;
            //std::cout << server[i].getServerName() << std::endl;
            //std::cout << server[i].getPort() << std::endl;
        }
       //std::cout << server[0].getHost() << std::endl;
        FD_ZERO(&master_fds);
        for (int i = 0; i < nb_server; ++i)
        { 
            //std::cout << server[i].getBodySize() << " port "<< server[i].getPort() << std::endl;
            if (server[i].getServerSocket() > max_fd)
                max_fd = server[i].getServerSocket();
            FD_SET(server[i].getServerSocket(), &master_fds);
        }
        while (1) 
        {
            read_fds = master_fds;
            if (select(FD_SETSIZE, &read_fds, NULL, NULL, NULL) < 0)
                throw SelectFailedException(); 

            for (int i = 0; i < max_fd; ++i) 
            {
                if (FD_ISSET(server[i].getServerSocket(), &read_fds)) 
                {
                    server[i].acceptClient();
                    if (server[i].getLastClientSocket() < 0)
                        std::cerr << "Erreur lors de l'acceptation de la connexion client" << std::endl;
                if (server[i].getLastClientSocket() > max_fd)
                    max_fd = server[i].getLastClientSocket();
                //std::cout << "Nouvelle connexion sur le serveur " << i << std::endl;
                FD_SET(server[i].getLastClientSocket(), &master_fds); 
                }
            }
            for (int i = 0; i < nb_server; ++i) 
            {
                for (size_t j = 0; j < server[i].getClientSocket().size(); ++j) 
                {
                    client_fd = server[i].getClientSocket(j);
                    if (FD_ISSET(client_fd, &read_fds)) 
                    {
                        handle_client(server[i].getBodySize(), client_fd, server[i].getVecLocation());
                        close(client_fd);
                        FD_CLR(client_fd, &read_fds);
                        FD_CLR(client_fd, &master_fds);
                        server[i].removeClient(j);
                    }
                }
            }
            
        }
    }
    catch (std::exception &e)
    {
        if (fcntl(client_fd, F_GETFL) > 0)
            close(client_fd);
        std::cerr << e.what() << std::endl;
    }       
}     