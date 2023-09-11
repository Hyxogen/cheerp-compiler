
/*
#include <stdio.h>

void print_val(int* p) {
        printf("%d\n", *p);
}

int main(void) {
        int i = 0;
        print_val(&i);
        return 0;
}
*/

void _start(void) {
        int *ptr = 0;
        (void)*ptr;
}

/*
int main(void) {
        char str[] = "hoi";
        return str[5];
}*/
