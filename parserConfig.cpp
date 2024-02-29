#include "webserv.hpp"

int parserConfig(std::vector<Server> server, std::string path_configfile)
{
    std::ifstream configfile(path_configfile);
    configfile.open (path_configfile, std::ifstream::in);

    if (configfile.is_open())
    {
        std::cout << "file is opened\n";
    }
    else
        return (1);

    configfile.close();
    return (0);
}