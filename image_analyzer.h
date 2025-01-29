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
