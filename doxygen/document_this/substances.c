#include "substances.h"

static double min(double a, double b){
    return (a < b ? a : b);
}

inline double substances_calculate_alcohol_dose(Person * p_person){
    return 0.0;
}

double substances_calculate_MDMA_dose(Person * p_person){

    // A "linear dose" in milligrams; 1.5 mg/kg * body_mass
    double linear_dose = 1.5 * p_person->body_mass;

    // A "safer dose" that heavier people with a "normal" or
    // "fast" metabolism should opt for if the linear dose
    // exceeds this one. Given in milligrams.
    double threshold_dose = 50 + p_person->body_mass;

    // The "safest dose" (except for no dose), that should
    // always be the upper limit for people with a "slow"
    // metabolism, regardless of body mass.
    // Given in milligrams.
    double safest_dose = 120;

    double mdma_dose;
    if(p_person->metabolism == METABOLISM_SLOW){
        mdma_dose = min(linear_dose, safest_dose);
    }
    else{
        mdma_dose = min(linear_dose, threshold_dose);
    }

    return mdma_dose;
}
