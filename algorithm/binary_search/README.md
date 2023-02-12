```cpp
int right, left = 0;
right = nums.size() - 1;
int mid = 0;
while(left < right) {
    mid = (right - left)/2 + left;
    if (target == nums[mid]) {
                return mid;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
}
```

