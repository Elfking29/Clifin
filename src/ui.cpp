#include "models.h"
#include "ui.h"
#include <string>
#include <vector>
#include <form.h>
#include <array>
#include <ncurses.h>



UI::UI(){initscr();keypad(stdscr, TRUE);cbreak;}

void UI::update_size(){
    int r,c;
    getmaxyx(stdscr,r,c);
    this->rows=r;
    this->cols=c;
}

void UI::printc(std::string str, int row){
    update_size();
    if (row>this->rows){row=this->rows;}
    else if (row<0){row=0;}
    str=str.length()<=this->cols?str:str.substr(str.length()-this->cols);
    mvprintw(row,(this->cols-str.length())/2,str.c_str());
}

std::array<std::string,3> UI::auth_window(){
    update_size();
    FIELD* field[4];
    FORM* my_form;
    int ch;

    // 1. Define fields: (height, width, top_row, left_col, offscreen_rows, n_buffers)
    field[0] = new_field(1, 20, 4, 18, 0, 0); 
    field[1] = new_field(1, 20, 8, 18, 0, 0); 
    field[2] = new_field(1, 20, 12, 18, 0, 0); 
    field[3] = NULL;

    set_field_back(field[0], A_UNDERLINE);
    set_field_back(field[1], A_UNDERLINE);
    set_field_back(field[2], A_UNDERLINE);

    my_form = new_form(field);
    post_form(my_form);

    int h = 10, w = 45;
    WINDOW* box_win = newwin(h, w, (LINES - h) / 2, (COLS - w) / 2);
    keypad(box_win, TRUE);

    // 5. CRITICAL STEP: Bind the form to our window structures
    set_form_win(my_form, box_win);
    set_form_sub(my_form, derwin(box_win, h - 2, w - 2, 1, 1));
    box(box_win, 0, 0);
    mvwprintw(box_win, 4, 4, "Username:");
    mvwprintw(box_win, 6, 4, "Password:");
    wrefresh(box_win);

    refresh();

    // 5. Loop to handle Tab navigation and typing
    while ((ch = getch()) != KEY_F(1)) { // Press F1 to exit
        switch (ch) {
            case '\t': // Tab moves to next field
                form_driver(my_form, REQ_NEXT_FIELD);
                form_driver(my_form, REQ_END_LINE); // Move cursor to end of text
                break;
            case KEY_BTAB: // Shift+Tab moves to previous field
                form_driver(my_form, REQ_PREV_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            case KEY_BACKSPACE:
            case 127:
                form_driver(my_form, REQ_DEL_PREV);
                break;
            default:
                form_driver(my_form, ch); // Regular typing character
                break;
        }
    }

    // Cleanup memory
    unpost_form(my_form);
    free_form(my_form);
    free_field(field[0]);
    free_field(field[1]);
    endwin();



    return {"","",""};
}