// app.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include "counter.h"


int main(int argc, char *argv[]) //pocet parametrov, pole parametrov
{
	std::string retazec;

	if (argc == 1)
	{
		return 0;
	}
	else if (argc == 2)
	{
		if (std::string(argv[1]) == ("-c"))
		{
			//pocitanie znakov v texte
			std::cout << "Pocitanie znakov v texte. Zadajte retazec" << std::endl;
			getline(std::cin, retazec);
			std::cout << "Pocet znakov v retazci je: " << counter_c(retazec) << std::endl;
		}

		if (std::string(argv[1]) == ("-w"))
		{
			//pocitanie slov v texte
			std::string line;
			std::cout << "Pocitanie slov v zadanom texte. Zadajte retazec" << std::endl;
			getline(std::cin,retazec);
		//	retazec += std::string(line + " ");
			std::cout << "Pocet slov v retazci je: " << counter_w(retazec+ " ") << std::endl;
		}
			
		if (std::string(argv[1]) == ("-l"))
		{
			//pocitanie riadkov v texte
			std::cout << "Pocitanie riadkov v zadanom texte. Zadajte retazec" << std::endl;
			char c;
			std::string retazec;
			while (std::cin.get(c))
			{
				retazec += c;
				if (c == '\t')
					break;
			}
			std::cout << "Pocet riadkov je: " << counter_l(retazec) << std::endl;
		}
	}

	else if (argc == 3)
	{
			std::string subornazov;
			subornazov = std::string(argv[2]);
			std::fstream subor;
			subor.open(subornazov, std::fstream::in);
			std::string line;
			if (!subor.is_open()) {
				std::cout << "Subor sa nepodarilo otvorit." << std::endl;
			}

			if (std::string(argv[1]) == ("-c"))
			{
				//nacitanie textu do premennej typu string
				while (getline(subor, line)) {
					retazec += line;
				}
				subor.close();
				std::cout << "Pocet znakov v subore je: " << counter_c(retazec) << std::endl;
			}
			
			if (std::string(argv[1]) == ("-w"))
			{
				//pocitanie slov v texte
				while (getline(subor, line)) { 
				//	retazec += line;
					retazec += std::string(line + " ");
				}
				subor.close();
				std::cout << "Pocet slov v subore je: " << counter_w(retazec) << std::endl;
			}

			if (std::string(argv[1]) == ("-l"))
			{
				//pocitanie riadkov v texte
				char c;
				while (!subor.eof())
				{
					subor.get(c);
					retazec += c;
				}
	
				subor.close();
				std::cout << "Pocet riadkov v subore je: " << counter_l(retazec) << std::endl;
			}	
	}

	return 0;
}
