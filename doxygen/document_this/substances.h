#ifndef SUBSTANCES_H
#define SUBSTANCES_H
#include "person.h"
/**
 * @file
 * @brief Advanced subrance algorthims for crazy people.
 *
 * substances contains a collection of algorithms that can help
 * users calculate recomended maximum dose of a collection
 * of substances. Use with caution.
 *
 * Stay safe kids.
 * (You should probably stay away from MDMA alltogether)
 * (But if you don't, at least hydrate)
 */


/**
 * @brief This function calculates a recommended dose of alcohol,
 * based on the information in the supplied person object.
 *
 * We always return no dose at all, because Norway
 * has a pretty bad alcohol culture, and we do not
 * want to contribute to the deterioration of livers
 * around our beautiful country.
 *
 * @note Returns 0.0 always.
 * @param p_person well. It does not matter really what you pass in.
 * @return double
 */
double substances_calculate_alcohol_dose(Person * p_person);

/**
 * @brief This function calculates a recommended dose of MDMA,
based on the information in the supplied person object.
 *
 * First of all, NTNU does not condone the illicit
 * use of prohibited substances, and it is a bit sketchy
 * that the vitass "sort of" gives advice on MDMA doses.
 * So, just to keep things above board: that is not what
 * you should use this program for. However, I think you
 * will all remember doxygen quite a bit better on
 * account of the cheeky content of this assignment ;)
 *
 * @param p_person
 * @return double
 */
double substances_calculate_MDMA_dose(Person * p_person);

#endif
