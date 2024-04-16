#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <map>
# include "webserv.hpp"

class Location {

    public:

        Location();
        Location(std::string path);
        ~Location();
        Location(const Location& other);
        Location& operator=(const Location& other);

        int getAllowGet() const;
        int getAllowPost() const;
        int getAllowDelete() const;
        int getAutonindex() const;
        std::string getPath() const;
        std::string getRoot() const;
        std::string getIndex() const;
        std::string getDefaultP() const;
        std::string getUploadStore() const;
        std::string getCgiBin() const;
        std::map<std::string, std::string> getMapReturn() const;
        std::map<std::string, std::string> getMapCgiPass() const;

        void setAllowGet(int allow_get);
        void setAllowPost(int allow_post);
        void setAllowDelete(int allow_delete);
        void setAutonindex(int autonindex);
        void setPath(const std::string& path);
        void setRoot(const std::string& root);
        void setIndex(const std::string& index);
        void setDefaultP(const std::string& defaultP); 
        void setUploadStore(const std::string& upload_store);
        void setCgiBin(const std::string& cgi_bin);
        void setMapReturn(const std::map<std::string, std::string>& map_return);
        void setMapCgiPass(const std::map<std::string, std::string>& map_cgi_pass);

    private:

        int _allow_get;
        int _allow_post;
        int _allow_delete;
        int _autonindex;
        std::string _path;
        std::string _root;
        std::string _index;
        std::string _defaultP;
        std::string _upload_store;
        std::string _cgi_bin;
        std::map<std::string, std::string> _map_return;
        std::map<std::string, std::string> _map_cgi_pass;


};

#endif