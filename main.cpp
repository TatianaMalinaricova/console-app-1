// app.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
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
			//	std::iftream f(argv[1]);
			//	std::istream_iterator<char> my_it;
			//	std::distance(std::istream_iterator<char>(s));
		}
		if (std::string(argv[1]) == ("-w"))
		{
			//pocitanie slov v texte
			std::cout << "Pocitanie slov v zadanom texte. Zadajte retazec" << std::endl;
			getline(std::cin, retazec);
			std::cout << "Pocet slov v retazci je: " << counter_c(retazec) << std::endl;

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
	return 0;
}
