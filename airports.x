struct airport {
    char code[4];
    char name[50];
    double latitude;
    double longitude;
    double distance;
};

struct airportsResults {
    airport airports[5];
};

struct placesArg {
    double latitude;
    double longitude;
};

union airportsRet switch (int err) {
    case 0:
        airportsResults result;
    default:
        void; /* error occured, nothing returned */
};

program AIRPORTS_PROG {
    version AIRPORTS_VERS {
        airportsRet AIRPORTS_NEAR_COORD(placesArg) = 1;
    } = 1;
} = 0x38710268;
