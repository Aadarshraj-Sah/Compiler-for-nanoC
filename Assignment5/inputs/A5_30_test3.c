int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

// Add two numbers from input
int main() {
    int x;
    int y;
    int z;
    x= readInt(&x);
    y= readInt(&y);
    z = x + y;
    printInt(x);
    printStr("+");
    printInt(y);
    printStr(" = ");
    printInt(z);
    return 0;
}

