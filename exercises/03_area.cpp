#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <functional>

// Change function `areaLessThan20` into lambda.
// Then change it into `areaLessThanX`, which takes `x = 20` on a capture list.
// What is the problem?
// Use `std::function` to solve the problem.

using namespace std;

class Circle {
    double r_{};

public:
    Circle(double r) : r_{r} {}

    double getArea() const {
       return 3.14 * r_ * r_;
    }

    void print() const {
        std::cout << "Circle:\n"
                  << "  radius: " << r_ << '\n'
                  << "    area: " << getArea() << '\n';
    }
};

using CirclePtr = shared_ptr<Circle>;
using Collection = vector<CirclePtr>;

void printCollection(const Collection& collection) {
    for (const auto & it : collection) {
        if (it) {
            it->print();
        }
    }
}

void printAreas(const Collection& collection) {
    for (const auto & it : collection) {
        if (it) {
            cout << it->getArea() << std::endl;
        }
    }
}

void findFirstShapeMatchingPredicate(const Collection& collection,
                                     std::string info,
                                     std::function<bool(CirclePtr)> predicate
                                    //  bool (*predicate)(CirclePtr s)
                                     ) {
    auto it = std::find_if(collection.begin(), collection.end(), predicate);
    if(it != collection.end()) {
        cout << "First shape matching predicate: " << info << endl;
        (*it)->print();
    } else {
        cout << "There is no shape matching predicate " << info << endl;
    }
}

int main() {
    // const int a = 10;
    // // const int & b = a;
    // [&b = a]() mutable {
    //     return b++;
    // }();

    Collection circles {
        make_shared<Circle>(4.0),
        make_shared<Circle>(3.0),
        make_shared<Circle>(2.0),
        make_shared<Circle>(4.0),
    };
    printCollection(circles);

    cout << "Areas before sort: " << std::endl;
    printAreas(circles);

    std::sort(circles.begin(), circles.end(), [](auto lhs, auto rhs) {
        if(!lhs || !rhs)
            return false;
        return (lhs->getArea() < rhs->getArea());
    });

    cout << "Areas after sort: " << std::endl;
    printAreas(circles);

    auto areaLessThanX = [x = 20](CirclePtr s) {
        return (s && s->getArea() < x);
    };

    findFirstShapeMatchingPredicate(circles,
                                    "area less than 20",
                                    areaLessThanX);

    return 0;
}
