#include <gtest/gtest.h>
#include "../src/aho_corasick.cpp"
#include "../src/wildcard_functions.cpp"

namespace {

using ::testing::TestWithParam;
using ::testing::Values;

Trie GetResultForPos(const string& text, const vector<string>& patterns) {
   Trie tr;
   for(const auto& patt : patterns) {
      tr.AddStringToTrie(patt);
   }
   tr.FindAllPos(text);
   return tr;
}

vector<int> GetResulForWildCard(const string& text, const string& patt, char joker) {
    Trie tr;
    SplitStringAndAddAllPartsInTrie(patt, tr, joker);
    tr.FindAllPos(text);
    PositionsOfFullPattern(tr, patt.size(), text.size());
    return ResultPos(tr);
}

void Vectors_Comparison(vector<int> v1, vector<int> v2) {
    for (size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]) << "Vectors x and y differ at index " << i;
    }
}

struct PatternsSearchTest
{
    string text;
	vector<string> patterns;
	vector<int> expected_poss;
	vector<int> expected_nums_of_patterns;
};

class PSFixture : public TestWithParam<PatternsSearchTest>
{
public:
	virtual void SetUp() {
	    string _text = GetParam().text;
	    vector<string> _patterns = GetParam().patterns;
	    tr = GetResultForPos(_text, _patterns);
	}
    virtual void TearDown() { }

protected:
    Trie tr;
};

INSTANTIATE_TEST_CASE_P(PsInstantiate, PSFixture,
Values(
    PatternsSearchTest{"CCCA", {"CC"}, {0, 1}, {0, 0}},
    PatternsSearchTest{"CCCA", {"CC", "A"}, {0, 1, 3}, {0, 0, 1}},
    PatternsSearchTest{"ACGTNNTGCA", {"CG", "GTN", "CGTN", "A"}, {0, 1, 1, 2, 9}, {3, 0, 2, 1, 3}},
    PatternsSearchTest{"ACGTNNNNACGN", {"AGTCN", "AGT", "GT", "NA", "NAG"}, {2, 7}, {2, 3}},
    PatternsSearchTest{"AAAC", {"G", "T"}, {}, {}}
));

TEST_P(PSFixture, PSTest) {
    ASSERT_EQ(GetParam().expected_poss.size(), tr.all_poss.size())
    << "Vector size returning in KMP must be eq " << GetParam().expected_poss.size();
    Vectors_Comparison(GetParam().expected_poss, tr.all_poss);

    ASSERT_EQ(GetParam().expected_nums_of_patterns.size(), tr.nums_of_pattern.size())
    << "Vector size returning in Prefix Function must be eq " << GetParam().expected_nums_of_patterns.size();
    Vectors_Comparison(GetParam().expected_nums_of_patterns, tr.nums_of_pattern);
}

struct WildCardTest
{
    string text;
	string pattern;
	char joker;
	vector<int> expected_poss;
};

class WCFixture : public TestWithParam<WildCardTest>
{
public:
	virtual void SetUp() {
	    _positions = GetResulForWildCard(GetParam().text,
	                GetParam().pattern, GetParam().joker);
	}
    virtual void TearDown() { }

protected:
	vector<int> _positions;
};

INSTANTIATE_TEST_CASE_P(WcInstantiate, WCFixture,
Values(
	WildCardTest{"ACT", "A$", '$', {1}},
	WildCardTest{"AAA", "A$", '$', {1, 2}},
	WildCardTest{"AAAA", "A$A", '$', {1, 2}},
	WildCardTest{"AAAAA", "$A$A$", '$', {1}},
	WildCardTest{"ACGTNACGTNACGTNACGTN", "ACG$NAC$TNA$GT$A$G$$", '$', {1}},
	WildCardTest{"ACGTNNGCGCGNCA", "CG??N?", '?', {2, 8}},
	WildCardTest{"AAAAAAA", "A****", '*', {1, 2, 3}},
	WildCardTest{"AAAAAAA", "####A", '#', {1, 2, 3}},
	WildCardTest{"AAAAAAA", "*A****", '*', {1, 2}},
	WildCardTest{"AAAAAAA", "####A#", '#', {1, 2}}
));

TEST_P(WCFixture, WCSearchTest) {
    ASSERT_EQ(GetParam().expected_poss.size(), _positions.size())
    << "Vector size returning in KMP must be eq " << GetParam().expected_poss.size();
    Vectors_Comparison(GetParam().expected_poss, _positions);
}

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}