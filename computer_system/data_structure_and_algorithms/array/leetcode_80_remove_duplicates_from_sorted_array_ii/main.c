#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_duplicates(int *nums, int numsSize)
{
	int old_idx;
	int new_idx = 1;
	int last;
	int repeat = 1;

	if (numsSize <= 0) {
		return 0;
	}

	last = nums[0];
	for (old_idx = 1; old_idx < numsSize; old_idx++) {
		/* new one */
		if (nums[old_idx] != last) {
			nums[new_idx] = nums[old_idx];
			last = nums[new_idx];
			new_idx++;
			repeat = 1;
		} else if (repeat < 2) {
			nums[new_idx] = nums[old_idx];
			new_idx++;
			repeat++;
		}
	}
	return new_idx;
}

int main(void)
{
	int numsSize;
	int *nums;
	int i;
	int new_size;

	scanf("%d", &numsSize);

	nums = calloc(1, sizeof(int) * numsSize);
	for (i = 0; i < numsSize; i++) {
		scanf("%d", &nums[i]);
	}

	new_size = remove_duplicates(nums, numsSize);
	for (i = 0; i < new_size; i++) {
		printf("%d ", nums[i]);
	}
	printf("\n%d\n", new_size);

	free(nums);
	return 0;
}
