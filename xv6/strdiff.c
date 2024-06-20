#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void StrDiffCalculate(const char *word1, const char *word2, char *result) {
    int length1 = strlen(word1);
    int length2 = strlen(word2);
    int max_length = (length1 > length2) ? length1 : length2;

    for (int i = 0; i < max_length; i++) {
        if (i >= length1) {
            result[i] = '1';
        } else if (i >= length2) {
            result[i] = '0';
        }
        else {
            if (word1[i] >= word2[i]) {
                result[i] = '0';
            } else {
                result[i] = '1';
            }
        }
    }
    result[max_length] = '\n';
}

int main(int argc, char *argv[]) {
    char *word1, *word2, result[16];
    int fd;

    if (argc != 3) {
        printf(1, "strdiff: 2 words required\n");
        exit();
    }
    word1 = argv[1];
    word2 = argv[2];

    StrDiffCalculate(word1, word2, result);
    fd = open("strdiff_result.txt", O_CREATE | O_RDWR);

    if (fd < 0) {
        printf(1, "Can't create or open the file\n");
        exit();
    }
    write(fd, result, strlen(result));
    close(fd);
    exit();
}


