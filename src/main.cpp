#include <print>
#include <iostream>
#include <vector>
#include <string>

#include "network.h"
#include "models.h"

int main() {
    Network n("https://mediaserver.derekramsey.com","Avery","ace293562222329");
    std::vector<Item> v = n.getLibraries();
    std::vector<Item> j = n.getAlbums(v.front().id);
    for (Item i : j){
        std::print("{} - {}\n",i.name,i.id);
    }
    return 0;
}
