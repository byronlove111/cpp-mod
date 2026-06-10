#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange {
private:
    std::map<std::string, float> _db;

    bool    isValidDate(const std::string& date) const;
    float   getRate(const std::string& date) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    bool    init(const std::string& csvPath);
    void    processInput(const std::string& inputPath) const;
};

#endif
