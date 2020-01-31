#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* a[i], ..., a[n], a[0], ..., a[i - 1] */
int search(int *nums, int numsSize, int target)
{
	int left = 0;
	int right = numsSize - 1;
	int middle = (left + right) / 2;

	while (left <= right) {
		/* a[middle] in left part a[i]->a[n] */
		if (nums[left] <= nums[middle]) {
			if (nums[middle] == target) {
				return middle;
			} else if (nums[middle] < target) {
				left = middle + 1;
			} else {
				/* a[i] -> a[middle] */
				if (nums[left] <= target) {
					right = middle - 1;
				} else {
					/* a[0]->a[i - 1] */
					left = middle + 1;
				}
			}
		/* a[middle] in right part a[0]->a[i - 1]*/
		} else {
			if (nums[middle] == target) {
				return middle;
			} else if (nums[middle] > target) {
				right = middle - 1;
			} else {
				/* a[middle]->a[i - 1]*/
				if (nums[right] >= target) {
					left = middle + 1;
				} else {
					right = middle - 1;
				}
			}
		}
		middle = (left + right) / 2;
	}

	return -1;
}

int main(void)
{
	int numsSize;
	int nums[1024] = {0};
	int target;
	int i;

	scanf("%d %d", &numsSize, &target);
	for (i = 0; i < numsSize; i++) {
		scanf("%d", &nums[i]);
	}
	printf("%d\n", search(nums, numsSize, target));

	return 0;
}
