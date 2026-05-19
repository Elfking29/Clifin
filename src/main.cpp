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

    UI ui;
    ui.auth_window();

    return 0;
}
