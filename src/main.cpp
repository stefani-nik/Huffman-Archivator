#include "stdafx.h"
#include "HuffmanCoding.h"
#include <string>
#undef UNICODE // Had to undefine the unicode because of the CreateDirectory function?
#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm> 
#include <functional> 


using namespace std;

void getDir(string d, vector<string> & f); // goes recursively through the directory
int compress(string h, string in, string out);  // commpress with Huffman algorithm
int decompress(string in, string out); // commpress with Huffman algorithm
string unitefiles( string dir); // unites all files from the directory
void reunitefiles(string file, string dir); // reunites all files from the archive 
void findFiles(string file); // finds the files which are includes in the archive 
void writeList(string header,string file); // writing the header file 
string extractText(string t, string d1, string d2); // Helper function for extracting text between two delimeters
static inline string &ltrim(string &s);
static inline string &rtrim(string &s);    // trimming functions used in the getDir function 
static inline string &trim(string &s);

class str
{
public:
	string data;
	unsigned int length;
};

int main()
{
	string command;
	cin >> command;

	if (command == "-Pack")
	{
		string input, output;
		cin >> input >> output;
	
		string header = unitefiles(input);
		compress(header, "output.pac", output);
		remove("output.pac");
		string headerFile = extractText(output, "\\", ".") + ".header";
		writeList(header, headerFile);
	}
	else if (command == "-Unpack")
	{
		string input, output;
		cin >> input >> output;

		decompress(input, "output.pac");
		reunitefiles("output.pac",output);
		remove("output.pac");

	}
	else if (command == "-List")
	{	
		string input;
		cin >> input;
		string header = extractText(input, "\\" ,".") + ".header";
		findFiles(header);
	
	}
	else
	{
		cout << "Invalid command!" << endl;
	}
}


//compress using HuffmanCoding
int compress(string h, string in, string out)
{
	HuffmanCoding hc;
	try
	{
		hc.compress(h,in, out);
	}
	catch (...)
	{
		cout << "Error occured" << endl;
	}
	return 0;
}

//decompress using HuffmanCoding
int decompress(string in, string out)
{
	HuffmanCoding hc;
	try
	{
		hc.decompress(in, out);
	}
	catch (...)
	{
		cout << "Error occured" << endl;
	}
	return 0;
}
void getDir(string d, vector<string> & f)
{
	FILE* pipe = NULL;
	string pCmd = "dir /B /S " + string(d);
	char buf[256];

	if (NULL == (pipe = _popen(pCmd.c_str(), "rt")))
	{
		cout << "Error occurred" << endl;
		return;
	}

	while (!feof(pipe))
	{
		if (fgets(buf, 256, pipe) != NULL)
		{
			f.push_back(trim(string(buf)));
		}

	}
	_pclose(pipe);
}
string unitefiles(string dir)
{
	unsigned char uc;
	char c;

	// Vector for all the files which is passed to the getDir function
	vector<string> files;
	getDir(dir, files);

	//Vector for the file names which is used for storing all files' names and length 
	vector<str> f_names;
	string header;
	str st;
    //Iterator for the files vector 
	vector<string>::const_iterator it = files.begin();

	//Reading each file of the vector 
	while (it != files.end())
	{
		//Assign data (the name o the file)
		st.data = string(*it);

		if (st.data.empty())
		{
			break;
		}
		//Reading the file 
		ifstream infile(st.data.c_str(), ios::in | ios::binary);
		
		if(infile)
		{
			//Counting all the character in the file (Slow)
			st.length = 0;
			while (infile.get(c))
			{
				++st.length;
			}
			infile.clear(); //clear the EOF flag
			infile.seekg(0); //reset the pointer to beginning
			infile.close();

			f_names.push_back(st);
			header += st.data + ";";
			
		}
		it++;
	}
	
	//Creating the temporary file 
	string s = "output.pac";
	ofstream outfile(s.c_str(), ios::out | ios::binary);
	if (!outfile)
	{
		cerr << "The file " << s << " could not be opened!" << endl;
	}

	//Iterating through all the files in the f_names vector 
	for (unsigned int i = 0; i < f_names.size(); ++i)
	{
		outfile.write(f_names.at(i).data.c_str(), f_names.at(i).data.size());
		//add a next line char to the end of the file name
		c = '\n';
		uc = c;
		outfile.put(uc);

		//write the file length
		//divide 32 bit u. int values into 4 bytes
		outfile.put(static_cast<unsigned char>(f_names.at(i).length >> 24));
		outfile.put(static_cast<unsigned char>((f_names.at(i).length >> 16) % 256));
		outfile.put(static_cast<unsigned char>((f_names.at(i).length >> 8) % 256));
		outfile.put(static_cast<unsigned char>(f_names.at(i).length % 256));

		//write the file 
		ifstream infile(f_names.at(i).data.c_str(), ios::in | ios::binary);
		for (unsigned int j = 0; j < f_names.at(i).length; ++j)
		{
			infile.get(c);
			outfile.put(c);
		}
		infile.clear(); //clear the EOF flag
		infile.seekg(0); //reset the pointer to beginning
		infile.close();
	}

	return header;
}
void reunitefiles(string file,string dir )
{
	unsigned char uc;
	char c;

	//Reading the united file 
	ifstream infile(file, ios::in | ios::binary);
	if (!infile)
	{
		cerr << "The file " << file << " could not be opened!" << endl;
		return;
	}

	string s;
	unsigned int l, j;
	getline(infile, s);

	//Find the first directory of the path 
	int cur = s.find_last_of("\\");
	int currentFirst = s.find_last_of("\\", cur - 1 );
	string firstDir = s.substr(currentFirst + 1 , cur - currentFirst - 1);

	while (true)
	{
		//Break the while loop
		if (s.empty())
		{
			break;
		}
		
		//get the file length
		//read 4 bytes and combine them into one 32 bit u. int value
		l = 0;
		j = 1;
		for (int k = 3; k >= 0; --k)
		{
			infile.get(c);
			uc = c;
			l += uc*(j << (8 * k));
		}
		
		//Assing the path 
		string path = dir + "\\" + s.substr(s.find(firstDir), s.length());
	

		ofstream outfile(path.c_str(), ios::out | ios::binary);


		//If no such path exists create new directory
		if (!outfile)
		{
			int dirIndex = path.find_last_of("\\");
			int dirStartIndex = path.find_last_of("\\", dirIndex - 1);
			string directoryName = path.substr(0, dirIndex);

			CreateDirectory(directoryName.c_str(), NULL);

			outfile.close();
			outfile.open(path);

			if (!outfile)

			{
				return;
			}

		}
		//Write the file 
		for (unsigned int i = 0; i<l; ++i)
		{
			infile.get(c);
			outfile.put(c);
		}
		outfile.close();
		getline(infile, s);
	}
	infile.close();
}

//Listing the files contained in the archive 
void findFiles(string input)
{
	ifstream in(input);
	string header;
	getline(in, header);

	//Split and print 
	size_t pos = 0;
	string token;
	while ((pos = header.find(';')) != string::npos) {
		token = header.substr(0, pos);
		header.erase(0, pos +1);
		cout << token << endl;
	}
	in.close();
}

//Writing he header file 
void writeList(string header,string file)
{
	ofstream out(file);
	out << header;
	out.close();
}

//Helper function for extracting text between two delimeters
string extractText(string t, string d1, string d2)
{
	int index1 = t.find_last_of(d1);
	int index2 = t.find_last_of(d2);
	string result = t.substr(index1 + 1, index2 - index1 - 1) ;
	return result;
}

//trim from left end 
static inline string &ltrim(string &s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(),
		not1(ptr_fun<int, int>(isspace))));
	return s;
}

// trim from right end
static inline string &rtrim(string &s) {
	s.erase(find_if(s.rbegin(), s.rend(),
		not1(ptr_fun<int, int>(isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline string &trim(string &s) {
	return ltrim(rtrim(s));
}



