#include "catch_amalgamated.hpp"
#include "schedule.hpp"
#include <chrono>
#include <string>

using namespace std::chrono_literals;

template <typename F, typename ... Args>
struct ParamPack {
    ParamPack(F f, Args... a) : func(f), args{a...} {}
    void operator()() { std::apply(func, args); }

    F func;
    std::tuple<Args...> args;
};

SCENARIO("Testing schedule function with any function", "[schedule][template][variadic]") {
    GIVEN("a variable i = 0, duration = 1s and a set of 8 functions of a different signature") {
        int i = 0;
        auto func1 = [&](std::string, std::string){ i = 1; return "text"; };
        auto func2 = [&](){ i = 2; return "text"; };
        auto func3 = [&](){ i = 3; };
        auto func4 = [&](double){ i = 4; return 42.5; };
        auto func5 = [&](double, int, int, char){ i = 5; return 42.5; };
        auto func6 = [&](double, int, int){ i = 6; return 42; };
        auto func7 = [&](double, int){ i = 7; return false; };
        auto func8 = [&](char, char, std::vector<int>){ i = 8; return true; };
        constexpr auto duration = 0s;

        WHEN("schedule takes each function, duration and params") {
            auto start = std::chrono::system_clock::now();
            schedule(func1, duration, "notImportant", "empty");
            CHECK(i == 1);
            schedule(func2, duration);
            CHECK(i == 2);
            schedule(func3, duration);
            CHECK(i == 3);
            schedule(func4, duration, 42.0);
            CHECK(i == 4);
            schedule(func5, duration, 3.14, 2, 3, 'z');
            CHECK(i == 5);
            schedule(func6, duration, 3.14, 2, 3);
            CHECK(i == 6);
            schedule(func7, duration, 3.14, 2);
            CHECK(i == 7);
            schedule(func8, duration, 'a', 'z', std::vector<int>{1, 2, 3});
            CHECK(i == 8);
            auto stop = std::chrono::system_clock::now();

            THEN("everything took at least 8 * duration but no more than 8 * duration + 1s") {
                std::chrono::duration<double> diff = stop - start;
                CHECK(diff >= 8 * duration);
                CHECK(diff <= 8 * duration + 1s);
            }
        }
    }
}