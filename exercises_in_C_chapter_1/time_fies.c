// Write a program which allows the user to enter two times in 24-hour clock
//format, and computes the length of time between the two, e.g.:

#include <stdio.h>

int main(void)
{
    int start_time_hours, start_time_minutes, end_time_hours, end_time_minutes;
    printf("Enter two times:\n");
    scanf("%i:%i %i:%i", &start_time_hours , &start_time_minutes, &end_time_hours, &end_time_minutes);

    //and what should I do next?
    // 1) Convert to minutes
    // 2) Substract one from the other
    // 3) Add 1,440 minutes if the difference is negative
    // 4) convert back to hours and minutes

    int start_mins, end_mins, difference;
    start_mins = start_time_hours * 60 + start_time_minutes;
    end_mins = end_time_hours * 60 + end_time_minutes;
    difference = end_mins - start_mins;
    if (difference < 0){
        difference += 1440;
    }

    int answer_hours, answer_minutes;
    answer_hours = difference / 60;
    answer_minutes = difference % 60;

    printf("The time difference is %i:%i\n", answer_hours, answer_minutes);
}

