#ifndef ENIA_H_INCLUDED
#define ENIA_H_INCLUDED
#include "structures.h"

void updateVehicleAndClient(char* plateNumber, char* clientID) {
    FILE* vehiclesFile = fopen("vehicles.txt", "r");
    if (vehiclesFile == NULL) {
        printf("Cannot open the vehicles file!\n");
        return;
    }

    FILE* tempVehiclesFile = fopen("temp_vehicles.txt", "w");
    if (tempVehiclesFile == NULL) {
        printf("Cannot create temporary file!\n");
        fclose(vehiclesFile);
        return;
    }

    char line[100];
    char currPlateNumber[10];
    int foundVehicle = 0;

    while (fgets(line, sizeof(line), vehiclesFile)) {
    sscanf(line, "%s", currPlateNumber);

    if (strcmp(currPlateNumber, plateNumber) == 0) {
        char* lastSpace = strrchr(line, ' ');
        if (lastSpace == NULL) {
            printf("Invalid format in vehicles file!\n");
            fclose(vehiclesFile);
            fclose(tempVehiclesFile);
            remove("temp_vehicles.txt");
            return;
        }

        int value;
        sscanf(lastSpace, " %d", &value);

        value++;

        char incrementedValue[10];
        sprintf(incrementedValue, " %d\n", value);

        strncpy(lastSpace, incrementedValue, sizeof(line) - (lastSpace - line));

        foundVehicle = 1;
    }

    fprintf(tempVehiclesFile, "%s", line);
}

fclose(vehiclesFile);
fclose(tempVehiclesFile);

    if (!foundVehicle) {
        printf("Vehicle with plate number %s not found in the vehicles list!\n", plateNumber);
        remove("temp_vehicles.txt");
        return;
    }

    if (remove("vehicles.txt") == 0) {
        if (rename("temp_vehicles.txt", "vehicles.txt") != 0) {
            printf("Error renaming the temporary file!\n");
        }
    } else {
        printf("Error deleting the vehicles file!\n");
        remove("temp_vehicles.txt");
    }

    FILE* clientsFile = fopen("clients.txt", "r");
    if (clientsFile == NULL) {
        printf("Cannot open the clients file!\n");
        return;
    }

    FILE* tempClientsFile = fopen("temp_clients.txt", "w");
    if (tempClientsFile == NULL) {
        printf("Cannot create temporary file!\n");
        fclose(clientsFile);
        return;
    }

    char currClientID[10];
    int foundClient = 0;

    while (fgets(line, sizeof(line), clientsFile)) {
        sscanf(line, "%s", currClientID);

        if (strcmp(currClientID, clientID) == 0) {
            char* lastSpace = strrchr(line, ' ');
            if (lastSpace == NULL) {
                printf("Invalid format in clients file!\n");
                fclose(clientsFile);
                fclose(tempClientsFile);
                remove("temp_clients.txt");
                return;
            }

            int value;
            sscanf(lastSpace, " %d", &value);

            value++;

            snprintf(lastSpace, sizeof(line) - (lastSpace - line), " %d\n", value);

            foundClient = 1;
        }

        fprintf(tempClientsFile, "%s", line);
    }

    fclose(clientsFile);
    fclose(tempClientsFile);

    if (!foundClient) {
        printf("Client with ID %s not found in the clients list!\n", clientID);
        remove("temp_clients.txt");
        return;
    }

    if (remove("clients.txt") == 0) {
        if (rename("temp_clients.txt", "clients.txt") != 0) {
            printf("Error renaming the temporary file!\n");
        }
    } else {
        printf("Error deleting the clients file!\n");
        remove("temp_clients.txt");
    }
}

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
            sscanf(line, "%*s %*d %*[^0-9]%f", &dailyPrice);
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
    } else if (option == 2) {
        if (newReservation->nrOfDays >= 7 && newReservation->nrOfDays < 14) {
            newReservation->totalPrice = dailyPrice * newReservation->nrOfDays * 0.9;
            printf("Total price: %.2f\n", newReservation->totalPrice);
        } else if (newReservation->nrOfDays >= 14 && newReservation->nrOfDays < 30) {
            newReservation->totalPrice = dailyPrice * newReservation->nrOfDays * 0.85;
            printf("Total price: %.2f\n", newReservation->totalPrice);
        } else if (newReservation->nrOfDays >= 30) {
            newReservation->totalPrice = dailyPrice * newReservation->nrOfDays * 0.8;
            printf("Total price: %.2f\n", newReservation->totalPrice);
        } else {
            printf("Invalid number of days for discount!\n");
            return;
        }
    } else {
        printf("Invalid option!\n");
        return;
    }

    newReservation->nextReserve = NULL;

    if (*head == NULL) {
        *head = newReservation;
        *tail = newReservation;
    } else {
        (*tail)->nextReserve = newReservation;
        *tail = newReservation;
    }

    FILE* reservationsFile = fopen("reservations.txt", "a");
    if (reservationsFile == NULL) {
        printf("Cannot open the reservations file!\n");
        return;
    } else {
        fprintf(reservationsFile, "%d %s %s %s %d %.2f\n", newReservation->ID, newReservation->date,
                newReservation->clientID, newReservation->plateNumber, newReservation->nrOfDays,
                newReservation->totalPrice);
        fclose(reservationsFile);
    }

    FILE* availableVehiclesFile = fopen("available_vehicles.txt", "r");
    if (availableVehiclesFile == NULL) {
        printf("Cannot open the available vehicles file!\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Cannot create temporary file!\n");
        fclose(availableVehiclesFile);
        return;
    }

    char plateNum[100];
    int plateNumMatch = 0;

    while (fgets(line, sizeof(line), availableVehiclesFile)) {
        sscanf(line, "%s", plateNum);

        if (strcmp(plateNum, newReservation->plateNumber) == 0) {
            plateNumMatch = 1;
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(availableVehiclesFile);
    fclose(tempFile);

    if (!plateNumMatch) {
        printf("Vehicle with plate number %s not found in the available vehicles list!\n", newReservation->plateNumber);
        remove("temp.txt");
        return;
    }

    if (remove("available_vehicles.txt") == 0) {
        if (rename("temp.txt", "available_vehicles.txt") != 0) {
            printf("Error renaming the temporary file!\n");
        }
    } else {
        printf("Error deleting the available vehicles file!\n");
        remove("temp.txt");
    }

    updateVehicleAndClient(newReservation->plateNumber, newReservation->clientID);
}

void addVehicleToList(char* plateNumber) {
    FILE* vehiclesFile = fopen("vehicles.txt", "r");
    FILE* availableVehiclesFile = fopen("available_vehicles.txt", "a");

    if (vehiclesFile == NULL || availableVehiclesFile == NULL) {
        printf("Error opening files!\n");
        return;
    }

    char line[256];
    char currPlateNumber[10];
    int plateNumberMatch = 0;

    while (fgets(line, sizeof(line), vehiclesFile)) {
        sscanf(line, "%s", currPlateNumber);

        if (strcmp(currPlateNumber, plateNumber) == 0) {
            fprintf(availableVehiclesFile, "%s", line);
            plateNumberMatch = 1;
            break;
        }
    }

    fclose(vehiclesFile);
    fclose(availableVehiclesFile);

    if (!plateNumberMatch) {
        printf("Vehicle with plate number %s not found in the vehicles list!\n", plateNumber);
    }
}

void deleteReservation(int reservationID) {
    FILE* reservationsFile = fopen("reservations.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");

    if (reservationsFile == NULL || tempFile == NULL) {
        printf("Error opening files!\n");
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), reservationsFile)) {
        int id;
        sscanf(line, "%d", &id);

        if (id != reservationID) {
            fprintf(tempFile, "%s", line);
        } else {
            found = 1;
            char plateNumber[10];
            sscanf(line, "%*d %*s %*s %s", plateNumber);
            addVehicleToList(plateNumber);
        }
    }

    fclose(reservationsFile);
    fclose(tempFile);

    if (!found) {
        printf("Reservation with ID %d not found.\n", reservationID);
        remove("temp.txt");
        return;
    }

    remove("reservations.txt");
    rename("temp.txt", "reservations.txt");

    printf("Reservation with ID %d deleted.\n", reservationID);
}


#endif // ENIA_H_INCLUDED
