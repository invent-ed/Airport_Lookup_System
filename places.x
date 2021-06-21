struct location {
    char state[4];
    char city[50];
    double latitude;
    double longitude;
};

struct clientArg {
    string city<>;
    string state<>;
};

struct airportInfo {
    char code[4];
    char name[50];
    double latitude;
    double longitude;
    double distance;
};

struct placesResults {
    struct location location;
    airportInfo airports[5];
};

union placesRet switch (int err) {
    case 0:
        placesResults results;
    default:
        void; /* error occured, nothing returned */
};

program PLACES_PROG {
    version PLACES_VERS {
        placesRet AIRPORTS_NEAR_CITY(clientArg) = 1;
    } = 1;
} = 0x34865249;
