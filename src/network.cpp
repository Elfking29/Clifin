#include "network.h"
#include "cpr/cpr.h"
#include "models.h"
#include <cpr/parameters.h>
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
    this->setHeader("MediaBrowser Client=\"Clifin\", Device=\"Laptop\", DeviceId=\"1\", Version=\"0.0.1\"");
    this->setUrl(url);

    nlohmann::json body;
    body["Username"]=user;
    body["Pw"]=pass;

    cpr::Response r = cpr::Post(
        cpr::Url{url+"/Users/AuthenticateByName"},
        cpr::Header{
            {"Content-Type", "application/json"},
            {"Accept","application/json"},
            {"Authorization",this->getHeader()}
        },
        cpr::Body{body.dump()}
    );
    
    this->setHeader(header+", Token=\""+nlohmann::json::parse(r.text)["AccessToken"].get<std::string>()+"\"");
}

std::vector<Item> Network::getLibraries(){
    cpr::Response r = cpr::Get(
        cpr::Url{url+"/UserViews"},
        cpr::Header{{"Authorization",this->getHeader()}},
        cpr::Parameters{
            {"presetViews","music"}
        }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    
    std::vector<Item> items;
    for (int i=0; i<res["Items"].size(); i++){
        if (res["Items"][i]["CollectionType"].dump()=="\"music\""){
            items.push_back({res["Items"][i]["Name"].get<std::string>(),res["Items"][i]["Id"].get<std::string>()});
        }
    }

    return items;
}

std::vector<Item> Network::getAlbums(std::string id){
    cpr::Response r = cpr::Get(
        cpr::Url{url+"/Items"},
        cpr::Header{{"Authorization",this->getHeader()}},
        cpr::Parameters{
            {"IncludeItemTypes","MusicAlbum"},
            {"Recursive","true"},
            {"ParentId",id}
        }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Item> items;
    for (int i=0; i<res["Items"].size(); i++){
        items.push_back({res["Items"][i]["Name"].get<std::string>(),res["Items"][i]["Id"].get<std::string>()});
    }

    return items;
}