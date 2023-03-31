#include <vector>
#include <algorithm>

using namespace std;

void quicksort(vector<int>& nums, int left, int right) {
    if (left >= right) { return; }
    
    int pivot = nums[left + (right - left) / 2];
    int i = left - 1, j = right + 1;
    
    while (i < j) {
        do {
            i++;
        } while (nums[i] < pivot);
        
        do {
            j--;
        } while (nums[j] > pivot);
        
        if (i < j) {
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
    }
    
    // Recursively sort left and right partitions
    quicksort(nums, left, j);
    quicksort(nums, j + 1, right);
}