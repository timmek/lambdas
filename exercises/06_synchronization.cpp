#include <vector>
#include <thread>
#include <iostream>
using namespace std;

vector<int> generateContainer() {
    vector<int> input = {2, 4, 6, 8, 10, 1, 3, 5, 7, 9};
    vector<int> output;
    vector<thread> threads;
    for (auto i = 0u; i < input.size(); i++) {
        threads.emplace_back([&] {
            output.push_back(input[i]);
        });
    }
    for (auto && t : threads) {
        t.join();
    }
    return output;
}

void printContainer(const vector<int>& c) {
    for (const auto & value : c)
        cout << value << " ";
    cout << endl;
}

// Fix `generateContainer()` function.
// We want to have each value from 1 to 10 to be printed on the screen only once.
// Every thread should put only one value to the shared vector.
// The order does not matter.
// Possible outputs:
// `1, 2, 3, 4, 5, 6, 7, 8, 9, 10`
// `2, 4, 6, 8, 10, 1, 3, 5, 7, 9`
// `1, 3, 2, 4, 5, 6, 8, 10, 9, 7`

int main() {
    auto container = generateContainer();
    printContainer(container);

    return 0;
}
