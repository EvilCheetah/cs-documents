#include <stdio.h>
#include <stdlib.h>

// Reference: https://stackoverflow.com/questions/8345581
#define OUTPUT_FORMAT "%.1f\n"


// Reference:
//      Book Name: Introduction to Algorithms, 4th Edition
//      Authors: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein
//      ISBN: 9780262046305
//      Pages: 36, 39
//      Notes: Proudly Owned
void merge_sort(float array[], int left, int right);
void merge     (float array[], int left, int middle, int right);

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
    merge_sort(array, 0, size - 1);

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


void merge_sort(float array[], int left, int right)
{
    if ( left >= right )
    {
        return;
    }

    // Avoids Integer Overflow
    int middle = left + (right - left) / 2;
    merge_sort(array,    left   , middle);
    merge_sort(array, middle + 1, right );

    merge(array, left, middle, right);
}

void merge(float array[], int left, int middle, int right)
{
    int left_size  = middle - left + 1,
        right_size = right  - middle;

    float temp_left[left_size],
          temp_right[right_size];

    for (int i = 0; i < left_size; ++i)
    {
        temp_left[i] = array[left + i];
    }

    for (int j = 0; j < right_size; ++j)
    {
        temp_right[j] = array[middle + j + 1];
    }


    int i = 0,
        j = 0,
        k = left;

    while ( i < left_size && j < right_size )
    {
        if ( temp_left[i] <= temp_right[j] )
        {
            array[k] = temp_left[i];
            ++i;
        }
        else
        {
            array[k] = temp_right[j];
            ++j;
        }
        ++k;
    }

    while ( i < left_size )
    {
        array[k] = temp_left[i];
        ++i;
        ++k;
    }
    
    while ( j < right_size )
    {
        array[k] = temp_right[j];
        ++j;
        ++k;
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
