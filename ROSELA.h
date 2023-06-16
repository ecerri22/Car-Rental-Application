#ifndef ROSELA_H_INCLUDED
#define ROSELA_H_INCLUDED

void searchVehicleByPlateNumber(char* plateNumber) {
    FILE *vehiclesFile;

    vehiclesFile = fopen("vehicles.txt", "r");

    if (vehiclesFile == NULL) {
        printf("Failed to open the vehicles file.\n");
        return;
    }

    char tempPlateNumber[20];
    int year;
    char model[50];
    char fuelType[50];
    float consumption;
    int seats;
    float dailyPrice;
    int reservationCount;

    int found = 0;
    while (fscanf(vehiclesFile, "%s %d %s %s %f %d %f %d", tempPlateNumber, &year, model, fuelType, &consumption, &seats, &dailyPrice, &reservationCount) == 8) {
        if (strcmp(tempPlateNumber, plateNumber) == 0) {
            printf("Plate Number: %s\n", tempPlateNumber);
            printf("Year: %d\n", year);
            printf("Model: %s\n", model);
            printf("Fuel type: %s\n", fuelType);
            printf("Consumption: %.2f\n", consumption);
            printf("Seats: %d\n", seats);
            printf("Daily price: %.2f\n", dailyPrice);
            printf("Number of reservations: %d\n", reservationCount);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Vehicle with plate number '%s' not found.\n", plateNumber);
    }

    fclose(vehiclesFile);
}

void filterReservations(float price) {
    FILE* reservationsFile = fopen("reservations.txt", "r");
    if (reservationsFile == NULL) {
        printf("Failed to open the reservations file.\n");
        return;
    }

    FILE* newFile = fopen("reservationsoverX.txt", "w");
    if (newFile == NULL) {
        printf("Failed to create the new file.\n");
        fclose(reservationsFile);
        return;
    }

    int reservationID;
    char date[20];
    int clientID;
    char plate[20];
    int days;
    float totalPrice;

    int cnt=0;

    while (fscanf(reservationsFile, "%d %s %d %s %d %f", &reservationID, date, &clientID, plate, &days, &totalPrice) == 6) {

            if (totalPrice > price) {
                fprintf(newFile, "%d %s %d %s %d %.2f\n", reservationID, date, clientID, plate, days, totalPrice);
                cnt++;
            }
       }
       if(cnt!=0)
       printf("Reservations with price greater than %.2f have been saved.\n", price);

       else
        printf("No reservations exceeding the price you entered were made.\n");


    fclose(reservationsFile);
    fclose(newFile);
}

void sorting() {
    FILE *vehiclesFile;
    vehiclesFile = fopen("vehicles.txt", "r");

    if (vehiclesFile == NULL) {
        printf("Failed to open the vehicles file.\n");
        return;
    }

    int maxVehicles = 10000;
    struct Vehicle vehicles[maxVehicles];

    int i = 0;

    while (fscanf(vehiclesFile, "%s %d %s %s %f %d %f %d",
                  vehicles[i].plate,
                  &vehicles[i].year,
                  vehicles[i].model,
                  vehicles[i].fuelType,
                  &vehicles[i].consumption,
                  &vehicles[i].seats,
                  &vehicles[i].dailyPrice,
                  &vehicles[i].rentCount) == 8) {
        i++;
    }

    fclose(vehiclesFile);


    for (int k = 0; k < i - 1; k++) {
        int minIndex = k;
        for (int j = k + 1; j < i; j++) {
            if (vehicles[j].dailyPrice < vehicles[minIndex].dailyPrice) {
                minIndex = j;
            }
        }

        struct Vehicle temp = vehicles[k];
        vehicles[k] = vehicles[minIndex];
        vehicles[minIndex] = temp;
    }

    for (int k = 0; k < i; k++) {
        printf("Plate Number: %s\n", vehicles[k].plate);
        printf("Year: %d\n", vehicles[k].year);
        printf("Model: %s\n", vehicles[k].model);
        printf("Fuel Type: %s\n", vehicles[k].fuelType);
        printf("Consumption: %.2f\n", vehicles[k].consumption);
        printf("Seats: %d\n", vehicles[k].seats);
        printf("Daily Price: %.2f\n", vehicles[k].dailyPrice);
        printf("Reservation Count: %d\n", vehicles[k].rentCount);
        printf("------------------------\n");
    }
}

int counter=0;

void addNewClient(struct Client **head3,struct Client **tail3)
{
    struct Client *newClient;
    newClient=(struct Client*)malloc(sizeof(struct Client));
    printf("\nPlease enter the data for the new client: \n");
    printf("Client ID: ");
    scanf("%d", &newClient->clientID);
    printf("Name: ");
    scanf("%s", newClient->name);
    printf("Surname: ");
    scanf("%s", newClient->surname);
    printf("Passport ID: ");
    scanf("%s", newClient->passportID);
    printf("State: ");
    scanf("%s", newClient->state);
    printf("Phone number: ");
    scanf("%s", newClient->phoneNumber);
    newClient->reservationCount = 0;

    newClient->nextClient=NULL;

    if(*head3==NULL) //if there are no nodes in the list
    {
        *head3=newClient; //makes the head point to the newly created vehicle
        *tail3=newClient;
    }

    else
    {
        (*tail3)->nextClient=newClient;
        *tail3=newClient;
    }
    printf("New client added successfully!");
    counter++; //increment the number of vehicles

    FILE *fp=fopen("clients.txt","a"); //open in appending mode to ensure there is no overwriting


    if(fp==NULL)
    {
        printf("Cannot open this file!");
        return;
    }

    else
    {
        fprintf(fp, "%d %s %s %s %s %s %d\n", newClient->clientID, newClient->name,
                newClient->surname, newClient->passportID, newClient->state,
                newClient->phoneNumber, newClient->reservationCount);
    }

    fclose(fp);
}


#endif // ROSELA_H_INCLUDED
