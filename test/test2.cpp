#include <gtest/gtest.h>
#include "../src/aho_corasick.cpp"
#include "../src/wildcard_functions.cpp"

namespace {

using ::testing::TestWithParam;
using ::testing::Values;

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