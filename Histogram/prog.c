#include <stdio.h>
#include <ctype.h>

#define NUM_LETTERS 26
#define BAR_MARK    'x'
#define BLANK       ' '


void count_letters(FILE *file, int counts[NUM_LETTERS]);
int  max_count(const int counts[NUM_LETTERS]);
void write_histogram(FILE *file, const int counts[NUM_LETTERS]);


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

    // Count Characters
    int counts[NUM_LETTERS] = {0};
    count_letters(file_in, counts);
    fclose(file_in);

    // Open Output File
    FILE *file_out = fopen(argv[2], "w");
    if ( !file_out )
    {
        perror(argv[2]);
        return 1;
    }

    // Write Histogram
    write_histogram(file_out, counts);

    // Cleanup
    fclose(file_out);

    return 0;
}


void count_letters(FILE *file, int counts[NUM_LETTERS])
{
    int character;
    while ( (character = fgetc(file)) != EOF )
    {
        if ( isalpha(character) )
        {
            counts[tolower(character) - 'a']++;
        }
    }
}


int max_count(const int counts[NUM_LETTERS])
{
    int max = 0;
    for (int index = 0; index < NUM_LETTERS; ++index)
    {
        if ( counts[index] > max )
        {
            max = counts[index];
        }
    }
 
    return max;
}


void write_histogram(FILE *file, const int counts[NUM_LETTERS])
{
    int max = max_count(counts);
 
    for (int level = max; level >= 1; --level)
    {
        int last = NUM_LETTERS - 1;
        while ( counts[last] < level )
        {
            --last;
        }
 
        for (int index = 0; index <= last; ++index)
        {
            fputc(counts[index] >= level ? BAR_MARK : BLANK, file);
        }
        fputc('\n', file);
    }
 
    // Baseline
    for (int index = 0; index < NUM_LETTERS; ++index)
    {
        fputc('_', file);
    }
    fputc('\n', file);
 
    // Letters
    for (int index = 0; index < NUM_LETTERS; ++index)
    {
        fputc('a' + index, file);
    }
    fputc('\n', file);
}

