#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class Network {
    private:
        std::string header;
        std::string token;
        std::string url;

    public:
        Network(std::string url, std::string us, std::string pw);

};

#endif