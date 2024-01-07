#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <3ds.h>
#include <citro3d.h>
#include <signal.h>

void renameAndDeleteFiles(const char *directory);

void cleanup() {
    socExit();
    gfxExit();
    cfguExit();
    aptExit();
    srvExit();
    gspExit();
}


int main() {

    int checksum = 0;
    const char *targetDirectory = "/mc3ds_files/attribute_conv";
    const char *baseDirectory = "/mc3ds_files";
    
    atexit(cleanup);
    srvInit();
    aptInit();
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    consoleClear();

    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();

    struct stat dirStats;
    if (stat(baseDirectory, &dirStats) != 0) {
        if (mkdir(baseDirectory, 0777) != 0) {
            perror("Error creating directory");
            exit(EXIT_FAILURE);
        }
    }

    struct stat dirStat;
    if (stat(targetDirectory, &dirStat) != 0) {
        if (mkdir(targetDirectory, 0777) != 0) {
            perror("Error creating directory");
            exit(EXIT_FAILURE);
        }
        checksum++;
        svcSleepThread(200000000);
        printf("Directory created:\n");
        printf(targetDirectory);
        printf("\n");
        fflush(stdout);

    }

    if (checksum == 0) {
        renameAndDeleteFiles(targetDirectory);
        svcSleepThread(650000000);
        printf("\nConverted All Possible Attribute Files.\n");
        fflush(stdout);
        printf("Press the 'start' key to exit the application...\n");
        fflush(stdout);
    }
    else {
        svcSleepThread(650000000);
        printf("\nCannot Convert Files in a Newly Created Dir.\n");
        fflush(stdout);
        printf("Press the 'start' key to exit the application...\n");
        fflush(stdout);
    }

    while (aptMainLoop()) {
        hidScanInput();

        if (hidKeysDown() & KEY_START) {
            break;
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    return 0;
}

int endsWithJson(const char *filename) {
    size_t len = strlen(filename);
    return (len >= 5) && (strcmp(filename + len - 5, ".json") == 0);
}

void renameAndDeleteFiles(const char *directory) {
    atexit(cleanup);
    srvInit();
    aptInit();
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();

        if (entry->d_type == DT_REG) {
            char filename[256];
            strcpy(filename, directory);
            strcat(filename, "/");
            strcat(filename, entry->d_name);

            const char *extensions[] = {".material3DS", ".material", ".images", ".mat", ".dat", ".bak"};
            int match = 0;
            for (int i = 0; i < sizeof(extensions) / sizeof(extensions[0]); i++) {
                if (strstr(entry->d_name, extensions[i]) != NULL) {
                    match = 1;
                    break;
                }
            }

            if (match && !endsWithJson(entry->d_name)) {
                char newFilename[256];
                strcpy(newFilename, filename);
                strcat(newFilename, ".json");
                rename(filename, newFilename);

                remove(filename);

                svcSleepThread(42500000);
                printf("\nConverted and Renamed File:\n");
                printf(filename);
                printf("\n");
                printf(newFilename);
                printf("\n");
                printf("\n\n");
                fflush(stdout);

            }
            else {
                svcSleepThread(42500000);
                printf("\nIgnored File:\n");
                printf(filename);
                printf("\n\n");
            }
        }
    }

    closedir(dir);
}