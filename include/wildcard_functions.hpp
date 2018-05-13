#ifndef WILDCARD_FUNCTIONS_H
#define WILDCARD_FUNCTIONS_H

#include "../include/aho_corasick.hpp"

void SplitStringAndAddAllPartsInTrie(const string& str, Trie& tr, char sep);
void PositionsOfFullPattern(Trie& tr, int pattern_sz, int text_sz);
vector<int> ResultPos(Trie& tr);

#endif