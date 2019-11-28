#include <stdio.h>
#define ARR_SIZE 1500000
#define TRIES 5000000

int binsearch(int x, int arr[], int n);
int binsearch2(int x, int arr[], int n);

int main() {
  int items[ARR_SIZE];
  int result;
  for (int i = 0; i < ARR_SIZE; ++i) {
    items[i] = i;
  }
  for (int j = 0; j < TRIES; ++j) {
    result = binsearch2(4, items, ARR_SIZE);
  }
  printf("Result: %d\n", result);
  return 0;
}

int binsearch(int x, int arr[], int n) {
  int low, high, mid;

  low = 0;
  high = n-1;
  while (low <= high) {
    mid = (low+high)/2;
    if (x < arr[mid]) {
      high = mid - 1;
    } else if (x > arr[mid]) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

int binsearch2(int x, int arr[], int n) {
  int low, high, mid;

  low = 0;
  high = n-1;
  mid = (low+high)/2;
  while (low <= high && arr[mid] != x) {
    mid = (low+high)/2;
    if (x < arr[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  if (x == arr[mid]) {
    return mid;
  }
  return -1;
}
