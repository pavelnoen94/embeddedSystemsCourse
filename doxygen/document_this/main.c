#include <stdio.h>
#include "person.h"
#include "substances.h"
int main(){
    Person * p_person = person_new("Kolbjørn", 80.0, METABOLISM_FAST);

    double recommended_alcohol_dose, recommended_mdma_dose;
    recommended_alcohol_dose = substances_calculate_alcohol_dose(p_person);
    recommended_mdma_dose = substances_calculate_MDMA_dose(p_person);

    printf(
        "If %s were to do drugs, these would be some recommended doses:\n\n",
        p_person->name
    );
    printf("Alcohol: %.2f mg\n", recommended_alcohol_dose);
    printf("MDMA: %.2f mg\n", recommended_mdma_dose);

    person_delete(p_person);

    return 0;
}
