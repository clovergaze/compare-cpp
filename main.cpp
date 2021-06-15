#include <cstdio>
#include <cstdlib>

long int fsize(FILE *file);

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("Syntax: compare <file1> <file2>\n");
        return 0;
    }

    char *filename1 = argv[1];
    FILE *file1 = fopen(filename1, "rb");

    if (!file1) {
        printf("Error opening file \"%s\".\n", filename1);
        exit(EXIT_FAILURE);
    }

    long int filesize1 = fsize(file1);

    char *filename2 = argv[2];
    FILE *file2 = fopen(filename2, "rb");

    if (!file2) {
        printf("Error opening file \"%s\".\n", filename2);
        exit(EXIT_FAILURE);
    }

    long int filesize2 = fsize(file2);

    if (filesize1 != filesize2) {
        printf("Files are not identical, the size is unequal.\n");
        return 0;
    }

    char *buffer1 = (char *) calloc(filesize1, sizeof(char));

    if (!buffer1) {
        printf("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    unsigned int count1 = fread(buffer1, sizeof(char), filesize1, file1);

    if (count1 != filesize1) {
        printf("Error reading file \"%s\".\n", filename1);
        exit(EXIT_FAILURE);
    }

    char *buffer2 = (char *) calloc(filesize2, sizeof(char));

    if (!buffer2) {
        printf("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    unsigned int count2 = fread(buffer2, sizeof(char), filesize2, file2);

    if (count2 != filesize2) {
        printf("Error reading file \"%s\".\n", filename2);
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < filesize1; i++) {
        if (buffer1[i] != buffer2[i]) {
            printf("Files are not identical.\n");
            return 0;
        }
    }

    printf("Files are identical.\n");

    free(buffer1);
    free(buffer2);

    fclose(file1);
    fclose(file2);

    return 0;
}

long int fsize(FILE *file) {
    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    rewind(file);

    return size;
}
