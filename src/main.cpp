#include <iostream>
#include <exception>

#include "ConverterJSON.h"
#include "InvertedIndex.h"

int main() {
    auto converterJSON = ConverterJSON("json/config.json", "json/requests.json");
    auto invertedindex = InvertedIndex();

    try {
        invertedindex.UpdateDocumentBase(converterJSON.GetTextDocuments());
        SearchServer server(invertedindex);
        server.setResponseLimit(converterJSON.GetResponseLimit());
        auto answers = server.search(converterJSON.GetRequests(), converterJSON.GetResponseLimit());
        converterJSON.putAnswers(answers, "json/answers.json");
    } catch (std::exception& x) {
        std::cerr << "Exception handled! Program failed!" << x.what();
        std::exit(5);
    }

    std::cout << "Program succeed!" << std::endl;
}