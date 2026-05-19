#include <print>
#include <iostream>
#include <string>
#include <csignal>
#include <unistd.h>

#include "network.h"
#include "ui.h"
#include "models.h"

int main() {
    //Set up terminal resizing
    struct sigaction sa{};
    sa.sa_handler = on_winch;
    sigaction(SIGWINCH, &sa, nullptr);

    UI ui;
    ui.print("In the beginning was the word",0,4);

    return 0;
}
