#include <stdlib.h>
#include <string.h>

#define string char*
#define boolean int

#define true 1
#define false 0

typedef struct SkillList SkillList;
typedef struct SkillListNode SkillListNode;

typedef struct SkillDependencyList SkillDependencyList;
typedef struct SkillDependencyListNode SkillDependencyListNode;

typedef struct Skill Skill;

struct SkillList {
    SkillListNode* head;
    SkillListNode* tail;
};

struct SkillListNode {
    Skill* value;
    SkillListNode* next;
};

struct SkillDependencyList {
    SkillDependencyListNode* head;
    SkillDependencyListNode* tail;
};

struct SkillDependencyListNode {
    Skill* skill;
    int required_level;
    SkillDependencyListNode* next;
};

struct Skill {
    string name;
    int level;
    int max_level;

    SkillDependencyList* dependencies;
};

SkillList* create_skill_list() {
    SkillList* skills = malloc(sizeof(SkillList));
    
    skills->head = NULL;
    skills->tail = NULL;

    return skills;
}

SkillListNode* create_skill_node(Skill* value) {
    SkillListNode* node = malloc(sizeof(SkillListNode));

    node->value = value;
    node->next = NULL;

    return node;
}

SkillDependencyList* create_skill_dependency_list() {
    SkillDependencyList* dependencies = malloc(sizeof(SkillDependencyList));
    
    dependencies->head = NULL;
    dependencies->tail = NULL;

    return dependencies;
}

SkillDependencyListNode* create_skill_dependency_node(Skill* skill, int required_level) {
    SkillDependencyListNode* node = malloc(sizeof(SkillDependencyListNode));

    node->skill = skill;
    node->required_level = required_level;
    node->next = NULL;

    return node;
}

Skill* create_skill(string name, int max_level) {
    Skill* skill = malloc(sizeof(Skill));

    skill->name = name;
    skill->level = 0;
    skill->max_level = max_level;
    skill->dependencies = create_skill_dependency_list();

    return skill;
}

Skill* find_skill(SkillList* skills, string name) {
    SkillListNode* current = skills->head;

    while (current != NULL) {
        if(strcmp(current->value->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }

    printf("Cannot find skill \"%s\"!\n", name);
    return NULL;
}

void add(SkillList* skills, Skill* skill) {
    SkillListNode* node = create_skill_node(skill);

    SkillListNode* tail = skills->tail;

    if (tail == NULL) {
        skills->head = skills->tail = node;
    } else {
        tail->next = node;
        skills->tail = node;
    }
}

void add_dependency(Skill* skill, Skill* dependency, int required_level) {
    SkillDependencyList* dependencies = skill->dependencies;

    SkillDependencyListNode* node = create_skill_dependency_node(dependency, required_level);

    SkillDependencyListNode* tail = dependencies->tail;

    if (tail == NULL) {
        dependencies->head = dependencies->tail = node;
    } else {
        tail->next = node;
        dependencies->tail = node;
    }
}

void print_dependencies(SkillDependencyList* dependencies) {
    SkillDependencyListNode* dependency = dependencies->head;
    while (dependency != NULL) {
        printf("%s %d\n", dependency->skill->name, dependency->required_level);
        dependency = dependency->next;
    }
}

void print_skill(Skill* skill) {
    printf("- %s %d\n", skill->name, skill->level);
}

void print_skills(SkillList* skills) {
    SkillListNode* current = skills->head;
    while (current != NULL) {
        if (current->value->level > 0) {
            print_skill(current->value);
        }
        current = current->next;
    }
}

boolean unlocked(Skill* skill) {
    SkillDependencyListNode* dependency = skill->dependencies->head;

    while (dependency != NULL) {
        if (dependency->skill->level < dependency->required_level) {
            return false;
        }
        dependency = dependency->next;
    }

    return true;
}

int allocate_points(Skill* skill, int target_level) {
    int points_used = 0;

    SkillDependencyList* dependencies = skill->dependencies;

    while ( ! unlocked(skill)) {
        SkillDependencyListNode* dependency = dependencies->head;

        while (dependency != NULL) {
            points_used += allocate_points(dependency->skill, dependency->required_level);
            dependency = dependency->next;
        }
    }

    if (skill->level < target_level) {
        points_used += target_level - skill->level;
        skill->level = target_level;
    }

    return points_used;
}

