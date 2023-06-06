#ifndef DANIELA_H_INCLUDED
#define DANIELA_H_INCLUDED
#include "structures.h"

/*
addNewReservation - Works!!!
deleteReservation - To be done
displayReservations - Works!!!
*/

void addNewReservation(struct Reservation** head, struct Reservation** tail) {
    struct Reservation* newReservation = (struct Reservation*)malloc(sizeof(struct Reservation));

    printf("\nPlease enter the data for the new reservation:\n");
    printf("Reservation ID: ");
    scanf("%d", &newReservation->ID);
    printf("Reservation date: ");
    scanf("%s", newReservation->date);
    printf("Client ID: ");
    scanf("%s", newReservation->clientID);
    printf("Vehicle Plate Number: ");
    scanf("%s", newReservation->plateNumber);
    printf("Rent days: ");
    scanf("%d", &newReservation->nrOfDays);

    int option;
    printf("Enter 1 for fixed price or 2 for discount:\n");
    scanf("%d", &option);

    FILE* vehiclesFile = fopen("vehicles.txt", "r");
    if (vehiclesFile == NULL) {
        printf("Cannot open the vehicles file!\n");
        return;
    }

    char line[100];
    char plateNumber[10];
    float dailyPrice = 0.0;
    int plateNumberMatch = 0;

    while (fgets(line, sizeof(line), vehiclesFile)) {
        sscanf(line, "%s", plateNumber);

        if (strcmp(plateNumber, newReservation->plateNumber) == 0) {
            sscanf(line, "%*s %*d %*s %*s %*f %*d %f", &dailyPrice);
            plateNumberMatch = 1;
            break;
        }
    }

    fclose(vehiclesFile);

    if (!plateNumberMatch) {
        printf("Vehicle with plate number %s not found!\n", newReservation->plateNumber);
        return;
    }


    if (option == 1) {
        newReservation->totalPrice = dailyPrice * newReservation->nrOfDays;
        printf("Total price: %.2f\n", newReservation->totalPrice);
    }
    else if (option == 2) {
        if (newReservation->nrOfDays >= 7 && newReservation->nrOfDays < 14) {
            newReservation->totalPrice = dailyPrice * newReservation->nrOfDays * 0.9;
            printf("Total price: %.2f\n", newReservation->totalPrice);
        }
        else if (newReservation->nrOfDays >= 14 && newReservation->nrOfDays < 30) {
            newReservation->totalPrice = dailyPrice * newReservation->nrOfDays * 0.85;
            printf("Total price: %.2f\n", newReservation->totalPrice);
        }
        else if (newReservation->nrOfDays >= 30) {
            newReservation->totalPrice = dailyPrice * newReservation->nrOfDays * 0.8;
            printf("Total price: %.2f\n", newReservation->totalPrice);
        }
        else {
            printf("Invalid number of days for discount!\n");
            return;
        }
    }
    else {
        printf("Invalid option!\n");
        return;
    }

    newReservation->nextReserve = NULL;

    if (*head == NULL) {
        *head = newReservation;
        *tail = newReservation;
    }
    else {
        (*tail)->nextReserve = newReservation;
        *tail = newReservation;
    }

    FILE* reservationsFile = fopen("reservations.txt", "a");
    if (reservationsFile == NULL) {
        printf("Cannot open the reservations file!\n");
        return;
    }
    else {
        fprintf(reservationsFile, "%d %s %s %s %d %.2f\n", newReservation->ID, newReservation->date,
                newReservation->clientID, newReservation->plateNumber, newReservation->nrOfDays,
                newReservation->totalPrice);
        fclose(reservationsFile);
    }

    FILE* availableVehiclesFile = fopen("available_vehicles.txt", "a");
    if (availableVehiclesFile == NULL) {
        printf("Cannot open the available vehicles file!\n");
        return;
    }
    else {
        fprintf(availableVehiclesFile, "%d %s %s %s %d %.2f\n", newReservation->ID, newReservation->date,
                newReservation->clientID, newReservation->plateNumber, newReservation->nrOfDays,
                newReservation->totalPrice);
        fclose(availableVehiclesFile);
    }
}

void displayReservations() {
    FILE* f = fopen("reservations.txt", "r");
    if (f == NULL) {
        printf("Cannot open file 'reservations.txt'!\n");
        return;
    }

    struct Reservation currentReservation;

    while (fscanf(f, "%d %s %s %s %d %f", &currentReservation.ID, currentReservation.date,
                  currentReservation.clientID, currentReservation.plateNumber, &currentReservation.nrOfDays,
                  &currentReservation.totalPrice) == EOF) {
        printf("Reservation ID: %d\n", currentReservation.ID);
        printf("Reservation Date: %s\n", currentReservation.date);
        printf("Client ID: %s\n", currentReservation.clientID);
        printf("Plate Number: %s\n", currentReservation.plateNumber);
        printf("Number of Days: %d\n", currentReservation.nrOfDays);
        printf("Total Price: %.2f\n", currentReservation.totalPrice);
        printf("\n");
    }

    fclose(f);
}

void printTop3Clients() {
    FILE* clientsFile = fopen("clients.txt", "r");
    char client[100];
    int clientCount = 0;
    int reservationCount[100];

    if (clientsFile == NULL) {
        printf("Couldn't open the file \n");
        return;
    }

    while (fgets(client, sizeof(client), clientsFile) != NULL) {
        sscanf(client, "%*d %*s %*s %*s %*s %*s %d", &reservationCount[clientCount]);
        clientCount++;
    }

    for (int i=0; i<clientCount-1; i++) {
        for (int j=0; j<clientCount-i-1; j++) {
            if (reservationCount[j] < reservationCount[j+1]) {
                int temp = reservationCount[j];
                reservationCount[j] = reservationCount[j+1];
                reservationCount[j + 1] = temp;
            }
        }
    }

    printf("Top 3 Clients with Most Reservations:\n");
    rewind(clientsFile);

    int count = 0;

    while (fgets(client, sizeof(client), clientsFile) != NULL && count < 3) {
        printf("%s\n", client);
        count++;
    }

    fclose(clientsFile);
}

#endif // DANIELA_H_INCLUDED
