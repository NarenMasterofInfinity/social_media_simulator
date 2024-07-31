#include "classes.hpp"
#include <string>
#include <sstream>
#include <iterator>

#ifndef EMOJI_H
#define EMOJI_H

void String::setContent(string content)
{
	this->content = content;
}
void String::display()
{
	cout << content << endl;
}

void Emoji::display()
{
	cout << converted << endl;
}
void Emoji::setContent(string content)
{
	this->content = converted = parse_and_replace(content);
}
string Emoji::getContent()
{
	return content;
}
string String::getContent()
{
	return content;
}
string Emoji::parse_and_replace(string content)
{
	stringstream ss(content);
	vector<string> v;
	string s;
	while (getline(ss, s, ' '))
	{
		for (auto &x : s)
		{
			x = tolower(x);
		}
		v.push_back(s);
	}
	string res = "";
	for (auto i = v.begin(); i != v.end(); i++)
	{
		if ((*i)[0] == ':')
		{
			string emoji = i->substr(1, i->size() - 1);
			string replace = emojis[emoji];
			res += (replace + " ");
		}
		else
		{
			res += (*i);
			res += " ";
		}
	}
	return res;
}
#endif