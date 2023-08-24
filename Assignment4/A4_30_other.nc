// Add two numbers
int main() {
int x = 2;
int y = 3;
int z;
z = x + y;
printInt(x);
printStr("+");
printInt(y);
printStr(" = ");
printInt(z);
return 0;
}
int main() {
int x = 2;
int y = 3;
int z = 1;
int m;
m = x > y? x: y;
m = m > z? m: z;
printStr("max(");
printInt(x); printStr(", ");
printInt(y); printStr(", ");
printInt(z); printStr(") = ");
printInt(m);
return 0;
}
// Add two numbers from input
int main() {
int x;
int y;
int z;
readInt(&x);
readInt(&y);
z = x + y;
printInt(x);
printStr("+");
printInt(y);
printStr(" = ");
printInt(z);
return 0;
}
// Swap two numbers
void swap(int*, int*);
int main() {
int x;
int y;
readInt(&x);
readInt(&y);
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
// Find factorial by iteration
int main() {
int n;
int i = 0;
int r = 1;
readInt(&n);
for(i = 1; i <= n; i = i + 1)
r = r * i;
printInt(n);
printStr("! = ");
printInt(r);
return 0;
}
int main() {
int n;
int a[10];
int m;
int i;
readInt(&n);
for(i = 0; i < n; i = i + 1) {
readInt(&m);
a[i] = m;
}
m = a[0];
for(i = 1; i < n; i = i + 1) {
if (a[i] > m)
m = a[i];
}
printStr("Max of: ");
printInt(a[0]);
for(i = 1; i < n; i = i + 1) {
printStr(", "); printInt(a[i]);
}
printStr(": = ");
printInt(m);
return 0;
}
// Find factorial by recursion
int factorial(int n) {
if (n == 0)
return 1;
else
return n * factorial(n-1);
}
int main() {
int n = 5;
int r;
r = factorial(n);
printInt(n);
printStr("! = ");
printInt(r);
return 0;
}
// Find fibonacci by co-recursion
int f_odd(int);
int f_even(int);
int fibonacci(int n) {
return (n % 2 == 0)? f_even(n): f_odd(n);
}
int f_odd(int n) {
return (n == 1)? 1: f_even(n-1) + f_odd(n-2);
}
int f_even(int n) {
return (n == 0)? 0: f_odd(n-1) + f_even(n-2);
}
int main() {
int n = 10;
int r;
r = fibonacci(n);
printStr("fibo(");
printInt(n);
printStr(") = ");
printInt(r);
return 0;
}
// Forward declarations
void swap(int *p, int *q);
void readArray(int size);
void printArray(int size);
void bubbleSort(int n);
int arr[20]; // Global array
// Driver program to test above functions
int main() {
int n;
printStr("Input array size: \n");
readInt(&n);
printStr("Input array elements: \n");
readArray(n);
printStr("Input array: \n");
printArray(n);
bubbleSort(n);
printStr("Sorted array: \n");
printArray(n);
return 0;
}
void swap(int *p, int *q) { /* Swap two numbers */
int t = *p;
*p = *q;
*q = t;
}
void readArray(int size) { /* Function to read an array */
int i;
for (i = 0; i < size; i = i + 1) {
printStr("Input next element\n");
readInt(&arr[i]);
}
}
void printArray(int size) { /* Function to print an array */
int i;
for (i = 0; i < size; i = i + 1) {
printInt(arr[i]); printStr(" ");
}
printStr("\n");
}
void bubbleSort(int n) { /* A function to implement bubble sort */
int i;
int j;
for (i = 0; i < n - 1; i = i + 1)
// Last i elements are already in place
for (j = 0; j < n - i - 1; j = j + 1)
if (arr[j] > arr[j + 1])
swap(&arr[j], &arr[j + 1]);
}
int arr[10]; // Sorted array to search
// A recursive binary search function. It returns location of x
// in given array arr[l..r] is present, otherwise -1
int binarySearch(int l, int r, int x) {
if (r >= l) {
int mid = l + (r - l) / 2;
// If the element is present at the middle itself
if (arr[mid] == x)
return mid;
// If element is smaller than mid, then it can only be present in left subarray
if (arr[mid] > x)
return binarySearch(l, mid - 1, x);
// Else the element can only be present in right subarray
return binarySearch(mid + 1, r, x);
}
// We reach here when element is not present in array
return -1;
}
int main() {
    int n = 5; // Number of elements
arr[0] = 2;
arr[1] = 3;
arr[2] = 4;
arr[3] =10;
arr[4] = 40;
int x = 10; // Key to search
int result = binarySearch(0, n - 1, x);
if (result == -1)
printStr("Element is not present in array");
else {
printStr("Element is present at index ");
printInt(result);
}
return 0;
}
// Recursive ternary search in nanoC
/*
Function to perform Ternary Search
*/

int ar[10]; // Sorted array to search

int ternarySearch(int l, int r, int key)
{
	if (r >= l) {

		// Find the mid1 and mid2
		int mid1 = l + (r - l) / 3;
		int mid2 = r - (r - l) / 3;

		// Check if key is present at any mid
		if (ar[mid1] == key) {
			return mid1;
		}
		if (ar[mid2] == key) {
			return mid2;
		}

		/*
        Since the given key is not present at mid, 
        we determine which region to search next and perform a recursive call
		*/

		if (key < ar[mid1]) {

			// The key lies in between l and mid1
			return ternarySearch(l, mid1 - 1, key);
		}
		else if (key > ar[mid2]) {

			// The key lies in between mid2 and r
			return ternarySearch(mid2 + 1, r, key);
		}
		else {

			// The key lies in between mid1 and mid2
			return ternarySearch(mid1 + 1, mid2 - 1, key);
		}
	}

	// Key not found
	return -1;
}

// Driver code
int main()
{
    char ch = 't';
	int l;
	int r;
	int p;
	int key;
	// Assume we have a sorted array
    ar[0] = -91;
    ar[1] = -78;
    ar[2] = -60;
    ar[3] = 0;
    ar[4] = 1;
    ar[5] = 2;
    ar[6] = 23;
    ar[7] = 45;
    ar[8] = 67;
    ar[9] = 100;

    // Check Sorted
	int i=0;
    for (i = 0; i < 9 ; i = i + 1)
    {
        if(ar[i] > ar[i + 1])ch = 'f';
    }
	
    // Starting index
	l = 0;
	// length of array
	r = 9;

    // not sorted or length is improper
    if (ch == 'f' || r != 9) return 0;

	// Checking for integer taken as input
	readInt(&key);

	// Search the key using ternarySearch
	p = ternarySearch(l, r, key);
    if (p == -1)
        printStr("Element is not present in array");
    else {
        printStr("Element is present at index ");
        printInt(p);
    }
    return 0;
}
