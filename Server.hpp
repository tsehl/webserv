
#ifndef SERVER_HPP
# define SERVER_HPP
# include "webserv.hpp"

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
        void addClient(int client_sockets);

        // Getters
        std::vector<int> getClientSocket() const;
        int getClientSocket(int index) const;
        int getLastClientSocket() const;
        int getServerSocket() const;
        struct sockaddr_in getAddress() const;
        int getValRead() const;
        fd_set getSockets() const;
        int getPort() const;
        size_t getBodySize() const;

        // Setters
        void setClientSocket(std::vector<int> clientSocket);
        void setServerSocket(int serverSocket);
        void setBodySize(size_t body_size);
        void setAddress(const struct sockaddr_in& address);
        void setValRead(int valRead);
        void setSockets(const fd_set& sockets);
        void setPort(int port);

        void removeClient(int i);

    private:

        std::vector<int> _client_sockets;
        int _server_socket;
        struct sockaddr_in _address;
        int _valread;
        fd_set _sockets;
        int _port;
        size_t _body_size;
};

#endif