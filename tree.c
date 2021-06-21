/*
 make tree && ./tree
*/

#include "base.h"
#include <limits.h>


typedef struct Tree{
	int value;
	struct Tree* left;
	struct Tree* right;
}Tree;

// Creates a new binary tree node.
Tree* new_tree(Tree* left, int value, Tree* right) {
    //Tree* t = xcalloc(1, sizeof(Tree));
    Tree* t = xmalloc(sizeof(Tree));
	t->left = left;
	t->right = right;
	t->value = value;
	return t;
}

// Convenience function to create a leaf.
Tree* leaf(int value) {
    return new_tree(NULL, value, NULL);
}

// Convenience function to create a node.
Tree* node(Tree* left, int value, Tree* right) {
    return new_tree(left, value, right);
}

void free_tree(Tree* t){
	if(t){
		free_tree(t->left);
		free_tree(t->right);
		t->left = NULL;
		t->right = NULL;
		free(t);
	}
}
// Prints a tree.
void print_tree(Tree* n) {
    if (n == NULL) {
        prints("_");
    } else if (n->left == NULL && n->right == NULL) {
        prints("(");
        printi(n->value);
        prints(")");
    } else {
        prints("(");
        print_tree(n->left);
        prints(", ");
        printi(n->value);
        prints(", ");
        print_tree(n->right);
        prints(")");
    }
}

// Prints a tree followed by a line break.
void print_tree_ln(Tree* n) {
    print_tree(n);
    printsln("");
}

// Checks if t is a leaf (has no successors).
bool is_leaf(Tree* t) {
    return t != NULL && t->left == NULL && t->right == NULL;
}
//Hilffunktion
int max_int(int a, int b){
    if(a < b){
        return b;
    }else{
        return a;
    }
}

// Returns the maximum product of a path from the root to any leaf.
int max_path_prod_rec(Tree* t, int max_so_far, int path_prod) {
    // todo: implement
	
    if(!t){
        return 0;
    }
	//if has only one node
	if(!t->left && !t->right)
		return t->value;
	
	int s_left = max_path_prod_rec(t->left, max_so_far, path_prod);
	int s_right = max_path_prod_rec(t->right, max_so_far, path_prod);
	
	if(t->left && t->right){
		max_so_far = max_int(max_so_far, s_left * t->value);
		max_so_far = max_int(max_so_far, s_right * t->value);
	}
	
	if(!t->left){
		max_so_far = s_right * t->value;
	}else if(!t->right){
		max_so_far = s_left * t->value;
	}
	
    return max_so_far;
}

// Returns the maximum path product for t.
int max_path_prod(Tree* t) {
    require("path product only defined for non-empty trees", t != NULL);
    return max_path_prod_rec(t, INT_MIN, 1);
}
void test_max_path_prod(void) {
    Tree* t;

    // one-element tree
    t = leaf(100);
    test_equal_i(max_path_prod(t), 100);
	free_tree(t);
    
    //    2
    // 3     4
    t = new_tree(leaf(3), 2, leaf(4));
    test_equal_i(max_path_prod(t), 2 * 4);
	free_tree(t);

    //    2
    // 3     -4
    t = new_tree(leaf(3), 2, leaf(-4));
    test_equal_i(max_path_prod(t), 2 * 3);
	free_tree(t);

    //   10
    //  2   5
    // 1 -3 4 -6
    t = new_tree(node(leaf(1), 2, leaf(-3)), 10, node(leaf(4), 5, leaf(-6)));
    test_equal_i(max_path_prod(t), 10 * 5 * 4);
	free_tree(t);

    //   10
    //  2   -5
    // 1 -3 4 -6
    t = new_tree(node(leaf(1), 2, leaf(-3)), 10, node(leaf(4), -5, leaf(-6)));
    test_equal_i(max_path_prod(t), 10 * -5 * -6);
	free_tree(t);

    //   10
    //  2   -5
    // 1 -3 4 6
    t = new_tree(node(leaf(1), 2, leaf(-3)), 10, node(leaf(4), -5, leaf(6)));
    test_equal_i(max_path_prod(t), 10 * 2 * 1);
	free_tree(t);

    //          10
    //       2        5
    //    1     3   4   6
    //  10 -210
    t = new_tree(node(node(leaf(10), 1, leaf(-210)), 2, leaf(3)), 10, node(leaf(4), 5, leaf(6)));
    test_equal_i(max_path_prod(t), 10 * 5 * 6);
	free_tree(t);

    //                1
    //          2           3
    //      3      NULL
    // NULL   -4
    t = new_tree(node(node(NULL, 3, leaf(-4)), 2, NULL), 1, leaf(3));
    test_equal_i(max_path_prod(t), 1 *  3);
	free_tree(t);

    //                1
    //          2           3
    //      -3      NULL
    // NULL   -4
    t = new_tree(node(node(NULL, -3, leaf(-4)), 2, NULL), 1, leaf(3));
    test_equal_i(max_path_prod(t), 1 * 2 * -3 * -4);
    print_tree_ln(t);
	free_tree(t);
}

//count number the node of tree
int count_node_tree(Tree* t){
    if(t == 0) return 0;
    if(!t->left && !t->right) return 1;
	
	int node_left = count_node_tree(t->left);
	int node_right = count_node_tree(t->right);
    
    return node_left + 1 + node_right;
}
void test_count_node_tree(){
    Tree* t;
    
	t = new_tree(NULL, 6, NULL);
	test_equal_i(count_node_tree(t), 1);
	
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-1)));
    test_equal_i(count_node_tree(t), 4);
    
    t = new_tree(node(leaf(0), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(count_node_tree(t), 6);
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, leaf(3));
	test_equal_i(count_node_tree(t), 5);
}

//find sum all of inner nodes
int inner_sum_node(Tree* t){
    if(!t)
        return 0;

    //if t is blatt, will not caculate
    if(!t->left && !t->right){
        return 0;
    }

    int left_sum = inner_sum_node(t->left);
    int right_sum = inner_sum_node(t->right);

    int sum = left_sum + t->value + right_sum;

    return sum;
}
void test_inner_sum_node(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(inner_sum_node(t), 0);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-1)));
    test_equal_i(inner_sum_node(t), 8);
    
    t = new_tree(node(leaf(0), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(inner_sum_node(t), 6);
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, leaf(3));
    test_equal_i(inner_sum_node(t), 18);
}

//sum all Nodes of right Tree
int sum_nodes(Tree* t){

    if(!t) return 0;

    int sum;

    if(t){
        sum = sum_nodes(t->left) + t->value + sum_nodes(t->right);
    }
    return sum;
}
int sumNodes_right_tree(Tree* t){

    if(!t) return 0;

    if(t) 
        return sum_nodes(t->right);
}
void test_sumNodes_right_tree(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(sumNodes_right_tree(t), 0);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-10)));
    test_equal_i(sumNodes_right_tree(t), -6); //1 + 3 + -10
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(sumNodes_right_tree(t), -5); //-3 + -2
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(4), 1, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(sumNodes_right_tree(t), 23); //4 + 1 + 4 + 1 + 3 + 10

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 3, NULL));
    test_equal_i(sumNodes_right_tree(t), 3); //3

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(4), 1, node(leaf(1), 2, NULL)));
    test_equal_i(sumNodes_right_tree(t), 8); //4 + 1 + 2
}

//find sum all nodes in left tree
int sumNodes_left_tree(Tree* t){

    if(!t) return 0;

    if(t) return sum_nodes(t->left);
}
void test_sumNodes_left_tree(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(sumNodes_left_tree(t), 0);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-10)));
    test_equal_i(sumNodes_left_tree(t), 0);
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(sumNodes_left_tree(t), 5); //4 + 2 + -1
    
    t = new_tree(node(node(leaf(1), 5, leaf(2)), 4, leaf(2)), 1, node(leaf(4), 1, leaf(1)));
    test_equal_i(sumNodes_left_tree(t), 14); //15 + 85 + 2

    t = new_tree(node(node(NULL, 15, leaf(5)), 2, node(leaf(2), 4, NULL)), 1, node(NULL, 3, NULL));
    test_equal_i(sumNodes_left_tree(t), 28); //15 + 5 + 2+ 2 + 4
}

//sum all right blätte in tree
int sumNodes_right_blatt(Tree* t){

    if(!t) return 0;

    int sum = 0;

    //find all right node
    if(t->right){

        //if this right node is Blatt
        if(!t->right->left && !t->right->right){
            sum += t->right->value;
        }
    }

    sum += sumNodes_right_blatt(t->right); //sum of right tree
    sum += sumNodes_right_blatt(t->left); // sum of left tree

    return sum;
}
void test_sumNodes_right_blatt(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(sumNodes_right_blatt(t), 0);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-5)));
    test_equal_i(sumNodes_right_blatt(t), -5); //1 + 3 + -10
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(sumNodes_right_blatt(t), -3); //-1 + -2
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(2), 10, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(sumNodes_right_blatt(t), 96); //85 + 1 + 10

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 3, NULL));
    test_equal_i(sumNodes_right_blatt(t), 88); //85 + 3

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(4), 1, node(leaf(1), 4, NULL)));
    test_equal_i(sumNodes_right_blatt(t), 85); //85
}

//find height of tree
int height_of_tree(Tree* t){

    if(!t){
        return 0;
    }else{
        int left = height_of_tree(t->left);
        int right = height_of_tree(t->right);

        if(left > right){
            return left + 1;
        }else{
            return right + 1;
        }
    }
 }

 void test_height_of_tree(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(height_of_tree(t), 1);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-5)));
    test_equal_i(height_of_tree(t), 3); //1 + 3 + -10
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(height_of_tree(t), 3); //-1 + -2
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(2), 10, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(height_of_tree(t), 5); //85 + 1 + 10

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 3, NULL));
    test_equal_i(height_of_tree(t), 4); //85 + 3

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(4), 1, node(leaf(1), 4, NULL)));
    test_equal_i(height_of_tree(t), 4); //85
}

int sum_without_leafs(Tree* t){

    if(!t)
        return 0;

    int sum = 0;

    //when a node isn't blatt
    if(t->left != NULL || t->right != NULL){
        sum += t->value;
        sum += sum_without_leafs(t->left);
        sum += sum_without_leafs(t->right);
    }

    return sum;
}

void test_sum_without_leafs(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(sum_without_leafs(t), 0);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-5)));
    test_equal_i(sum_without_leafs(t), 8); //5 + 3
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(sum_without_leafs(t), 6); //2 + 7 + -3
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(2), 10, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(sum_without_leafs(t), 35); //15 + 2 + 1 + 10 + 4+ 3

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 3, NULL));
    test_equal_i(sum_without_leafs(t), 18); //15 + 2+ 1

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(4), 1, node(leaf(1), 4, NULL)));
    test_equal_i(sum_without_leafs(t), 23); 
}

//find sum all leafs in tree
int sum_all_leafs(Tree* t){

    if(!t)
        return 0;

    int sum = 0;

    if(!t->left && !t->right){
        sum += t->value;
    }
    sum += sum_all_leafs(t->left);
    sum += sum_all_leafs(t->right);

    return sum;
}
void test_sum_all_leafs(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(sum_all_leafs(t), 6);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-5)));
    test_equal_i(sum_all_leafs(t), -4); //5 + 3
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(sum_all_leafs(t), 1); //2 + 7 + -3
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(2), 10, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(sum_all_leafs(t), 98); //15 + 2 + 1 + 10 + 4+ 3

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, leaf(3));
    test_equal_i(sum_all_leafs(t), 88); //15 + 2+ 1

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(4), 1, node(leaf(1), 4, NULL)));
    test_equal_i(sum_all_leafs(t), 90); 
}


int min_(int a, int b){
    if(a < b){
        return a;
    }else{
        return b;
    }
}
//find mind. element in tree
int find_min_Element(Tree* t){

    if(!t)
        return 0;
    
    int min = t->value;

    if(t){
        int left_min, right_min;

        //when has only right node or left node
        if(t->left){
            left_min = find_min_Element(t->left);
            min = min_(min, left_min);
        }
        if(t->right){
            right_min = find_min_Element(t->right);
            min = min_(min, right_min);
        }
    }
    return min;
}
void test_find_min_Element(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(find_min_Element(t), 6);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-5)));
    test_equal_i(find_min_Element(t), -5); //5 + 3
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(find_min_Element(t), -3); //2 + 7 + -3
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(2), 10, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(find_min_Element(t), 1); //15 + 2 + 1 + 10 + 4+ 3

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 3, NULL));
    test_equal_i(find_min_Element(t), 1); //15 + 2+ 1

    t = new_tree(node(node(NULL, 15, leaf(-9)), 2, NULL), 1, node(leaf(4), 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(find_min_Element(t), -9); 
}

//find max. element in tree
int find_max_Element(Tree* t){

    if(!t) return 0;

    int max = t->value;

    if(t){
        int left_max, right_max;

        if(t->right){
            right_max = find_max_Element(t->right);
            max = max_int(max, right_max);
        }

        if(t->left){
            left_max = find_max_Element(t->left);
            max = max_int(max, left_max);
        }
    }
    return max;
}

void test_find_max_Element(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(find_max_Element(t), 6);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-5)));
    test_equal_i(find_max_Element(t), 5); //5 + 3
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(find_max_Element(t), 7); //2 + 7 + -3
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(2), 10, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(find_max_Element(t), 85); //15 + 2 + 1 + 10 + 4+ 3

    t = new_tree(node(node(leaf(20), 15, leaf(85)), 2, node(NULL, 7, NULL)), 1, node(NULL, 3, NULL));
    test_equal_i(find_max_Element(t), 85); //15 + 2+ 1

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(find_max_Element(t), 85); 
}

//find number of node in tree
int count_leaf_Nodes(Tree* t){

    if(!t) return 0;

    int count = 0;
    if(t){

        if(!t->left && !t->right) count++;

        count += count_leaf_Nodes(t->left);
        count += count_leaf_Nodes(t->right);
    }
    return count;
}

void test_count_leaf_Nodes(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(count_leaf_Nodes(t), 1);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-5)));
    test_equal_i(count_leaf_Nodes(t), 2); //5 + 3
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(count_leaf_Nodes(t), 3); //2 + 7 + -3
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(2), 10, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(count_leaf_Nodes(t), 4); //15 + 2 + 1 + 10 + 4+ 3

    t = new_tree(node(node(leaf(20), 15, leaf(85)), 2, node(NULL, 7, NULL)), 1, node(NULL, 3, NULL));
    test_equal_i(count_leaf_Nodes(t), 4); //15 + 2+ 1

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(count_leaf_Nodes(t), 3); 
}

int count_total_number_node(Tree* t){

    int left, right;
    if(!t)
        return 0;

    left = count_total_number_node(t->left);
    right = count_total_number_node(t->right);

    return left + right + 1; // +1 parent/root
}

void test_count_total_number_node(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(count_total_number_node(t), 1);
    
    t = new_tree(NULL, 5, node(leaf(1), 3, leaf(-5)));
    test_equal_i(count_total_number_node(t), 4); 
    
    t = new_tree(node(leaf(4), 2, leaf(-1)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(count_total_number_node(t), 6); 
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(2), 10, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(count_total_number_node(t), 10);

    t = new_tree(node(node(leaf(20), 15, leaf(85)), 2, node(NULL, 7, NULL)), 1, node(NULL, 3, NULL));
    test_equal_i(count_total_number_node(t), 7);

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(count_total_number_node(t), 8); 
}

//find number of node equals parent node
int node_equals_root(Tree* t){
    if(!t)
        return 0;

    int left = 0, right = 0;

    if(t->left){
        if(t->left->value == t->value)
            left++;
        left += node_equals_root(t->left);
    }

    if(t->right){
        if(t->right->value == t->value)
            right++;
        right += node_equals_root(t->right);
    }

    return left + right;
}
void test_node_equals_root(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(node_equals_root(t), 0);
    
    t = new_tree(NULL, 3, node(leaf(1), 3, leaf(3)));
    test_equal_i(node_equals_root(t), 2); 
    
    t = new_tree(node(leaf(7), 2, leaf(7)), 7, node(NULL, -3, leaf(7)));
    test_equal_i(node_equals_root(t), 0); 
    
    t = new_tree(node(node(NULL, 15, leaf(1)), 1, NULL), 1, node(leaf(2), 10, node(node(NULL, 1, leaf(1)), 3, leaf(1))));
    test_equal_i(node_equals_root(t), 2);

    t = new_tree(node(node(leaf(2), 2, leaf(85)), 2, node(NULL, 7, NULL)), 2, node(NULL, 2, NULL));
    test_equal_i(node_equals_root(t), 4);

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(node_equals_root(t), 1); 

    t = new_tree(node(node(leaf(0), 0, leaf(0)), 0, node(NULL,0, NULL)), 0, node(NULL, 0, NULL));
    test_equal_i(node_equals_root(t), 6);
}


//find number of nodes different parent node
int child_different_parent(Tree* t){
    if(!t) return 0;

    int left = 0, right = 0;

    if(t->left){
        if(t->left->value != t->value)
            left++;
        left += child_different_parent(t->left);
    }

    if(t->right){
        if(t->right->value != t->value)
            right++;
        left += child_different_parent(t->right);
    }
    return left + right;
}
void test_child_different_parent(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(child_different_parent(t), 0);
    
    t = new_tree(NULL, 3, node(leaf(1), 3, leaf(3)));
    test_equal_i(child_different_parent(t), 1); 
    
    t = new_tree(node(leaf(7), 2, leaf(7)), 7, node(NULL, -3, leaf(7)));
    test_equal_i(child_different_parent(t), 5); 
    
    t = new_tree(node(node(NULL, 15, leaf(1)), 1, NULL), 1, node(leaf(2), 10, node(node(NULL, 1, leaf(1)), 3, leaf(1))));
    test_equal_i(child_different_parent(t), 7);

    t = new_tree(node(node(leaf(2), 2, leaf(85)), 2, node(NULL, 7, NULL)), 2, node(NULL, 2, NULL));
    test_equal_i(child_different_parent(t), 2);

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(child_different_parent(t), 6); 
}

int sum_left_blatts(Tree* t){

    //find sum all left-blatts on left tree
    if(t == NULL){
        return 0;
    }
    int left_sum = 0;

    if(t->left){
        if(!t->left->left && !t->left->right){
            left_sum += t->left->value;
        }
    }

    left_sum += sum_left_blatts(t->left);

    return left_sum;
}
void test_sum_left_blatts(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(sum_left_blatts(t), 0);
    
    t = new_tree(NULL, 3, node(leaf(1), 3, leaf(3)));
    test_equal_i(sum_left_blatts(t), 0); 
    
    t = new_tree(node(leaf(7), 2, leaf(7)), 7, node(NULL, -3, leaf(7)));
    test_equal_i(sum_left_blatts(t), 7); 
    
    t = new_tree(node(node(NULL, 15, leaf(1)), 1, NULL), 1, node(leaf(2), 10, node(node(NULL, 1, leaf(1)), 3, leaf(1))));
    test_equal_i(sum_left_blatts(t), 0);

    t = new_tree(node(node(leaf(2), 2, leaf(85)), 2, node(NULL, 7, NULL)), 2, node(NULL, 2, NULL));
    test_equal_i(sum_left_blatts(t), 2);

    t = new_tree(node(node(leaf(85), 15, NULL), 2, NULL), 1, node(NULL, 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(sum_left_blatts(t), 85); 
}

//find mind. level of leaf in tree
int min_leaf_level(Tree* t){

    if (!t) return 0;

    if (!t->left && !t->right)
        return 0;

    int min_l = INT_MAX, min_r = INT_MAX;

    if(t->left){
        min_l =  min_leaf_level(t->left) + 1;
    }
    if(t->right){
        min_r =  min_leaf_level(t->right) + 1;
    }

    return min_(min_l, min_r);
}
void test_min_leaf_level(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(min_leaf_level(t), 0);
    
    t = node(node(leaf(1), 124, NULL), 1000, NULL);
    test_equal_i(min_leaf_level(t), 2);

    t = new_tree(NULL, 3, node(leaf(1), 3, leaf(3)));
    test_equal_i(min_leaf_level(t), 2);
    
    t = new_tree(node(leaf(7), 2, leaf(7)), 7, node(NULL, -3, leaf(7)));
    test_equal_i(min_leaf_level(t), 2); 
    
    t = new_tree(node(node(NULL, 15, leaf(1)), 1, NULL), 1, node(leaf(2), 10, node(node(NULL, 1, leaf(1)), 3, leaf(1))));
    test_equal_i(min_leaf_level(t), 2);

    t = new_tree(node(node(leaf(2), 2, leaf(6)), 2, leaf(7)), 2, leaf(3));
    test_equal_i(min_leaf_level(t), 1);

    t = new_tree(node(node(leaf(85), 15, NULL), 2, NULL), 1, node(NULL, 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(min_leaf_level(t), 3);

    t = new_tree(node(node(leaf(2), 1, leaf(2)), 2, node(leaf(1), 3, leaf(2))), 1, node(leaf(2), 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(min_leaf_level(t), 2);

}

//find max node at given level
int find_maxNode_AtLevel(Tree* t, int level){

    if(!t) return 0;

    //at level 0 there is only root
    if(level == 0)
        return t->value;

    int l = find_maxNode_AtLevel(t->left, level - 1);
    int r = find_maxNode_AtLevel(t->right, level - 1);

    return max_int(l, r);
}
void test_find_maxNode_AtLevel(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(find_maxNode_AtLevel(t, 1), 0);
    
    t = new_tree(NULL, 3, node(leaf(1), 3, leaf(3)));
    test_equal_i(find_maxNode_AtLevel(t, 2), 3); 
    
    t = new_tree(node(leaf(7), 2, leaf(17)), 7, node(NULL, -3, leaf(1)));
    test_equal_i(find_maxNode_AtLevel(t, 2), 17); 
    
    t = new_tree(node(node(NULL, 15, leaf(1)), 1, NULL), 1, node(leaf(2), 10, node(node(NULL, 1, leaf(1)), 3, leaf(1))));
    test_equal_i(find_maxNode_AtLevel(t, 3), 1);

    t = new_tree(node(node(leaf(2), 2, leaf(6)), 2, leaf(1)), 2, leaf(3));
    test_equal_i(find_maxNode_AtLevel(t, 3), 6);

    t = new_tree(node(node(leaf(85), 15, NULL), 2, NULL), 1, node(NULL, 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(find_maxNode_AtLevel(t, 3), 85);

    t = new_tree(node(node(leaf(2), 1, leaf(2)), 2, node(leaf(1), 3, leaf(2))), 1, node(leaf(2), 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(find_maxNode_AtLevel(t, 2), 4);
}

int level_ofNode(Tree* t, int level, int data){

    if(t == NULL) return 0;

    //when found the data, return current level
    //alaways find to first node like data
    if(t->value == data){
        return level;
    }

    //when a node is blatt, return 0
    if(!t->left && !t->right)
        return 0;


    int l = level_ofNode(t->left, level + 1, data);
    int r = level_ofNode(t->right, level + 1, data);

    //max_int: because level alaway >= 0
    return max_int(l, r);
}
void test_level_ofNode(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(level_ofNode(t, 0, 6), 0);
    
    t = new_tree(NULL, 3, node(leaf(1), 3, leaf(3)));
    test_equal_i(level_ofNode(t, 0, 1), 2); 
    
    t = new_tree(node(leaf(7), 2, leaf(17)), 7, node(NULL, -3, leaf(1)));
    test_equal_i(level_ofNode(t, 0, 2), 1); 
    
    t = new_tree(node(node(NULL, 15, leaf(1)), 1, NULL), 1, node(leaf(2), 10, node(node(NULL, 1, leaf(1)), 3, leaf(1))));
    test_equal_i(level_ofNode(t, 0, 10), 1);

    t = new_tree(node(node(leaf(2), 2, leaf(6)), 2, leaf(1)), 2, leaf(3));
    test_equal_i(level_ofNode(t, 0, 3), 1);

    t = new_tree(node(node(leaf(85), 15, NULL), 2, NULL), 1, node(NULL, 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(level_ofNode(t, 0, 85), 3);

    t = new_tree(node(node(leaf(2), 1, leaf(2)), 2, node(leaf(1), 3, leaf(2))), 1, node(leaf(2), 1, node(leaf(1), 4, leaf(-5))));
    test_equal_i(level_ofNode(t, 0, -5), 3);
}

//find mind. leaf level at given level 0
int min_leaf_level_(Tree* t, int level) {

    if(!t) return level;

    if(!t->left && !t->right){
        return level;
    }

    int l_ = INT_MAX, r_ = INT_MAX;

    if(t->left){
        l_ = min_leaf_level_(t->left, level + 1);
    }

    if(t->right){
       r_ = min_leaf_level_(t->right, level + 1);
    }

    return min_(l_, r_);
}

void test_min_leaf_level_(void) {
    Tree* t;
    t = leaf(100);
    test_equal_i(min_leaf_level_(t, 0), 0);

    t = node(leaf(124), 1000, leaf(110));
    test_equal_i(min_leaf_level_(t, 0), 1);
    
    t = node(leaf(124), 1000, NULL);
    test_equal_i(min_leaf_level_(t, 0), 1);
    
    t = node(node(leaf(1), 124, NULL), 1000, NULL);
    test_equal_i(min_leaf_level_(t, 0), 2);

    t = node(node(leaf(4), 2, NULL), 1, leaf(3));
    test_equal_i(min_leaf_level_(t, 0), 1);
    
    t = node(node(leaf(4), 2, leaf(5)), 1, leaf(3));
    test_equal_i(min_leaf_level_(t, 0), 1);
    
    t = node(node(node(NULL, 4, leaf(5)), 2, NULL), 1, leaf(3));
    test_equal_i(min_leaf_level_(t, 0), 1);
    
    t = node(node(leaf(3), 2, leaf(4)), 1, node(leaf(6), 5, leaf(7)));
    test_equal_i(min_leaf_level_(t, 0), 2);
    
    t = node(node(node(NULL, 4, node(leaf(6), 5, NULL)), 2, NULL), 1, leaf(3));
    test_equal_i(min_leaf_level_(t, 0), 1);

    t = node(node(node(NULL, 15, leaf(1)), 1, NULL), 1, node(leaf(2), 10, node(node(NULL, 1, leaf(1)), 3, leaf(1))));
    test_equal_i(min_leaf_level_(t, 0), 2);
}

//count the number of even node in tree
int count_even_node(Tree* t){

    if(t == NULL) return 0;

    int count = 0;

    if(t->value % 2 == 0)
        count++;

    if(t->left){
        count += count_even_node(t->left);
    }

    if(t->right){
        count += count_even_node(t->right);
    }

    return count;
}
void test_count_even_node(void) {
    Tree* t;
    t = new_tree(NULL, 100, NULL);
    test_equal_i(count_even_node(t), 1);

    t = node(leaf(124), 1000, leaf(110));
    test_equal_i(count_even_node(t), 3);
    
    t = node(leaf(124), 1000, NULL);
    test_equal_i(count_even_node(t), 2);
    
    t = node(node(leaf(1), 124, NULL), 1000, NULL);
    test_equal_i(count_even_node(t), 2);

    t = node(node(leaf(4), 2, NULL), 1, leaf(3));
    test_equal_i(count_even_node(t), 2);
    
    t = node(node(leaf(4), 2, leaf(5)), 1, leaf(3));
    test_equal_i(count_even_node(t), 2);
    
    t = node(node(node(NULL, 4, leaf(5)), 2, NULL), 1, leaf(3));
    test_equal_i(count_even_node(t), 2);
    
    t = node(node(leaf(3), 2, leaf(4)), 1, node(leaf(6), 5, leaf(7)));
    test_equal_i(count_even_node(t), 3);
    
    t = node(node(node(NULL, 4, node(leaf(6), 5, NULL)), 2, NULL), 1, leaf(3));
    test_equal_i(count_even_node(t), 3);

    t = node(node(node(NULL, 15, leaf(1)), 1, NULL), 1, node(leaf(2), 10, node(node(NULL, 1, leaf(1)), 3, leaf(1))));
    test_equal_i(count_even_node(t), 2);
}

//count blatt like parent in tree
int count_blatt_like_parent(Tree* t){
    if(!t) return 0;

    int count = 0;

    if(t->left){
        if(!t->left->left && !t->left->right){
            if(t->value == t->left->value)
                count++;
        }
        count += count_blatt_like_parent(t->left);
    }

    if(t->right){
        if(!t->right->left && !t->right->right){
            if(t->value == t->right->value)
                count++;
        }
        count += count_blatt_like_parent(t->right);
    }

    return count;
}

void test_count_like_parent(){
    Tree* t;

    t = new_tree(NULL, 6, NULL);
    test_equal_i(count_blatt_like_parent(t), 0);
    
    t = new_tree(NULL, 1, node(leaf(1), 3, leaf(-10)));
    test_equal_i(count_blatt_like_parent(t), 0); //1 + 3 + -10
    
    t = new_tree(node(leaf(2), 2, leaf(2)), 7, node(NULL, -3, leaf(-2)));
    test_equal_i(count_blatt_like_parent(t), 2); //-3 + -2
    
    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(4), 1, node(node(NULL, 4, leaf(1)), 3, leaf(10))));
    test_equal_i(count_blatt_like_parent(t), 0); //4 + 1 + 4 + 1 + 3 + 10

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(NULL, 1, NULL));
    test_equal_i(count_blatt_like_parent(t), 1); //3

    t = new_tree(node(node(NULL, 15, leaf(85)), 2, NULL), 1, node(leaf(4), 1, node(leaf(1), 1, NULL)));
    test_equal_i(count_blatt_like_parent(t), 1); //4 + 1 + 2
}

int main() {
    test_max_path_prod();
	test_count_node_tree();
    test_inner_sum_node();
    test_sumNodes_right_tree(); //dung them ham phu de tinh tong cac node, sau do ap dung vao bai toan
    test_sumNodes_left_tree(); //tinh tong Nodes roi van dung vao tinh rieng le
    test_sumNodes_right_blatt(); //sum all of right blatts in tree
    test_sum_left_blatts(); //sum all left-blatts on left tree
    test_height_of_tree();
    test_sum_without_leafs();
    test_sum_all_leafs();
    test_find_min_Element();
    test_find_max_Element();
    test_count_leaf_Nodes();
    test_count_total_number_node();
    test_node_equals_root();
    test_child_different_parent();
    test_min_leaf_level(); //without given paramenter
    test_find_maxNode_AtLevel();
    test_level_ofNode();
    test_min_leaf_level_();
    test_count_even_node();
    test_count_like_parent();
    return 0;
}
