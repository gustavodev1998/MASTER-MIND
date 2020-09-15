
	
/**
 * nomes_tests.c
 * Este programa contém um conjunto de testes para validar as implementações
 * presentes no ficheiro "nomes.c".
 * 
 * Isel, outubro de 2019
 * 
 * Build : gcc -Wall -std=c99 -o nomes_testes nomes_testes.c nomes.c tests/unity.c 
 * Execute : nomes_testes
 *---------------------------------------------------------------------------*/

#include <stdbool.h>
#include <string.h>

#include "tests/tests.h"

#include "nomes.h"


// auxiliary functions
void copy_len(char dst[], char src[], int size) {
	for(int i=0; i < size; ++i) dst[i] = src[i];
}

// name_all_upper tests


void test_name_all_upper_of_empty_name() {
	char empty_name[] = { "          " };
	char expected[] =   { "          " };
	char result[MAX_NAME_SIZE];
	
	name_all_upper(empty_name, result);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	 
}

void test_name_all_upper_of_short_name() {
	char short_name[] = "little";
	char result[MAX_NAME_SIZE];
	
	char expected[] = "LITTLE";
	
	name_all_upper(short_name, result);
	TEST_ASSERT_EQUAL_STRING(expected, result);
}

void test_name_all_upper_of_long_name() {
	char long_name[] = " carlos   manuel guerreiro  pessOA  ";
	char result[MAX_NAME_SIZE] = {0};
	
	
	char expected[MAX_NAME_SIZE] = {0};
	strcpy(expected, " CARLOS   MANUEL GUERREIRO  PESSOA  ");
	
	name_all_upper(long_name, result);
	TEST_ASSERT_EQUAL_INT8_ARRAY(expected, result, MAX_NAME_SIZE);
}


// count_words tests

void test_name_count_words_of_empty_name() {
	char name[] = { "          " };
	int expected = 0, result;
	
 	
	result = count_words(name);
	TEST_ASSERT_EQUAL_INT(expected, result);
}

void test_name_count_words_of_short_name() {
	char name[] = "  little  ";
	int expected = 1, result;
	
 	
	result = count_words(name);
	TEST_ASSERT_EQUAL_INT(expected, result);
}

void test_name_count_words_of_long_name_with_spaces() {
	char name[] = " carlos   manuel guerreiro  pessOA  ";
	int expected = 4, result;
	
 	
	result = count_words(name);
	TEST_ASSERT_EQUAL_INT(expected, result);
}

void test_name_count_words_of_long_name_without_spaces() {
	char name[] = "carlos manuel guerreiro pessOA";
	int expected = 4, result;
	
 	
	result = count_words(name);
	TEST_ASSERT_EQUAL_INT(expected, result);
}

// name_trimmed  tests

void test_name_trimmed_of_empty_name() {
	char name[] = { "          " };
	char expected[] =  {'\0'};
	char result[MAX_NAME_SIZE];
	int expected2=0;
 	
	int result2 = name_trimmed(name, result);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	TEST_ASSERT_EQUAL_INT(expected2, result2);
}

void test_name_trimmed_of_short_name() {
	char name[] = "  little  ";
	char expected[] = "little";
	char result[MAX_NAME_SIZE];
	int expected2 = strlen(expected);
 	
	int result2 = name_trimmed(name, result);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	TEST_ASSERT_EQUAL_INT(expected2, result2);
}

void test_name_trimmed_of_long_name() {
	char name[] = " carlos   manuel guerreiro  pessOA  ";
	char expected[MAX_NAME_SIZE] = {0};
	strcpy(expected, "carlos manuel guerreiro pessOA");
	
	 
	char result[MAX_NAME_SIZE] = {0};
	int expected2 = strlen(expected);
 	
	int result2 = name_trimmed(name, result);
	TEST_ASSERT_EQUAL_INT8_ARRAY(expected, result, MAX_NAME_SIZE);
	TEST_ASSERT_EQUAL_INT(expected2, result2);
}

// name_first_upper tests

void test_name_first_upper_of_empty_name() {
	char name[] = { "          " };
	char expected[] =  {'\0'};
	char result[MAX_NAME_SIZE] = { 'X' };
 	
	name_first_upper(name, result);
	TEST_ASSERT_EQUAL_STRING(expected, result);
}

void test_name_first_upper_of_short_name() {
	char name[] = "  liTTle  ";
	char expected[] = "Little";
	char result[MAX_NAME_SIZE];
	 	
	name_first_upper(name, result);
	TEST_ASSERT_EQUAL_STRING(expected, result); 
}

void test_name_first_upper_of_long_name() {
	char name[] = " carloS   MAnuel gueRReiro  pessOA  ";
	char expected[MAX_NAME_SIZE] = {0};
	strcpy(expected, "Carlos Manuel Guerreiro Pessoa");
	
	 
	char result[MAX_NAME_SIZE] = {0};
	 	
	name_first_upper(name, result);
	TEST_ASSERT_EQUAL_INT8_ARRAY(expected, result, MAX_NAME_SIZE); 
}


// name_compressed tests
void test_name_compressed_of_empty_name() {
	char name[] = { "          " };
	char expected[MAX_NAME_SIZE] =  { };
	char result[MAX_NAME_SIZE] = { };
  
 	
	TEST_ASSERT_FALSE(name_compressed(name, result));
	TEST_ASSERT_EQUAL_INT8_ARRAY(expected, result, MAX_NAME_SIZE); 
}

void test_name_compressed_of_short_name() {
	char name[] = "  liTTle  ";
	char expected[MAX_NAME_SIZE] =  { };
	char result[MAX_NAME_SIZE] = { };
  
 	
	TEST_ASSERT_FALSE(name_compressed(name, result));
	TEST_ASSERT_EQUAL_INT8_ARRAY(expected, result, MAX_NAME_SIZE); 
}

void test_name_compressed_of_long_name_no_spaces() {
	char name[] = "carlos manuel guerreiro pessOA";
	char expected[MAX_NAME_SIZE] =  "Pessoa C.";
	char result[MAX_NAME_SIZE] = { };
  
 	
	TEST_ASSERT_TRUE(name_compressed(name, result));
	TEST_ASSERT_EQUAL_STRING(expected, result); 
}

void test_name_compressed_of_long_name_with_spaces() {
	char name[] = "  carlos  manuel      guerreiro pessOA     ";
	char expected[MAX_NAME_SIZE] =  "Pessoa C.";
	char result[MAX_NAME_SIZE] = { };
  
 	
	TEST_ASSERT_TRUE(name_compressed(name, result));
	TEST_ASSERT_EQUAL_STRING(expected, result); 
}

// name_middle_compressed tests
void test_name_middle_compressed_of_empty_name() {
	char name[] = { "          " };
	char expected[MAX_NAME_SIZE] =  { };
	char result[MAX_NAME_SIZE] = { };
  
 	
	TEST_ASSERT_FALSE(name_middle_compressed(name, result));
	TEST_ASSERT_EQUAL_INT8_ARRAY(expected, result, MAX_NAME_SIZE); 
}

void test_name_middle_compressed_of_short_name() {
	char name[] = "  liTTle  ";
	char expected[MAX_NAME_SIZE] =  { };
	char result[MAX_NAME_SIZE] = { };
  
 	
	TEST_ASSERT_FALSE(name_middle_compressed(name, result));
	TEST_ASSERT_EQUAL_INT8_ARRAY(expected, result, MAX_NAME_SIZE); 
}

void test_name_middle_compressed_of_long_name_no_spaces() {
	char name[] = "carlos manuel guerreiro pessOA";
	char expected[MAX_NAME_SIZE] =  "Carlos M. G. Pessoa";
	char result[MAX_NAME_SIZE] = { };
  
 	
	TEST_ASSERT_TRUE(name_middle_compressed(name, result));
	TEST_ASSERT_EQUAL_STRING(expected, result); 
}

void test_name_middle_compressed_of_long_name_with_spaces() {
	char name[] = "  carlos  manuel      guerreiro pessOA     ";
	char expected[MAX_NAME_SIZE] =  "Carlos M. G. Pessoa";
	char result[MAX_NAME_SIZE] = { };
  
 	
	TEST_ASSERT_TRUE(name_middle_compressed(name, result));
	TEST_ASSERT_EQUAL_STRING(expected, result); 
}





int main() {
	BEGIN_TESTS();
	
	// name_all_upper testes
 
	RUN_TEST(test_name_all_upper_of_empty_name);
	RUN_TEST(test_name_all_upper_of_short_name);
	RUN_TEST(test_name_all_upper_of_long_name);
	 
	
	// count_words tests
	RUN_TEST(test_name_count_words_of_empty_name);
	RUN_TEST(test_name_count_words_of_short_name);
	RUN_TEST(test_name_count_words_of_long_name_with_spaces);
	RUN_TEST(test_name_count_words_of_long_name_without_spaces);
	
	// name_trimmed  tests
	RUN_TEST(test_name_trimmed_of_empty_name);
	RUN_TEST(test_name_trimmed_of_short_name);
	RUN_TEST(test_name_trimmed_of_long_name);
	
	// name_first_upper tests
	RUN_TEST(test_name_first_upper_of_empty_name);
	RUN_TEST(test_name_first_upper_of_short_name);
	RUN_TEST(test_name_first_upper_of_long_name);
 
	// name_compressed tests
	RUN_TEST(test_name_compressed_of_empty_name);
	RUN_TEST(test_name_compressed_of_short_name);
	RUN_TEST(test_name_compressed_of_long_name_no_spaces);
	RUN_TEST(test_name_compressed_of_long_name_with_spaces);
	
	// name_middle_compressed tests
	RUN_TEST(test_name_middle_compressed_of_empty_name);
	RUN_TEST(test_name_middle_compressed_of_short_name);
	RUN_TEST(test_name_middle_compressed_of_long_name_no_spaces);
	RUN_TEST(test_name_middle_compressed_of_long_name_with_spaces);

	END_TESTS();
	return 0;
}
	




