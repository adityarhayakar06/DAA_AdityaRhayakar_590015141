#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100000
#define RUNS 5
// Binary Search
int searchBinary(int arr[], int size, int key) {
int start = 0, end = size - 1;
while (start <= end) {
int middle = start + (end - start) / 2;
if (arr[middle] == key) return middle;
else if (arr[middle] < key) start = middle + 1;
else end = middle - 1;
}
return -1;
}
// Generate sorted array
void generateArray(int arr[], int size) {
for (int i = 0; i < size; i++) arr[i] = i + 1;
}
// Current time in nanoseconds
long long currentTime() {
struct timespec ts;
clock_gettime(CLOCK_MONOTONIC, &ts);
return (long long) ts.tv_sec * 1000000000LL + ts.tv_nsec;
}
// Measure time
long long measureTime(int arr[], int size, int key) {
long long start = currentTime();
searchBinary(arr, size, key);
long long end = currentTime();
return end - start;
}
void runCaseTests(int arr[], int size, int keys[], const char *caseName) {
printf("\n%s CASE TESTS\n", caseName);
for (int i = 0; i < RUNS; i++) {
long long timeTaken = measureTime(arr, size, keys[i]);
printf("Run %d: Key = %d -> Time = %lld ns\n", i + 1, keys[i], timeTaken);
}
}
int main() {
int arr[SIZE];
generateArray(arr, SIZE);
srand(time(NULL));
// Best case keys (middle element)
int bestKeys[RUNS] = {SIZE / 2, SIZE / 2, SIZE / 2, SIZE / 2, SIZE / 2};
// Worst case keys (not found or near array ends)
int worstKeys[RUNS] = {0, SIZE + 1, -5, SIZE + 10, SIZE * 2};
// Average case keys (random)
int avgKeys[RUNS] = {
rand() % SIZE, rand() % SIZE, rand() % SIZE, rand() % SIZE, rand() % SIZE
};
// Edge cases
int emptyArr[1]; // Empty array
int singleElementArr[1] = {42}; // One element
int edgeKeys[RUNS] = {42, 1, SIZE, SIZE/4, -10};
runCaseTests(arr, SIZE, bestKeys, "BEST");
runCaseTests(arr, SIZE, worstKeys, "WORST");
runCaseTests(arr, SIZE, avgKeys, "AVERAGE");
printf("\nEDGE CASE TESTS\n");
printf("Empty Array: Time = %lld ns\n", measureTime(emptyArr, 0, 50));
printf("Single Element (found): Time = %lld ns\n",
measureTime(singleElementArr, 1, 42));
printf("Single Element (not found): Time = %lld ns\n",
measureTime(singleElementArr, 1, 99));
for (int i = 0; i < RUNS; i++) {
printf("Run %d (Array with duplicates/negatives test): Key = %d -> Time
= %lld ns\n",
i + 1, edgeKeys[i], measureTime(arr, SIZE, edgeKeys[i]));
}
return 0;
}
