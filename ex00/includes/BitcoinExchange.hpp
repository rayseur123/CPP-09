#ifndef BTC_CPP
#define BTC_CPP

#include <map>
#include <string>
#include <ctime>

class	BitcoinExchange
{
	private:
        std::map<std::time_t, float> btcMap_;
	public:
		void	display_map() const;
		void	addData(std::string& date, std::string& value);
		void	fillingDataMap(std::ifstream& dataFile);
		void	handleBtc(std::string inputName);
		void	getAmountBtc(std::ifstream& inputFile);

		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const& toCopy);
		~BitcoinExchange();

		BitcoinExchange const& operator=(BitcoinExchange const& toCopy);
};

#endif
