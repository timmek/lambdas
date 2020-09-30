#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

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

class Ellipse : public Circle {
    using Circle::Circle;
};

using CirclePtr = shared_ptr<Circle>;
using Collection = vector<CirclePtr>;

bool areaLessThan20(CirclePtr s) {
    return (s && s->getArea() < 20);
}

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
                                     bool (*predicate)(CirclePtr s)) {
    auto it = std::find_if(collection.begin(), collection.end(), predicate);
    if(it != collection.end()) {
        cout << "First shape matching predicate: " << info << endl;
        (*it)->print();
    } else {
        cout << "There is no shape matching predicate " << info << endl;
    }
}

// Write a function `insert()` that allows inserting objects of class derived from Circle to be inserted into collection. Usage:
// insert(Circle{1.0}, circles);
// insert(Ellipse{1.1}, circles);      // derives from Circle
// insert(double{1.1}, circles);        // not allowed
// You may use SFINAE (`std::enable_if`) or `constexpr if`.

int main() {
    Collection circles {
        make_shared<Circle>(4.0),
        make_shared<Circle>(3.0),
        make_shared<Circle>(2.0),
        make_shared<Circle>(4.0),
    };

    // insert(Circle{1.0}, circles);
    // insert(Ellipse{1.1}, circles);
    // insert(double{1.1}, circles);

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

    findFirstShapeMatchingPredicate(circles,
                                    "area less than 20",
                                    areaLessThan20);

    return 0;
}
