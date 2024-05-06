#include <stdio.h>
#include <string.h>
#include "actions.h"

char *gap(float jarak)
{
    if (jarak < 3.5)
        return "Gogogo";
    else if (jarak > 3.5 && jarak <= 10)
        return "Push";
    else
        return "Stay out of trouble";
}

char *fuel(int sisaBensin)
{
    if (sisaBensin > 80)
        return "Push Push Push";
    else if (sisaBensin >= 50 && sisaBensin <= 80)
        return "You can go";
    else
        return "Conserve Fuel";
}

char *tire(int sisaBan)
{
    if (sisaBan > 80)
        return "Go Push Go Push";
    else if (sisaBan >= 50 && sisaBan <= 80)
        return "Good Tire Wear";
    else if (sisaBan >= 30 && sisaBan < 50)
        return "Conserve Your Tire";
    else
        return "Box Box Box";
}

char *tireChange(char *tipeBan)
{
    if (strcmp(tipeBan, "Soft") == 0)
        return "Mediums Ready";
    else
        return "Box for Softs";
}
