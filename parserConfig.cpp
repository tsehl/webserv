#include "webserv.hpp"
#include "Server.hpp"


int is_double(std::string line, std::vector<std::string> tab_keys)
{
    for (size_t i = 0; i < tab_keys.size(); i++)
    {
        if (line.compare(tab_keys[i]) == 0)
            return (1);
    }
    return (0);
}

int is_server(std::string line)
{
    std::string first_line = "server{";
    int j = 0;

    for (size_t i = 0; i <= line.length(); i++)
    {
        if (j == 7)
            break;
        while (isspace(line[i]))
            i++;
        if (line[i] != first_line[j])
            return (0);
        j++;
    }
    return (1);
}

int is_closed(std::string line)
{
    for (size_t i = 0; i < line.length(); i++)
    {
        while (isspace(line[i]))
            i++;
        if (line[i] == '}')
            return (1);
    }
    return (0);
}

int check_listen(std::string &value)
{
 
    if (value[value.size() - 1] != ';')
        return (0);
    if (std::stoi(value) < 0)
        return (0);
    return (1);
}

int check_host(std::string &value)
{
    if (value[value.size() - 1] != ';')
        return (0);
    if (value.compare("127.0.0.1;") != 0)
        return (0);
    return (1);
}

int check_server_name(std::string &value)
{
    if (value[value.size() - 1] != ';')
        return (0);
    if (value.compare("") == 0 || value.compare(";") == 0)
        return (0);
    return (1);
}

int check_body_size(std::string &value)
{
    if (value[value.size() - 1] != ';')
        return (0);
    if (std::stoi(value) < 0)
        return (0);
    return (1);
}

int check_root(std::string &value)
{
    if (value[value.size() - 1] != ';')
        return (0);
    struct stat buffer;
    std::string path = value.erase(value.size() - 1);
    
    return (stat(path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

int check_requests(std::string &value, std::vector<std::string> &tab_keys)
{
    if (value[value.size() - 1] != ';')
        return (0);
    if ((value.compare("GET;") != 0 && value.compare("POST;") != 0 && value.compare("DELETE;") != 0 ) || is_double(value, tab_keys))
        return (0);
    tab_keys.push_back(value);
    return (1);
}

int check_error_page(std::string &value1, std::string &value2)
{
    if (value2[value2.size() - 1] != ';')
        return (0);
    std::ifstream ifs;
    std::string path = value2.erase(value2.size() - 1);
    if (std::stoi(value1) < 0)
        return (0);
    ifs.open(path, std::ifstream::in);
    if (!ifs.is_open())
    {
        ifs.close();
        return (0);
    }
    ifs.close();
    return (1);
}

int check_index(std::string &value)
{
    if (value[value.size() - 1] != ';')
        return (0);
    std::ifstream ifs;
    std::string path = value.erase(value.size() - 1);
    ifs.open(path, std::ifstream::in);
    if (!ifs.is_open())
    {
        ifs.close();
        return (0);
    }
    ifs.close();
    return (1);
}

int check_autoindex(std::string &value)
{
    if (value[value.size() - 1] != ';')
        return (0);
    if (value.compare("on;") != 0 && value.compare("off;") != 0)
        return (0);
    return (1);
}

int check_upload(std::string &value)
{
    if (value[value.size() - 1] != ';')
        return (0);
    struct stat buffer;
    std::string path = value.erase(value.size() - 1);
    
    return (stat(path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

int check_return(std::string &value1, std::string &value2)
{
    if (value2[value2.size() - 1] != ';')
        return (0);
    std::ifstream ifs;
    std::string path1 = value1;
    ifs.open(path1, std::ifstream::in);
    if (!ifs.is_open())
        return (0);
    ifs.close();
    std::string path2 = value2.erase(value2.size() - 1);
    ifs.open(path2, std::ifstream::in);
    if (!ifs.is_open())
    {
        ifs.close();
        return (0);
    }
    ifs.close();
    return (1);
    
}

int check_cgi_pass(std::string &value1, std::string &value2)
{
     if (value2[value2.size() - 1] != ';')
        return (0);
    if (value1.compare(".py") == 0)
    {
        if (value2.compare("/usr/bin/Python3;") == 0)
            return (1);
    }
    if (value1.compare(".sh") == 0)
    {
        if (value2.compare("/bin/bash;") == 0)
            return (1);
    }
    return (0);
}

int check_cgi_bin(std::string &value)
{
    if (value.compare("/cgi-bin/;") == 0)
        return (1);
    return (0);
}

int check_values(std::vector<std::string> &tab_lines, std::vector<Server>& server, std::vector<std::string> &tab_keys,  std::map<size_t, std::string> &map)
{

    if (tab_lines[0].compare("listen") == 0 && !is_double(tab_lines[0], tab_keys))
    {
        tab_keys.push_back("listen");
        if (check_listen(tab_lines[1]))
        {
            server.push_back(Server(std::stoi(tab_lines[1])));
            return (1);
        }
    }
    if (tab_lines[0].compare("host") == 0 && !is_double(tab_lines[0], tab_keys))
    {
        tab_keys.push_back("host");
        if (check_host(tab_lines[1]))
        {
            server.back().setHost(tab_lines[1].substr(0, tab_lines[1].length() - 1));
            return (1);
        }
    }
    if (tab_lines[0].compare("server_name") == 0 && !is_double(tab_lines[0], tab_keys))
    {
        tab_keys.push_back("server_name");
        if (check_server_name(tab_lines[1]))
        {
            server.back().setServerName(tab_lines[1].substr(0, tab_lines[1].length() - 1));
            return (1);
        }
    }
    if (tab_lines[0].compare("client_max_body_size") == 0 && !is_double(tab_lines[0], tab_keys))
    {
        tab_keys.push_back("client_max_body_size");
        if (check_body_size(tab_lines[1]))
        {
            server.back().setBodySize(std::stoi(tab_lines[1]));
            return (1);
        }
    }
    if (tab_lines[0].compare("root") == 0 && !is_double(tab_lines[0], tab_keys))
    {
        tab_keys.push_back("root");
        if (check_root(tab_lines[1]))
        {   
            server.back().setRoot(tab_lines[1].substr(0, tab_lines[1].length() - 1));
            return(1);
        }
    }
    if (tab_lines[0].compare("allow") == 0 || tab_lines[0].compare("deny") == 0)
    {

        if (check_requests(tab_lines[1], tab_keys))
        {
            if (tab_lines[0].compare("allow") == 0 && tab_lines[1].compare("GET;") == 0)
                server.back().setAllowGet(1);
            if (tab_lines[0].compare("allow") == 0 && tab_lines[1].compare("POST;") == 0)
                server.back().setAllowPost(1);
            if (tab_lines[0].compare("allow") == 0 && tab_lines[1].compare("DELETE;") == 0)
                server.back().setAllowDelete(1);
            return (1);
        }
    }
    if (tab_lines[0].compare("error_page") == 0)
    {
        if (check_error_page(tab_lines[1], tab_lines[2]))
        {
            map.insert(std::make_pair(std::stoi(tab_lines[1]), tab_lines[2]));
            server.back().setMapError(map);
            return (1);
        }
    }
    if (tab_lines[0].compare("") == 0)
        return (1);

    return (0);
}

int check_values_location(std::vector<std::string> &tab_lines_location, std::vector<std::string> &tab_keys_location, 
    std::vector<Location>& vec_location,  std::map<std::string, std::string>& map_location)
{
    if (tab_lines_location[0].compare("allow") == 0 || tab_lines_location[0].compare("deny") == 0)
    {
        if (check_requests(tab_lines_location[1], tab_keys_location))
        {
            if (tab_lines_location[0].compare("allow") == 0 && tab_lines_location[1].compare("GET;") == 0)
                vec_location.back().setAllowGet(1);
            if (tab_lines_location[0].compare("allow") == 0 && tab_lines_location[1].compare("POST;") == 0)
                vec_location.back().setAllowPost(1);
            if (tab_lines_location[0].compare("allow") == 0 && tab_lines_location[1].compare("DELETE;") == 0)
                vec_location.back().setAllowDelete(1);
            return (1);
        }
    }
    if (tab_lines_location[0].compare("index") == 0 && !is_double(tab_lines_location[0], tab_keys_location))
    {
        if (check_index(tab_lines_location[1]))
            vec_location.back().setIndex(tab_lines_location[1]);
        return (1);
    }
    if (tab_lines_location[0].compare("defaultP") == 0 && !is_double(tab_lines_location[0], tab_keys_location))
    {
        if (check_index(tab_lines_location[1]))
            vec_location.back().setDefaultP(tab_lines_location[1]);
        return (1);
    }
    if (tab_lines_location[0].compare("autoindex") == 0 && !is_double(tab_lines_location[0], tab_keys_location))
    {
        if (check_autoindex(tab_lines_location[1]))
            vec_location.back().setAutonindex(1);
        return (1);
    }
    if (tab_lines_location[0].compare("upload_store") == 0 && !is_double(tab_lines_location[0], tab_keys_location))
    {
        if (check_upload(tab_lines_location[1]))
            vec_location.back().setUploadStore(tab_lines_location[1]);
        return (1);
    }
    if (tab_lines_location[0].compare("return") == 0 && !is_double(tab_lines_location[0], tab_keys_location))
    {
        if (check_return(tab_lines_location[1], tab_lines_location[2]))
        {
            map_location.insert(std::make_pair(tab_lines_location[1], tab_lines_location[2]));
            vec_location.back().setMapReturn(map_location);
        }
        return (1);
    }
    if (tab_lines_location[0].compare("root") == 0 && !is_double(tab_lines_location[0], tab_keys_location))
    {
        if (check_root(tab_lines_location[1]))
            vec_location.back().setRoot(tab_lines_location[1]);
        return (1);
    }
    if (tab_lines_location[0].compare("cgi_pass") == 0)
    {
        if (check_cgi_pass(tab_lines_location[1], tab_lines_location[2]))
        {
            map_location.insert(std::make_pair(tab_lines_location[1], tab_lines_location[2]));
            vec_location.back().setMapReturn(map_location);
        }
        return (1);
    }
    if (tab_lines_location[0].compare("cgi_bin") == 0)
    {
        if (check_cgi_bin(tab_lines_location[1]))
            vec_location.back().setCgiBin(tab_lines_location[1].substr(0, tab_lines_location[1].length() - 1));
        return (1);
    }
    if (tab_lines_location[0].compare("") == 0)
        return (1);
    return (0);
}

void split_line(std::string line, std::vector<std::string> &tab_lines)
{
    size_t i = 0;
    size_t index = 0;
    
    while (i < line.length())
    {
        while (isspace(line[i]) && i < line.length())
            i++;
        while (!isspace(line[i]) && i < line.length())
            tab_lines[index].push_back(line[i++]);
        index++;
    }
}

int is_location(std::vector<std::string> &tab_lines, std::vector<std::string> &tab_paths_location)
{
    if (tab_lines[0].compare("location") != 0)
        return (0);
    //struct stat buffer;
    std::string path = tab_lines[1];
    if (is_double(path, tab_paths_location))
        return (0);
    /*if (!(stat(path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode)))
        return (0);*/
    if (tab_lines[2].compare("{") != 0)
        return (0);
    return (1);
}

int check_line(std::string line, std::vector<Server>& server, std::vector<std::string> &tab_keys, std::ifstream *configfile, std::vector<std::string> &tab_paths_location, 
    std::map<size_t, std::string> &map, std::vector<Location>& vec_location,  std::map<std::string, std::string>& map_location)
{
    std::vector<std::string> tab_lines;
    tab_lines.push_back("");
    tab_lines.push_back("");
    tab_lines.push_back("");

    split_line(line, tab_lines);
    if (is_location(tab_lines, tab_paths_location))
    {
        tab_paths_location.push_back(tab_lines[1]);
        std::vector<std::string> tab_keys_location;
        //std::cout << "location : " << tab_lines[1] << std::endl;
        vec_location.push_back(Location(tab_lines[1]));
        while (std::getline(*configfile, line) && !is_closed(line))
        {
            std::vector<std::string> tab_lines_location;
            tab_lines_location.push_back("");
            tab_lines_location.push_back("");
            tab_lines_location.push_back("");
            split_line(line, tab_lines_location);
            if (!check_values_location(tab_lines_location,  tab_keys_location, vec_location, map_location))
                return (0);
        }
        if (!is_closed(line))
            return (0);
    }
    if (!check_values(tab_lines, server, tab_keys, map) && !is_closed(line))
        return (0);
    return (1);
}

int check_server(std::ifstream *configfile, std::vector<Server>& server)
{
    int nb_server = 0;
    std::string line = "";
    std::map<size_t, std::string> map;

    while (std::getline(*configfile, line))
    {
        while (line.empty())
        {
            if (!std::getline(*configfile, line))
                break;
        }
        std::vector<std::string> tab_keys;
        std::vector<std::string> tab_paths_location;
        if (is_server(line))
        {
            std::vector<Location> vec_location;
            std::map<std::string, std::string> map_location;
            nb_server++;
            while (std::getline(*configfile, line) && !is_closed(line))
            {
                if(!check_line(line, server, tab_keys, configfile, tab_paths_location, map, vec_location, map_location))
                    return (0);    
            }
            if (!is_closed(line))
                return (0);
            server.back().setVecLocation(vec_location);
        }
    }
    return (nb_server);
}

int parserConfig(std::vector<Server>& server, std::string path_configfile)
{
    std::ifstream configfile;
    configfile.open (path_configfile, std::ifstream::in);
    int nb_server = 0;

    if (configfile.is_open())
    {
        nb_server = check_server(&configfile, server);
        if (nb_server == 0)
            return (0);
    }
    else
        return (0);
    
    configfile.close();
    return (nb_server);
}