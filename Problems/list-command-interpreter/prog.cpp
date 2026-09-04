// Sources: https://www.youtube.com/watch?v=g9wTzeq0Y-g

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "command.h"
#include "bounded-list.h"



int main(int argc, char *argv[])
{
    if ( argc != 3 )
    {
        std::cerr << "Usage: " << argv[0] << " <input_filename> <output_filename>" << std::endl;
        return 1;
    }


    // Open Input File
    std::ifstream file_in(argv[1]);
    if ( !file_in )
    {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    // Open Output File
    std::ofstream file_out(argv[2]);
    if ( !file_out )
    {
        std::cerr << "Failed to open file: " << argv[2] << std::endl;
        return 1;
    }

    BoundedList list;
    std::string line;

    for (int line_number = 0; std::getline(file_in, line); ++line_number)
    {
        const auto command = parse_command(line);
        if ( !command )
        {
            std::cerr << "Line " << line_number << ": invalid command" << std::endl;
            return 1;
        }

        if ( (line_number == 0) != ( command->operation == Operation::Spec ) )
        {
            std::cerr << "Line " << line_number
                      << ": 'spec' must be exactly the first line" << std::endl;
            return 1;
        }

        std::string rejected;
        switch ( command->operation )
        {
            case Operation::Spec:
                list.set_capacity(command->size);
                break;

            case Operation::Insert:
                if ( !list.insert(command->side, command->character) )
                {
                    rejected = std::string(1, command->character) + '^';
                }
                break;

            case Operation::Remove:
                if ( !list.remove(command->side) )
                {
                    rejected = "()^";
                }
                break;
        }

        std::vector<std::string> tokens;
        for (const char character : list.items())
        {
            tokens.emplace_back(1, character);
        }

        if ( !rejected.empty() )
        {
            if ( command->operation == Operation::Remove || command->side == Side::Front )
            {
                tokens.insert(tokens.begin(), rejected);
            }
            else
            {
                tokens.push_back(rejected);
            }

        }

        file_out << line_number << ": " << list.size() << " |";
        for (const auto& token : tokens )
        {
            file_out << ' ' << token;
        }
        file_out << std::endl;
    }

    return 0;
}

