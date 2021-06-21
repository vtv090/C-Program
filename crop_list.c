/*
make crop_list && ./crop_list
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

// Counts the number of values in list.
int length_list(Node* list) {
    // todo: implement
    int length = 0;
    for(Node* node = list; node != NULL; node = node->next){
        length++;
    }
    return length;
}

// Creates a result list from the input list, by removing the first r and the last r elements from the input list. 
//For example, crop([1, 2, 3, 4], 1) becomes [2, 3]. Maintains the original order of the remaining elements. Does not change the input list.
Node* crop_list(Node* list, int r) {
    require("not negative", r >= 0);
    // todo: implement
    
    if(list == NULL)
        return list;
    if(r == 0){
        return list;
    }
    
    int length = length_list(list);
    int count = 0;
    
    //remove first r Emlements
    while(count < r){
        list = list->next; 
        count++;
    }
    
    length = length - 2 * r;
    //when remove all of Elements in List
    if(length <= 0){
        return NULL;
    }
    
    int j = 0;
    //remove r last Elements on right
    while(j < r){
        Node* current = list;
        
        //go to end of list
        while(current->next->next != NULL){
            current = current->next;
        }
        //4 5 6 7: curr = 5 => curr = curr->next = 6 => last_node = 7 => set current->next = NULL
		//return first element in List
        //when current next element is last element
        Node* last_node = current->next;
        current->next = NULL;  //assign last element is NULL
        j++;
        free(last_node);
    }

    return list;
}

void test_crop_list(void) {
    Node *list0, *list;

    Node* list_a = NULL;
    test_equal_i(length_list(list_a), 0);

    list_a = new_node(1, list_a);
    test_equal_i(length_list(list_a), 1);

    list_a = new_node(2, list_a);
    test_equal_i(length_list(list_a), 2);

    list_a = new_node(3, list_a);
    test_equal_i(length_list(list_a), 3);

    list0 = NULL;
    list = crop_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 2, 3, 4]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, new_node(5, NULL)))));
    list = crop_list(list0, 2);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[3]"); 

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 2);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, new_node(5, new_node(6, NULL))))));
    list = crop_list(list0, 2);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[3, 4]");

    list0 = new_node(0, new_node(1, new_node(2, new_node(3, new_node(4, NULL)))));
    list = crop_list(list0, 2); 
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[2]"); 

    list0 = new_node(0, new_node(1, new_node(2, new_node(3, new_node(4, NULL)))));
    list = crop_list(list0, 3);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");
}

int main(void) {
    test_crop_list();
    return 0;
}
