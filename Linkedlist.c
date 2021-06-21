

//make 17list && ./17list

#include "base.h"
#include <limits.h>

typedef struct Intlist{
	int value;
	struct Intlist* next;
}Intlist;

Intlist* prepend(int value, Intlist* list){
	//Intlist* node = xcalloc(1, sizeof(Intlist));
	Intlist* node = xmalloc(sizeof(Intlist));
	node->value = value;
	node->next = list;
	return node;
}
//find middle of list: if have no middle list, return 0, else return that value
int center_or_zero(Intlist* list){
	
	int length = 0;
	Intlist* current = list;
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

//find number of elements befor changing from positiv number to negativ number
int find_neighbour(Intlist* list){
	int count  = 0;
	int length = 0;
	
	//calculate length of list
	for(Intlist* node = list; node != NULL; node = node->next){
		length++;
	}
	
	if(length == 0 || length == 1) return 0;
	
	for(Intlist* node = list; node != NULL; node = node->next){
		
		Intlist* node_next = node->next;
		
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

//count number of change from  "+  to -" or "- to +"
int number_of_change(Intlist* list){
	int count = 0;
	int length = 0;
	Intlist* current = list;
	while(current){
		length++;
		current = current->next;
	}
	if(length == 0 || length == 1) return 0;
	for(Intlist* node = list; node != NULL; node = node->next){
		
		Intlist* node_next = node->next;
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

//number of struct like "+ - +" or "- + -" in linked list
int number_of_struct(Intlist* list){
	int count = 0;
	int length = 0;
	
	Intlist* current = list;
	while(current){
		length++;
		current = current->next;
	}
	
	for(Intlist* node = list; node != NULL; node = node->next){
		Intlist* nnode = node->next;
		
		if(nnode){
			Intlist* nnnode = nnode->next;
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

int find_max_subElements(Intlist* list){
	int temp_max = INT_MIN;
	int max = INT_MIN;
	
	for(Intlist* node = list; node != NULL; node = node->next){
		
		if(temp_max < 0){
			temp_max = node->value;
		}else{
			temp_max += node->value;
		}
		max = maxint(max, temp_max);
	}
	return max;
}
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
int find_min_subElements(Intlist* list){
	int min_temp = INT_MAX;
	int min = INT_MAX;
	
	for(Intlist* node = list; node != NULL; node = node->next){
		if(min_temp > 0){
			min_temp = node->value;
		}else{
			min_temp += node->value;
		}
		min = minint(min_temp, min);
	}
	return min;
}
void test_find_min_subElements(){
    test_equal_i(find_min_subElements(prepend(3, prepend(5, prepend(-5, prepend(-3, prepend(-1, NULL)))))), -9);
    test_equal_i(find_min_subElements(prepend(3, prepend(-2, prepend(6, prepend(1, prepend(-1, prepend(-2, prepend(1, NULL)))))))), -3);
    test_equal_i(find_min_subElements(prepend(-3, prepend(-1, prepend(5, prepend(-3, prepend(-1, prepend(-4, prepend(2, NULL)))))))), -8);
	test_equal_i(find_min_subElements(prepend(1, prepend(1, prepend(2, prepend(5, prepend(1, prepend(3, prepend(2, NULL)))))))), 1);
}


int find_smallest_inList(Intlist* list){
	//set min as first element
	int min = list->value;

	for(Intlist* node = list; node != NULL; node = node->next){
		min = minint(min, node->value); //compare to another elements
	}
	return min;
}https://github.com/vtv090/C-Program/blob/main/17list.c

void test_find_smallest_inList(){
    test_equal_i(find_smallest_inList(prepend(3, prepend(5, prepend(-5, prepend(-3, prepend(-1, NULL)))))), -5);
    test_equal_i(find_smallest_inList(prepend(3, prepend(-3, prepend(6, prepend(1, prepend(-1, prepend(-2, prepend(-10, NULL)))))))), -10);
    test_equal_i(find_smallest_inList(prepend(-3, prepend(-1, prepend(5, prepend(-3, prepend(-1, prepend(-4, prepend(2, NULL)))))))), -4);
	test_equal_i(find_smallest_inList(prepend(1, prepend(1, prepend(2, prepend(5, prepend(1, prepend(3, prepend(-2, NULL)))))))), -2);
}

//find max Product Sub Array in List
int find_max_multiple(Intlist* list){
	//Viet lai
	int max = list->value; //set max as first Node in List
	
	for(Intlist* node = list; node != NULL; node = node->next){
		//Intlist* nnode = node->next;
		int temp_multi = node->value;
		
		for(Intlist* n = node->next; n != NULL; n = n->next){
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

int find_max_inList(Intlist* list){
	
	//set first element as max
	int max = list->value;
	
	for(Intlist* node = list; node != NULL; node = node->next){
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

int node_difference(Intlist* list){

	if(list == 0) return 0;

	int min = list->value, max = list->value;

	for(Intlist* node = list; node != NULL; node = node->next){
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
//find Largest subarray with equal number of 0s and 1s
int find_path_1_0(Intlist* list){

	int length = 0;
	for(Intlist* node = list; node != NULL; node = node->next){
		length++;
	}
	if(length == 0 && length == 1)
		return 0;

	int sum = 0, max = 0;

	for(Intlist* node = list; node != NULL; node = node->next){
		int temp = 0;

		if(node->value == 1){
			sum = 1;
			temp++;
		}else{
			sum = -1;
			temp++;
		}

		for(Intlist* n = node->next; n != NULL; n = n->next){
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
int main(){
	test_center_or_zero();
	test_find_neighbour();
	test_number_of_change();
	test_number_of_struct();
	test_find_max_subElements();
	test_find_min_subElements();
	test_find_smallest_inList();
	test_find_max_multiple();
	test_find_max_inList();
	test_node_difference();
	test_find_path_1_0();
	return 0;
}
