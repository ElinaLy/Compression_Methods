#pragma once
#include <unordered_map>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <random>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <bitset>
#include <iterator>
#include <ctime> 

using namespace std;


struct Node;
Node* getNode(char ch, int freq, Node* left, Node* right);
struct comp;
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode);
void decode(Node* root, int& index, string str);
string buildHuffmanTree(string text);
struct data;

vector<int> encoding(string s1);
void decoding(vector<int> op);

struct Node1;
void st_Node(Node1* head, int index, string data);
void insert_Node(Node1* head, int index, string data);
Node1* search_Node(Node1* head, string data);
Node1* search_Node(Node1* head, int index);
bool delete_Node(Node1* head, Node1* to_delete);
vector <string> split(string str, char delimiter);
string LZ78(string input, int option);












