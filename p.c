// main.c - Main program file
#include <stdio.h>
#include <stdlib.h>
#include "image_analyzer.h"
#include "location_service.h"
#include "metadata_extractor.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }
    
    const char* image_path = argv[1];
    printf("\n=== OSINT Image Analysis Tool ===\n\n");

    // Extract and display metadata
    ImageMetadata metadata = extract_metadata(image_path);
    print_metadata(metadata);
    
    // Get and display location information if GPS data exists
    if (metadata.has_gps) {
        LocationInfo location = get_location_info(metadata.latitude, metadata.longitude);
        print_location_info(location);
        free_location_info(&location);
    }
    
    // Analyze and display visual features
    ImageAnalysis analysis = analyze_image(image_path);
    print_image_analysis(analysis);
    free_image_analysis(&analysis);

    return 0;
}

// metadata_extractor.h
#ifndef METADATA_EXTRACTOR_H
#define METADATA_EXTRACTOR_H

typedef struct {
    double latitude;
    double longitude;
    char datetime[64];
    char camera_model[128];
    int has_gps;
} ImageMetadata;

ImageMetadata extract_metadata(const char* image_path);
void print_metadata(ImageMetadata metadata);

#endif

// location_service.h
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

// image_analyzer.h
#ifndef IMAGE_ANALYZER_H
#define IMAGE_ANALYZER_H

typedef struct {
    int feature_count;
    float* color_distribution;
    char** detected_objects;
    int object_count;
} ImageAnalysis;

ImageAnalysis analyze_image(const char* image_path);
void print_image_analysis(ImageAnalysis analysis);
void free_image_analysis(ImageAnalysis* analysis);

#endif

/*
Implementation files (metadata_extractor.c, location_service.c, image_analyzer.c)
would contain the actual implementations of these functions.

Build using:
gcc -o osint_tool main.c metadata_extractor.c location_service.c image_analyzer.c -I.

Directory structure:
/osint_tool
    /src
        main.c
        metadata_extractor.c
        location_service.c
        image_analyzer.c
    /include
        metadata_extractor.h
        location_service.h
        image_analyzer.h
    /lib
        (external libraries)
    Makefile
*/

