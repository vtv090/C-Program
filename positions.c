/*
make positions && ./positions
*/

#include "base.h"

// Represents a cursor position in a document. The cursor is always positioned between two characters or at the beginning or end of a line.
typedef struct {
    int line;
    int column;
} Position;

// Create a new cursor position.
Position make_position(int line, int column) {
    require("not negative", line >= 0);
    require("not negative", column >= 0);
    Position p = { line, column };
    return p;
}

// Represents a document consisting of line_count lines.
typedef struct {
    char** lines; // an array of lines, each line is a zero-terminated string
    int line_count; // the number of lines in the document
} Document;

// Create a new document.
Document make_document(char** lines, int line_count) {
    require_not_null(lines);
    require("not negative", line_count >= 0);
    // require("no null lines", forall(i, line_count, lines[i] != NULL));
    Document d = { lines, line_count };
    return d;
}

// Checks if the given position is a valid position in the given document.
bool is_valid_position(Position pos, Document doc) {
    if(pos.column > strlen(*doc.lines) || pos.column <= 0) return false;
    if(pos.line > doc.line_count || pos.line < 0) return false;
    return true;
}

// Returns the offset corresponding to the given position in the given document.
int offset_at(Position pos, Document doc) {
    int a = 0;

    for(int i = 0; i < pos.line; i++){
        a  += strlen(doc.lines[i]) + 1;
    }
    int b = a + pos.column;
    return b;
}

void test(void) {
    char* letter[] = {
        "Dear Grandma,",
        "",
        "My first semester at the university",
        "is now over. I very much liked",
        "Programming 1. What I did not like",
        "so much was that all courses were",
        "online. All the best!",
        "",
        "Yours,",
        "Otto"
    };
    int n = sizeof(letter) / sizeof(char*);
    printiln(n);
    printsln(letter[0]);
    printsln(letter[1]);
    printsln(letter[2]);
    Document doc = make_document(letter, n);

    Position pos = { -1, 0 };
    test_equal_b(is_valid_position(pos, doc), false);
    test_equal_b(is_valid_position(make_position(n, 0), doc), false);
    test_equal_b(is_valid_position(make_position(0, 13), doc), true);
    test_equal_b(is_valid_position(make_position(0, 14), doc), false);

    test_equal_i(offset_at(make_position(0, 0), doc), 0);
    test_equal_i(offset_at(make_position(0, 1), doc), 1);
    test_equal_i(offset_at(make_position(0, 2), doc), 2);
    test_equal_i(offset_at(make_position(0, 13), doc), 13);
    // test_equal_i(offset_at(make_position(0, 14), doc), 13); // invalid position
    test_equal_i(offset_at(make_position(1, 0), doc), 14);
    test_equal_i(offset_at(make_position(2, 0), doc), 15);
    test_equal_i(offset_at(make_position(2, 1), doc), 16);
    test_equal_i(offset_at(make_position(3, 0), doc), 51);
}

int main(void) {
    test();
    return 0;
}