#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _db = other._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

static std::string stripWhitespace(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] < '0' || date[i] > '9')
            return false;
    }
    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    int  daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeapYear    = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (month == 2 && isLeapYear)
        daysInMonth[2] = 29;
    return day <= daysInMonth[month];
}

float BitcoinExchange::getRate(const std::string& date) const
{
    if (_db.empty())
        return -1.0f;
    std::map<std::string, float>::const_iterator it = _db.upper_bound(date);
    if (it == _db.begin())
        return -1.0f;
    --it;
    return it->second;
}

bool BitcoinExchange::init(const std::string& csvPath)
{
    std::ifstream file(csvPath.c_str());
    if (!file.is_open())
        return false;
    std::string line;
    bool        skipHeader = true;
    while (std::getline(file, line))
    {
        if (skipHeader) { skipHeader = false; continue; }
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos)
            continue;
        std::string date    = stripWhitespace(line.substr(0, commaPos));
        std::string rateStr = stripWhitespace(line.substr(commaPos + 1));
        char*       end;
        float       rate    = static_cast<float>(std::strtod(rateStr.c_str(), &end));
        if (end == rateStr.c_str())
            continue;
        _db[date] = rate;
    }
    return !_db.empty();
}

void BitcoinExchange::processInput(const std::string& inputPath) const
{
    std::ifstream file(inputPath.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        size_t sepPos = line.find(" | ");
        if (sepPos == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date   = stripWhitespace(line.substr(0, sepPos));
        std::string valStr = stripWhitespace(line.substr(sepPos + 3));

        if (date == "date")
            continue;
        if (!isValidDate(date))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        char*  end;
        double value = std::strtod(valStr.c_str(), &end);
        if (end == valStr.c_str() || *end != '\0' || value != value)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (value < 0.0)
        {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000.0)
        {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        float rate = getRate(date);
        if (rate < 0.0f)
        {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}
