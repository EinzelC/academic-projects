#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Perform insertion sort and print snapshots
    for (int k = 1; k < n; k++) {
        int key = arr[k];
        int j = k - 1;

        // Insert arr[k] into the sorted sequence arr[0..k-1]
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;

        // Print the first k+1 elements (in sorted order so far)
        for (int m = 0; m <= k; m++) {
            cout << arr[m] << ";";
        }
        cout << "\n";
    }

    return 0;
}