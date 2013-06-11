// Project: Monoalphabet Cipher
// Author:  Yonglei Tao

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// substitute characters given in the list for characters in the input stream
// and then send them to the output stream

void substitute (istream& in, ostream& out, char list[])
{  
	char ch;
	int pos;

	while (in.get(ch))
	{
		if ( ch >= 'a' && ch <= 'z' )
		{
			pos = ch - 'a';
			out << list[pos];
		}
		else
			out << ch;
	}
}


// check and see if a letter is included in the list already

bool found (char list[], int size, char ch)
{
	int i = 0;
	while ( i < size && list[i] != ch)
		i++;
	if (i < size && list[i] == ch)
		return true;
	return false;
}


// a helper function that displays the contents of array list

void display(char list[], int size)
{
	for (int i = 0; i < size; i++)
		cout << list[i];
	cout << endl;
}

int main()
{  
	// allow the user to decide what one wants to do and provide the key
	
	int choice;
	cout << "Options\n\n";
	cout << "1. Encryption\n";
	cout << "2. Decryption\n\n";
	cout << "Enter your choice: ";
	cin >> choice;

	string key;
	cout << "Enter your key: ";
	cin >> key;
	cout << endl;


	char sub[26];
	char res[26];

	// load array sub with the alphabet for substitution

	for (int i = 0; i < key.length(); i++)
		sub[i] = key.at(i);
	
	int pos = key.length();

	for (int ch = 'z'; ch >= 'a'; ch--)
		if ( ! found(sub, key.length(), ch) )
			sub[pos++] = ch;

	// open the input and output files

	string infname;
	cout << "Enter the input file name: ";
	cin >> infname;

	ifstream infile;
	infile.open(infname.c_str());

	if (infile.fail()) 
	{
		cout << endl << "Input file not found\n";
		exit(1);
	}
		
	string outfname;
	cout << "Enter the output file name: ";
	cin >> outfname;

	ofstream outfile;
	outfile.open (outfname.c_str());

	if (choice == 1)		
	{
		// perform encryption
		
		substitute (infile, outfile, sub);
	}
	else					
	{
		// load the array with the alphabet for reverse substitution

		for (int i = 0; i < 26; i++)
			res[ sub[i] - 'a'] = i + 'a';

		// perform decryption

		substitute (infile, outfile, res);
	}

	infile.close();
	outfile.close();

	// display the contents of the two substitution arrays

	cout << endl;
	cout << "Show the alphabet for substitution" << endl;
	display (sub, 26);
	if (choice == 2)
	{
		cout << "\nShow the alphabet for reverse substitution" << endl;
		display (res, 26);
	}
	cout << endl;

	return 0;
}
