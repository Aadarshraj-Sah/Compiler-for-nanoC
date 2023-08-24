int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

// Swap two numbers
void swap(int* p, int* q);
int main() {
    int x;
    int y;
    printStr("Enter numbers:\n");
    x = readInt(&x);
    y = readInt(&y);
    printStr("Before swap:\n");
    printStr("x = "); printInt(x);
    printStr(" y = "); printInt(y);

    swap(&x, &y);
    printStr("\nAfter swap:\n");
    printStr("x = "); printInt(x);
    printStr(" y = "); printInt(y);
    return 0;
}
void swap(int *p, int *q) {
    int t;
    t = *p;
    *p = *q;
    *q = t;
    return;
}