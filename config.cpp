#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
void Hello();
int config (char* file_name, char* login, char* password)
{
	std::string log1, log2; //Хешируем логин
	log1 = login;
	log2 = "Danil";
	std::hash<std::string> hash_log;
	size_t hash_log1 = hash_log (log1);
	size_t hash_log2 = hash_log (log2);
	
	std::string pass1, pass2; //Хэшируем пароль
	pass1 = password;
	pass2 = "123321";
	std::hash <std::string> hash_pass;
	size_t hash_pass1 = hash_pass (pass1);
	size_t hash_pass2 = hash_pass (pass2);
	
	if ((hash_log1 == hash_log2) && (hash_pass1 == hash_pass2))
	{
		Hello();	
		std::ofstream file;
		file.open(file_name, std::ios::out);
		if (!(file.is_open()))
		{
			std::cout << "Ошибка открытия файла \n";
			return 0;
		}
		std::cout<<"Ввод товаров. \n";
		std::cout<<"Для окончания ввода введите 0 \n";
		std::cout << "----------------------------- \n";
		int i=1;
		std::string name;
		int price;
		int count;
		int balance;
		while (1)
		{
			std::cout<< i << " Товар \n";
			std::cout << "Наименование товара: ";
			std::cin >> name;
			std::cout << "Количество товара: ";
			std::cin >> count;
			if (name == "0") { break; }
			std::cout << "Цена товара: ";
			std::cin >> price;
			if (price == 0) {break; }
			file << i << " " <<name << " " << price << " " <<count << "\n";
			i++;
		}
		std::cout << "------------------------------- \n";
		file.close();
	}
	else
	{
		std::cout<<"Ошибка ввода логина или пароля. \n";
	}
	return 0;
}
void Hello()
{

	std::cout << "*****************************************\n"
		<< "* Nizhniy Novgorod Technical University *\n"
		<< "*    Study work number 5, variant 3     *\n"
		<< "*   Performed student Baryshev Danil    *\n"
		<< "*****************************************\n";
}