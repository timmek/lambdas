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

int main() {
    auto container = generateContainer();
    printContainer(container);

    return 0;
}
