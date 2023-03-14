#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PEOPLE 100
#define MAX_APPOINTMENTS 7

struct Person {
    char name[100];
    char dob[9];
    struct Date_want_to_meet {
        char day[20];
        int hour;
        int minute;
    } date_want_to_meet;
};

void input_info(struct Person *person) {
    printf("Enter information for person:\n");
    printf("Name: ");
    scanf(" %[^\n]s", person->name);
    printf("Date of birth (DDMMYYYY): ");
    scanf("%s", person->dob);
    printf("Desired meeting day (day dd/mm/yyyy): ");
    scanf(" %[^\n]s", person->date_want_to_meet.day);
    printf("Desired meeting time (HH MM): ");
    scanf("%d %d", &person->date_want_to_meet.hour, &person->date_want_to_meet.minute);
}
void schedule_appointments(struct Person people[], int num_people, struct Person appointments[], int *num_appointments) {
    int i, j;
    for (i = 0; i < num_people; i++) {
        for (j = 0; j < *num_appointments; j++) {
            if (strcmp(appointments[j].date_want_to_meet.day, people[i].date_want_to_meet.day) == 0 &&
                appointments[j].date_want_to_meet.hour == people[i].date_want_to_meet.hour &&
                appointments[j].date_want_to_meet.minute == people[i].date_want_to_meet.minute) {
                printf("Appointment time already taken, cannot schedule.\n");
                break;
            }
        }
        if (j == *num_appointments) {
            appointments[*num_appointments] = people[i];
            (*num_appointments)++;
        }
    }
}
void print_appointments(struct Person *appointments, int num_appointments) {
    printf("\nScheduled appointments:\n");
    for (int i = 0; i < num_appointments; i++) {
        printf("%s (DOB: %s) - %s at %02d:%02d\n", appointments[i].name, appointments[i].dob, appointments[i].date_want_to_meet.day,
               appointments[i].date_want_to_meet.hour, appointments[i].date_want_to_meet.minute);
    }
}
int main() {
    int num_people, num_appointments = 0;
    struct Person people[MAX_PEOPLE];
    struct Person appointments[MAX_APPOINTMENTS];
    printf("Enter the number of people to schedule appointments for: ");
    scanf("%d", &num_people);
    for (int i = 0; i < num_people; i++) {
        input_info(&people[i]);
        int j;
        for (j = 0; j < num_appointments; j++) {
            if (strcmp(appointments[j].date_want_to_meet.day, people[i].date_want_to_meet.day) == 0 &&
                appointments[j].date_want_to_meet.hour == people[i].date_want_to_meet.hour &&
                appointments[j].date_want_to_meet.minute == people[i].date_want_to_meet.minute) {
                printf("Appointment time already taken, cannot schedule.\n");
                break;
            }
        }

        if (j == num_appointments) {
            appointments[num_appointments] = people[i];
            num_appointments++;
        }
    }
    print_appointments(appointments, num_appointments);
    return 0;
}