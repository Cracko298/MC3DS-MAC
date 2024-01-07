#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <3ds.h>
#include <sys/stat.h>

void renameFile(const char *oldName, const char *newExtension) {
    // Get the base name of the file
    char *baseName = strdup(oldName);
    char *dot = strrchr(baseName, '.');
    if (dot != NULL) {
        *dot = '\0';  // Remove the old extension
    }

    // Create the new file name with the desired extension
    char *newName = (char *)malloc(strlen(baseName) + strlen(newExtension) + 2);
    snprintf(newName, strlen(baseName) + strlen(newExtension) + 2, "%s.%s", baseName, newExtension);

    // Rename the file
    rename(oldName, newName);
    printf(oldName);

    // Free allocated memory
    free(baseName);
    free(newName);
}

void processFiles(const char *folderPath) {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(folderPath)) != NULL) {
        // Iterate over all files in the directory
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                // Check if the file has one of the specified extensions
                const char *extensions[] = {".material3DS", ".material", ".images", ".mat", ".dat"};
                for (int i = 0; i < sizeof(extensions) / sizeof(extensions[0]); ++i) {
                    if (strstr(ent->d_name, extensions[i]) != NULL) {
                        // Rename the file with a new extension (.json)
                        char filePath[512];
                        snprintf(filePath, sizeof(filePath), "%s/%s", folderPath, ent->d_name);
                        renameFile(filePath, "json");
                    }
                }
            }
        }
        closedir(dir);
    } else {
        // Folder doesn't exist, create it
        mkdir(folderPath, 0777);
    }
}

int main() {
    const char *folderPath = "/mc3ds_files";  // Change this path accordingly

    // Open the folder and process the files
    processFiles(folderPath);

    return 0;
}
