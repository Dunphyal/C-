// Date - 12/11/2016
// Student Name - Alex Dunphy
// Student Number - 12303659

#include <stdio.h>
#include <stdlib.h>

int probe = 0;

void swap(int *array, int x, int y) { //swap function
	int temp = array[x];              //stores the x value in a temp variable
	array[x] =array[y];
	array[y] = temp;                  //use the temp value to assign y the original x value
}

void selection_sort(int *array, int size) {   // elementary selection sort
	
	for (int k = 0; k < size-1; k++) {  //for loop cycles through the array leaving out the last value as the list should be sorted by this point
		int current_pos = k;
		int min_val = k;                //set the current position as the beginning minimum value
		for (int i = k; i < size; i++) {  //for loop cycles from the current position in the array to the end
			probe++;
			if (array[i] < array[min_val]) {  
				min_val = i;            // if the current value (i) is less than the minimum value, i becomes the minimum value
			}
		}
		swap(array, k, min_val);        // the swap function is called to switch the value of current position in the outer for loop with the value of min_val
	}
}

void print(int*array, int size) {

	for (int i = 0; i < size; i++) {
		printf("%i ", array[i]);
	}
	printf("\n");
}

void make_array(int*array,int*array2,int size) {  //function to fill the array with random values
	for (int i = 0; i < size; i++) {
		array[i] = rand()%30;
		array2[i] = array[i];                     //second array acts as a duplicate to ensure that the array for each sort method is identical
	}
}

int partition(int*array, int first, int last) { //partition fucntion 
	int x = array[last];
	int i = first - 1;
	for (int j = first; j < last; j++) {
		probe++;
		if (array[j] <= x) {
			i++; 
			swap(array, i, j);                  //all values less than the value in the last position are moved to the left of the prospective pivot   
		}
	}
	swap(array, i + 1, last);                   //the first value found to be larger is then switched with the value of last
	return i + 1;                               // returns the value to be used as the pivot point
}

void quicksort(int*array, int first, int last) {           
	if (first < last) {                                  //if statment ensures that if we get down to one value the function will stop
		int pivot_index = partition(array, first, last); //partition function called to provide a mid point which we can use to split the array
		quicksort(array, first, pivot_index - 1);        
		quicksort(array, pivot_index + 1, last);         //array split into two arrays, quicksort called recursively until the if statment isnt satisfied
	}
}

int main() {
	
	const int size = 20;
	int myarray[size];
	int duplicate_array[size];
	make_array(myarray, duplicate_array, size);

	// Unsorted Array
	printf("unsorted array = ");
	print(myarray, size);
	printf("\n");

	// Selection Sort
	selection_sort(myarray, size);
	printf("Selection Sort = ");
	print(myarray, size);
	printf("probes = %i \n\n", probe);
	
	// Quicksort
	probe = 0;
	quicksort(duplicate_array, 0, size-1);      
	printf("Quicksort = ");
	print(duplicate_array, size);
	printf("probes = %i \n\n", probe);

	return 0;
}