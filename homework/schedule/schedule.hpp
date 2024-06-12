#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <functional>

void schedule( std::function<void()> func, std::chrono::seconds sec);
void schedule(std::function<void(int)> func, std::chrono::seconds sec, int number);
void schedule(std::function<void(std::string, double)> func, std::chrono::seconds sec, std::string text, double number);

void schedule( std::function<void()> func, std::chrono::seconds sec)
{
    auto start = std::chrono::system_clock::now();
    while ((std::chrono::system_clock::now() - start) < (std::chrono::duration < double>)sec)
        continue;

    func();
}

void schedule(std::function<void(int)> func, std::chrono::seconds sec, int number)
{
    auto start = std::chrono::system_clock::now();
    while ((std::chrono::system_clock::now() - start) < (std::chrono::duration < double>)sec)
        continue;

    func(number);
}

void schedule(std::function<void(std::string, double)> func, std::chrono::seconds sec, std::string text, double number)
{
    auto start = std::chrono::system_clock::now();
    while ((std::chrono::system_clock::now() - start) < (std::chrono::duration < double>)sec)
        continue;

    func(text, number);
}
