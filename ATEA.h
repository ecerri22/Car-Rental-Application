#ifndef ATEA_H_INCLUDED
#define ATEA_H_INCLUDED
#include "structures.h"

int cnt=0;

void addNewVehicle(struct Vehicle **head, struct Vehicle **tail)
{
    struct Vehicle *newVehicle = (struct Vehicle*)malloc(sizeof(struct Vehicle));

    printf("\nPlease enter the data for the new vehicle:\n");
    printf("Plate number: ");
    scanf("%s", newVehicle->plate);
    printf("Year: ");
    scanf("%d", &newVehicle->year);
    printf("Model: ");
    scanf("%s", newVehicle->model);
    printf("Fuel Type: ");
    scanf("%s", newVehicle->fuelType);
    printf("Consumption (liters per km): ");
    scanf("%f", &newVehicle->consumption);
    printf("Seats: ");
    scanf("%d", &newVehicle->seats);
    printf("Daily Price: ");
    scanf("%f", &newVehicle->dailyPrice);
    newVehicle->rentCount = 0;

    newVehicle->nextVehicle = NULL;

    if (*head == NULL) //If the list is empty, make the new vehicle the head and tail
    {
        *head = newVehicle;
        *tail = newVehicle;
    }
    else //if not,add the new vehicle at the end of the list
    {
        (*tail)->nextVehicle = newVehicle;
        *tail = newVehicle;
    }

    printf("New vehicle added successfully!");
    cnt++;

    FILE* fp = fopen("vehicles.txt", "a");
    if (fp == NULL)
    {
        printf("Cannot open this file!\n");
        return;
    }
    else  //Write the vehicle data to 'vehicles.txt'
    {
        fprintf(fp, "%s %d %s %s %.2f %d %.2f %d\n", newVehicle->plate, newVehicle->year,
                newVehicle->model, newVehicle->fuelType, newVehicle->consumption,
                newVehicle->seats, newVehicle->dailyPrice, newVehicle->rentCount);
    }

    fclose(fp);

    FILE* fp1 = fopen("available_vehicles.txt", "a");
    if (fp1 == NULL)
    {
        printf("Cannot open this file!\n");
        return;
    }
    else
    {
        fprintf(fp1, "%s %d %s %s %.2f %d %.2f\n", newVehicle->plate, newVehicle->year,
                newVehicle->model, newVehicle->fuelType, newVehicle->consumption,
                newVehicle->seats, newVehicle->dailyPrice);
    }

    fclose(fp1);
}

void removeVehicle(char* plate) {
    // Remove from vehicles.txt
    FILE* fp1 = fopen("vehicles.txt", "r");
    if (fp1 == NULL) {
        printf("Cannot open file 'vehicles.txt'!\n");
        return;
    }

    FILE* temp1 = fopen("temp1.txt", "w");
    if (temp1 == NULL) {
        printf("Cannot open file 'temp1.txt'!\n");
        fclose(fp1);
        return;
    }

    struct Vehicle currentVehicle;
    int plateFound = 0;

     //// Read vehicle data from 'vehicles.txt'
    while (fscanf(fp1, "%s %d %s %s %f %d %f %d", currentVehicle.plate, &currentVehicle.year,
                  currentVehicle.model, currentVehicle.fuelType, &currentVehicle.consumption,
                  &currentVehicle.seats, &currentVehicle.dailyPrice, &currentVehicle.rentCount) == 8) {
        // Write the vehicle data to 'temp1.txt' if the plate number doesn't match
        if (strcmp(currentVehicle.plate, plate) != 0) {
            fprintf(temp1, "%s %d %s %s %.2f %d %.2f %d\n", currentVehicle.plate, currentVehicle.year,
                    currentVehicle.model, currentVehicle.fuelType, currentVehicle.consumption,
                    currentVehicle.seats, currentVehicle.dailyPrice, currentVehicle.rentCount);
        } else {
            plateFound = 1;
        }
    }

    fclose(fp1);
    fclose(temp1);


    //delete 'vehicles.txt'
    if (remove("vehicles.txt") != 0) {
        printf("Cannot delete file 'vehicles.txt'!\n");
        return;
    }


    // Rename 'temp1.txt' to 'vehicles.txt'
    if (rename("temp1.txt", "vehicles.txt") != 0) {
        printf("Cannot rename file 'temp1.txt'!\n");
        return;
    }

    if (plateFound) {
        printf("The vehicle with plate %s is removed from 'vehicles.txt' successfully!\n", plate);
    } else {
        printf("Vehicle with plate %s was not found in 'vehicles.txt'!\n", plate);
    }

    // Remove from available_vehicles.txt
    FILE* fp2 = fopen("available_vehicles.txt", "r");
    if (fp2 == NULL) {
        printf("Cannot open file 'available_vehicles.txt'!\n");
        return;
    }

    FILE* temp2 = fopen("temp2.txt", "w");
    if (temp2 == NULL) {
        printf("Cannot open file 'temp2.txt'!\n");
        fclose(fp2);
        return;
    }

    int plateFound2 = 0;
    struct Vehicle available_currentVehicle;

    while (fscanf(fp2, "%s %d %s %s %f %d %f %d", available_currentVehicle.plate, &available_currentVehicle.year,
                  available_currentVehicle.model, available_currentVehicle.fuelType, &available_currentVehicle.consumption,
                  &available_currentVehicle.seats, &available_currentVehicle.dailyPrice, &available_currentVehicle.rentCount) == 8) {
        if (strcmp(available_currentVehicle.plate, plate) != 0) {
            fprintf(temp2, "%s %d %s %s %.2f %d %.2f %d\n", available_currentVehicle.plate, available_currentVehicle.year,
                    available_currentVehicle.model, available_currentVehicle.fuelType, available_currentVehicle.consumption,
                    available_currentVehicle.seats, available_currentVehicle.dailyPrice, available_currentVehicle.rentCount);
        } else {
            plateFound2 = 1;
        }
    }

    fclose(fp2);
    fclose(temp2);

    if (remove("available_vehicles.txt") != 0) {
        printf("Cannot delete file 'available_vehicles.txt'!\n");
        return;
    }

    if (rename("temp2.txt", "available_vehicles.txt") != 0) {
        printf("Cannot rename file 'temp2.txt'!\n");
        return;
    }

    if (plateFound2) {
        printf("The vehicle with plate %s is removed from 'available_vehicles.txt' successfully!\n", plate);
    }

    FILE* fp3 = fopen("reservations.txt", "r");
    if (fp3 == NULL) {
        printf("Cannot open file 'reservations.txt'!\n");
        return;
    }

    //Remove vehicle from 'reservations.txt'
    FILE* temp3 = fopen("temp3.txt", "w");
    if (temp3 == NULL) {
        printf("Cannot open file 'temp3.txt'!\n");
        fclose(fp3);
        return;
    }

    struct Reservation currentReservation;
    int plateFound3 = 0;

    while (fscanf(fp3, "%d %s %s %s %d %d", &currentReservation.ID, currentReservation.date,
                  currentReservation.clientID, currentReservation.plateNumber,
                  &currentReservation.nrOfDays, &currentReservation.totalPrice) == 6) {
        if (strcmp(currentReservation.plateNumber, plate) != 0) {
            fprintf(temp3, "%d %s %s %s %d %d\n", currentReservation.ID, currentReservation.date,
                    currentReservation.clientID, currentReservation.plateNumber,
                    currentReservation.nrOfDays, currentReservation.totalPrice);
        } else {
            plateFound3 = 1;
        }
    }

    fclose(fp3);
    fclose(temp3);

    if (remove("reservations.txt") != 0) {
        printf("Cannot delete file 'reservations.txt'!\n");
        return;
    }

    if (rename("temp3.txt", "reservations.txt") != 0) {
        printf("Cannot rename file 'temp3.txt'!\n");
        return;
    }

    if (plateFound3) {
        printf("The vehicle with plate %s is removed from 'reservations.txt' successfully!\n", plate);
    }

}


void displayAllVehicles()
{
    FILE* file = fopen("vehicles.txt", "r");
    if (file == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }

    printf("\nAll Vehicles:\n");
    printf("--------------------------------------------------\n");

    struct Vehicle currentVehicle;


    // Read vehicle data from 'vehicles.txt'
    while (fscanf(file, "%s %d %s %s %f %d %f", currentVehicle.plate, &currentVehicle.year,
                  currentVehicle.model, currentVehicle.fuelType, &currentVehicle.consumption,
                  &currentVehicle.seats, &currentVehicle.dailyPrice) != EOF)
    {

     // Print vehicle information
        printf("Plate:         %s\n", currentVehicle.plate);
        printf("Year:          %d\n", currentVehicle.year);
        printf("Model:         %s\n", currentVehicle.model);
        printf("Fuel Type:     %s\n", currentVehicle.fuelType);
        printf("Consumption:   %f\n", currentVehicle.consumption);
        printf("Seats:         %d\n", currentVehicle.seats);
        printf("Daily Price:   %f\n", currentVehicle.dailyPrice);
        printf("--------------------------------------------------\n");
    }

    fclose(file);
}

void modifyVehicle(char* plateNumber)
{
    FILE* file = fopen("vehicles.txt", "r+");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    struct Vehicle currentVehicle;
    int vehicleFound = 0;

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

     //Read data from 'vehicles.txt'
    while (fscanf(file, "%s %d %s %s %f %d %f %d", currentVehicle.plate, &currentVehicle.year,
                  currentVehicle.model, currentVehicle.fuelType, &currentVehicle.consumption,
                  &currentVehicle.seats, &currentVehicle.dailyPrice, &currentVehicle.rentCount) == 8)
    {

        //Check if the current vehicle matches the plate number given by the user
        if (strcmp(currentVehicle.plate, plateNumber) == 0)
        {
            printf("Enter new information for the vehicle with plate number %s:\n", plateNumber);
            printf("Year: ");
            scanf("%d", &currentVehicle.year);
            printf("Model: ");
            scanf("%49s", currentVehicle.model);
            printf("Fuel Type: ");
            scanf("%19s", currentVehicle.fuelType);
            printf("Consumption (liters per km): ");
            scanf("%f", &currentVehicle.consumption);
            printf("Seats: ");
            scanf("%d", &currentVehicle.seats);
            printf("Daily Price: ");
            scanf("%f", &currentVehicle.dailyPrice);
            vehicleFound++;
        }


         //Write the new data to the temporary file
        fprintf(tempFile, "%s %d %s %s %.2f %d %.2f %d\n", currentVehicle.plate, currentVehicle.year,
                currentVehicle.model, currentVehicle.fuelType, currentVehicle.consumption,
                currentVehicle.seats, currentVehicle.dailyPrice, currentVehicle.rentCount);
    }

    fclose(file);
    fclose(tempFile);

    if (vehicleFound > 0) //Delete 'vehicles.txt' file
    {
        if (remove("vehicles.txt") != 0)//Rename the temporary file to 'vehicles.txt'
        {
            printf("Error deleting file.\n");
            return;
        }

        if (rename("temp.txt", "vehicles.txt") != 0)
        {
            printf("Error renaming file.\n");
            return;
        }

        printf("Vehicle with plate number %s modified successfully.\n", plateNumber);

        FILE* availableFile = fopen("available_vehicles.txt", "r");
        FILE* tempAvailableFile = fopen("temp_available.txt", "w");
        if (availableFile == NULL || tempAvailableFile == NULL)
        {
            printf("Error opening available vehicle files.\n");
            return;
        }

        struct Vehicle availableVehicle;

        while (fscanf(availableFile, "%s", availableVehicle.plate) == 1)
        {
            if (strcmp(availableVehicle.plate, plateNumber) != 0)
            {
                fprintf(tempAvailableFile, "%s\n", availableVehicle.plate);
            }
            else
            {
                fprintf(tempAvailableFile, "%s\n", currentVehicle.plate);
            }
        }

        fclose(availableFile);
        fclose(tempAvailableFile);

        if (remove("available_vehicles.txt") != 0)
        {
            printf("Error deleting available_vehicles.txt file.\n");
            return;
        }

        if (rename("temp_available.txt", "available_vehicles.txt") != 0)
        {
            printf("Error renaming available_vehicles.txt file.\n");
            return;
        }
    }
    else
    {
        printf("Plate %s not found!\n", plateNumber);
    }
}

#endif // ATEA_H_INCLUDED
