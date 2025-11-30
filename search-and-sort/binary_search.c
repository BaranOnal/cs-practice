#include<stdio.h>
//iterative 
int binarySearch(int arr[], int left, int right, int num) {

	while (left <= right)
	{
		int mid = (left + right) / 2;

		if (arr[mid] == num)
			return mid;

		if (arr[mid] < num)
			left = mid + 1;
		else
		{
			right = mid - 1;
		}
	}
	return -1;
}

//recursive
int binarySearchR(int arr[], int left, int right, int num) {

	if (right >= left) {
		int mid = left + (right - left) / 2;


		if (arr[mid] == num)
			return mid;

		if (arr[mid] > num)
			return binarySearchR(arr, left, mid - 1, num);



		return binarySearchR(arr, mid + 1, right, num);


	}
	return -1;
}
int main() {

	int Arr[8] = { 0,5,9,11,15,22,35,47 };
	int size = sizeof(Arr) / sizeof(Arr[0]);
	int num = 35;

	int result = binarySearchR(Arr, 0, size - 1, num);


	(result == -1)
		? printf("Element is not present in array") :
		printf("Element is present at index %d", result);


	return 0;
}