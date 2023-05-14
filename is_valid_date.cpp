#include <iostream>
#include <string>

bool isValidDate(const std::string &date)
{
    // Check if the string has the correct format "dd/mm/yyyy"
    if (date.size() != 10 || date[2] != '/' || date[5] != '/')
        return false;

    int day, month, year;
    if (sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) != 3)
        return false;

    // Check if day, month, and year are within reasonable ranges
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // Check for specific month and day ranges
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            if (day > 29)
                return false;
        }
        else
        {
            if (day > 28)
                return false;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return false;
    }

    return true;
}

int main()
{
    while(1){
    std::string date;

    std::cout << "Enter a date (dd/mm/yyyy): ";
    std::cin >> date;

    if (isValidDate(date))
        std::cout << "The date is valid." << std::endl;
    else
        std::cout << "The date is not valid." << std::endl;

    }
    return 0;


}