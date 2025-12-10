#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#define GOOD_INDEX 3
#define dir "/var/tmp/check_decoy.txt"


int get_num_from_file() {
    FILE *fptr = fopen(dir, "r");
    int num;

    fscanf(fptr,"%d", &num);
    fclose(fptr);
    return num;
}


int main() {
    // get first modified time
    struct stat attr;
    time_t t1, t2;
    int last_num;

    if (stat(dir, &attr) == 0)
        t1 = attr.st_mtim.tv_sec;

    last_num = get_num_from_file();

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
