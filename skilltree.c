#include <stdio.h>
#include <stdlib.h>
#include "inputskills.h"

SkillList* read_skills(FILE* file_source) {
    SkillList* skills = create_skill_list();

    int line_count = read_int(file_source);

    for (int i = 0; i < line_count; i++) {
        add(skills, read_skill_details(file_source));
    }

    return skills;
}

void read_skill_dependencies(FILE* file_source, SkillList* skills) {
    int line_count = read_int(file_source);

    for (int i = 0; i < line_count; i++) {
        clean_new_line(file_source);
        string name = read_string_until_pipe(file_source);
        clean_pipe(file_source);
        Skill* dependency = read_skill_details(file_source);

        add_dependency(
                find_skill(skills, name),
                find_skill(skills, dependency->name),
                dependency->max_level
        );
    }
}

int read_skill_targets(FILE* file_source, SkillList* skills, SkillList* allocations) {
    int points_used = 0;

    int line_count = read_int(file_source);

    for (int i = 0; i < line_count; i++) {
        Skill* target = read_skill_details(file_source);
        points_used += allocate_points(
                find_skill(skills, target->name),
                target->max_level,
                allocations
        );
    }

    return points_used;
}

void solve_case(FILE* file_source) {
    SkillList* skills = read_skills(file_source);

    read_skill_dependencies(file_source, skills);

    if (skills_contain_circular_dependencies(skills)) {
        printf("Not possible\n"); 

        return;
    }

    SkillList* allocations = create_skill_list();

    int points_used = read_skill_targets(file_source, skills, allocations);

    printf("%d point/s\n", points_used);

    print_skills(allocations);

    printf("\n");

    free(allocations);
    free(skills);
}

int main() {
    FILE* file_source = fopen("input.txt", "r");

    int case_count = read_int(file_source);

    for (int i = 0; i < case_count; i++) {
        printf("Case #%d: ", i+1);
        solve_case(file_source);
    }

    fclose(file_source);

    printf("\n");

    return 0;
}

