#include "webserv.hpp"

int main()
{
    try
    {
        int valread;
        std::string buffer(1024, '\0');
        int client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (client_fd < 0)
            throw SocketFailedException();
        struct sockaddr_in address;
        const int PORT = 8080;
        memset((char *)&address, 0, sizeof(address)); 
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = htonl(INADDR_ANY); 
        address.sin_port = htons(PORT); 
        long len = sizeof(address);
        if ((connect(client_fd,  (struct sockaddr *)&address, len)) < 0)
            throw ConnectFailedException();
        send(client_fd, "hillo", 5, 0);
        valread = read(client_fd, &buffer[0], 1024); // Utilisation de i au lieu de client_fd
        if (valread < 0)
            throw ReadFailedException();
        write(0,&buffer[0], 1024);

    }
    catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
    }
}