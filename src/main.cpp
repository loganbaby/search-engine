#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"

int main() {
    auto converterJSON = ConverterJSON("json/config.json", "json/requests.json");
    auto invertedindex = InvertedIndex();

    invertedindex.UpdateDocumentBase(converterJSON.GetTextDocuments());
    SearchServer server(invertedindex);
    server.setResponseLimit(converterJSON.GetResponseLimit());
    auto answers = server.search(converterJSON.GetRequests());
    converterJSON.putAnswers(answers, "json/answers.json");
    
    std::cout << "Execution is complete!" << std::endl;
}