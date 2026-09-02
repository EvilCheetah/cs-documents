#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Reference: https://stackoverflow.com/questions/8345581
#define OUTPUT_FORMAT "%.1lf\n"
#define STD_DEV_FORMAT "%.15lf\n"


int  read_values(FILE *file, double *buffer, int size);
void calculate_stats(
    const double array[], int size,
    double *min,
    double *max,
    double *avg,
    double *std
);


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
    double *array = malloc((size_t)(size > 0 ? size : 1) * sizeof(double));
    if ( array == NULL || read_values(file_in, array, size) != size )
    {
        fprintf(stderr, "Error: unable to read %d values from %s\n", size, argv[1]);
        free(array);
        fclose(file_in);
        return 1;
    }
    fclose(file_in);


    // Write Statistical Data
    FILE *file_out = fopen(argv[2], "w");
    if ( !file_out )
    {
        perror(argv[2]);
        free(array);
        return 1;
    }

    double min,
          max,
          avg,
          std;

    calculate_stats(
        array, size,
        &min, &max, &avg, &std
    );


    fprintf(file_out, "Min: " OUTPUT_FORMAT,  min);
    fprintf(file_out, "Max: " OUTPUT_FORMAT,  max);
    fprintf(file_out, "Avg: " OUTPUT_FORMAT,  avg);
    fprintf(file_out, "Std: " STD_DEV_FORMAT, std);

    // Cleanup
    fclose(file_out);
    free(array);

    return 0;
}


void calculate_stats(
    const double array[], int size,
    double *min, double *max, double *avg, double *std
)
{
    double sum                 = 0.0;
    double sum_of_squared_diff = 0.0;

    *min = *max = *avg = *std = 0.0;

    if ( size <= 0 )
    {
        return;
    }

    *min = *max = array[0];
    for (int index = 0; index < size; ++index)
    {
        if ( array[index] < *min )
        {
            *min = array[index];
        }

        if ( array[index] > *max )
        {
            *max = array[index];
        }

        sum += array[index];
    }

    *avg = sum / size;

    for (int index = 0; index < size; ++index)
    {
        double diff = array[index] - *avg;
        sum_of_squared_diff += diff * diff;
    }

    *std = sqrt(sum_of_squared_diff / size);
}


int read_values(FILE *file, double *buffer, int size)
{
    int index;
    for (index = 0; index < size; ++index)
    {
        // Value Not Read
        // Source: https://stackoverflow.com/questions/28661915
        if ( fscanf(file, "%lf", &buffer[index]) != 1 )
        {
            break;
        }
    }

    return index;
}
