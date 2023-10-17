#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "config.cpp"
#define LINE20 "--------------------"
#define INPUT "<< INPUT >> "
#define OUTPUT "<< OUTPUT >> " 
int main (int argc, char **argv)
{
	if ((argc==5) && (strcmp(argv[1], "-c")==0 || strcmp(argv[1], "--config")==0)) //Запуск программы в режиме конфигурации
	{
		config(argv[2], argv[3], argv[4]);
		return 0;
	}
	
	if ((argc==3) && (strcmp(argv[1], "-w")==0 || strcmp(argv[1], "--work")==0)) //Запуск программы в рабочем режиме
	{
		Hello();
		std::string line, str, product;
		int balance = 100;
		int count, k, buy, price, code, Select_Product, number;
		
		enum command_code { WAITING, SELECTING, WAITING_PAYMENT, DISPENSING, HELP, EXIT, STATUS, ERROR };
		std::string commands[]{ "SELECT", "DISPENSE", "HELP", "EXIT", "STATUS" };
		
		std::vector<std::string> products;
		std::vector<int> prices;
		std::vector<int> _count;
		std::vector<int> numbers;
		
		////////////////////////////////////////
		
		std::ifstream file1;
		file1.open(argv[2]);
		if (!(file1.is_open()))
		{
			std::cout<< "Ошибка открытия файла для чтения. \n";
			return 0;
		}
		
		
		while ((getline (file1, str)) && (!(str.empty()))) //Считвание данных из файла
		{
			std::istringstream iss(str);
			iss >> number >> product >> price >> count;
			products.push_back(product);
			prices.push_back(price);
			_count.push_back(count);
			numbers.push_back(number);
		}
		file1.close();
		
		////////////////////////////////////////
		
		std::ofstream file; //Открытие файла для дозаписи
		file.open(argv[2], std::ios::app);
		if (!(file.is_open()))
		{
			std::cout<< "Ошибка открытия файла для записи. \n";
			return 0;
		}
		
		std::cout << "START:\n";
		std::cout << LINE20 << "\n";
		file<<'\n';
		file << LINE20 << "\n";
		file << "START: \n";
		while (1)
		{
			code = WAITING;
			file << "<Состояние> WAITING \n";
			std::cout << INPUT;
			std::cin >> line;
			if (line == "HELP")
			{
				code = HELP;
				file << "<Ввод> HELP \n" ;
				file << "<Состояние> HELP"<< "\n";
				file << "Выведен список команд\n";
				std::cout << "Command list: SELECT, DISPENSE, HELP, EXIT, STATUS \n";
			}
			else if (line == "STATUS")
			{
				code = STATUS;
				file << "<Ввод> STATUS \n" ;
				file << "<Состояние> STATUS"<< "\n";
				std::cout << OUTPUT;
				std::cout << "Your balance: " << balance << "$ \n";
				file << "Выведен баланс пользователя \n" ;
				std::cout << OUTPUT;
				std::cout << "Products in stock: \n";
				file << "Выведение продукты, которые есть в наличии \n" ;
				file << "В наличии " << numbers.size() << " товаров \n";
				for (int i=0; i<numbers.size(); i++)
				{
					std::cout << OUTPUT;
					std::cout << numbers[i] << ". " << products[i] << " " << prices[i] << "$ (" << _count[i] << " pieces) \n";
				}
			}
			else if (line == "SELECT")
			{
				code = SELECTING;
				std::cout << OUTPUT;
				file << "<Ввод> SELECT \n" ;
				file << "<Состояние> SELECTING"<< "\n";
				std::cout << "What do you want to buy? Enter the product number.\n";
				std::cout << INPUT;
				std::cin >> Select_Product;
				int j=Select_Product;
				if (Select_Product == numbers[j-1])
				{
					std::cout << OUTPUT;
					std::cout << "How much product do you want to buy? \n";
					std::cout << INPUT;
					std::cin >> k;
					if (k < 0)
					{
						code = ERROR;
						std::cout << OUTPUT;
						std::cout << "INPUT ERROR! \n";
						file << "Выведена ошибка \n" ;
						break;
					}
					else if (k > _count[j-1])
					{
						code = ERROR;
						std::cout << OUTPUT;
						std::cout << "There is not so much product in stock \n";
						file << "Выведена ошибка \n" ;
						break;
					}
					std::cout << OUTPUT;
					std::cout << "Great! Deposit money. You have to pay: " << prices[j-1]*k << "$ \n";
					file << "К оплате: " << prices[j-1]*k << "$ \n";
					code = WAITING_PAYMENT;
					file << "<Состояние> WAITING_PAYMENT \n" ;
					std::cout << INPUT;
					std::cin >> buy;
					file << "Оплата: " << buy << "$\n";
					if (buy > balance)
					{
						code = ERROR;
						std::cout << OUTPUT;
						std::cout << "Ops... You don't have money \n";
						file << "Выведена ошибка \n" ;
						break;
					}
					else if (buy < (prices[j-1]*k))
					{
						code = ERROR;
						std::cout << OUTPUT;
						std::cout << "ERROR! Not enough money \n";
						file << "Выведена ошибка \n" ;
						break;
					}
					else if (buy > (prices[j-1]*k))
					{
						std::cout << OUTPUT;
						std::cout << "Your change: "<< buy - (prices[j-1]*k) <<"$ \n";
						file << "Сдача: " << buy - (prices[j-1]*k) << "$ \n";
					}
					balance = balance - (prices[j-1]*k);
					_count[j-1]=_count[j-1]-k;
					std::cout << OUTPUT;
					std::cout << "GOOD! Purchase made \n";
					file << "Выведено сообщение о том, что покупка совершена \n" ;
				}
				else if (Select_Product == 0 || Select_Product > numbers.size() || Select_Product < 0)
				{
					code = ERROR;
					file << "< INPUT >" << commands[code] << '\n';
					std::cout << OUTPUT;
					std::cout << "Incorrect product number! \n";
					file << "Выведена ошибка \n" ;
					break;
				} 
			}
			else if (line == "DISPENSE")
			{
				code = DISPENSING;
				file << "<Ввод> DISPENSE \n" ;
				file << "<Статус> DISPENSING \n" ;
				std::cout << OUTPUT;
				std::cout << "The product has been issued \n";
				file << "Выведено сообщение о получении товара \n" ;
			}
			else if (line == "EXIT")
			{
				code = EXIT;
				file << "<Ввод> EXIT \n" ;
				file << "<Статус> EXIT \n" ;
				break;
			}
			else
			{
				code = ERROR;
				std::cout << "Invalid command entered \n";
			} 
		}
		std::cout << LINE20 << "\n";
		std::cout << "STOP: \n";
		file << "STOP: \n";
		file << LINE20 << "\n";
		file.close();
		return 0;
	}	
}