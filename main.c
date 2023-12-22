#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint-gcc.h>
#include <png.h>


void printHex(char* ptr, long size);
int readFile(char* fileName, char** bufferPtr, long* fileSizePtr);
void printBinary(const unsigned char byte);
void memoryDump(char* ptr, long size);
void printGraph(uint8_t map[256][256]);

int main(int argv, char** argc) {
    if (argv != 2) {
        fprintf(stderr, "Need file path\n");
        return EXIT_FAILURE;
    }
    char* buffer;
    long fileSize;
    if(!readFile(argc[1], &buffer, &fileSize)) {
        return EXIT_FAILURE;
    }

    //memoryDump(buffer, fileSize);

    uint8_t map[256][256] = {0};
    for (int i = 0; i < fileSize -1; ++i) {
        uint8_t x = buffer[i];
        uint8_t y = buffer[i+1];
        map[y][x] += 1;
    }
    printGraph(map);
    printHex(buffer, fileSize);
    free(buffer);
    return EXIT_SUCCESS;
}

int readFile(char* fileName, char** bufferPtr, long* fileSizePtr) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    *fileSizePtr = fileSize;
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize);
    if (buffer == NULL) {
        fprintf(stderr, "Failed to malloc buffer\n");
        return 0;
    }


    size_t result = fread(buffer, 1, fileSize, file);
    if (result != fileSize) {
        fprintf(stderr, "Failed to read file\n");
        free(buffer);
        return 0;
    }

    *bufferPtr = buffer;

    fclose(file);

    return 1;
}

void printBinary(const unsigned char byte) {
    for (int i = 7; i >= 0; --i) {
        putchar((byte & (1 << i)) ? '1' : '0');
    }
}

void memoryDump(char* ptr, long size) {

    for (long i = 0; i < size; ++i) {
        printBinary(ptr[i]);
        putchar(' '); // Space between bytes for readability
    }
    putchar('\n'); // Newline at the end

    for (size_t i = 0; i < size; ++i) {
        printf("%02X ", ptr[i]);  // Print each byte in hex
        if ((i + 1) % 16 == 0) {   // Newline every 16 bytes for readability
            putchar('\n');
        }
    }
    putchar('\n');
    for (long i = 0; i < size; ++i) {
        printf("%c",ptr[i]);
        putchar(' '); // Space between bytes for readability
    }
    putchar('\n');


}

void printHex(char* ptr, long size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%02X ", ptr[i]);  // Print each byte in hex
        if ((i + 1) % 16 == 0) {   // Newline every 16 bytes for readability
            putchar('\n');
        }
    }
    putchar('\n');
}

void printGraph(uint8_t map[256][256]) {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            if (map[i][j] > 100) {
                printf("O");  // Change 'A' to whatever character you want for values > 10000
            } else if (map[i][j] > 50) {
                printf("0");  // Change 'B' to whatever character you want for values > 1000
            } else if (map[i][j] > 10) {
                printf("o");  // Change 'C' to whatever character you want for values > 100
            } else if (map[i][j] > 5) {
                printf("*");  // Change 'D' to whatever character you want for values > 10
            } else {
                printf(".");  // For values <= 10
            }
        }
        printf("\n");
    }
    printf("\n");
}