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
	//pocitanie slov v texte
	int poc = 0;
	char nasled;
	for (int i = 0; i < int(retazec.length()); i++)
	{
		nasled = retazec.at(i);
		if (isspace(retazec[i]))
			poc++;
	}
	return poc;
}

int counter_l(std::string retazec)
{
	//pocitanie riadkov v texte
	int poc = 0;

	for (int i = 0; i < retazec.size(); i++)
	{
		if (retazec[i] == '\n')
			poc++;
	}
	return poc;
}


