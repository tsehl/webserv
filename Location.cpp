#include "Location.hpp"

Location::Location()
{
    _path = "./location";
    _allow_get = 0;
    _allow_post = 0;
    _allow_delete = 0;
    _autonindex = 0;
}

Location::Location(std::string path)
{
    _path = path;
    _allow_get = 0;
    _allow_post = 0;
    _allow_delete = 0;
    _autonindex = 0;
}

Location::~Location()
{

}

Location::Location(const Location& other)
:
    
    _allow_get(other._allow_get),
    _allow_post(other._allow_post),
    _allow_delete(other._allow_delete),
    _autonindex(other._autonindex),
    _path(other._path),
    _root(other._root),
    _index(other._index),
    _upload_store(other._upload_store),
    _cgi_bin(other._cgi_bin),
    _map_return(other._map_return),
    _map_cgi_pass(other._map_cgi_pass) {}


Location& Location::operator=(const Location& other)
{
    _allow_get = other._allow_get;
    _allow_post = other._allow_post;
    _allow_delete = other._allow_delete;
    _autonindex = other._autonindex;
    _root = other._root;
    _index = other._index;
    _upload_store = other._upload_store;
    _cgi_bin = other._cgi_bin;
    _path = other._path;

    return *this;
}

int Location::getAllowGet() const 
{
    return _allow_get;
}

int Location::getAllowPost() const 
{
    return _allow_post;
}

std::string Location::getPath() const 
{
    return _path;
}

int Location::getAllowDelete() const 
{
    return _allow_delete;
}

int Location::getAutonindex() const 
{
    return _autonindex;
}

std::string Location::getRoot() const 
{
    return _root;
}

std::string Location::getIndex() const 
{
    return _index;
}

std::string Location::getUploadStore() const 
{
    return _upload_store;
}

std::string Location::getCgiBin() const 
{
    return _cgi_bin;
}

std::map<std::string, std::string> Location::getMapReturn() const 
{
    return _map_return;
}

std::map<std::string, std::string> Location::getMapCgiPass() const 
{
    return _map_cgi_pass;
}

void Location::setAllowGet(int allow_get) 
{
    _allow_get = allow_get;
}

void Location::setPath(const std::string& path) 
{
    _path = path;
}

void Location::setAllowPost(int allow_post) 
{
    _allow_post = allow_post;
}

void Location::setAllowDelete(int allow_delete) 
{
    _allow_delete = allow_delete;
}

void Location::setAutonindex(int autonindex) 
{
    _autonindex = autonindex;
}

void Location::setRoot(const std::string& root) 
{
    _root = root;
}

void Location::setIndex(const std::string& index) 
{
    _index = index;
}

void Location::setUploadStore(const std::string& upload_store) 
{
    _upload_store = upload_store;
}

void Location::setCgiBin(const std::string& cgi_bin) 
{
    _cgi_bin = cgi_bin;
}

void Location::setMapReturn(const std::map<std::string, std::string>& map_return) 
{
    _map_return = map_return;
}

void Location::setMapCgiPass(const std::map<std::string, std::string>& map_cgi_pass) 
{
    _map_cgi_pass = map_cgi_pass;
}
