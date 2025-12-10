#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#define GOOD_INDEX 3
#define dir "/var/tmp/check_decoy.txt"


int get_num_from_file() {
    FILE *fptr = fopen(dir, "r");
    if (fptr == NULL) {
        perror("Error opening file");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    int num;
    if (fscanf(fptr,"%d", &num) != 1) {
        perror("Error reading from file");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }
    fclose(fptr);
    return num;
}


int main() {
    // get first modified time
    struct stat attr;
    time_t t1, t2;
    int last_num;

    last_num = get_num_from_file();
    if (stat(dir, &attr) == 0)
        t1 = attr.st_mtim.tv_sec;

    while (1) {
        if (stat(dir, &attr) == 0)
            t2 = attr.st_mtim.tv_sec;

        if (t1 != t2) {
            last_num = get_num_from_file();
            if (last_num == GOOD_INDEX)
                printf("KEY: Good key was used\n");
            else
                printf("KEY: DECOY was used\n");

            t1=t2;
        }
        sleep(1);
    }

    return 0;
}
