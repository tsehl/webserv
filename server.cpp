#include "Server.hpp"


Server::Server() 
{
    _port = 8080;
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket < 0)
        throw SocketFailedException();
    memset((char *)&_address, 0, sizeof(_address)); 
    _address.sin_family = AF_INET; 
    _address.sin_addr.s_addr = htonl(INADDR_ANY); 
    _address.sin_port = htons(_port); 
    if (bind(_server_socket,(struct sockaddr *)&_address,sizeof(_address)) < 0)
        throw BindFailedException();
    if (listen(_server_socket, 3) < 0) 
        throw ListenFailedException();
    FD_ZERO(&_sockets);
    FD_SET(_server_socket, &_sockets);
    std::cout << "Le serveur a été créé avec comme port : 8080" << std::endl;
}

Server::Server(int port) 
{
    _port = port;
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket < 0)
        throw SocketFailedException();
    memset((char *)&_address, 0, sizeof(_address)); 
    _address.sin_family = AF_INET; 
    _address.sin_addr.s_addr = htonl(INADDR_ANY); 
    _address.sin_port = htons(_port); 
    if (bind(_server_socket,(struct sockaddr *)&_address,sizeof(_address)) < 0)
        throw BindFailedException();
    if (listen(_server_socket, 3) < 0) 
        throw ListenFailedException();
    FD_ZERO(&_sockets);
    FD_SET(_server_socket, &_sockets);
    std::cout << "Le serveur a été créé avec comme port : " << port << std::endl;
}

Server::~Server() 
{
    //std::cout << "Le serveur a été détruit." << std::endl;
}

Server::Server(const Server& other) 
{
    _server_socket = other._server_socket;
    _address = other._address;
    _valread = other._valread;
    _sockets = other._sockets;
    _port = other._port;
    //std::cout << _port << std::endl;
    //std::cout << "Le serveur a été copié." << std::endl;
}

int Server::getServerSocket() const
{
    return _server_socket;
}

void Server::setServerSocket(int server_socket)
{
    _server_socket = server_socket;
}

struct sockaddr_in Server::getAddress() const
{
    return _address;
}

void Server::setAddress(const struct sockaddr_in& address)
{
    _address = address;
}

int Server::getValRead() const
{
    return _valread;
}

void Server::setValRead(int valread)
{
    _valread = valread;
}

fd_set Server::getSockets() const
{
    return _sockets;
}

void Server::setSockets(const fd_set& sockets)
{
    _sockets = sockets;
}

int Server::getPort() const
{
    return _port;
}

void Server::setPort(int port)
{
    _port = port;
}

int Server::getClientSocket() const
{
    return _client_socket;
}

void Server::setClientSocket(int client_socket)
{
    _client_socket = client_socket;
}

Server& Server::operator=(const Server& other) 
{
    std::cout << "Le serveur a été assigné par copie." << std::endl;
    _server_socket = other._server_socket;
    _address = other._address;
    _valread = other._valread;
    _sockets = other._sockets;
    _port = other._port;

    return *this;
}


void Server::clearSockets(int i)
{
    FD_CLR(i, &_sockets);
}

void Server::acceptClient()
{
    long len = sizeof(_address);
    _client_socket = accept(_server_socket, (struct sockaddr *)&_address, (socklen_t*)&len);
    if (_client_socket < 0)
        throw AcceptFailedException();
    FD_SET(_client_socket, &_sockets);
}


