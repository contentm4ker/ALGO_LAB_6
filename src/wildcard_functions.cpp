#include "../include/wildcard_functions.hpp"

void SplitStringAndAddAllPartsInTrie(const string& str, Trie& tr, char sep) {
   string p;
   for(size_t i = 0; i < str.length(); ++i) {
       if(str[i] != sep) {
           p += str[i];
           if(str[i+1] == sep || str[i+1] == '\0') {
              tr.AddStringToTrie(p);
              tr.poss_of_patterns_set.push_back(i - p.length() + 2);
              p = "";
           }
       }
   }
}

void PositionsOfFullPattern(Trie& tr, int pattern_sz, int text_sz) {
    tr.C.resize(text_sz);
    for(size_t i = 0; i < tr.nums_of_pattern.size(); ++i) {
      int text_position = tr.all_poss[i];
      int in_set_position = tr.poss_of_patterns_set[tr.nums_of_pattern[i]];
      int index = text_position - in_set_position + 1;
      if(index + pattern_sz > text_sz)
         continue;
      if(text_position >= in_set_position - 1)
         tr.C[index]++;
   }
}

vector<int> ResultPos(Trie& tr) {
    vector<int> res;
    for(size_t i = 0; i < tr.C.size(); ++i) {
        if(tr.C[i] == tr.pattern.size())
            res.push_back(i + 1);
    }
    return res;
}