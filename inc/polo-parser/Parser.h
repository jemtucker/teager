#ifndef __PARSER_H_
#define __PARSER_H_

#include <string>
#include <memory>

class ParserImpl;

class Parser {
public:
    Parser();
    ~Parser();

    void parse_file(const std::string& file);

private:
    std::unique_ptr<ParserImpl> m_impl;
};

#endif  //__PARSER_H_
