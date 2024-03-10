#include "searcher.hpp"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

const std::string input = "data/raw_html/raw.txt";

int main()
{
    ns_searcher::Searcher *search = new ns_searcher::Searcher();
    search->InitSearcher(input);

    std::string query;
    std::string json_string;

    char buf[1024];

    while (true)
    {
        std::cout << "Please Enter You Search Query# ";
        // std::cin >> query;
        fgets(buf, sizeof(buf) - 1, stdin);
        buf[strlen(buf) - 1] = 0;
        search->Search(buf, &json_string);
        std::cout << json_string << std::endl;
    }

    return 0;
}
