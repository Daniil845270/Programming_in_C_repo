// Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

// Note that you must do this in-place without making a copy of the array.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool checkzeros(int* nums, int i);
void putaway(int* nums, int i);
void moveZeroes(int* nums, int numsSize);

int main(void)
{
    int a[5] = {0,1,0,3,12};
    moveZeroes(a, 5); 
    return 0;

}

void moveZeroes(int* nums, int numsSize) {
    for (int i = 0; i < ((numsSize) - 1); i++){
        if (nums[i] == 0){
            if (checkzeros(nums, i) == false){
                putaway(nums, i);
            }
        }
    }
}

bool checkzeros(int* nums, int i){
    while (nums[i]){
        if (nums[i] != 0){
            return false;
        }
        i++;
    }
    return true;
}

void putaway(int* nums, int i){
    printf("was here\n");
    int j = i + 1; 
    int temp;
    while (nums[j]){
        temp = nums[j];
        nums[j] = nums[i];
        nums[i] = temp;
        j++; i++;
    }
}