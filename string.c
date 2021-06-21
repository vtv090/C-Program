
// make string && ./string

#include "base.h"

//remove digit in string with pointer
char* remove_digit(char* s){
	int length = strlen(s);
	
	if(length == 0)
		return "";
	
	char* result = (char*)xmalloc(length + 1);
	int i = 0;
	for(int j = 0; j < length; j++){
		if(s[j] < '0' || s[j] > '9'){
			result[i++] = s[j];
		}
	}
	result[i] = '\0';
	return result;
}


void test_remove_digit(){
    test_equal_s(remove_digit("1dsj 8s9shd"),"dsj sshd");
    test_equal_s(remove_digit("1ensd48fjfld"),"ensdfjfld");
    test_equal_s(remove_digit("29djjjda9923j"),"djjjdaj");
	test_equal_s(remove_digit(""),"");
}

//remove spaces in string with pointer
char* remove_space(char* s){
	int length = strlen(s);
	//char* result = (char*)xmalloc(length + 1);
	char* result = xcalloc(length, sizeof(char));
	
	int c = 0;
	for(int i = 0; i < length; i++){
		if(s[i] != ' '){
			result[c++] = s[i];
		}
	}
	result[c] ='\0';
	return result;
}
void test_remove_space(){
    test_equal_s(remove_space("1dsj 8s9shd"),"1dsj8s9shd");
    test_equal_s(remove_space("1 en sd   48fjf ld"),"1ensd48fjfld");
    test_equal_s(remove_space("29 djjj da99 23j"),"29djjjda9923j");
	test_equal_s(remove_space(""),"");
}

//check whether a string is a sub String in given string
bool is_subString(char* s, char* sub){
	int s_length = strlen(s);
	int sub_length = strlen(sub);
	
	for(int i = 0; i < s_length; i++){
		if(s[i] == sub[0]){
			
			int k = 0;
			for(int j = 0; j < sub_length; j++){
				if(s[i+j] == sub[j]) k++;
			}
			
			if(k == sub_length){
				return true;
			}else{
				return false;
			}
		}
	}
	return true;
}

void test_is_subString(){
    test_equal_b(is_subString("Hello luh", "uh"), true);
    test_equal_b(is_subString("welcom to cualo", " cuao"), false);
    test_equal_b(is_subString("Hello luh", "uss"), false);
}

//append 2 strings with pointer
char* append_strings(char* a, char* b){
	int a_length = strlen(a);
	int b_length = strlen(b);
	
	char* result = (char*)xmalloc(a_length + b_length + 1);
	
	int c = 0;
	for(int i = 0; i < a_length; i++){
		result[c++] = a[i];
	}
	
	for(int j = 0; j < b_length; j++){
		result[c++] = b[j];
	}
	result[c] = '\0'; //null terminiert
	
	return result;
}
void test_append_strings(){
    test_equal_s(append_strings("asjsd", "7w9w"), "asjsd7w9w");
    test_equal_s(append_strings("1424", "vwed2"), "1424vwed2");
    test_equal_s(append_strings("asjsd", "7w9w"), "asjsd7w9w");
}


//remove duplicated elements in given string with pointer
char* remove_duplicate(char* s){
	
	int length = strlen(s);
	char* result = (char*)xmalloc(length +1);
	int c = 0;

	for(int i = 0; i < length; i++){
		int j;
		for( j= 0; j < i; j++){
			if(s[i] == s[j] && s[i] != ' ')
				break; //return to first for-loop, ignore this s[i]
		}
		//if from 0 to i there are no dupplicate
		if(j == i)
			result[c++] = s[i];
	}
	result[c] ='\0'; //Nullterminiert
	
	return result;
}
void test_remove_duplicate(){
    test_equal_s(remove_duplicate("asjsd7w9w"), "asjd7w9");
    test_equal_s(remove_duplicate("1424 vwe d2"), "142 vwe d");
    test_equal_s(remove_duplicate("a sj sd7 w9w"), "a sj d7 w9");
}

//sort given string with pointer
char* sorting_str(char* s){

	int length = strlen(s);
	
	char* result = (char*)xmalloc(length + 1);

	//initialisiert array with length 128
	int char_temp[128] ={0};

	for(int i = 0; i < length; i++){
		//add sequence of each character to char_temp
		char_temp[s[i]]++;
	}
	
	int c = 0;
	for(int j = 0; j < 128; j++){
		//if at j has character -> char_temp[j] >= 1
        if(char_temp[j] != 0){

        	while(char_temp[j] > 0){
        		result[c++] = j; //will convert from hexa to character
        		char_temp[j]--; //reduce number of character after adding in result
        	}
        }
    }
	result[c] = '\0';

	return result;
}
void test_sorting_str(){
	test_equal_s(sorting_str("sadcbpm"), "abcdmps");
	test_equal_s(sorting_str("cafdaysqp"), "aacdfpqsy");
    test_equal_s(sorting_str("cfdaA12ysqp"), "12Aacdfpqsy");
}

//replace a sub string by another string with pointer
char* replace_string_byString(char* s, char* sub, char* rep){
	/*
    * Replace a given string by another string
    */
	int length = strlen(s);
	int sub_len = strlen(sub);
	int rep_len = strlen(rep);
	if(sub_len == 0)
		return s;
	
	int count = 0;
	//count number of sub in String s
	for(int i = 0; i < length; i++){
		if(s[i] == sub[0]){
			int j;
			for(j = 0; j < sub_len; j++){
				if(s[i+j] != sub[j]) break;
			}
			if(j == sub_len){
				count++;
				i += (sub_len - 1); //i jump more strlen(sub) characters
			}
		}
	}
	
	char* result = (char*)xmalloc(length + count *(rep_len - sub_len) + 1);
	int k = 0;
	
	for(int i = 0; i < length; i++){
		if(s[i] == sub[0]){
			int j;
			for(j = 0; j < sub_len; j++){
				if(s[i+j] != s[j]){
					result[k++] = s[i];
					break;
				}
			}
			if(j == sub_len){
				if(rep_len == 0){
					return result;
				}else{
					int c = 0;
					while(c < rep_len){
						result[k++] = rep[c++];
					}
				}
				i += sub_len - 1;
			}
		}else{
			result[k++] = s[i];
		}
	}
	result[k] = '\0';
	
	return result;
}
void test_replace_string_byString(){
	test_equal_s(replace_string_byString("AB syAB cbbpm", "AB", "_aA"), "_aA sy_aA cbbpm");
	test_equal_s(replace_string_byString("cABa fcAB dayccABqp", "cAB", "_aA"), "_aAa f_aA dayc_aAqp");
    test_equal_s(replace_string_byString("aabbccdd", "aa", "d"), "dbbccdd");
	test_equal_s(replace_string_byString("hello, hello world", "hello", "bye"), "bye, bye world");
	test_equal_s(replace_string_byString("sajdssnskds", "", "c"), "sajdssnskds");
	test_equal_s(replace_string_byString("aabbccdd", "b", ""), "aaccdd");
}

char* str_cat(char* s1, char* s2){

    int n = 0;
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    char* result = (char*)xmalloc(strlen(s1) + strlen(s2) +1);

    for(int i = 0; i < l1; i++){
        result[n++] = s1[i];
    }

    for(int i = 0; i < l2; i++){
        result[n++] = s2[i];
    }
    result[n] = '\0';

    return result;
}

//remove char at index in string
char* remove_char_with_index(char* s, int index){

	int length = strlen(s);
	char* result = (char*)xmalloc(length - 1 + 1);

	if(index < 0)
		return s;

	int k = 0;
	for(int i = 0; i < length; i++){
		if(i != index){
			result[k++] = s[i];
		}
	}

	result[k] = '\0';

	return result;
}
void test_remove_char_with_index(){
	test_equal_s(remove_char_with_index("jds49fndfl", 0),"ds49fndfl");
    test_equal_s(remove_char_with_index("48ffm cd3nfdl", 12),"48ffm cd3nfd");
    test_equal_s(remove_char_with_index("dsv3xcxls", 1),"dv3xcxls");
    test_equal_s(remove_char_with_index("94flfdlsdn", 4),"94fldlsdn");
    test_equal_s(remove_char_with_index("94flfdlsdn", -1),"94flfdlsdn");
}

char* remove_char_like_char(char* s, char c){
	int length = strlen(s);
	char* result = (char*)xmalloc(length + 1);

	int k = 0;
	for(int i = 0; i < length; i++){
		if(s[i] != c){
			result[k++] = s[i];
		}
	}
	result[k] = '\0';

	return result;
}
void test_remove_char_like_char(){
	test_equal_s(remove_char_like_char("48ffm cd3nfd", 'd'),"48ffm c3nf");
    test_equal_s(remove_char_like_char("dsv3xcxls", 'x'),"dsv3cls");
    test_equal_s(remove_char_like_char("94flfdlsdn", 'l'),"94ffdsdn");
    test_equal_s(remove_char_like_char("94flfdlsdn", '9'),"4flfdlsdn");
}

char* find_distict_two_string(char* a, char* b){
	//find all characters in a but not in b

	int a_len = strlen(a);
	int b_len = strlen(b);
	char* result = (char*)xmalloc(a_len + 1);

	int k = 0;

	for(int i = 0; i < a_len; i++){

		int j;
		for(j = 0; j < b_len; j++){

			if(a[i] == b[j]) break;
		}

		if(j == b_len){
			result[k++] = a[i];
		}
	}
	
	result[k] = '\0';

	return result;
}

void test_find_distict_two_string(){
	test_equal_s(find_distict_two_string("abacs", "cxzca"), "bs");
	test_equal_s(find_distict_two_string("127283", "1nd239"), "78");
	test_equal_s(find_distict_two_string("ah uewn dsks", "cxzca"), "h uewn dsks");
}

//find common char in two given Strings
char* find_common_inStrings(char* a, char* b){
	int a_len = strlen(a);
	int b_len = strlen(b);
	char* result = (char*)xmalloc(a_len + 1);

	int k = 0;
	for(int i = 0; i < a_len; i++){
		for(int j = 0; j < b_len; j++){
			if(a[i] == b[j] && a[i] != ' '){
				result[k++] = a[i];
				break;
			}
		}
	}
	result[k] = '\0';
	return result;
}
void test_find_common_inStrings(){
	test_equal_s(find_common_inStrings("abacs", "cxzca"), "aac");
	test_equal_s(find_common_inStrings("127 dsj923", "328n09"), "2923");
	test_equal_s(find_common_inStrings("ab ac ssd", "c xz cad"), "aacd");
}

char* split_string(char* s, int x){
	//split String s to smaller strings with length x
	require("x", x > 0);
	int length = strlen(s);
	int count = length/x;
	char* result = (char*)xmalloc(length + count +1);
	int k = 0;
	int c = 0;


	if(length == 0) return "";

	for(int i = 0; i < length; i++){

		int j;
		//add each small String to result
		for(j = 0; j < x; j++){
			result[k++] = s[i+j];
		}
		//count number of smaller Strings
		if(j == x){
			c++;
		}
		//after adding, i increase more (x-1) steps
		i += (x-1);

		//Add space for not-end String
		if(c != count){
			result[k++] = ' ';
		}else if(c == count && i < length-1){
			result[k++] = ' ';
		}
		
	}
	result[k] = '\0';

	return result;
}
void test_split_string(){
	test_equal_s(split_string("1ABsj8s9ABshd", 4), "1ABs j8s9 ABsh d");
	test_equal_s(split_string("1ensAB48fABfld", 4),"1ens AB48 fABf ld");
	test_equal_s(split_string("", 4),"");
	test_equal_s(split_string("dblfdlkfdo3n", 2),"db lf dl kf do 3n");
}

//check whether 4 last digits is sorted
bool four_sorted_chars(char* s){
	int length = strlen(s);

	for(int i = 0; i < length; i++){
		int count = 0;
		for(int j = 0; j < 4; j++){
			if(s[i+j] <= s[i+j+1] && (s[i+j] >='0' && s[i+j] <= 'z'))
				count++;
		}
		if( count == 3){
			return true;
		}
	}
	return false;
}
void test_four_sorted_chars(){
    test_equal_b(four_sorted_chars("1b cxkjy"), false);
    test_equal_b(four_sorted_chars("11 afkl 32"), true);
    test_equal_b(four_sorted_chars("1 b 1479"), true);
    test_equal_b(four_sorted_chars("12b oars"), false);
    test_equal_b(four_sorted_chars("14b zw91 jy"), false);
}

//find sequence a substring in String
int sequence_inString(char*a, char* b){
	int a_len = strlen(a);
	int b_len = strlen(b);
	int count = 0;

	for(int i = 0; i< a_len; i++){
		if(a[i] == b[0]){
			int j;
			for(j = 0; j < b_len; j++){
				if(a[i+j] != b[j])
					break;
			}
			if(j == b_len)
				count++;
		}
	}

	return count;
}
void test_sequence_inString(){
	test_equal_i(sequence_inString("hello world", "l"), 3);
    test_equal_i(sequence_inString("hello world", "w"), 1);
    test_equal_i(sequence_inString("hello worlld", "ll"), 2);
    test_equal_i(sequence_inString("hello world  ", " "), 3);
    test_equal_i(sequence_inString("hello world hello", "hello"), 2);
    test_equal_i(sequence_inString("hello world", "not"), 0);
    test_equal_i(sequence_inString("hello world", "not in there..."), 0);
    test_equal_i(sequence_inString("...", "..."), 1);
    test_equal_i(sequence_inString("....", "..."), 2);
    test_equal_i(sequence_inString(".....", "..."), 3);
}


char* remove_digits(char* s){
	int length = strlen(s);
	if(length <= 1) return s;
	char* result = (char*)xmalloc(length + 1);
	int k = 0;

	for(int i = 0; i < length; i++){
		if(s[i] > '9')
			result[k++] = s[i];
	}
	result[k] = '\0';
	return result;

}
void test_remove_digits(void) {
test_equal_s(remove_digits(""), "");
test_equal_s(remove_digits("x"), "x");
test_equal_s(remove_digits("11"), "");
test_equal_s(remove_digits("11x"), "x");
test_equal_s(remove_digits("x11buo8"), "xbuo");
test_equal_s(remove_digits("x11x"), "xx");
test_equal_s(remove_digits("1a2b3c4"), "abc");
}

bool is_in_alphabet(char c){
	return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}
bool is_Palindrome(char* s){

	int length = strlen(s);
	if(length == 0) return false;

	for(int i = 0, j = length-1; i < length && j >= 0; i++, j--){

		//when s[i] not alphabet, i++
		while(!is_in_alphabet(s[i])){
			i++;
		}

		while(!is_in_alphabet(s[j])){
			j--;
		}

		if(s[i] != s[j])
			return false;
	}

	return true;
}


void test_is_Palindrome(){
	test_equal_b(is_Palindrome("hello world"), false);
    test_equal_b(is_Palindrome("anna"), true);
    test_equal_b(is_Palindrome(""), false);
    test_equal_b(is_Palindrome("shower."), false);
    test_equal_b(is_Palindrome("madam ?"), true);
    test_equal_b(is_Palindrome("nurses *+ run"), true);
}
char* remove_notChar(char* s){
	int length = strlen(s);
	char* result = (char*)xmalloc(length + 1);
	int c = 0;

	for(int i = 0; i < length; i++){
		if(is_in_alphabet(s[i])){
			result[c++] = s[i];
		}
	}

	result[c] = '\0';

	return result;
}


//is contains palindrome with length from x characters
bool is_contains_palindrome(char* s, int x){

	int length = strlen(s);
	
	if(x > length)
		return false;


	if(length == 0 && x == 0)
		return false;

	char* new_s = remove_notChar(s);
	int new_len = strlen(new_s);

	for(int k = x; k <= new_len; k++){


		//"new_len - k + 1": for situation k = new_len (must more 1 increase)
		for(int i = 0; i < new_len - k + 1; i++){

			//creat temporal String with length k
			char* temp = (char*)xmalloc(x + 1);

			int j;
			//add k characters from i-th char to temp
			for(j = 0; j < k; j++){
				temp[j] = new_s[i+j];
			}
			temp[j] = '\0';

			//check whether this String palindrome
			if(is_Palindrome(temp))
				return true;

			free(temp);
		}
	}
	return false;
}


void test_is_contains_palindrome(){
	test_equal_b(is_contains_palindrome("hello world", 4), false);
    test_equal_b(is_contains_palindrome("hello world", 3), true);
    test_equal_b(is_contains_palindrome("anna", 3), true);
    test_equal_b(is_contains_palindrome("", 0), false);
    test_equal_b(is_contains_palindrome("shower thoughts by madam anna", 4), true);
    test_equal_b(is_contains_palindrome("madam anna is a nurse", 3), true);
    test_equal_b(is_contains_palindrome("nurses run", 4), true);
}
char to_lower(char c){

	if(c >= 'A' && c <= 'Z'){
		c = c + 32;
	}

	return c;
}


char to_upper(char c){

	if(c >= 'a' && c <= 'z'){
		c = c - 32;
	}
	return c;
}
//given a String then return a new String with Uppercase at first of each word
//VUON nhA cO -> Vuon Nha Co
char* auto_correct(char* s){
	int length = strlen(s);
	char* result = (char*)xmalloc(length + 1);

	int i;
	for(i = 0; i < length; i++){
		
		//add first character in Sentence
		if(i == 0 && (s[i] <= 'Z' && s[i] >= 'A')){
			result[i] = s[i];
		}else if(i == 0 && (s[i] <= 'z' && s[i] >= 'a')){
			result[i] = to_upper(s[i]);
		}

		//add space and first char of each word to result
		if(s[i] == ' ' && (s[i+1] <= 'z' && s[i+1] >= 'a') && i+1 < length){
			result[i] = s[i];
			result[i+1] = to_upper(s[i+1]);

		}else if(s[i] == ' ' && (s[i+1] <= 'Z' && s[i+1] >= 'A') && i+1 < length){
			result[i] = s[i];
			result[i+1] = s[i+1];
		}

		//When s[i] is not first Char in Word
		if(i != 0 && s[i-1] != ' ' && (s[i] <= 'Z' && s[i] >= 'A')){
			result[i] = to_lower(s[i]);
		}else if(i != 0 && s[i-1] != ' ' && (s[i] <= 'z' && s[i] >= 'a')){
			result[i] = s[i];
		}
	}
	result[i] = '\0';

	return result;
}
void test_auto_correct(){
	test_equal_s(auto_correct("NhA TOi CO"), "Nha Toi Co");
	test_equal_s(auto_correct("vuON nHa CO hOa"), "Vuon Nha Co Hoa");
	test_equal_s(auto_correct("EM DEP vAI"), "Em Dep Vai");
}


char* next_occurence(char* s, char* find){
	
	int s_len = strlen(s);
	int f_len = strlen(find);
	
	char* result = (char*)xmalloc(s_len + 1);
	
	for(int i = 0; i < s_len; i++){
		if(s[i] == find[0]){
			int j;
			for(j = 0; j < f_len; j++){
				if(s[i+j] != find[j])
					break;
			}
			
			if(j == f_len){
				//add the rest of String s to result
				int n = 0;
				for(int k = i; k < s_len; k++){
					result[n++] = s[k];
				}
				result[n] = '\0';
				
				return result;
			}
		}
	}
	return 0;
}
void test_next_occurence(){
    test_equal_s(next_occurence("aabbccdd", "bb"), "bbccdd");
    test_equal_b(next_occurence("abbccdd", "aa") == NULL, true);
    test_equal_b(next_occurence("d", "aa")== NULL, true);
    test_equal_s(next_occurence("abbccdda", "a"), "abbccdda");
    test_equal_s(next_occurence("bccdda", "a"), "a");
    test_equal_s(next_occurence("hello, hello world", "hello"), "hello, hello world");
    test_equal_s(next_occurence("ello, hello world", "hello"), "hello world");
    test_equal_s(next_occurence("llo, hello world", "rld"), "rld");
    test_equal_b(next_occurence("hello, hello world", "bye")== NULL, true);
}


int main(void) {
	test_remove_digit();
	test_remove_space();
	test_is_subString();
	test_append_strings();
	test_remove_duplicate();
	test_sorting_str();
	test_replace_string_byString();
	test_remove_char_with_index();
	test_remove_char_like_char();
	test_find_distict_two_string();
	test_find_common_inStrings();
	test_split_string();
	test_four_sorted_chars();
	test_sequence_inString();
	test_remove_digits();
	test_is_Palindrome();
	test_is_contains_palindrome();
	test_auto_correct();
	test_next_occurence();
	return 0;
}
