#include <stdio.h>
#include <stdlib.h>

/* front-tail pointers to solve the problem. */
int target_sum(int *nums, int nums_size, int target, int *ret_array)
{
	int front = 0;
	int tail = nums_size - 1;

	if ((!nums) || (!ret_array) || (nums_size < 2)) {
		return -1;
	}

	while (front < tail) {
		if ((nums[front] + nums[tail]) == target) {
			/* find the solution */
			ret_array[0] = nums[front];
			ret_array[1] = nums[tail];
			break;
		}
		if ((nums[front] + nums[tail]) < target) {
			/* increase left part */
			front++;
		} else if((nums[front] + nums[tail]) > target) {
			/* decrease left part */
			tail--;
		}
	}

	return (front < tail) ? 0 : -1;
}

int main(void)
{
	int nums_size = 0;
	int target = 0;
	int *nums = NULL;
	int *ret_array = calloc(1, sizeof(int) * 2);
	int i = 0;

	scanf("%d", &nums_size);
	nums = calloc(1, sizeof(int) * nums_size);
	for (i = 0; i < nums_size; i++) {
		scanf("%d", &nums[i]);
	}
	scanf("%d", &target);

	if (target_sum(nums, nums_size, target, ret_array) == 0) {
		printf("%d %d\n", ret_array[0], ret_array[1]);
	}

	free(nums);
	free(ret_array);

	return 0;
}
