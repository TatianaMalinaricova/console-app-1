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
			std::cout << "Zadajte retazec" << std::endl;
			getline(std::cin,retazec);
			std::cout<<"Pocet znakov v retazci je: " << retazec.size() << std::endl;

		//	std::istream s(std::string(argv[1]));
		//	std::istream_iterator<char> it = ;
		//	std::distance(std::istream_iterator<char>(s));
		}
		if (std::string(argv[1]) == ("-w"))
		{
			//pocitanie slov v texte
			int poc=0;
			std::cout << "Zadajte retazec" << std::endl;
			getline(std::cin, retazec);

			char nasled;
			for (int i = 0; i<int(retazec.length()); i++)
			{
				nasled = retazec.at(i); 
				if (isspace(retazec[i]))
					poc++;
			}
			std::cout << "\nPocet slov je: " << poc<< std::endl;
			
		}
		if (argv[1] == ("-l"))
		{
			//pocitanie riadkov v texte

		}
	}


	system("pause");
	return 0;
}
