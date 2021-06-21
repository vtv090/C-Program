

//make list && ./list

#include "base.h"
#include <limits.h>

typedef struct Node{
	int value;
	struct Node* next;
}Node;

Node* prepend(int value, Node* list){
	//Node* node = xcalloc(1, sizeof(Node));
	Node* node = xmalloc(sizeof(Node));
	node->value = value;
	node->next = list;
	return node;
}

int center_or_zero(Node* list){
	
	int length = 0;
	Node* current = list;
	while(current){
		length++;
		current = current->next;
	}
	
	if(length%2 == 0) 
		return 0;

	int mid = length/2;
	for(int i = 0; i < mid; i++){
		list = list->next;
	}
	return list->value;
	
}

void test_center_or_zero() {
    test_equal_i(center_or_zero(NULL), 0);
    test_equal_i(center_or_zero(prepend(-10, NULL)), -10);
    test_equal_i(center_or_zero(prepend(1, prepend(10, NULL))), 0);
    test_equal_i(center_or_zero(prepend(2, prepend(1, prepend(-2, NULL)))), 1);
    test_equal_i(center_or_zero(prepend(2, prepend(-1, prepend(2, NULL)))), -1);
    test_equal_i(center_or_zero(prepend(1, prepend(-1, prepend(9, prepend(-2, prepend(2, NULL)))))), 9);
    test_equal_i(center_or_zero(prepend(6, prepend(8, prepend(-3, prepend(-4, NULL))))), 0);
}

//find number of node befor changing + to - or - to +
int find_neighbour(Node* list){
	int count  = 0;
	int length = 0;
	
	//calculate length of list
	for(Node* node = list; node != NULL; node = node->next){
		length++;
	}
	
	if(length == 0 || length == 1) return 0;
	
	for(Node* node = list; node != NULL; node = node->next){
		
		Node* node_next = node->next;
		
		if(node_next){
			//calculate  number of elements from begin both > 0 oder both < 0
			if((node->value < 0 && node_next->value < 0) || (node->value > 0 && node_next->value > 0)){
				count++;
			}
			//when there is element < 0 & next_element > 0 or backwards, return with count + 1
			if((node->value < 0 && node_next->value > 0) || (node->value > 0 && node_next->value < 0)){
				return count + 1; //+1 for current element
			}
		}
	}
	return count;
}
void test_find_neighbour(){
    test_equal_i(find_neighbour(prepend(2, prepend(1, prepend(50, prepend(4, prepend(-2, NULL)))))), 4);
    test_equal_i(find_neighbour(prepend(4, prepend(-1, prepend(-5, NULL)))), 1);
    test_equal_i(find_neighbour(prepend(4, prepend(1, prepend(-5, NULL)))), 2);
    test_equal_i(find_neighbour(prepend(4, prepend(-1, prepend(5, NULL)))), 1);
    test_equal_i(find_neighbour(prepend(4, prepend(1, prepend(-3, prepend(5, NULL))))), 2);
    test_equal_i(find_neighbour(prepend(4, prepend(-1, NULL))), 1);
    test_equal_i(find_neighbour(prepend(4,  NULL)), 0);
    test_equal_i(find_neighbour(NULL), 0);
}

//find how many times change + to - or - to +
int number_of_change(Node* list){
	int count = 0;
	int length = 0;
	Node* current = list;
	while(current){
		length++;
		current = current->next;
	}
	if(length == 0 || length == 1) return 0;
	for(Node* node = list; node != NULL; node = node->next){
		
		Node* node_next = node->next;
		if(node_next){
			if((node->value < 0 && node_next->value > 0) || (node->value > 0 && node_next->value < 0))
				count++;
		}
	}
	return count;
}
void test_number_of_change(){
     test_equal_i(number_of_change(prepend(2, prepend(-1, prepend(-5, prepend(4, prepend(-2, prepend(-5, prepend(1, NULL)))))))), 4); //2 -1 -5 4 -2
     test_equal_i(number_of_change(prepend(3, prepend(-1, prepend(5, prepend(-2, NULL))))), 3);
     test_equal_i(number_of_change(prepend(4, prepend(-1, prepend(3, NULL)))), 2);
     test_equal_i(number_of_change(prepend(2, prepend(1, prepend(-3, prepend(5, NULL))))), 2); //-3 1 -3 5
     test_equal_i(number_of_change(prepend(5, NULL)), 0); 
}


//number of struct like + - + or - + -
int number_of_struct(Node* list){
	int count = 0;
	int length = 0;
	
	Node* current = list;
	while(current){
		length++;
		current = current->next;
	}
	
	for(Node* node = list; node != NULL; node = node->next){
		Node* nnode = node->next;
		
		if(nnode){
			Node* nnnode = nnode->next;
			if(nnnode){
				if(node->value > 0 && nnode->value < 0)
					if(nnnode->value > 0)
						count++;
				
				if(node->value < 0 && nnode->value > 0)
					if(nnnode->value < 0)
						count++;
			}
		}
	}
	
	return count;
}

void test_number_of_struct(){
    test_equal_i(number_of_struct(prepend(2, prepend(-1, prepend(-5, prepend(4, prepend(-2, prepend(5, prepend(1, NULL)))))))), 2); //2 -1 -5 4 -2 5 1
    test_equal_i(number_of_struct(prepend(3, prepend(-1, prepend(5, prepend(-2, NULL))))), 2);
    test_equal_i(number_of_struct(prepend(4, prepend(-1, prepend(3, NULL)))), 1); //4 -1 3
    test_equal_i(number_of_struct(prepend(3, prepend(5, NULL))), 0); //3 5
}

int maxint(int a, int b){
	if(a < b){
		return b;
	}else{
		return a;
	}
}
int find_max_subElements(Node* list){
	int temp_max = INT_MIN;
	int max = INT_MIN;
	
	for(Node* node = list; node != NULL; node = node->next){
		
		if(temp_max < 0){
			temp_max = node->value;
		}else{
			temp_max += node->value;
		}
		max = maxint(max, temp_max);
	}
	return max;
}
/*
//find max sub-element in linked list
int find_max_subElements(Node* list){
	int max = list->value;

	for(Node* node = list; node != NULL; node = node->next){

		int temp = node->value;
		max = maxint(max, temp); 

		for(Node* n = node->next; n != NULL; n = n->next){
			temp += n->value;
			max = maxint(max, temp);
		}
	}
	return max;
}
*/
void test_find_max_subElements(){
    test_equal_i(find_max_subElements(prepend(3, prepend(5, prepend(-5, prepend(-3, prepend(-1, NULL)))))), 8);
    test_equal_i(find_max_subElements(prepend(-3, prepend(2, prepend(6, prepend(1, prepend(-1, prepend(-2, prepend(1, NULL)))))))), 9);
    test_equal_i(find_max_subElements(prepend(-3, prepend(-1, prepend(5, prepend(-3, prepend(-1, prepend(-4, prepend(2, NULL)))))))), 5);
	test_equal_i(find_max_subElements(prepend(-3, prepend(-1, prepend(-5, prepend(-3, prepend(-1, prepend(-4, prepend(-2, NULL)))))))), -1);
}

int minint(int a, int b){
	if(a < b){
		return a;
	}else{
		return b;
	}
}
//find min sub-element in linked list
int find_min_subElements(Node* list){
	int min_temp = INT_MAX;
	int min = INT_MAX;
	
	for(Node* node = list; node != NULL; node = node->next){
		if(min_temp > 0){
			min_temp = node->value;
		}else{
			min_temp += node->value;
		}
		min = minint(min_temp, min);
	}
	return min;
}

/*int find_min_subElements(Node* list){

    int min = list->value;

    for(Node* node = list; node != NULL; node = node->next){

        int temp = node->value;
		min = minint(min, temp); //find whether a node min or not


        for(Node* n = node->next; n != NULL; n = n->next){
            temp += n->value;
            min = minint(min, temp);
        }
    }
    return min;
}*/

void test_find_min_subElements(){
    test_equal_i(find_min_subElements(prepend(3, prepend(5, prepend(-5, prepend(-3, prepend(-1, NULL)))))), -9);
    test_equal_i(find_min_subElements(prepend(3, prepend(-2, prepend(6, prepend(1, prepend(-1, prepend(-2, prepend(1, NULL)))))))), -3);
    test_equal_i(find_min_subElements(prepend(-3, prepend(-1, prepend(5, prepend(-3, prepend(-1, prepend(-4, prepend(2, NULL)))))))), -8);
	test_equal_i(find_min_subElements(prepend(1, prepend(1, prepend(2, prepend(5, prepend(1, prepend(3, prepend(2, NULL)))))))), 1);
}


int find_smallest_inList(Node* list){
	//set min as first element
	int min = list->value;

	for(Node* node = list; node != NULL; node = node->next){
		min = minint(min, node->value); //compare to another elements
	}
	return min;
}

void test_find_smallest_inList(){
    test_equal_i(find_smallest_inList(prepend(3, prepend(5, prepend(-5, prepend(-3, prepend(-1, NULL)))))), -5);
    test_equal_i(find_smallest_inList(prepend(3, prepend(-3, prepend(6, prepend(1, prepend(-1, prepend(-2, prepend(-10, NULL)))))))), -10);
    test_equal_i(find_smallest_inList(prepend(-3, prepend(-1, prepend(5, prepend(-3, prepend(-1, prepend(-4, prepend(2, NULL)))))))), -4);
	test_equal_i(find_smallest_inList(prepend(1, prepend(1, prepend(2, prepend(5, prepend(1, prepend(3, prepend(-2, NULL)))))))), -2);
}

//find max Product Sub Array in List
int find_max_multiple(Node* list){
	//Viet lai
	int max = list->value; //set max as first Node in List
	
	for(Node* node = list; node != NULL; node = node->next){
		//Node* nnode = node->next;
		int temp_multi = node->value;
		
		for(Node* n = node->next; n != NULL; n = n->next){
			temp_multi *= n->value;
			max = maxint(max, temp_multi); //compare max vs temp_multi
		}
	}
	return max;
}

void test_find_max_multiple(){
    test_equal_i(find_max_multiple(prepend(3, prepend(5, prepend(-5, prepend(-3, prepend(-1, NULL)))))), 225); //3* 5 * -5 *-3
    test_equal_i(find_max_multiple(prepend(3, prepend(-3, prepend(6, prepend(1, prepend(-1, prepend(-2, prepend(-10, NULL)))))))), 1080);//3 * -3 * 6 * 1 *-1 *-2 * -10
    test_equal_i(find_max_multiple(prepend(-5, prepend(-1, prepend(5, prepend(-3, prepend(-1, prepend(-4, prepend(2, NULL)))))))), 120); // -3 * -2 * 5 * -3 * -1
	test_equal_i(find_max_multiple(prepend(1, prepend(1, prepend(2, prepend(5, prepend(1, prepend(3, prepend(-2, NULL)))))))), 30); //1*1*2*5*1*3
	test_equal_i(find_max_multiple(prepend(0, prepend(-1, prepend(-2, prepend(-5, prepend(-1, prepend(1, prepend(0, NULL)))))))), 10); //1*1*2*5*1*3
}

//find Largest subarray with equal number of 0s and 1s
int max_subArray(Node* list){
	
	int max = 0;
	for(Node* node = list; node != NULL; node = node->next){
		int sum;
		int temp_size = 0;
		
		//set if value = 1 sum = 1, else value = 0 sum = -1
		if(node->value == 1){
			sum = 1;
			temp_size++;
		}else{
			sum = -1;
			temp_size++;
		}
		
		for(Node* n = node->next; n != NULL; n = n->next){
			
			if(n->value == 1){
				sum += 1;
				temp_size++;
			}else{
				sum += -1;
				temp_size++;
			}
			//when 1s & 0s equal, take maximum between max and temp_size
			if(sum == 0){
				max = maxint(max, temp_size);
			}
		}
	}
	return max; 
}
void test_max_subArray(){
    test_equal_i(max_subArray(prepend(0, prepend(0, prepend(0, prepend(0, prepend(1, NULL)))))), 2); 
    test_equal_i(max_subArray(prepend(1, prepend(0, prepend(0, prepend(1, prepend(0, prepend(1, prepend(0, NULL)))))))), 6);
    test_equal_i(max_subArray(prepend(0, prepend(0, prepend(1, prepend(0, prepend(0, prepend(1, prepend(1, NULL)))))))), 6);
	test_equal_i(max_subArray(prepend(0, prepend(0, prepend(1, prepend(0, prepend(0, prepend(1, prepend(1, prepend(0, prepend(0, NULL)))))))))), 6);//0 0 1 0 0 1 1 0 0
	test_equal_i(max_subArray(prepend(0, prepend(0, prepend(0, prepend(0, NULL))))), 0);
	test_equal_i(max_subArray(prepend(1, prepend(1, prepend(1, prepend(1, prepend(1, NULL)))))), 0); 
}

int find_max_inList(Node* list){
	
	//set first element as max
	int max = list->value;
	
	for(Node* node = list; node != NULL; node = node->next){
		max = maxint(max, node->value);
	}
	return max;
}

void test_find_max_inList(){
    test_equal_i(find_max_inList(prepend(3, prepend(5, prepend(-5, prepend(-3, prepend(-1, NULL)))))), 5);
    test_equal_i(find_max_inList(prepend(3, prepend(-3, prepend(6, prepend(1, prepend(-1, prepend(-2, prepend(-10, NULL)))))))), 6);
    test_equal_i(find_max_inList(prepend(-3, prepend(-1, prepend(5, prepend(-3, prepend(-1, prepend(-4, prepend(2, NULL)))))))), 5);
	test_equal_i(find_max_inList(prepend(1, prepend(1, prepend(2, prepend(5, prepend(1, prepend(3, prepend(-2, NULL)))))))), 5);
}

int node_difference(Node* list){

	if(list == 0) return 0;

	int min = list->value, max = list->value;

	for(Node* node = list; node != NULL; node = node->next){
		min = minint(min, node->value);
		max = maxint(max, node->value);
	}

	return max - min;
}

void test_node_difference(){
    test_equal_i(node_difference(prepend(3, prepend(5, prepend(-5, prepend(-3, prepend(-1, NULL)))))), 10);
    test_equal_i(node_difference(prepend(3, prepend(-3, prepend(6, prepend(1, prepend(-1, prepend(-2, prepend(-10, NULL)))))))), 16);
    test_equal_i(node_difference(prepend(-3, prepend(-1, prepend(5, prepend(-3, prepend(-1, prepend(-4, prepend(2, NULL)))))))), 9);
	test_equal_i(node_difference(prepend(1, prepend(1, prepend(2, prepend(5, prepend(1, prepend(3, prepend(-2, NULL)))))))), 7);
}

//find max sub list in which number of 0 and 1 equals
int find_path_1_0(Node* list){

	int length = 0;
	for(Node* node = list; node != NULL; node = node->next){
		length++;
	}
	if(length == 0 && length == 1)
		return 0;

	int sum = 0, max = 0;

	for(Node* node = list; node != NULL; node = node->next){
		int temp = 0;

		if(node->value == 1){
			sum = 1;
			temp++;
		}else{
			sum = -1;
			temp++;
		}

		for(Node* n = node->next; n != NULL; n = n->next){
			if(n->value == 1){
				sum += 1;
				temp++;
			}else{
				sum -= 1;
				temp++;
			}

			if(sum == 0){
				max = maxint(max, temp);
			}
		}
	}

	return max;
}
void test_find_path_1_0(){
    test_equal_i(find_path_1_0(prepend(1, prepend(1, prepend(0, prepend(0, prepend(1, NULL)))))), 4);
    test_equal_i(find_path_1_0(prepend(0, prepend(0, prepend(1, prepend(1, prepend(1, prepend(0, prepend(0, NULL)))))))), 6);
    test_equal_i(find_path_1_0(prepend(1, prepend(1, prepend(1, prepend(0, prepend(1, prepend(0, prepend(1, NULL)))))))), 4);
	test_equal_i(find_path_1_0(prepend(1, prepend(1, prepend(0, prepend(0, prepend(1, prepend(1, prepend(0, prepend(1, prepend(1, NULL)))))))))), 6);
}

//Hilfsfunktion
int length_list(Node* list){
	int length = 0;

	for(Node* node = list; node != NULL; node = node->next){
		length++;
	}

	return length;
}
//count number of times of a repeated node in list
int contains(Node* list, int data){
	int count = 0;

	for(Node* node = list; node != NULL; node = node->next){
		if(node->value == data)
			count++;
	}

	return count;
}
//compare two lists 
bool compare_two_list(Node* l1, Node* l2){
	if(l1 == l2)
		return true;

	if(length_list(l1) != length_list(l2))
		return false;

	if(l1 == NULL || l2 == NULL)
		return false;

	for(Node* node = l1; node != NULL; node = node->next){
		//if number of repeated node in a not equals in b
		if(contains(l1, node->value) != contains(l2, node->value))
			return false;
	}

	return true;
}
void test_compare_two_list(){
    Node* a = NULL;
    Node* b = NULL;
    
    test_equal_b(compare_two_list(NULL, NULL), true);
    
    b = prepend(3, NULL);

    test_equal_b(compare_two_list(a, b), false);
    test_equal_b(compare_two_list(b, b), true);
    test_equal_b(compare_two_list(b, a), false);
    
    a = prepend(3, NULL);
    
    test_equal_b(compare_two_list(a, b), true);
    
    a = prepend(3, prepend(3, a));
    
    test_equal_b(compare_two_list(a, b), false);
    
    b = prepend(3, prepend(3, b));

    test_equal_b(compare_two_list(a, b), true);
    
    a = prepend(1, prepend(2, a));
    b = prepend(2, prepend(1, b));
    
    test_equal_b(compare_two_list(a, b), true);
    
    b = prepend(2, prepend(2, b));

    test_equal_b(compare_two_list(a, b), false);
    
    Node * c = prepend(1, prepend(2, prepend(1, prepend(3, prepend(4, prepend(3, NULL))))));
    Node * d = prepend(2, prepend(1, prepend(3, prepend(1, prepend(3, prepend(4, NULL))))));

    test_equal_b(compare_two_list(c, d), true);
    test_equal_b(compare_two_list(d, c), true);
}

int even_element(Node* list){
	int count = 0;

	if(list == NULL) return 0;

	for(Node* node = list; node != NULL; node = node->next){
		if(node->value % 2 == 0)
			count++;
	}

	return count;
}
void test_even_element(){
    test_equal_i(even_element(prepend(1, prepend(4, prepend(0, prepend(5, prepend(1, NULL)))))), 2);
    test_equal_i(even_element(prepend(0, prepend(0, prepend(1, prepend(1, prepend(1, prepend(0, prepend(0, NULL)))))))), 4);
    test_equal_i(even_element(prepend(8, prepend(2, prepend(1, prepend(3, prepend(1, prepend(0, prepend(1, NULL)))))))), 3);
	test_equal_i(even_element(prepend(1, prepend(4, prepend(1, prepend(8, prepend(1, prepend(12, prepend(88, prepend(1, prepend(1, NULL)))))))))), 4);
}
int main(){
	test_center_or_zero();
	test_find_neighbour();
	test_number_of_change();
	test_number_of_struct();
	test_find_max_subElements();
	test_find_min_subElements();
	test_find_smallest_inList();
	test_find_max_multiple();
	test_max_subArray();
	test_find_max_inList();
	test_node_difference();
	test_find_path_1_0();
	test_compare_two_list();
	test_even_element();
	return 0;
}
