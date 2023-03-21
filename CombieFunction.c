#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PEOPLE 100
#define MAX_APPOINTMENTS 10

struct Date_want_to_meet
{
    char day[10];
    int hour;
    int minute;
};

struct Person
{
    char name[100];
    char dob[11];
    int sum_dob;
    int num_appointments;
    struct Date_want_to_meet appointments[MAX_APPOINTMENTS];
};

typedef enum
{
    false = 0,
    true = 1
} bool;
int sum_dob(char *dob)
{
    int dd = atoi(strtok(dob, "/"));
    int mm = atoi(strtok(NULL, "/"));
    int yyyy = atoi(strtok(NULL, "/"));

    return dd + mm + yyyy;
}
void input_person(struct Person people[], int *num_people)
{
    printf("Name: ");
    scanf(" %[^\n]s", people[*num_people].name);
    printf("Date of Birth (DD/MM/YYYY): ");
    scanf("%s", people[*num_people].dob);
    people[*num_people].sum_dob = sum_dob(people[*num_people].dob);
    int num_appointments = 0;
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
            strcpy(people[*num_people].appointments[i].day, "Monday");
        else if (strcmp(day, "Tuesday") == 0)
            strcpy(people[*num_people].appointments[i].day, "Tuesday");
        else if (strcmp(day, "Wednesday") == 0)
            strcpy(people[*num_people].appointments[i].day, "Wednesday");
        else if (strcmp(day, "Thursday") == 0)
            strcpy(people[*num_people].appointments[i].day, "Thursday");
        else if (strcmp(day, "Friday") == 0)
            strcpy(people[*num_people].appointments[i].day, "Friday");
        else if (strcmp(day, "Saturday") == 0)
            strcpy(people[*num_people].appointments[i].day, "Saturday");
        else if (strcmp(day, "Sunday") == 0)
            strcpy(people[*num_people].appointments[i].day, "Sunday");
        else
        {
            printf("Invalid input for day. Appointment not scheduled.\n");
            continue;
        }
        people[*num_people].appointments[i].hour = hour;
        people[*num_people].appointments[i].minute = minute;
        people[*num_people].num_appointments++;
    }
    (*num_people)++;
}

int good_hour(int sum_dob, int hour)
{
    int good_hours[] = {0, 1, 2, 3};
    int num_good_hours = sizeof(good_hours) / sizeof(good_hours[0]);
    int remainder = sum_dob % num_good_hours;
    return hour >= 0 && hour <= 23 && (hour % 4) == good_hours[remainder];
}
void print_good_times(struct Person *people, int num_people)
{
    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    struct Person valid_appointments[7][MAX_PEOPLE] = {0};
    int num_valid_appointments[7] = {0};
    bool has_valid_hour = false;

    for (int i = 0; i < num_people; i++)
    {
        struct Person p = people[i];

        for (int j = 0; j < p.num_appointments; j++)
        {
            int day_index = -1;
            for (int k = 0; k < 7; k++)
            {
                if (strcmp(p.appointments[j].day, days[k]) == 0)
                {
                    day_index = k;
                    break;
                }
            }

            if (day_index != -1 && good_hour(sum_dob(p.name), p.appointments[j].hour))
            {
                valid_appointments[day_index][num_valid_appointments[day_index]] = p;
                num_valid_appointments[day_index]++;
                has_valid_hour = true;
            }
        }
    }

    if (!has_valid_hour)
    {
        printf("Sorry, no valid appointment times found.\n");
        return;
    }

    for (int i = 0; i < 7; i++)
    {
        if (num_valid_appointments[i] > 0)
        {
            printf("%s:\n", days[i]);
            for (int j = 0; j < num_valid_appointments[i]; j++)
            {
                struct Person p = valid_appointments[i][j];
                printf("%s (DOB: %s) - %02d:%02d\n", p.name, p.dob, p.appointments[0].hour, p.appointments[0].minute);
            }
        }
    }
}
void schedule_appointments(struct Person people[], int num_people, struct Person appointments[], int *num_appointments)
{
    for (int i = 0; i < num_people; i++)
    {
        for (int j = 0; j < people[i].num_appointments; j++)
        {
            if (strcmp(appointments[i].appointments[j].day, people[i].appointments[j].day) == 0 &&
                appointments[i].appointments[j].hour == people[i].appointments[j].hour &&
                appointments[i].appointments[j].minute == people[i].appointments[j].minute)
            {
                appointments[*num_appointments] = people[i];
                (*num_appointments)++;
            }
        }
    }
}


void print_appointments(struct Person *appointments, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s wants to meet on %s at %02d:%02d\n",
               appointments[i].name,
               appointments[i].appointments->day, appointments[i].appointments->hour,
               appointments[i].appointments->minute);
    }
}

void nhapPhimBatKy(){
    printf("\nNhap phim bat ky de tiep tuc!");
    getch();
}

int main()
{
    struct Person people[MAX_PEOPLE];
    struct Person appointments[MAX_APPOINTMENTS];
    int n = 0;
    int num_appointments = 0;
    int chon;
    do
    {
        printf("\nMENU:");
        printf("\n1- In ra nhieu lich hen");
        printf("\n2- in ra lich hen");
        printf("\n3- in ra lich hen cua tung nguoi");
        scanf("%d", &chon);
        switch (chon)
        {
        case 1:
            input_person(people, &n);
            nhapPhimBatKy();
            break;
        case 2:
            schedule_appointments(people, n, appointments, &num_appointments);
            print_appointments(appointments, num_appointments);
            nhapPhimBatKy();
            break;
        case 3:
            print_good_times(people, n);
            nhapPhimBatKy();
            break;
        }
    } while (chon != 0);
    return 0;
}