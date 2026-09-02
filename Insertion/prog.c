#include <stdio.h>
#include <stdlib.h>

// Reference: https://stackoverflow.com/questions/8345581
#define OUTPUT_FORMAT "%.1f\n"


void insertion_sort(float array[], int size);
int  read_values(FILE *file, float *buffer, int size);


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

    // Read Array size
    int size = 0;
    if ( fscanf(file_in, "%d", &size) != 1 || size < 0 )
    {
        fprintf(stderr, "Error: The first line MUST contain a non-negative number representing the array size\n");
        fclose(file_in);
        return 1;
    }

    // Read Array Values
    float *array = malloc((size_t)(size > 0 ? size : 1) * sizeof(float));
    if ( array == NULL || read_values(file_in, array, size) != size )
    {
        fprintf(stderr, "Error: unable to read %d values from %s\n", size, argv[1]);
        free(array);
        fclose(file_in);
        return 1;
    }
    fclose(file_in);

    // Sort the Values
    insertion_sort(array, size);

    // Write Sorted Array
    FILE *file_out = fopen(argv[2], "w");
    if ( !file_out )
    {
        perror(argv[2]);
        free(array);
        return 1;
    }

    fprintf(file_out, "%d\n", size);
    for(int index = 0; index < size; ++index)
    {
        fprintf(file_out, OUTPUT_FORMAT, array[index]);
    }

    // Cleanup
    fclose(file_out);
    free(array);

    return 0;
}


void insertion_sort(float array[], int size)
{
    if ( array == NULL || size < 2 )
    {
        return;
    }

    for (int i = 1; i < size; ++i)
    {
        float key = array[i];
        int j   = i - 1;

        while ( j >= 0 && array[j] > key )
        {
            array[j + 1] = array[j];
            --j;
        }

        array[j + 1] = key;
    }
}


int read_values(FILE *file, float *buffer, int size)
{
    int index;
    for (index = 0; index < size; ++index)
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
