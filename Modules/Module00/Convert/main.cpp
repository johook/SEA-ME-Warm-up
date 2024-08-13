#include <iostream>
#include <string>

using namespace std;
string convert(string);

int main() {
	string str, uord, text;

	getline(cin, str);			// Get the sentence
	uord = str.substr(10);		// Remove ./convert to distinguish up or down

	text = convert(uord);		// Convert Function

	cout << text << endl;
	return 0;
}

string convert(string uord)		// Function that change to upper or Lower case
{
	string text;

	if (uord[0] == 'u')			// If word start with "u" which means "up", convert to UPPERCASE
	{
		text = uord.substr(3);

		for (int i = 0; i < text.size(); i++)
		{
			text[i] = toupper(text[i]);
		}
	}
	else if (uord[0] == 'd')	// If word start with "d" which means "down", convert to LOWERCASE
	{
		text = uord.substr(5);

		for (int i = 0; i < text.size(); i++)
		{
			text[i] = tolower(text[i]);
		}
	}
	else					   // neither condition, an error message will be displayed
	{
		cout << "Check the infomation" << endl;
	}

	return text;
}
