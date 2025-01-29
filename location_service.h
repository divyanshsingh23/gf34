#ifndef LOCATION_SERVICE_H
#define LOCATION_SERVICE_H

typedef struct {
    char* country;
    char* city;
    char* street;
    char* postal_code;
    char* landmarks[10];
    int landmark_count;
} LocationInfo;


LocationInfo get_location_info(double latitude, double longitude);
void print_location_info(LocationInfo info);
void free_location_info(LocationInfo* info);

#endif