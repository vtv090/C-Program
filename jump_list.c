/*
make jump_list && ./jump_list
*/

#include "base.h"

// Represents a list node.
typedef struct Node Node;
struct Node {
    int value;
    Node* next;
};

// Creates a new list node.
Node* new_node(int value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

// Prints the list into the given file.
void fprint_list(char* filename, Node* list) {
    require_not_null(filename);
    FILE* f = fopen(filename, "w");
    fprintf(f, "[");
    for (Node* n = list; n; n = n->next) {
        fprintf(f, "%d", n->value);
        if (n->next) fprintf(f, ", ");
    }
    fprintf(f, "]");
    fclose(f);
}

// Reverses list recursively. 
Node* reverse_list_rec(Node* list, Node* result) {
    if (list == NULL) return result;
    return reverse_list_rec(list->next, new_node(list->value, result));
}

// Reverses list.
Node* reverse_list(Node* list) {
    return reverse_list_rec(list, NULL);
}

/*
Vergleichen wir die Länger mit gap: wenn gap == 0 und gap > length.
Dannach löscht es die erst "gap" elemente.
Danach löscht es emelente mit Interval gap
*/
Node* jump_list(Node* list, int gap) {
    require("not negative", gap >= 0);
    // todo: implement

    int length = 0;

    for(Node* node = list; node != NULL; node = node->next){
        length++;
    }

    //if gap < 0, there is no jump
    if(gap == 0)
        return list;

    //gap > length, no element to remove
    if(gap > length)
        return NULL;


    Node* result = NULL;

    //ignore "gap" elements in list, add "gap + 1"th-element to result to ende of list
    for(Node* n = list; n != NULL; n = n->next){

        int j = 0;
        while(j < gap){

            if(n->next){
                n = n->next;
            }else{
                return result; //if last element but j == gap - 2
            }
            
            j++;
        }
        //add "gap + 1"th-element to result
        result = new_node(n->value, result);
    }

    result = reverse_list(result);

    return result;
}


void test(void) {
    Node *list0, *list;

    list0 = NULL;
    list = jump_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, new_node(5, new_node(6, NULL))))));
    list = jump_list(list0, 0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 2, 3, 4, 5, 6]");

    list = jump_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[2, 4, 6]");

    list = jump_list(list0, 2);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[3, 6]");

    list = jump_list(list0, 3);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[4]");

    list = jump_list(list0, 99);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");
}

int main(void) {
    test();
    return 0;
}