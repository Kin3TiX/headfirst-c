#include <stdio.h>
#include <hfcal.h>

void display_calories(float weight, float distance, float coeff)
{
  printf("Weight: %3.2f lbs\n", weight/2.2046);
  printf("Distance: %3.2f miles\n", distance*1.609344);
  printf("Calories burned: %4.2f cal\n", coeff*weight*distance);
}