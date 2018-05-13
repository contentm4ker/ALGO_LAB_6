#include "../include/aho_corasick.hpp"

int main() {
   Trie tr;
   string text, patt;
   int n;
   cin >> text >> n;
   for(size_t i = 0; i < n; ++i) {
      cin >> patt;
      tr.AddStringToTrie(patt);
   }
   tr.FindAllPos(text);
   for(size_t i = 0; i < tr.all_poss.size(); ++i)
       cout << tr.all_poss[i] + 1 << " " << tr.nums_of_pattern[i] + 1 <<endl;
   return 0;
}