#pragma once

#include <iostream>
#include <string>
#include <iterator>

template<typename T>
size_t spocitaj(std::string str)
{
	T obj(str);
	return obj.spocitaj();
}

typedef struct _char : public std::string
{
	_char(std::string retazec) : std::string(retazec){}
	int spocitaj()
	{
		//pocitanie znakov v texte
		return size();
	}
};

typedef struct _word : public std::string
{
	_word(std::string retazec) : std::string(retazec) {}
	int spocitaj()
	{
		int i = 0;
		int poc = 0;

		//preskoci medzery pred slovom
		while (isspace(at(i))) {
			i++;
		}
		for (; i < int(length()); i++)
		{
			if (isspace(at(i))) {
				poc++;
				if ((isspace(at(i + 1))) && (at(i + 2) == '\0'))
					poc--;
			}

		}
		return poc;
	}
};

typedef struct _line : public std::string
{
	_line(std::string retazec) : std::string(retazec) {}
	int spocitaj()
	{
		//pocitanie riadkov v texte
		int poc = 1;

		for (int i = 0; i < size(); i++)
		{
			if (at(i) == '\n')
				poc++;
		}
		return poc;
	}
};


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


