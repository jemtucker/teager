#include "polo-parser/Parser.h"

int main(int argc, char *argv[]) {
    Parser parser;

    if (argc > 1)
        parser.parse_file(argv[1]);

    return 0;
}
