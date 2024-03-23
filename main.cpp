#include "Server.hpp"


void handle_client(size_t max_body_size, int client_socket) 
{
    char buffer [100000];
    size_t bytes_received = sizeof(buffer);
    std::string request;

    while (bytes_received >= sizeof(buffer))
    {
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received < 0) 
        {   
            close(client_socket);
            throw RecvFailedException();
        }
        else if(bytes_received > max_body_size)
        {
            std::cout << bytes_received << " bd "<< max_body_size << std::endl;
            request = "GET /html/400.html HTTP/1.1";
        }
        else if (bytes_received > 0) 
        {
            buffer[bytes_received] = '\0';
            request.append(buffer);
        }
    }
    std::cout << request << std::endl;
    parsing_request(request, client_socket);
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
        //int nb_server= 3;
        int max_fd = -1;
        //int ports[] = {8080, 8081, 8082};
        std::vector<Server> server;
        fd_set read_fds, master_fds;
        int nb_server = parserConfig(server, path_configfile);
        if (nb_server < 1)
            throw ErrorParserConfigException();
        /*for (int i = 0; i < nb_server; i++)
            server.push_back(Server(ports[i]));*/
        //std::cout << "Servers have been created." << std::endl;
        FD_ZERO(&master_fds);
        for (int i = 0; i < nb_server; ++i)
        { 
            std::cout << server[i].getBodySize() << " port "<< server[i].getPort() << std::endl;
            if (server[i].getServerSocket() > max_fd)
                max_fd = server[i].getServerSocket();
            FD_SET(server[i].getServerSocket(), &master_fds);
        }
        while (1) 
        {
            read_fds = master_fds;
            if (select(FD_SETSIZE, &read_fds, nullptr, nullptr, nullptr) < 0)
                throw SelectFailedException(); 

            for (int i = 0; i < max_fd; ++i) 
            {
                if (FD_ISSET(server[i].getServerSocket(), &read_fds)) 
                {
                    server[i].acceptClient();
                    if (server[i].getLastClientSocket() < 0) {
                        std::cerr << "Erreur lors de l'acceptation de la connexion client" << std::endl;
                }
                if (server[i].getLastClientSocket() > max_fd)
                    max_fd = server[i].getLastClientSocket();
                std::cout << "Nouvelle connexion sur le serveur " << i << std::endl;
                FD_SET(server[i].getLastClientSocket(), &master_fds); // Ajout du descripteur à l'ensemble maître
                }
            }

        // Parcourir les descripteurs pour les clients
            for (int i = 0; i < nb_server; ++i) 
            {
                for (size_t j = 0; j < server[i].getClientSocket().size(); ++j) 
                {
                    client_fd = server[i].getClientSocket(j);
                    if (FD_ISSET(client_fd, &read_fds)) 
                    {
                        handle_client(server[i].getBodySize(), client_fd);
                        close(client_fd);
                        FD_CLR(client_fd, &read_fds);
                        FD_CLR(client_fd, &master_fds);
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
            /*for (int i = 0; i < nb_server; i++)
            {
                std::cout << "Server " << i << " is listening on port " << server[i].getPort() << std::endl;
                ready_sockets = server[i].getSockets();
                if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
                    throw SelectFailedException();
                for (int j = 0; j < FD_SETSIZE; j++) 
                {
                    if (FD_ISSET(j, &ready_sockets)) 
                    {
                        if (j == server[i].getServerSocket()) 
                            server[i].acceptClient();
                        else 
                        {
                            handle_client(j);
                            server[i].clearSockets(j);
                            close(j);
                        }
                    }
                }
            }*/

