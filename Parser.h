#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <iostream>
#include <sstream>

static const char *WHITESPACE = " \t\n\r";

class Parser {
   public:
      Parser(std::string line) : operation(""), arg1(""), arg2("") {
         std::stringstream is;
         trim_whitespace(line);
         is.str(line);
         if (is >> operation)
            if (is >> arg1) {
               getline(is, arg2);
               arg2.erase(0, arg2.find_first_not_of(WHITESPACE));
            }
      }
      std::string getOperation() {return operation;};
      std::string getArg1() {return arg1;};
      std::string getArg2() {return arg2;};

      static void trim_whitespace(std::string &s) {
         s.erase(0, s.find_first_not_of(WHITESPACE));
         s.erase(s.find_last_not_of(WHITESPACE) + 1);
      }
   private:
      std::string operation;
      std::string arg1;
      std::string arg2;
};

#endif
