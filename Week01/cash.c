#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Get user to input the amount of change owed
    float dollars;
    do
    {
        dollars = get_float("Amount of Change Due: ");
    }
    while (dollars < 0);

    // Convert the dollars to cents
    int cent = round(dollars * 100);

    // Start counting from 0
    int count = 0;

    // As long as change owed is more than 25 cents
    while (cent >= 25)
    {
        cent = cent - 25;
        count++;
    }

    // As long as change owed is more than 10 cents
    while (cent >= 10)
    {
        cent = cent - 10;
        count++;
    }

    //As long as change owed is more than 5 cents
    while (cent >= 5)
    {
        cent = cent - 5;
        count++;
    }

    // As long as change is more than 1 cent
    while (cent >= 1)
    {
        cent = cent - 1;
        count++;
    }
    printf("%i\n", count);
}