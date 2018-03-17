#include "polo-parser/Parser.h"

#include <iostream>

#include <clang-c/Index.h>

namespace {
    CXChildVisitResult visit_child(CXCursor child, CXCursor parent, CXClientData) {
        auto string = clang_getCursorUSR(child);

        std::cout << clang_getCString(string) << std::endl;

        clang_disposeString(string);
        return CXChildVisit_Recurse;
    }
}

class ParserImpl {
public:
    ParserImpl() {
        m_index = clang_createIndex(1 , 0);
    }

    ~ParserImpl() {
        clang_disposeIndex(m_index);
    }

    void parse_file(const std::string& file) {
        CXTranslationUnit tu = clang_parseTranslationUnit(
            m_index,
            file.c_str(),
            nullptr,
            0,
            nullptr,
            0,
            CXTranslationUnit_SkipFunctionBodies
        );

        if (!tu)
            return;

        CXCursor cursor = clang_getTranslationUnitCursor(tu);
        clang_visitChildren(
            cursor,
            &visit_child,
            nullptr
        );

        clang_disposeTranslationUnit(tu);
    }

private:
    CXIndex m_index;
};

Parser::Parser(): m_impl(std::make_unique<ParserImpl>()) {
}

Parser::~Parser() {
}

void Parser::parse_file(const std::string& file) {
    m_impl->parse_file(file);
}
