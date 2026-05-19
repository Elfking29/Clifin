#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include "models.h"

extern "C" void on_winch(int);

class UI {
    private:
        int rows=24;
        int cols=80;

        void clear_screen();
        void move(int row, int col);
        void home();
        void back_update();



    public:
        UI();
        void update();
        void print_center(std::string text, int line);
        void print(std::string text, int row, int col);
        

};






#endif