#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

struct Reservation
{
    int ID;
    char date[20];
    char clientID[10];
    char plateNumber[20];
    int nrOfDays;
    float totalPrice;

    struct Reservation *nextReserve;
};

struct Client
{
    int clientID;
    char name[20];
    char surname[20];
    char passportID[20];
    char state[20];
    char phoneNumber[20];
    int reservationCount;

    struct Client *nextClient;
};


struct Vehicle
{
    char plate[10];
    int year;
    char model[50];
    char fuelType[20];
    float consumption;
    int seats;
    float dailyPrice;
    int rentCount;

    struct Vehicle *nextVehicle;
};

#endif // STRUCTURES_H_INCLUDED
