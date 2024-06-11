#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <functional>

void schedule( std::function<void()> func, std::chrono::seconds sec);
void schedule(std::function<void(int)> func, std::chrono::seconds sec, int number);
void schedule(std::function<void(std::string, double)> func, std::chrono::seconds sec, std::string text, double number);
