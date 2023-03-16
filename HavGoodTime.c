#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PEOPLE 100
#define MAX_APPOINTMENTS 7

struct Date_want_to_meet
{
    int day;
    int hour;
    int minute;
};

struct Person
{
    char name[100];
    char dob[9];
    int sum_dob;
    struct Date_want_to_meet date_want_to_meet[10];
    int num_appointments;
};
typedef enum
{
    false = 0,
    true = 1
} bool;

void input_person(struct Person *person)
{
    printf("Name: ");
    scanf(" %[^\n]s", person->name);
    printf("Date of Birth (DD/MM/YYYY): ");
    scanf("%s", person->dob);
    int dd, mm, yyyy;
    sscanf(person->dob, "%d/%d/%d", &dd, &mm, &yyyy);
    person->sum_dob = dd + mm + yyyy;
    int num_appointments;
    printf("How many appointments do you want to schedule? ");
    scanf("%d", &num_appointments);
    if (num_appointments > MAX_APPOINTMENTS)
    {
        printf("Maximum number of appointments exceeded. Only %d appointments will be scheduled.\n", MAX_APPOINTMENTS);
        num_appointments = MAX_APPOINTMENTS;
    }
    for (int i = 0; i < num_appointments; i++)
    {
        printf("Appointment #%d\n", i + 1);
        printf("Date and Time of Appointment (Day Hour:Minute): ");
        char day[10];
        int hour, minute;
        scanf("%s %d:%d", day, &hour, &minute);
        if (strcmp(day, "Monday") == 0)
            person->date_want_to_meet[person->num_appointments].day = 1;
        else if (strcmp(day, "Tuesday") == 0)
            person->date_want_to_meet[person->num_appointments].day = 2;
        else if (strcmp(day, "Wednesday") == 0)
            person->date_want_to_meet[person->num_appointments].day = 3;
        else if (strcmp(day, "Thursday") == 0)
            person->date_want_to_meet[person->num_appointments].day = 4;
        else if (strcmp(day, "Friday") == 0)
            person->date_want_to_meet[person->num_appointments].day = 5;
        else if (strcmp(day, "Saturday") == 0)
            person->date_want_to_meet[person->num_appointments].day = 6;
        else if (strcmp(day, "Sunday") == 0)
            person->date_want_to_meet[person->num_appointments].day = 0;
        else
        {
            printf("Invalid input for day. Appointment not scheduled.\n");
            continue;
        }
        person->date_want_to_meet[person->num_appointments].hour = hour;
        person->date_want_to_meet[person->num_appointments].minute = minute;
        person->num_appointments++;
    }
}

int sum_dob(char *dob)
{
    int dd = atoi(strtok(dob, "/"));
    int mm = atoi(strtok(NULL, "/"));
    int yyyy = atoi(strtok(NULL, "/"));

    return dd + mm + yyyy;
}
int good_hour(int sum_dob, int hour)
{
    int good_hours[] = {0, 1, 2, 3};
    int num_good_hours = sizeof(good_hours) / sizeof(good_hours[0]);
    int remainder = sum_dob % num_good_hours;
    return hour >= 0 && hour <= 23 && (hour % 4) == good_hours[remainder];
}

void print_schedule(struct Person *people, int n)
{
    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    struct Person valid_appointments[MAX_PEOPLE] = {0};
    struct Person invalid_appointments[MAX_PEOPLE] = {0};
    int num_valid_appointments = 0;
    int num_invalid_appointments = 0;
    bool has_valid_hour = false;
    for (int i = 0; i < n; i++)
    {
        struct Person p = people[i];
        int day = p.date_want_to_meet->day;
        int hour = p.date_want_to_meet->hour;
        if (good_hour(p.sum_dob, hour))
        {
            if (day == -1)
                continue;
            if (!has_valid_hour || hour < valid_appointments[0].date_want_to_meet->hour)
            {
                has_valid_hour = true;
                num_valid_appointments = 0;
            }
            if (hour == valid_appointments[0].date_want_to_meet->hour)
            {
                valid_appointments[num_valid_appointments++] = p;
            }
            else
            {
                valid_appointments[0] = p;
                num_valid_appointments = 1;
            }
        }
        else
        {
            if (day != -1)
            {
                invalid_appointments[num_invalid_appointments++] = p;
            }
        }
    }
    printf("\nValid appointments:\n");
    for (int i = 0; i < num_valid_appointments; i++)
    {
        struct Person p = valid_appointments[i];
        printf("%s %d:%02d %s: %s\n", days[p.date_want_to_meet->day], p.date_want_to_meet->hour, p.date_want_to_meet->minute, p.dob, p.name);
    }
    if (num_valid_appointments == 0 && has_valid_hour)
    {
        printf("No valid appointment at this hour.\n");
    }
    if (num_invalid_appointments > 0)
    {
        printf("\nInvalid appointments:\n");
        for (int i = 0; i < num_invalid_appointments; i++)
        {
            struct Person p = invalid_appointments[i];
            printf("%s %d:%02d %s: %s\n", days[p.date_want_to_meet->day], p.date_want_to_meet->hour, p.date_want_to_meet->minute, p.dob, p.name);
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of people : ");
    scanf("%d", &n);
    struct Person people[MAX_PEOPLE];
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter information for person %d:\n", i + 1);
        input_person(&people[i]);
    }
    printf("\nScheduled Appointments:\n");
    print_schedule(people, n);
    return 0;
}