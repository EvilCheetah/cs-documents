#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "bounded-list.h"

enum class Operation {
    Spec,
    Insert,
    Remove,
};


struct Command {
    Operation operation;
    Side      side      = Side::Back;
    long      size      = -1;
    char      character = '\0';
};


std::optional<Operation> parse_operation(std::string_view name);
std::optional<Side>      parse_side     (std::string_view suffix);


// Grammar:
//   command   ::= ws* ( spec_cmd | insert_cmd | remove_cmd ) ws*
//
//   spec_cmd   ::= "spec" ws+ integer
//   insert_cmd ::= "insert" "-" side ws+ char
//   remove_cmd ::= "remove" "-" side
//
//   side       ::= "front" | "back"
//   integer    ::= [ "-" ] digit { digit }
//   digit      ::= "0" | "1" | ... | "9"
//   char       ::= any single printable, non-whitespace character
//   ws         ::= " " | "\t"
std::optional<Command>   parse_command  (const std::string& line);

