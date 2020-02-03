#ifndef PERSON_H
#define PERSON_H

/**
 * @file
 * @brief Person class some some cool stuff in it.
 */

/**
 * @brief Grade of Metabolism
 *
 */
typedef enum
{
    /** Fast */
    METABOLISM_FAST,
    /** Normal */
    METABOLISM_NORMAL,
    /** Slow */
    METABOLISM_SLOW
} Metabolism;

/**
 * @brief A structure to represent a person.
 */
typedef struct
{
    char *name;            /** < The person's name */
    double body_mass;      /** < The person's body mass */
    Metabolism metabolism; /** < The person's metabolism rate */
} Person;

/**
 * @brief Allocates memory on the heap and creates a person object.
 * This function dynamically allocate a new person object on the heap
 * Then the name is dynamicly allocated and the person class gets constructed and initialized.
 * @param name @c char*
 * @param body_mass @c double
 * @param metabolism @c Metabolism
 * @see @c Metabolism
 * @return Person*
 */
Person *person_new(char *name, double body_mass, Metabolism metabolism);

/**
 * @brief This function relinquishes the memory of a person object.
 * First the dynamically allocated variable @c name is freed then the rest of the object.
 * @param p_person
 */

void person_delete(Person *p_person);

#endif
