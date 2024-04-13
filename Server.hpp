
#ifndef SERVER_HPP
# define SERVER_HPP
# include "webserv.hpp"
# include "Location.hpp"


#include <map>

class Location;
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
        std::string getHost() const;
        std::string getServerName() const;
        std::string getRoot() const;
        int getAllowGet() const;
        int getAllowPost() const;
        int getAllowDelete() const;
        std::map<size_t, std::string> getMapError() const;
        std::vector<Location> getVecLocation() const;

        // Setters
        void setClientSocket(std::vector<int> clientSocket);
        void setServerSocket(int serverSocket);
        void setBodySize(size_t body_size);
        void setAddress(const struct sockaddr_in& address);
        void setValRead(int valRead);
        void setSockets(const fd_set& sockets);
        void setPort(int port);
        void setHost(std::string host);
        void setServerName(std::string server_name);
        void setRoot(std::string root);
        void setAllowGet(int allow_get);
        void setAllowPost(int allow_post);
        void setAllowDelete(int allow_delete);
        void setMapError(std::map<size_t, std::string> map_error);
        void setVecLocation(std::vector<Location> vec_location);

        void removeClient(int i);

    private:

        std::vector<int> _client_sockets;
        int _server_socket;
        struct sockaddr_in _address;
        int _valread;
        fd_set _sockets;
        int _port;
        size_t _body_size;
        std::string _host;
        std::string _server_name;
        std::string _root;
        int _allow_get;
        int _allow_post;
        int _allow_delete;
        std::map<size_t, std::string> _map_error;
        std::vector<Location> _vec_location;




};

#endif