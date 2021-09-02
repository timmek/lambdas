#include "catch_amalgamated.hpp"
#include "schedule.hpp"
#include <chrono>
#include <string>

using namespace std::chrono_literals;


SCENARIO("Testing schedule function with void()", "[schedule]") {
    GIVEN("a function that modifies variable and a 2 seconds duration") {
        int i = 0;
        constexpr int newValue = 42;
        auto func = [&i]{ i = newValue; };
        constexpr auto duration = 2s;

        WHEN("schedule takes func and duration") {
            auto start = std::chrono::system_clock::now();
            schedule(func, duration);
            auto stop = std::chrono::system_clock::now();

            THEN("everything took at least the provided duration and the variable is modified") {
                std::chrono::duration<double> diff = stop - start;
                CHECK(diff >= duration);
                CHECK(i == newValue);
            }
        }
    }
}

SCENARIO("Testing schedule function with void(int)", "[schedule]") {
    GIVEN("a function that modifies variable and a 1 second duration") {
        int i = 0;
        constexpr int newValue = 42;
        auto func = [&i](int){ i = newValue; };
        constexpr auto duration = 1s;
        int notImportantValue = 23;

        WHEN("schedule takes func and duration") {
            auto start = std::chrono::system_clock::now();
            schedule(func, duration, notImportantValue);
            auto stop = std::chrono::system_clock::now();

            THEN("everything took at least the provided duration and the variable is modified") {
                std::chrono::duration<double> diff = stop - start;
                CHECK(diff >= duration);
                CHECK(i == newValue);
            }
        }
    }
}

SCENARIO("Testing schedule function with void(std::string, double)", "[schedule]") {
    GIVEN("a function that modifies variable and a 0 second duration") {
        int i = 0;
        constexpr int newValue = 42;
        auto func = [&i](std::string, double){ i = newValue; };
        constexpr auto duration = 0s;
        std::string notImportantString = "text";
        double notImportantDouble = 3.14;

        WHEN("schedule takes func and duration") {
            auto start = std::chrono::system_clock::now();
            schedule(func, duration, notImportantString, notImportantDouble);
            auto stop = std::chrono::system_clock::now();

            THEN("everything took at least the provided duration and the variable is modified") {
                std::chrono::duration<double> diff = stop - start;
                CHECK(diff >= duration);
                CHECK(i == newValue);
            }
        }
    }
}