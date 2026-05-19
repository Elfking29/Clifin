#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include <array>
#include "models.h"

class UI {
    private:
        int rows;
        int cols;
        void update_size();
        void printc(std::string str, int row);

    public:
        UI();
        std::array<std::string,3> auth_window();

        

};






#endif