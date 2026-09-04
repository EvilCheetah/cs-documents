#include <optional>
#include <sstream>
#include <string>
#include <string_view>

#include "command.h"
#include "bounded-list.h"


std::optional<Operation> parse_operation(std::string_view name)
{
    if ( name == "spec"   ) return Operation::Spec;
    if ( name == "insert" ) return Operation::Insert;
    if ( name == "remove" ) return Operation::Remove;

    return std::nullopt;
}


std::optional<Side> parse_side(std::string_view suffix)
{
    if ( suffix == "front" ) return Side::Front;
    if ( suffix == "back"  ) return Side::Back;

    return std::nullopt;
}


std::optional<Command> parse_command(const std::string& line)
{
    std::istringstream iss(line);
    std::string        word;

    if ( !(iss >> word) )
    {
        return std::nullopt;
    }

    const std::string_view w  = word;

    const auto dash = w.find('-');
    const auto op   = parse_operation(w.substr(0, dash));
    const auto side = parse_side(
        dash == std::string_view::npos
            ? std::string_view{} // no-dash
            : w.substr(dash + 1) // string after dash
    );

    if ( !op )
    {
        return std::nullopt;
    }

    const bool needs_side = ( *op != Operation::Spec );
    if ( needs_side != side.has_value() )
    {
        return std::nullopt;
    }

    Command command{*op};
    if ( side )
    {
        command.side = *side;
    }

    switch (*op)
    {
        case Operation::Spec:
            if ( !(iss >> command.size) )
            {
                return std::nullopt;
            }
            break;

        case Operation::Insert:
            if ( !(iss >> command.character) )
            {
                return std::nullopt;
            }
            break;

        case Operation::Remove:
            break;
    }

    std::string extra;
    if ( iss >> extra )
    {
        return std::nullopt;
    }

    return command;
}

