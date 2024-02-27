#include "webserv.hpp"

class Server 
{
    public:

        Server();
        Server(int port);
        ~Server();
        Server(const Server& other);
        Server& operator=(const Server& other);
        void init_server();
        void clearSockets(int i);
        void acceptClient();

        // Getters
        int getClientSocket() const;
        int getServerSocket() const;
        struct sockaddr_in getAddress() const;
        int getValRead() const;
        fd_set getSockets() const;
        int getPort() const;

        // Setters
        void setClientSocket(int clientSocket);
        void setServerSocket(int serverSocket);
        void setAddress(const struct sockaddr_in& address);
        void setValRead(int valRead);
        void setSockets(const fd_set& sockets);
        void setPort(int port);

    private:

        int _client_socket;
        int _server_socket;
        struct sockaddr_in _address;
        int _valread;
        fd_set _sockets;
        int _port;
};
    