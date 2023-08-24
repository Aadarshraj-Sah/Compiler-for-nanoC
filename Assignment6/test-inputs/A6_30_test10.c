int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

// A recursive binary search function. It returns location of x
// in given array arr[l..r] is present, otherwise -1
int binarySearch(int l, int r, int x) {
    int arr[10];
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
return -1; }
int main() {
    int n;
    int err=0;
    printStr("Input array size: \n");
    n = readInt(&n);
    int arr[10];
    printStr("Input array: \n");
    int i;
    for (i = 0; i < n; i = i + 1) {
        printStr("Input next element\n");
        arr[i] = readInt(&err);
    } 
    printStr("Search: ");
    int f=0;
    int key =  readInt(&key);
    for (i = 0; i < n; i = i + 1) {
        if(arr[i] == key)
        {   
            printInt(i); 
            f=1;
        }
    }
    if(f==0)
    {
        printStr("not found.");
    }
    printStr("\n");
    
    return 0; 
}

