#ifndef __PARSER_H_
#define __PARSER_H_

#include <string>
#include <memory>
#include <functional>

class ParserImpl;

class Parser {
public:
    Parser();
    ~Parser();

    void parse_file(
            const std::string& file, 
            std::function<void(const std::string&)> cb);

private:
    std::unique_ptr<ParserImpl> m_impl;
};

#endif  //__PARSER_H_
