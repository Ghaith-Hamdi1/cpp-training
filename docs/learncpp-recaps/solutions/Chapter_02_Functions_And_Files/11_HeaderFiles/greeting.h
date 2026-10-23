// greeting.h - Forward declarations for greeting functions

#ifndef GREETING_H
#define GREETING_H

#include <string> // Needed because parameters use std::string

void sayHello(const std::string &name);
void sayGoodbye(const std::string &name);

#endif // GREETING_H
