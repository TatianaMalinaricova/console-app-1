// app.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <iterator>

int main(int argc, char *argv[]) //pocet parametrov, pole parametrov
{
	char prepinac;
	std::cout << "Hello World!" << std::endl;
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
			getline(std::cin,retazec);
			std::cout<<"Pocet znakov v retazci je: " << retazec.size() << std::endl;

		//	std::iftream f(argv[1]);
		//	std::istream_iterator<char> my_it;
		//	std::distance(std::istream_iterator<char>(s));
		}
		if (std::string(argv[1]) == ("-w"))
		{
			//pocitanie slov v texte
			int poc=0;
			std::cout << "Pocitanie slov v zadanom texte. Zadajte retazec" << std::endl;
			getline(std::cin, retazec);

			char nasled;
			for (int i = 0; i <	int(retazec.length()); i++)
			{
				nasled = retazec.at(i); 
				if (isspace(retazec[i]))
					poc++;
			}
			std::cout << "\nPocet slov je: " << poc<< std::endl;
			
		}
		if (std::string(argv[1]) == ("-l"))
		{
			//pocitanie riadkov v texte
			std::cout << "Pocitanie riadkov v zadanom texte. Zadajte retazec" << std::endl;
			char c;
			int poc = 0;

			while (std::cin.get(c)) 
			{ 
				if (c == '\n')
					poc++;

				if (c == '\t')
					break;
			}
			std::cout << "Pocet riadkov je: " << poc<<std::endl;


		}
	}
	return 0;
}
