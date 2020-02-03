#include "person.h"
#include <stdlib.h>
#include <string.h>

Person *person_new(char *name, double body_mass, Metabolism metabolism)
{
    // First we dynamically allocate a new person
    Person *p_person = (Person *)malloc(sizeof(Person));

    // Then we "construct" the person object.
    // We also allocate extra space for the name of the person,
    // in case the string we got is freed somewhere else.
    // We add 1 to allow for the terminating '\0' byte.
    int name_length = strlen(name) + 1;
    p_person->name = (char *)malloc(name_length * sizeof(char));
    strcpy(p_person->name, name);

    p_person->body_mass = body_mass;
    p_person->metabolism = metabolism;

    // Finally we return a pointer to the newly created person object.
    return p_person;
}

void person_delete(Person *p_person)
{
    free(p_person->name);
    free(p_person);
}
