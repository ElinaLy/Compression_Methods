
#include "Header.h"
//#include "zlib\zlib.h"




using namespace std;
namespace fs = std::filesystem;




void  writefile(ofstream& file, int lines) 
{
		for (int i = 0; i < lines; i++) 
		{
			unsigned int uIntNumber = rand();
			float floatNumber = static_cast<float>(rand()) / RAND_MAX;
			unsigned short uShortNumber = static_cast<unsigned short>(rand());

			file << uIntNumber << " " << floatNumber << " " << uShortNumber << "\n";
		}
	
	std::cout << "File has been written" << std::endl;
}



vector<uint8_t> compressByteArray(const string& compressed) 
{
	vector<uint8_t> byte_array;
	for (size_t i = 0; i < compressed.size(); i += 8) 
	{
		string byte_str = compressed.substr(i, 8);
		uint8_t byte = bitset<1>(byte_str).to_ulong();
		byte_array.push_back(byte);
	}
	return byte_array;
}

bool comparefiles(string& file, const string& str) {
	std::string line;
	ifstream in(file); 
	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (line != str)
				return 0;	
		}
	}
	in.close();
	return 1;

}

void Huffman(ofstream &newf, string &content) {
	string compressed = buildHuffmanTree(content); //строка из 0 и 1
	vector<uint8_t> byte_array = compressByteArray(compressed);
	for (uint8_t i : byte_array)
		newf << i;
}

void lzw(ofstream& newf, string& content) {
	vector<int> output_code = encoding(content);
	stringstream ss;

	for (auto i = 0; i < output_code.size(); i++)
	{
		auto a = bitset<1>(output_code[i]);
		ss << a;
	}
	string compressed = ss.str(); //строка из цифр
	//cout << compressed;
	vector<uint8_t> byte_array = compressByteArray(compressed);
	for (uint8_t i : byte_array) {
		newf << i;
		//cout << "i:  " << i << endl;
	}

	//cout << "Output Codes are: ";
	/*for (int i = 0; i < output_code.size(); i++) {
		cout << output_code[i] << " ";
	}
	*///cout << endl;
	decoding(output_code);

}

void lz78(ofstream& newf, string& content) {
	string result, result1;
	result = LZ78(content, 1);
	//cout << "\nresult : " << result;
	//cout << "\nFinal result : " << result << endl;
	stringstream ss;

	for (auto i = 0; i < result.size(); i++)
	{
		auto a = bitset<1>(result[i]);
		ss << a;
	}

	string compressed = ss.str(); //строка из цифр
	cout << endl;
	vector<uint8_t> byte_array = compressByteArray(compressed);
	for (uint8_t i : byte_array) {

		newf << i;

	}
	result1 = LZ78(result, 2);
	//cout << "\nFinal result : " << result1 << endl;



}

int main()
{
	setlocale(LC_ALL, "rus");
    int lines;
	 
	cout << "Enter the number of lines in a file\n";
	cin >> lines;
	ofstream gf;
	gf.open("f1.txt");      

	if (gf.is_open())
	{
		writefile(gf, lines);
	}
	gf.close();
    uintmax_t fileSize = std::filesystem::file_size("f1.txt"); 
    cout << "File size: " << fileSize << " byte" << endl;

	ifstream in("f1.txt"); // read file
	string str, content;
	if (in.is_open())
	{
		while (!in.eof()) 
		{
			getline(in, str);
			content += str + '\n';
		}
	}
	in.close();

    
	string compressed;
  
    ofstream newf; 
	newf.open("newfile.bin", ios::binary);
	if (newf.is_open())
	{
		int q;
		cout << "Choose the method:" << "\t\n 1 - Huffman \n 2 - LZW \n 3 - LZ78\n";
		cin >> q;
		switch (q) {
		
		//srand(time(0));
		case 1:
			Huffman(newf, content);
			break;
		case 2:
			lzw(newf, content);
			break;
		case 3:
			lz78(newf, content);
			break;
		default:
			cout << "Method is not found. Compression doesn't exist";
			break;
		//cout << "runtime = " << clock() / 1000.0 << endl;
		}
		
	}
	newf.close();
	uintmax_t fileSize2 = std::filesystem::file_size("newfile.bin"); 
	std::cout << "\nCompressed file size : " << fileSize2 << " byte" << std::endl;
	system("pause");
    return 0;
}
