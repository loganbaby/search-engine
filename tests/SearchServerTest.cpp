#include "SearchServer.h"
#include "gtest/gtest.h"

#include <iostream>

using std::vector;
using std::string;

TEST(TestCaseSearchServer, TestCaseSearchingServer) {
    const vector<string> docs = {
        "milk milk milk milk water water water",                     // milk - 4 | water - 3 | abs - 7  | rel - 7 / 10 = 0.7
        "milk water water",                                          // milk - 1 | water - 2 | abs - 3  | rel - 3 / 10 = 0.3
        "milk milk milk milk milk water water water water water",    // milk - 5 | water - 5 | abs - 10 | rel - 10 / 10 = 1
        "americano cappuccino"                                       // milk - 0 | water - 0 | abs - 0  | rel - false
    };

    const vector<string> request = {"milk water", "sugar"};
    const std::vector<vector<RelativeIndex>> expected = {{{2, 1}, {0, 0.7}, {1, 0.3}}, {}};

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request, 5);
    ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, TestTop5) {
    const vector<string> docs = {
        "london is the capital of great britain",
        "paris is the capital of france",
        "berlin is the capital of germany",
        "rome is the capital of italy",
        "madrid is the capital of spain",
        "lisboa is the capital of portugal",
        "bern is the capital of switzerland",
        "moscow is the capital of russia",
        "kiev is the capital of ukraine",
        "minsk is the capital of belarus",
        "astana is the capital of kazakhstan",
        "beijing is the capital of china",
        "tokyo is the capital of japan",
        "bangkok is the capital of thailand",
        "welcome to moscow the capital of russia the third rome",
        "amsterdam is the capital of netherlands",
        "helsinki is the capital of finland",
        "oslo is the capital of norway",
        "stockholm is the capital of sweden",
        "riga is the capital of latvia",
        "tallinn is the capital of estonia",
        "warsaw is the capital of poland",
    };

    const vector<string> request = {"moscow is the capital of russia"};
    const std::vector<vector<RelativeIndex>> expected = {{
        {7, 1},
        {14, 1},
        {0, 0.666666687},
		{1, 0.666666687},
		{2, 0.666666687}}};

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request, 5);

    ASSERT_EQ(result, expected);
}