#include <stdio.h>
#include <stdlib.h>

// Reference: https://stackoverflow.com/questions/8345581
#define OUTPUT_FORMAT "%.1f\n"


// Reference:
//      Book Name: Introduction to Algorithms, 4th Edition
//      Authors: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein
//      ISBN: 9780262046305
//      Pages: 183, 184
//      Notes: Proudly Owned
void swap(float *left, float *right);
void quicksort(float array[], int low, int high);
int  partition(float array[], int low, int high);

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
    quicksort(array, 0, size - 1);

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


void swap(float *left, float *right)
{
    float temp = *left;
    *left = *right;
    *right = temp;
}


void quicksort(float array[], int low, int high)
{
    if ( low >= high )
    {
        return;
    }

    // Avoids Integer Overflow
    int pivot_index = partition(array, low, high);
    quicksort(array,      low       ,  pivot_index - 1);
    quicksort(array, pivot_index + 1,       high      );
}

int partition(float array[], int low, int high)
{
    float pivot = array[high];
    int   i     = low;

    for (int j = low; j < high; ++j)
    {
        if ( array[j] <= pivot )
        {
            swap(&array[i], &array[j]);
            ++i;
        }
    }
    swap(&array[i], &array[high]);

    return i;
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
