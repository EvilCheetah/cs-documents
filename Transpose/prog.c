#include <stdio.h>
#include <stdlib.h>

// Reference: https://stackoverflow.com/questions/8345581
#define MATRIX_FORMAT "%g"


int  read_matrix    (FILE *file, int rows, int columns, double matrix[rows][columns]);
void write_transpose(FILE *file, int rows, int columns, double matrix[rows][columns]);


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

    // Read Matrix size
    int rows    = 0,
        columns = 0;
    if ( fscanf(file_in, "%d %d", &rows, &columns) != 2 || rows < 0 || columns < 0)
    {
        fprintf(stderr, "Error: The first line MUST contain two non-negative numbers representing rows and columns of a matrix\n");
        fclose(file_in);
        return 1;
    }

    // Allocate Matrix
    // Reference: https://www.geeksforgeeks.org/c/dynamically-allocate-2d-array-c/
    // Solution 6
    double (*matrix)[columns] = calloc(rows, sizeof *matrix);

    // Read Matrix Values from File
    if ( (!matrix && (rows * columns > 0)) || read_matrix(file_in, rows, columns, matrix) != rows * columns )
    {
        fprintf(stderr, "Error: unable to read %d x %d values from %s\n", rows, columns, argv[1]);
        free(matrix);
        fclose(file_in);
        return 1;
    }
    fclose(file_in);


    // Open Output File
    FILE *file_out = fopen(argv[2], "w");
    if ( !file_out )
    {
        perror(argv[2]);
        free(matrix);
        return 1;
    }

    // Write Trasnposed Matrix into the File
    write_transpose(file_out, rows, columns, matrix);

    // Cleanup
    fclose(file_out);
    free(matrix);

    return 0;
}


int read_matrix(FILE *file, int rows, int columns, double matrix[rows][columns])
{
    int count = 0;
    for (int row = 0; row < rows; ++row)
    {
        for (int column = 0; column < columns; ++column)
        {
            if ( fscanf(file, "%lf", &matrix[row][column]) != 1 )
            {
                return count;
            }
            ++count;
        }
    }

    return count;
}


void write_transpose(FILE *file, int rows, int columns, double matrix[rows][columns])
{
    fprintf(file, "%d %d\n", columns, rows);
 
    for (int column = 0; column < columns; ++column)
    {
        for (int row = 0; row < rows; ++row)
        {
            fprintf(file, row == 0 ? MATRIX_FORMAT : " " MATRIX_FORMAT, matrix[row][column]);
        }
        fprintf(file, "\n");
    }
}

