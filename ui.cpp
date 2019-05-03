#include "ui.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

//����ԭ��
//1.���з������ո�
//2.��������ո�ֻ����һ���ո�
//3.ȥ�������š������š����š��Ⱥ�����Ŀո�
//4.WHERE�����������඼����һ���ո�
void UI::preProcess(std::string& sentence) {
	findKeywords(sentence);
	No_n(sentence);
	NoExtraSpace(sentence);
	return;
}


void UI::findKeywords(std::string& _info)
{
	std::string info(_info);
	transform(info.begin(), info.end(), info.begin(), ::toupper);
	std::vector<std::string> words;
	words.push_back("CREATE");
	words.push_back("DATABASE");
	words.push_back("DATABASES");
	words.push_back("DROP");
	words.push_back("USE");
	words.push_back("SHOW");
	words.push_back("TABLE");
	words.push_back("NOT");
	words.push_back("NULL");
	words.push_back("PRIMARY");
	words.push_back("KEY");
	words.push_back("COLUMNS");
	words.push_back("FROM");
	words.push_back("INSERT");
	words.push_back("INTO");
	words.push_back("VALUES");
	words.push_back("WHERE");
	words.push_back("UPDATE");
	words.push_back("SET");
	words.push_back("SELECT");
	words.push_back("AND");
	words.push_back("OR");
	for (size_t i = 0; i < words.size(); i++)
	{
		int x = -1;
		while (true)
		{
			x = info.find(words[i], x + 1);
			if (x == info.npos) break;
			_info.replace(x, words[i].size(), words[i]);
		}
	}
	return;
}
void UI::No_n(std::string& info)
{
	int x1 = -1;
	while (true)
	{
		x1 = info.find('\n', x1 + 1);
		if (x1 != info.npos) info[x1] = ' ';
		else break;
	}
}
void UI::NoExtraSpace(std::string& sentence)
{
	int x1 = -1;
	while (sentence[0] == ' ') sentence.erase(0, 1);
	while (sentence[sentence.size() - 1] == ' ')sentence.erase(sentence.size() - 1, 1);
	while (1)
	{
		x1 = sentence.find(' ', x1 + 1);
		if (x1 == sentence.npos)break;//�Ҳ����ո�
		while (sentence[x1 + 1] == ' ')
		{
			sentence.erase(x1 + 1, 1);
		}
	}
	x1 = -1;
	while (1)
	{
		x1 = sentence.find('=', x1 + 1);
		if (x1 != sentence.npos)
		{
			if (x1 == 0 && sentence[x1 + 1] == ' ')
			{
				sentence.erase(x1 + 1, 1);
			}
			else if (x1 == sentence.size() - 1 && sentence[x1 - 1] == ' ')
			{
				sentence.erase(x1 - 1, 1);
			}
			else
			{
				if (sentence[x1 + 1] == ' ')
					sentence.erase(x1 + 1, 1);
				if (sentence[x1 - 1] == ' ')
					sentence.erase(x1 - 1, 1);
			}
		}
		else break;
	}
	x1 = -1;
	while (1)
	{
		x1 = sentence.find(',', x1 + 1);
		if (x1 != sentence.npos)
		{
			if (x1 == 0 && sentence[x1 + 1] == ' ')
			{
				sentence.erase(x1 + 1, 1);
			}
			else if (x1 == sentence.size() - 1 && sentence[x1 - 1] == ' ')
			{
				sentence.erase(x1 - 1, 1);
			}
			else
			{
				if (sentence[x1 + 1] == ' ')
					sentence.erase(x1 + 1, 1);
				if (sentence[x1 - 1] == ' ')
					sentence.erase(x1 - 1, 1);
			}
		}
		else break;
	}
	x1 = -1;
	int x2 = 0;
	while (1)
	{
		x2 = sentence.find("WHERE", 0);
		x1 = sentence.find('(', x1 + 1);
		if (x1 != sentence.npos)
		{
			if (x2 != sentence.npos&&x1 > x2)
			{
				if (sentence[x1 + 1] != ' ')sentence.insert(x1 + 1, 1, ' ');
				if (sentence[x1 - 1] != ' ')sentence.insert(x1, 1, ' ');
			}
			else if (x1 == 0 && sentence[x1 + 1] == ' ')
			{
				sentence.erase(x1 + 1, 1);
			}
			else if (x1 == sentence.size() - 1 && sentence[x1 - 1] == ' ')
			{
				sentence.erase(x1 - 1, 1);
			}
			else
			{
				if (sentence[x1 + 1] == ' ')
					sentence.erase(x1 + 1, 1);
				if (sentence[x1 - 1] == ' ')
					sentence.erase(x1 - 1, 1);
			}
		}
		else break;
	}
	x1 = -1;
	while (1)
	{
		x2 = sentence.find("WHERE", 0);
		x1 = sentence.find(')', x1 + 1);
		if (x1 != sentence.npos)
		{
			if (x2 != sentence.npos&&x1 > x2)
			{
				if (sentence[x1 + 1] != ' ')sentence.insert(x1 + 1, 1, ' ');
				if (sentence[x1 - 1] != ' ')sentence.insert(x1, 1, ' ');
			}
			else if (x1 == 0 && sentence[x1 + 1] == ' ')
			{
				sentence.erase(x1 + 1, 1);
			}
			else if (x1 == sentence.size() - 1 && sentence[x1 - 1] == ' ')
			{
				sentence.erase(x1 - 1, 1);
			}
			else
			{
				if (sentence[x1 + 1] == ' ')
					sentence.erase(x1 + 1, 1);
				if (sentence[x1 - 1] == ' ')
					sentence.erase(x1 - 1, 1);
			}
		}
		else break;
	}
}
std::stringstream UI::getCommand() {
	/*
	if (std::cin.rdbuf()->in_avail() == 0 || std::cin.rdbuf()->in_avail() == 1)
		std::cout << "mysql>";
	*/
	std::string sentence;
	getline(std::cin, sentence, ';');
	preProcess(sentence);
	std::stringstream myinput(sentence);
	return myinput;
}