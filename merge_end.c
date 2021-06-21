/*
make merge_end && ./merge_end
*/

#include "base.h"

// Checks if s ends with end.
bool ends_with(String s, String end) {
    require_not_null(s);
    require_not_null(end);
    int ns = strlen(s);
    int nend = strlen(end);
    if (nend > ns) return false;
    int offset = ns - nend;
    return strcmp(s + offset, end) == 0;
}

// <purpose statement>
String merge_end(String* a, int n, String end) {
    require_not_null(a);
    require("not negative", n >= 0);
    require_not_null(end);

    int length = strlen(a);
    char* result = xmalloc(length + 1);

    int k = 0;
    for(int i = 0; i < length; i++){

        if(ends_with(a[i], end) == true){

            int len = strlen(a[i]);

            for(int j = 0; j < len; j++){
                
                result[k++] = a[i][j];
            }
            result[k++] = ' ';
        }
    }
    result[k] = '\0';
    // implement
    return result;
}

void test(void) {
    String a[] = { "abc", "xbc", "abx", "ccc", "bx", "x" };
    int n = sizeof(a) / sizeof(char*);
    printiln(n);
    test_equal_s(merge_end(a, n, "bc"), "abc xbc ");
    test_equal_s(merge_end(a, n, "bx"), "abx bx ");
    test_equal_s(merge_end(a, n, ""), "abc xbc abx ccc bx x ");
    test_equal_s(merge_end(a, n, "k"), "");
    test_equal_s(merge_end(a, n, "x"), "abx bx x ");
    test_equal_s(merge_end(a, n, "cc"), "ccc ");
}

int main(void) {
    test();
    return 0;
}