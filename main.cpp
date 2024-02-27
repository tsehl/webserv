#include "Server.hpp"

void handle_client(int client_socket) 
{
    char buffer [1024];

    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) 
    {
        std::cerr << "Erreur lors de la réception de données depuis le client" << std::endl;
        close(client_socket);
        return;
    }
    std::string request(buffer);
    std::cout << buffer << std::endl;
    parsing_request(request, client_socket);
}

int main()
{
    try
    {
        int nb_server= 3;
        int ports[] = {8080, 8081, 8082};
        std::vector<Server> server;
        for (int i = 0; i < nb_server; i++)
            server.push_back(Server(ports[i]));
        //std::cout << "Servers have been created." << std::endl;
        fd_set ready_sockets;
        while (1) 
        {
            for (int i = 0; i < nb_server; i++)
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
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}