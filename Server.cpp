#include "Server.hpp"


Server::Server() 
{
    _port = 8080;
    _body_size = 1000000;
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket < 0)
        throw SocketFailedException();
    int opt = 1;
    setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
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
    //std::cout << "Le serveur a été créé avec comme port : " << _port << std::endl;
}

Server::Server(int port) 
{
    _server_name = "default";
    _port = port;
    _body_size = 1000000;
    _allow_get = 0;
    _allow_post = 0;
    _allow_delete = 0;
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket < 0)
        throw SocketFailedException();
    int opt = 1;
    setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
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
    _body_size = other._body_size;
    _server_name = other._server_name;
    _host = other._host;
    _root = other._root;
    _client_sockets = other._client_sockets;
    _allow_get = other._allow_get;
    _allow_post = other._allow_post;
    _allow_delete = other._allow_delete;
    _map_error = other._map_error;
}

int Server::getServerSocket() const
{
    return _server_socket;
}

struct sockaddr_in Server::getAddress() const
{
    return _address;
}

int Server::getValRead() const
{
    return _valread;
}

size_t Server::getBodySize() const
{
    return _body_size;
}

std::string Server::getHost() const
{
    return _host;
}
std::string Server::getServerName() const
{
    return _server_name;
}
std::string Server::getRoot() const
{
    return _root;
}

int Server::getAllowGet() const
{
    return _allow_get;
}

int Server::getAllowPost() const
{
    return _allow_post;
}

int Server::getAllowDelete() const
{
    return _allow_delete;
}

std::map<size_t, std::string> Server::getMapError() const
{
    return _map_error;
}

fd_set Server::getSockets() const
{
    return _sockets;
}

void Server::setValRead(int valread)
{
    _valread = valread;
}

void Server::setAddress(const struct sockaddr_in& address)
{
    _address = address;
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

void Server::setBodySize(size_t body_size)
{
    _body_size = body_size;
}

void Server::setHost(std::string host)
{
    _host = host;
}

void Server::setServerName(std::string server_name)
{
    _server_name = server_name;
}

void Server::setRoot(std::string root)
{
    _root = root;
}

void Server::setAllowGet(int allow_get)
{
    _allow_get = allow_get;
}
void Server::setAllowPost(int allow_post)
{
    _allow_post = allow_post;
}
void Server::setAllowDelete(int allow_delete)
{
    _allow_delete = allow_delete;
}

void Server::setMapError(std::map<size_t, std::string> map_error)
{
    _map_error = map_error;
}

void Server::setServerSocket(int server_socket)
{
    _server_socket = server_socket;
}

std::vector<int> Server::getClientSocket() const
{
    return _client_sockets;
}

int Server::getClientSocket(int index) const
{
    return _client_sockets[index];
}

int Server::getLastClientSocket() const
{
    return _client_sockets.back();
}


void Server::setClientSocket(std::vector<int> client_sockets)
{
    _client_sockets = client_sockets;
}

Server& Server::operator=(const Server& other) 
{
    //std::cout << "Le serveur a été assigné par copie." << std::endl;
    _server_socket = other._server_socket;
    _address = other._address;
    _valread = other._valread;
    _sockets = other._sockets;
    _port = other._port;
    _body_size = other._body_size;
    _client_sockets = other._client_sockets;

    return *this;
}

void Server::addClient(int client_socket)
{
    _client_sockets.push_back(client_socket);
}

void Server::removeClient(int i)
{
     _client_sockets.erase(_client_sockets.begin() + i);
}

void Server::clearSockets(int i)
{
    FD_CLR(i, &_sockets);
}

void Server::acceptClient()
{
    int fd;
    long len = sizeof(_address);
    fd = accept(_server_socket, (struct sockaddr *)&_address, (socklen_t*)&len);
    if (fd < 0)
        throw AcceptFailedException();
    FD_SET(fd, &_sockets);
    _client_sockets.push_back(fd);
}


