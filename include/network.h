#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>
#include "models.h"

class Network {
    private:
        std::string header;
        std::string url;

        std::string getUrl();
        std::string getHeader();
        std::string getUser();
        std::string getPass();

        void setUrl(std::string url);
        void setHeader(std::string header);
        void setUser(std::string user);
        void setPass(std::string pass);

    public:
        Network(std::string url, std::string us, std::string pw);
        std::vector<Item> getLibraries();
        std::vector<Item> getAlbums(std::string id);

};

#endif