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