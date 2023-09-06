int main(int argc, char **argv) {
        __asm__ __volatile__("" : : "r" (argv) : "memory");
}
