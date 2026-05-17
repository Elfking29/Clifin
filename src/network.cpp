#include "network.h"
#include "cpr/cpr.h"
#include <nlohmann/json.hpp>
#include <string>

#include <print>

//These need to be reworked to use actual security, but its fine for now
//Get Methods First
std::string Network::getUrl(){return this->url;}
std::string Network::getHeader(){return this->header;}
std::string Network::getUser(){return "";}
std::string Network::getPass(){return "";}
//Set Methods
void Network::setUrl(std::string url){this->url=url;}
void Network::setHeader(std::string header){this->header=header;}
void Network::setUser(std::string user){}
void Network::setPass(std::string pass){}
//All of these above are the ones that need work

//Constructor. Authenticates the Username & Password at the URL. Saves the URL and Token
//Need to store the token,url,user,pw in safe place
//Also need to change how header is generated
Network::Network(std::string url, std::string user, std::string pass){
    this->header="MediaBrowser Client=\"Clifin\", Device=\"Laptop\", DeviceId=\"1\", Version=\"0.0.1\"";
    this->url=url;

    nlohmann::json body;
    body["Username"]=user;
    body["Pw"]=pass;

    cpr::Response r = cpr::Post(
        cpr::Url{url.append("/Users/AuthenticateByName")},
        cpr::Header{
            {"Content-Type", "application/json"},
            {"Accept","application/json"},
            {"Authorization",this->header}
        },
        cpr::Body{body.dump()}
    );
    

    this->header+=", Token=\""+nlohmann::json::parse(r.text)["AccessToken"].get<std::string>()+"\"";  
}