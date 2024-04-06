#include <iostream>
#include <string>
using namespace std;

class ArraySizeException 
{
public:
    const char* what() const noexcept 
    {
        return "Array size must be 4x4";
    }
};

class ArrayDataException 
{
string message;
public:
    explicit ArrayDataException(const string& msg) : message(msg) {}
    const char* what() const noexcept 
    {
        return message.c_str();
    }
};

class ArrayValueCalculator 
{
public:
    int doCalc(string array[4][4]) 
    {
        try 
        {
            checkArraySize(array);

            int sum = 0;

            for (int i = 0; i < 4; i++) 
            {
                for (int j = 0; j < 4; j++) 
                {
                    try 
                    {
                        sum += stoi(array[i][j]);
                    }
                    catch (const invalid_argument&) 
                    {
                        throw ArrayDataException("Invalid data at cell [" + to_string(i) + "][" + to_string(j) + "]");
                    }
                }
            }

            return sum;
        }
        catch (const ArraySizeException& e) 
        {
            cout << "ArraySizeException: " << e.what() << endl;
            throw;
        }
    }

private:
    void checkArraySize(string array[4][4]) 
    {
        if (sizeof(array) / sizeof(array[0]) != 4 || sizeof(array[0]) / sizeof(string) != 4) 
        {
            throw ArraySizeException();
        }
    }
};

int main() 
{
    ArrayValueCalculator calculator;
    string array[4][4] = 
    {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };

    try 
    {
        int result = calculator.doCalc(array);
        cout << "Sum: " << result << endl;
    }
    catch (const ArraySizeException& e) 
    {
        cout << "ArraySizeException: " << e.what() << endl;
    }
    catch (const ArrayDataException& e) 
    {
        cout << "ArrayDataException: " << e.what() << endl;
    }

    return 0;
}
