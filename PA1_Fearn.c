// Charles Fearn
// Programming Assignment 1
// CSCI 423 Operating Systems
// Dr. Wong
// Description:
// This C program reads a list of integers from a given input file, sorts them in increasing order, 
// and writes the sorted integers to another output file. The program is designed to be run from the 
// command line, accepting two command line arguments: the input file name and the output file name.


#include <stdio.h>
#include <stdlib.h>

// function to bubble sort the array of integers
void bubbleSort(int *arr, int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap if arr[j] is greater than arr[j+1]
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the number of command line arguments is correct
    if (argc != 3) {
        printf("Please provide the input and output text file names as %s name1 name2\n", argv[0]);
        return 1;
    }
    
    // Open input file for reading
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Input file %s cannot be opened.\n", argv[1]);
        return 1;
    }
    
    // Open output file for writing
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        printf("Output file %s cannot be opened.\n", argv[2]);
        fclose(input_file);
        return 1;
    }
    
    // Read integers from input file and store them dynamically
    int *numbers = NULL;
    int capacity = 0;
    int size = 0;
    int num;
    
    while (fscanf(input_file, "%d", &num) == 1) {
        // Resize array if necessary
        if (size >= capacity) {
            capacity += 10; // Increase capacity by 10
            numbers = (int*)realloc(numbers, capacity * sizeof(int));
            if (numbers == NULL) {
                printf("Memory allocation failed.\n");
                fclose(input_file);
                fclose(output_file);
                return 1;
            }
        }
        // Store the read integer
        numbers[size++] = num;
    }
    
    // Close input file
    fclose(input_file);
    
    // Sort the array of integers
    bubbleSort(numbers, size);
    
    // Print sorted integers to stdout and write to output file
    printf("The integers in file %s after sorting:\n", argv[1]);
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
        fprintf(output_file, "%d ", numbers[i]);
    }
    printf("\n");
    
    // Close output file
    fclose(output_file);
    
    // Free dynamically allocated memory
    free(numbers);
    
    return 0;
}
