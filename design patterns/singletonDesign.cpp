#include <iostream>
#include <mutex>
#include <string>

class Logger {
private:
    // 1. Private Constructor: Prevents anyone from doing 'Logger l;'
    Logger() {
        std::cout << "Logger Initialized (File opened).\n";
    }

    // 2. Static Instance: Holds the one and only copy
    static Logger* instance;
    static std::mutex mtx; // To make it thread-safe

public:
    // 3. Delete Copy Constructor & Assignment Operator
    // We don't want anyone cloning our single instance!
    Logger(const Logger& obj) = delete;
    void operator=(const Logger& obj) = delete;

    // 4. Global Access Point
    static Logger* getInstance() {
        if (instance == nullptr) { // Check 1
            std::lock_guard<std::mutex> lock(mtx); 
            if (instance == nullptr) { // Check 2 (Double-checked locking)
                instance = new Logger();
            }
        }
        return instance;
    }

    void log(std::string message) {
        std::cout << "[LOG]: " << message << std::endl;
    }
};

// Initialize static members
Logger* Logger::instance = nullptr;
std::mutex Logger::mtx;

int main() {
    // Logger myLogger; // ERROR: Constructor is private!

    // Get the logger from anywhere in the app
    Logger* logger1 = Logger::getInstance();
    logger1->log("User logged in.");

    Logger* logger2 = Logger::getInstance();
    logger2->log("Payment processed.");

    // Proof: Both pointers point to the same memory address
    std::cout << "Pointer 1: " << logger1 << "\nPointer 2: " << logger2 << std::endl;

    return 0;
}