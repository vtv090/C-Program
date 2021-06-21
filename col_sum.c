/*
make col_sum && ./col_sum
*/

#include "base.h"

/*
Brechenen wir die Größe von Maxtrix mit rows* cols
Allokiert result matrix mit Größe cols
Berechnen jede Cols die Summe
*/
// Calculate the sum of matrix columns
int* col_sum(int* a, int rows, int cols) {
    
    // int new_size = rows * cols;
    int* result = xcalloc(rows, sizeof(int));

    for(int i = 0; i < cols; i++){
        for(int j = i; j < rows * cols; j += cols){
            result[i] += a[j];
        }
    }

    return result;
}

void test(void) {
    int a[3][3] = {
        { 1, -1, 3}, 
        { 2, -2, 4}, 
        { 3, -3, 5}, 
    };
    printiln(a[0][0]);
    //a[0][0] + a[1][0] + a[2][0] == 6
    //a[0][1] + a[1][1] + a[2][1] == -6
    //a[0][2] + a[1][2] + a[2][2] == 12
    int* margin = col_sum((int*)a, 3, 3);
    int expected[] = { 6, -6, 12 };
    ia_test_equal(a_of_buffer(margin, 3, sizeof(int)), 
                  a_of_buffer(expected, 3, sizeof(int)));



    int b[3][2] = {
        { 1, -1 },
        { 0,  0 },
        { 3, -3 },
    };
    margin = col_sum((int*)b, 3, 2);
    int expected_b[] = { 4, -4 };
    ia_test_equal(a_of_buffer(margin, 2, sizeof(int)),
    a_of_buffer(expected_b, 2, sizeof(int)));


    int c[2][3] = {
    { 1, -1, 3 },
    { 2, -2, 4 },
    };
    margin = col_sum((int*)c, 2, 3);
    int expected_c[] = {3, -3, 7};
    ia_test_equal(a_of_buffer(margin, 3, sizeof(int)),
    a_of_buffer(expected_c, 3, sizeof(int)));
}

int main(void) {
    test();
    return 0;
}