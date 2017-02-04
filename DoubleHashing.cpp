
// Alex Dunphy 01/11/2016
// Student Number: 12303659
//


#include <stdio.h> // printf() etc.
#include <string.h> // strcpy(), strlen() etc.

//
// i #define array lengths so i only have to change them in one place
#define NUM_TEST_KEYS 7
#define MAX_KEY_LENGTH 16
#define HASH_TABLE_SIZE_M 17

//
// -- the hash table itself --
char hash_table[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];

//

int hash_function(const char *key, int table_size) {


	int index = 0;
	int count = 1;
	for (int i = 0; i < strlen(key);i++) {
		int j = key[i] * count;
		index = (index + j) % 15;
		count++;
	}

	return index;
}

int second_hash_function(const char *key, int table_size) {


	int index = strlen(key);

	return index;
}

int main() {

	//
	// example: array of test strings to use as keys
	char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH] = {
		"prince adam", "orko", "cringer", "teela", "aleet", "princess adora", "orko"
	};

	//
	printf(
		"     key           table index   probe\n-----------------------------------\n");
	int total_probe = 0;
	for (int i = 0; i < NUM_TEST_KEYS; i++) {
		int probe = 1;
		total_probe++;

		int index = hash_function(test_strings[i], HASH_TABLE_SIZE_M);
		while (hash_table[index][0] != 0) {
			
			int temp_index = second_hash_function(test_strings[i], HASH_TABLE_SIZE_M);
			index = (index + temp_index) % 17;

			probe++;
			total_probe++;
		}
		//add string into hash table position
		strcpy_s(hash_table[index], test_strings[i]);
		
		printf("%16s %6i %10i\n", test_strings[i], index, probe);
		
	}
	printf("%34i\n", total_probe);
	//
	// calculate table load here
	//number of used spaces divided by number of spaces
	
	double load = float(NUM_TEST_KEYS) / float(HASH_TABLE_SIZE_M);
	printf("     load = %f\n", load);

	return 0;
}