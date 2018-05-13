#include "../include/wildcard_functions.hpp"

int main(){
   Trie tr;
   string text, patt;
   char joker;
   cin >> text >> patt >> joker;

   SplitStringAndAddAllPartsInTrie(patt, tr, joker);

   tr.FindAllPos(text);

   PositionsOfFullPattern(tr, patt.size(), text.size());

   vector<int> res = ResultPos(tr);

   for(const auto& r : res)
      cout << r << endl;

   return 0;
}