//
// Created by Administrator on 2021/6/12.
//
#include <iostream>
#include <vector>
using namespace std;

void show(vector<int> nums){
    int len = nums.size();
    for(int i=0;i<len;i++){
        printf("%d%s", nums[i],i==len-1?"\n":" ");
    }
}

void bubbleSort(vector<int> nums){
    int len=nums.size();
    for(int i=1;i<len-1;i++){
        for(int j=0;j<len-i;j++){
            if(nums[j]>nums[j+1]){
                swap(nums[j], nums[j + 1]);
            }
        }
    }
    show(nums);
}

void bubbleSortImprove(vector<int> nums){
    int len=nums.size();
    for(int i=1;i<len-1;i++){
        bool sort=false;
        for(int j=0;j<len-i;j++){
            if(nums[j]>nums[j+1]){
                swap(nums[j], nums[j + 1]);
                sort=true;
            }
        }
        if(!sort)
            break;
    }
    show(nums);
}

void cocktailSort(vector<int> nums){
    int len=nums.size();
    int left=0,right=len-1;
    while(left<right) {
        for (int i = left; i < right; i++) {
            if(nums[i]>nums[i+1])
                swap(nums[i], nums[i + 1]);
        }
        right--;
        for(int i=right;i>left;i--){
            if(nums[i-1]>nums[i])
                swap(nums[i - 1], nums[i]);
        }
        left++;
    }
    show(nums);
}

void selectionSort(vector<int> &nums){
    int len=nums.size();
    int min;
    for(int i=0;i<len-1;i++){
        min=i;
        for(int j=i+1;j<len;j++){
            if(nums[j]<nums[min]){
                min = j;
            }
        }
        if(min!=i){
            swap(nums[min], nums[i]);
        }
    }
    show(nums);
}

void insertionSort(vector<int> &nums){
     int len=nums.size();
    for (int i = 1; i < len; i++) {
        int get = nums[i];
        int j=i-1;
        for(;j >= 0 && nums[j] > get;j--) {
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = get;
    }
    show(nums);
}

void shellSort(vector<int> nums){
    int len=nums.size();
    int h=0;
    while(h<=len){
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for(int i=h;i<len;i++){
            int j=i-h;
            int get = nums[i];
            while (j >= 0 && nums[j] > get) {
                nums[j + h] = nums[j];
                j -= h;
            }
            nums[j + h] = get;
        }
        h = (h - 1) / 3;
    }
    show(nums);
}
void merge(vector<int> &nums,int left,int mid,int right){
    int len = right - left + 1;
    vector<int> temp(len);
    int index=0;
    int i=left;
    int j = mid + 1;
    while (i <= mid && j <= right) {
        temp[index++] = nums[i] <= nums[j] ? nums[i++] : nums[j++];
    }
    while(i<=mid){
        temp[index++] = nums[i++];
    }
    while(j<=right){
        temp[index++] = nums[j++];
    }
    for(int k=0;k<len;k++){
        nums[left++] = temp[k];
    }
}
void mergeSort(vector<int> &nums,int left,int right){
    if(left==right)
        return ;
    int mid = (left + right) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
}
void heapify(vector<int> &nums,int i,int size){
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int max=i;
    if (leftChild < size && nums[leftChild] > nums[max]) {
        max = leftChild;
    }
    if (rightChild < size && nums[rightChild] > nums[max]) {
        max = rightChild;
    }
    if (max != i) {
        swap(nums[i], nums[max]);
        heapify(nums, max, size);
    }

}

void buildHeap(vector<int> &nums){
    int len = nums.size();
    for(int i=len/2-1;i>=0;i--){
        heapify(nums, i, len);
    }
}

void heapSort(vector<int> &nums){
    int len = nums.size();
    buildHeap(nums);
    while(len>1){
        swap(nums[0], nums[--len]);
        heapify(nums, 0, len);
    }
    show(nums);
}


void quickSort(vector<int>& nums,int left,int right){
    if(left>=right)
        return ;
    int pivot=nums[left];
    int i=left,j=right;
    while(i<j){
        while(i<=j&&nums[j]>=pivot)
            j--;
        if(i<=j)
            swap(nums[i],nums[j]);
        while(i<=j&&nums[i]<=pivot)
            i++;
        if(i<=j)
            swap(nums[i],nums[j]);
    }
    quickSort(nums,left,i-1);
    quickSort(nums,i+1,right);
}

void countingSort(vector<int> nums){
    const int k = 100;
    int count[k]={0};
    int len=nums.size();
    vector<int> temp(len);
    for (int i = 0; i < len; i++) {
        count[nums[i]]++;
    }
    for(int i=1;i<k;i++){
        count[i] = count[i - 1] + count[i];
    }
    for (int i = len - 1; i >= 0; i--) {
        temp[--count[nums[i]]] = nums[i];//count最小为1
    }
    for (int i = 0; i < len; i++) {
        nums[i] = temp[i];
    }
    show(nums);
}


int mapToBucket(int x){
    return x / 10;
}
void bucketInsertSort(vector<int> &nums,int left,int right){
    for(int i=left+1;i<=right;i++){
        int get = nums[i];
        int j=i-1;
        while(j>=left && nums[j]>get){
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = get;
    }
}
void bucketCountSort(vector<int> &nums,int count[],int bucketNum){
    int len = nums.size();
    vector<int> temp(len);
    for (int i = 0; i <len ; i++) {
        count[mapToBucket(nums[i])]++;
    }
    for(int i=1;i<bucketNum;i++){
        count[i] = count[i - 1] + count[i];
    }
    for (int i = len - 1; i >= 0; i--) {
        int tmp = mapToBucket(nums[i]);
        temp[--count[tmp]] = nums[i];//count最小为1
    }
    for (int i = 0; i < len; i++) {
        nums[i] = temp[i];
    }
}
void bucketSort(vector<int> &nums){
    const int bucketNum = 5;
    int count[bucketNum]={0};
    int len = nums.size();
    bucketCountSort(nums,count,bucketNum);
    for(int i=0;i<bucketNum;i++){
        int left = count[i];
        int right = (i == bucketNum - 1 ? len - 1 : count[i + 1] - 1);
        if(left<right)
            bucketInsertSort(nums, left, right);
    }
    show(nums);
}
int main(){
    vector<int> nums = {2, 4, 7, 0, 5, 12, 23, 9, 4, 1};
    int len=nums.size();
    bubbleSort(nums);
    bubbleSortImprove(nums);
    cocktailSort(nums);
    selectionSort(nums);
    insertionSort(nums);
    shellSort(nums);
    mergeSort(nums, 0, len - 1);show(nums);
    heapSort(nums);
    quickSort(nums, 0, len - 1);show(nums);
    countingSort(nums);
    bucketSort(nums);
    return 0;
}