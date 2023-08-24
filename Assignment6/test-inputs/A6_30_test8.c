int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);
int f_odd(int n);
int f_even(int n);
int fibonacci(int n);

// Find fibonacci by co-recursion
int f_odd(int n) {
    if(n==1){
        return 1;
    }
    return f_even(n-1) + f_odd(n-2);
    
}
int f_even(int n) {
    if(n==0){
        return 0;
    }
    return f_odd(n-1) + f_even(n-2);
    
}
int fibonacci(int n) {
    if(n%2==0){
        return f_even(n);
    }
    return f_odd(n);
    
}

int main() {
    int err = 0;
    printStr("Input: ");
    int m = readInt(&err);
    int r;
    
    r = fibonacci(m);
    printStr("fibo(");
    printInt(m);
    printStr(") = ");
    printInt(r);
    return 0;
}
