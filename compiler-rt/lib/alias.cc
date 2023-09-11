void __f (void) { /* Do something. */; }
void f (void) __attribute__ ((alias ("__f")));

int main() {
        __f();
        f();
}
