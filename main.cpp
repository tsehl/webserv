#include "Server.hpp"


void handle_client(int client_socket) 
{
    char buffer [1000];
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
        else if (bytes_received > 0) 
        {
            buffer[bytes_received] = '\0';
            request.append(buffer);
        }
    }
    std::cout << request << std::endl;
    parsing_request(request, client_socket);
}

int main()
{
    int client_fd = 1000000;
    try
    {
        int nb_server= 3;
        int max_fd = -1;
        int ports[] = {8080, 8081, 8082};
        std::vector<Server> server;
        fd_set read_fds, master_fds;
        for (int i = 0; i < nb_server; i++)
            server.push_back(Server(ports[i]));
        //std::cout << "Servers have been created." << std::endl;
        FD_ZERO(&master_fds);
        for (int i = 0; i < nb_server; ++i)
        { 
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
                        handle_client(client_fd);
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

