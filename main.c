#include <stdio.h>
#include <stdlib.h>
#include "image_analyzer.h"
#include "location_service.h"
#include "metadata_extractor.h"
#include "face_detector.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }
    
    const char* image_path = argv[1];
    printf("\n=== Advanced OSINT Image Analysis Tool ===\n\n");

    // Extract and display detailed metadata
    ImageMetadata metadata = extract_metadata(image_path);
    printf("=== Image Metadata ===\n");
    print_metadata(metadata);
    printf("\n");
    
    // Get and display comprehensive location information if GPS data exists
    if (metadata.has_gps) {
        printf("=== Location Information ===\n");
        LocationInfo location = get_location_info(metadata.latitude, metadata.longitude);
        print_location_info(location);
        
        // Additional location context
        printf("Nearby Points of Interest:\n");
        for (int i = 0; i < location.landmark_count; i++) {
            printf("- %s\n", location.landmarks[i]);
        }
        
        free_location_info(&location);
        printf("\n");
    }
    
    // Analyze and display detailed visual features
    printf("=== Visual Analysis ===\n");
    ImageAnalysis analysis = analyze_image(image_path);
    printf("Color Distribution:\n");
    for (int i = 0; i < analysis.feature_count; i++) {
        printf("Channel %d: %.2f%%\n", i, analysis.color_distribution[i] * 100);
    }
    
    printf("\nDetected Objects:\n");
    for (int i = 0; i < analysis.object_count; i++) {
        printf("- %s\n", analysis.detected_objects[i]);
    }
    
    // Perform facial detection and analysis
    printf("\n=== People Detection ===\n");
    FaceAnalysis faces = detect_faces(image_path);
    printf("Detected %d people in the image\n", faces.face_count);
    
    for (int i = 0; i < faces.face_count; i++) {
        Face face = faces.faces[i];
        printf("\nPerson %d:\n", i + 1);
        printf("- Position: (x: %d, y: %d)\n", face.x, face.y);
        printf("- Estimated age range: %d-%d years\n", face.age_min, face.age_max);
        printf("- Gender probability: %.2f%% %s\n", face.gender_confidence * 100, face.gender);
        printf("- Expression: %s (%.2f%% confidence)\n", face.expression, face.expression_confidence * 100);
        
        if (face.has_accessories) {
            printf("- Wearing:");
            for (int j = 0; j < face.accessory_count; j++) {
                printf(" %s", face.accessories[j]);
                if (j < face.accessory_count - 1) printf(",");
            }
            printf("\n");
        }
    }
    
    free_image_analysis(&analysis);
    free_face_analysis(&faces);

    return 0;
}
