#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>

using std::string;
using std::vector;
using std::out_of_range;
using std::cin;
using std::cout;
using std::endl;

const vector<char> alphabet = {'A', 'C', 'G', 'T', 'N'};

int GetIndInAlphabet(char ch);

struct TrieVrtx{
   //номер вершины в которую мы придем по символу номер i в алфавите
   vector<int> next_vrtx;

   //номера шаблонов в данной вершине
   vector<int> pat_nums;

   //суффиксные ссылки
   int suff_link = -1;
   int suff_flink = -1; //"хорошая"

   //запоминание перехода автомата
   vector<int> auto_move;

   //вершина-родитель в дереве
   int parent;

   //является ли вершина строкой
   bool flag = false;

   //символ на ребре от parent к этой вершине
   char symb;
};

class Trie {
private:
   TrieVrtx MakeTrieVrtx(int p, char c); //добавление вершины в бор
   void TrieInit();    //добавление корня

   //две рекурсивные функции, вызывающие друг друга
   int GetSuffLink(int v);
   int GetAutoMove(int v, int ch);

   //вычисление хорошей суффиксной ссылки
   int GetSuffFLink(int v);

   void Check(int v, int i);

public:
//methods:
   Trie() { TrieInit(); };
   void FindAllPos(const string& s);
   //добавление строки в бор
   void AddStringToTrie(const string& s);

//data:
   vector<TrieVrtx> trie; //вершины бора
   vector<string> pattern; //хранит набор максимальных подстрок без джокеров
   vector<int> C; //массив для поиска строки с "джокерами"
   //хранит начaльные позиции этих подстрок в шаблоне с "джокерами"
   vector<int> poss_of_patterns_set;
   //все позиции вхождения шаблонов в текст
   vector<int> all_poss;
   //номера шаблонов, которые содержатся в тексте
   vector<int> nums_of_pattern;
};

#endif