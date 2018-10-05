#pragma once

#include <iostream>
#include <string>
#include <iterator>

int counter_c(std::string retazec)
{
		//pocitanie znakov v texte
	return retazec.size();
}

int counter_w(std::string retazec)
{
	int i = 0;
	int poc = 0;

	//preskoci medzery pred slovom
	while (isspace(retazec.at(i))) {
		i++;
	}
	for (;i < int(retazec.length()); i++)
	{
		if (isspace(retazec[i])) {
			poc++;
			if ((isspace(retazec[i+1])) && (retazec[i + 2] == '\0')) 
				poc--;
		}
			
	}
	return poc;

}

int counter_l(std::string retazec)
{
	//pocitanie riadkov v texte
	int poc = 1;

	for (int i = 0; i < retazec.size(); i++)
	{
		if (retazec[i] == '\n')
			poc++;
	}
	return poc;
}


