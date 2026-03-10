#include <iostream>
#include "console_ui.hpp"

int main() {
    try {
        std::cout << "=== Visual Sort ===" << std::endl;
        
        ConsoleUI ui;
        ui.showMenu();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
