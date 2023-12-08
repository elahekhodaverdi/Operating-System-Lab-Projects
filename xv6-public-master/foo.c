#include "types.h"
#include "user.h"

int main() {
    for(int i = 0; i < 5; i++) {
        if(fork() == 0) {
            for(int j = 0; j < 1000000; j++) {}
            sleep(5000);
            return 0;
        }
    }

    for(int i = 0; i < 5; i++) {
        wait();
    }
    return 0;
}
