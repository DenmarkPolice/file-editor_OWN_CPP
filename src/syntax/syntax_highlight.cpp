#include "include/syntax_highlight.hpp"

const char* SYNTAX_YELLOW = "\x1b[33m";
const char* SYNTAX_BLUE = "\x1b[36m";
const char* SYNTAX_GREEN = "\x1b[92m";
const char* SYNTAX_BRIGHT_YELLOW = "\x1b[93m";
const char* SYNTAX_RESET = "\x1b[0m";
int SIZE_OF_COLOR_ESC = 5;
int SIZE_OF_RESET_ESC = 4;

int SyntaxHighlight::detectFiletype(char* file_ext) {
    if (strcmp(file_ext, ".cpp") ||
        strcmp(file_ext, ".c") ||
        strcmp(file_ext, ".hpp") ||
        strcmp(file_ext, ".h")) {
            return 1;
        }
    return 0;
}

std::string SyntaxHighlight::hightlightLine(char* line, char* file_ext) {
    int c = detectFiletype(file_ext);

    switch(c) {
        // C/C++ code
        case 1:
            return cppStyle(line);
            break;
        // No case found
        default:
            // Should set status message of the editor to no highlighting found
            return line;
            break;
    }
}

std::string SyntaxHighlight::cppStyle(char* line) {

    //Regex combinations
    auto const regex_string = std::regex("\".*\"");
    auto const regex_comment = std::regex("(//).*");
    auto const regex_statement = std::regex(
        "(std::endl|std::cerr|std::ifstream|std::cout|break |if |while |switch|case|throw|catch|default|do|goto|return|try|for |#include)");
    auto const regex_type = std::regex(
        "(|int|std::string|std::vector|long|char|size_t|namespace)");
    auto search_results = std::smatch{};
    std::string search_text = std::string(line);
    int comment_index = -1;

    auto is_comment = std::regex_search(search_text, search_results, regex_comment);
    if (is_comment) {
        for (auto it = std::sregex_iterator(search_text.begin(), search_text.end(), regex_comment);
        it != std::sregex_iterator();
        ++it) {
            added_length += (SIZE_OF_RESET_ESC + SIZE_OF_COLOR_ESC);
            comment_index = it->position();
            search_text.insert(it->position()+it->length(), SYNTAX_RESET);
            search_text.insert(it->position(), SYNTAX_GREEN);
            break;
        }
    }

    auto is_string = std::regex_search(search_text, search_results, regex_string);
    if (is_string) {
        std::vector<std::pair<int,int>> index_length;
        for (auto it = std::sregex_iterator(search_text.begin(), search_text.end(), regex_string);
        it != std::sregex_iterator();
        ++it) {
            if (comment_index != -1 && comment_index < it->position()) {
                break;
            }
            if(it->length() > 0) {
                index_length.push_back(std::make_pair<int, int>(it->position(), it->length()));
            }
        }
        for (int found_index = index_length.size(); found_index > 0; found_index--) {
            search_text.insert(index_length[found_index-1].first+index_length[found_index-1].second, SYNTAX_RESET);
            search_text.insert(index_length[found_index-1].first, SYNTAX_BRIGHT_YELLOW);
            added_length += (SIZE_OF_RESET_ESC + SIZE_OF_COLOR_ESC);
        }
    }

    auto is_type = std::regex_search(search_text, search_results, regex_type);
    if (is_type) {
        std::vector<std::pair<int,int>> index_length;
        for (auto it = std::sregex_iterator(search_text.begin(), search_text.end(), regex_type);
        it != std::sregex_iterator();
        ++it) {
            if (comment_index != -1 && comment_index < it->position()) {
                break;
            }
            if(it->length() > 0) {
                index_length.push_back(std::make_pair<int, int>(it->position(), it->length()));
            }
        }
        for (int found_index = index_length.size(); found_index > 0; found_index--) {
            search_text.insert(index_length[found_index-1].first+index_length[found_index-1].second, SYNTAX_RESET);
            search_text.insert(index_length[found_index-1].first, SYNTAX_BRIGHT_YELLOW);
            added_length += (SIZE_OF_RESET_ESC + SIZE_OF_COLOR_ESC);
        }
    }

    auto is_statement = std::regex_search(search_text, search_results, regex_statement);
    if (is_statement) {
        std::vector<std::pair<int,int>> index_length;
        for (auto it = std::sregex_iterator(search_text.begin(), search_text.end(), regex_statement);
        it != std::sregex_iterator();
        ++it) {
            if (comment_index != -1 && comment_index < it->position()) {
                break;
            }
            if(it->length() > 0) {
                index_length.push_back(std::make_pair<int, int>(it->position(), it->length()));
            }
        }
        for (int found_index = index_length.size(); found_index > 0; found_index--) {
            search_text.insert(index_length[found_index-1].first+index_length[found_index-1].second, SYNTAX_RESET);
            search_text.insert(index_length[found_index-1].first, SYNTAX_BRIGHT_YELLOW);
            added_length += (SIZE_OF_RESET_ESC + SIZE_OF_COLOR_ESC);
        }
    }

    return (search_text);
}
