#include "skills.h"
#include "input.h"

Skill* read_skill_details(FILE* source) {
    clean_new_line(source);

    string name = read_string(source);
    int level = read_int(source);

    return create_skill(name, level);
}

