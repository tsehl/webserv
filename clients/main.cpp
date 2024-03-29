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
    //write(0, &buffer[0], 100);
    parsing_request(request, client_socket);
}

int main()
{
    try
    {
        Server server(8080);
        fd_set ready_sockets;
        while (1) 
        {
                ready_sockets = server.getSockets();
            if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
                throw SelectFailedException();
            for (int i = 0; i < FD_SETSIZE; i++) 
            {
                if (FD_ISSET(i, &ready_sockets)) 
                {
                    if (i == server.getServerSocket()) 
                        server.acceptClient();
                    else 
                    {
                        handle_client(i);
                        server.clearSockets(i);
                        close(i);
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