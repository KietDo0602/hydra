#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <limits>
using namespace std;

#define INVALID (-1)

class Utils
{
private:
public:
    Utils();
    ~Utils();

    template<typename returnType>
    returnType custom_cin(returnType &returnValue, const string &question);
};

template<typename returnType>
returnType Utils::custom_cin(returnType &returnValue, const string &question) 
{
    while (true)
    {
        cout << question << endl;
        cin >> returnValue;
        if (cin.eof())
        {
            cin.ignore();
            exit(EXIT_SUCCESS);
        }
        else if (cin.fail())
        {
            cin.clear();
	    cout << "Invalid Input. Please try again." << endl;
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    return returnValue;
}

static Utils util;

#endif // __UTILS_H__
