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

