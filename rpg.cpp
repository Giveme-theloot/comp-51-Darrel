#include <iostream>
#include <string>
#include <chrono>
#include <thread>

void typewriter_print(const std::string& text, int delay_ms = 100) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    std::cout << std::endl;
}

int main() {
    std::string my_text = "This is a typewriter effect in C++!";
    typewriter_print(my_text, 50); 
    return 0;
}