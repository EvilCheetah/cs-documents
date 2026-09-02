#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Reference: https://stackoverflow.com/questions/8345581
#define OUTPUT_FORMAT "%.1f\n"


void swap(float *left, float *right);
void bubble_sort(float array[], int length);
int  read_values(FILE *file, float *buffer, int length);


int main(int argc, char *argv[])
{
    // Check Number of Params
    if ( argc != 3 )
    {
        fprintf(stderr, "Usage: %s <input_filename> <output_filename>\n", argv[0]);
        return 1;
    }

    // Read Input File
    FILE *file_in = fopen(argv[1], "r");
    if ( !file_in )
    {
        perror(argv[1]);
        return 1;
    }

    // Read Array Length
    int length = 0;
    if ( fscanf(file_in, "%d", &length) != 1 || length < 0 )
    {
        fprintf(stderr, "Error: The first line MUST contain a non-negative number representing the array length\n");
        fclose(file_in);
        return 1;
    }

    // Read Array Values
    float *array = malloc((size_t)(length > 0 ? length : 1) * sizeof(float));
    if ( array == NULL || read_values(file_in, array, length) != length )
    {
        fprintf(stderr, "Error: unable to read %d values from %s\n", length, argv[1]);
        free(array);
        fclose(file_in);
        return 1;
    }
    fclose(file_in);

    // Sort the Values
    bubble_sort(array, length);

    // Write Sorted Array
    FILE *file_out = fopen(argv[2], "w");
    if ( !file_out )
    {
        perror(argv[2]);
        free(array);
        return 1;
    }

    fprintf(file_out, "%d\n", length);
    for(int index = 0; index < length; ++index)
    {
        fprintf(file_out, OUTPUT_FORMAT, array[index]);
    }

    // Cleanup
    fclose(file_out);
    free(array);

    return 0;
}


void swap(float *left, float *right)
{
    float temp = *left;
    *left = *right;
    *right = temp;
}


void bubble_sort(float array[], int length)
{
    if ( array == NULL || length < 2 )
    {
        return;
    }
    
    for (int i = 0; i < length - 1; ++i)
    {
        for (int j = 0; j < length - i - 1; ++j)
        {
            if ( array[j] > array[j + 1] )
            {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}


int read_values(FILE *file, float *buffer, int length)
{
    int index;
    for (index = 0; index < length; ++index)
    {
        // Value Not Read
        // Source: https://stackoverflow.com/questions/28661915
        if ( fscanf(file, "%f", &buffer[index]) != 1 )
        {
            break;
        }
    }

    return index;
}
