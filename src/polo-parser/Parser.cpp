#include "polo-parser/Parser.h"

#include <iostream>

#include <clang-c/Index.h>

namespace {
    class String {
    public:
        String(CXString& s): m_str(clang_getCString(s)), m_data(s) {}
        ~String() { clang_disposeString(m_data); }

        const char *data() { return m_str; }
    private:
        const char *m_str;
        CXString m_data;
    };

    void print_function(const CXCursor& cursor) {
        auto usr = clang_getCursorUSR(cursor);
        auto str = String(usr); 
        std::cout << str.data() << std::endl;
    }

    CXChildVisitResult visit_child(CXCursor child, CXCursor parent, CXClientData) {
        auto type = clang_getCursorType(child);
        switch (type.kind)
        {
            case CXType_FunctionProto:
            case CXType_FunctionNoProto:
                print_function(child);
                return CXChildVisit_Continue;            
            default:
                return CXChildVisit_Recurse;
        }
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
