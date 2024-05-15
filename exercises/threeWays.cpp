#include <iostream>
#include <vector>
#include <algorithm>

bool functionDiv3(vector<int> numbers);

class FunctorDiv3
{
public:
    bool operator ()(vector<int> numbers) const
    {
        bool retVal = false;
        int count = 0;
        for (int i : numbers)
        {
            if ((i % 3) == 0)
                count++;
        }
        if (count == numbers.size())
            retVal = true;

        return retVal;
    }
};

int main() {
    std::vector numbers = {18, 21, 36, 90, 27, 14, 103};

    /* Function */
    cout << "Function" << endl;
    bool retVal1 = functionDiv3(numbers);
    cout << "functionDiv3 = " << retVal1 << endl << endl;

    /* Lambda */
    cout << "Lambda" << endl;
    bool retVal2 = [numbers]() -> bool {
        bool retVal = false;
        int count = 0;
        for (int i : numbers)
        {
            if ((i % 3) == 0)
                count++;
        }
        if (count == numbers.size())
            retVal = true;

        return retVal;
        }();
        cout << "lambdaDiv3 = " << retVal2 << endl << endl;

    /* Functor */
    cout << "Functor" << endl;
    FunctorDiv3 f1;
    cout << "lambdaDiv3 = " << f1(numbers) << endl << endl;

    return 0;
}

bool functionDiv3(vector<int> numbers)
{
    bool retVal = false;
    int count = 0;
    for (int i : numbers)
    {
        if ((i % 3) == 0)
            count++;
    }
    if (count == numbers.size())
        retVal = true;

    return retVal;
}
