#include "network.h"
#include "models.h"
#include "ui.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <string>
#include <print>
#include <csignal>
#include <atomic>

std::atomic<bool> resized{false};

extern "C" void on_winch(int) {
    resized.store(true);
}

void UI::clear_screen(){std::print("\n\033[2J\033[H");}

UI::UI(){this->clear_screen();this->back_update();}

void UI::move(int row, int col){std::print("\n\033[{};{}H",row,col);}

void UI::home(){std::print("\033[H");}

void UI::back_update(){
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    this->cols = ws.ws_col;
    this->rows = ws.ws_row;
}

void UI::update(){
    if (resized.exchange(false)){
        this->back_update();
        std::println("Rows: {} - Cols: {}",this->rows,this->cols);
    }
}

void UI::print_center(std::string text, int row){
    if (row<0){row=0;}
    else if (row>this->rows){row=this->rows;}
    int col;
    if (text.length()>=this->cols){
        col=0;
        text=text.substr(0,this->cols);
    }
    else {
        col=(int)((this->cols-text.length())/2);
    }
    this->move(row,col);
    std::print("{}\n",text);
}

void UI::print(std::string text, int row, int col){
    if (row<0){row=0;}
    else if (row>this->rows){row=this->rows;}
    if (text.length()>=this->cols-col){text=text.substr(0,this->cols-col);}

    this->move(row,col);
    std::print("{}\n",text);    
}