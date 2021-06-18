//
// Created by Administrator on 2021/6/12.
//
#include <iostream>
#include <vector>
using namespace std;
//打印数组
void show(vector<int> nums){
    int len = nums.size();
    for(int i=0;i<len;i++){
        printf("%d%s", nums[i],i==len-1?"\n":" ");
    }
}
//冒泡排序  O(n²) 稳定
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
//冒泡排序改进  O(n²) 稳定
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
//鸡尾酒排序  O(n²) 稳定
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
//选择排序 O(n²) 不稳定
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
//插入排序  O(n²) 稳定
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
//希尔排序  O(n²) //不稳定
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
//并操作
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
//归并排序   O(nlogn) 稳定
void mergeSort(vector<int> &nums,int left,int right){
    if(left==right)
        return ;
    int mid = (left + right) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
}
//堆调整
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
//建立一个最大堆
void buildHeap(vector<int> &nums){
    int len = nums.size();
    for(int i=len/2-1;i>=0;i--){
        heapify(nums, i, len);
    }
}
//堆排序    O(nlogn)  不稳定
void heapSort(vector<int> &nums){
    int len = nums.size();
    buildHeap(nums);
    while(len>1){
        swap(nums[0], nums[--len]);
        heapify(nums, 0, len);
    }
    show(nums);
}

//快速排序    O(nlogn)    不稳定
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
//随机快速排序
int divide(vector<int>& nums, int start, int end)
{
    int i=rand()%(end-start+1)+start;
    swap(nums[start],nums[i]);
    int cur=nums[start];
    while(start<end)
    {
        while(start<end && nums[end]>=cur)--end;
//        nums[start]=nums[end];
        swap(nums[start],nums[end]);
        while(start<end && nums[start]<=cur)++start;
//        nums[end]=nums[start];
        swap(nums[start], nums[end]);
    }
//    nums[start]=cur;
    return start;
}
void randQuickSort(vector<int>& nums,int start,int end)
{
    if(start<end)
    {
        int mid=divide(nums,start,end);
        quickSort(nums,start,mid-1);
        quickSort(nums,mid+1,end);
    }
}
//计数排序       O(n+k)     稳定
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

//得到元素x的第d位数字
int getDigit(int x,int d){
    if(d==1)
        return x%10;
    else {
        int value = x / ( (d - 1) * 10) % 10;
        return value;
    }
}
//根据元素的d位数字进行计数排序
void radixCountSort(vector<int> &nums,vector<int> count,int d,int radix){
    int len = nums.size();
    vector<int> temp(len);
    for (int i = 0; i <len ; i++) {
        count[getDigit(nums[i],d)]++;
    }
    for(int i=1;i<radix;i++){
        count[i] = count[i - 1] + count[i];
    }
    for (int i = len - 1; i >= 0; i--) {
        int digit = getDigit(nums[i],d);
        temp[--count[digit]] = nums[i];//count最小为1
    }
    for (int i = 0; i < len; i++) {
        nums[i] = temp[i];
    }
}
//基数排序   O(n+k)    稳定
void radixSort(vector<int> &nums){
    const int digitNum=2;//样例数组的最大位数
    const int radix = 10;
    vector<int> count(radix, 0);
    for(int i=1;i<=digitNum;i++){
        radixCountSort(nums, count, i, radix);
    }
    show(nums);
}
//划分桶边界
int mapToBucket(int x){
    return x / 10;
}
//可以随便选择一种排序方法将桶内的方法进行排序
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
//将数组内的元素按照边界放入桶内
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
//桶排序     O(n+k)    稳定
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
//    vector<int> nums = {2, 4, 7, 0, 5, 12, 23, 9, 4, 1};
    vector<int> nums={-74,48,-20,2,10,-84,-5,-9,11,-24,-91,2,-71,64,63,80,28,-30,-58,-11,-44,-87,-22,54,-74,-10,-55,-28,-46,29,10,50,-72,34,26,25,8,51,13,30,35,-8,50,65,-6,16,-2,21,-78,35,-13,14,23,-3,26,-90,86,25,-56,91,-13,92,-25,37,57,-20,-69,98,95,45,47,29,86,-28,73,-44,-46,65,-84,-96,-24,-12,72,-68,93,57,92,52,-45,-2,85,-63,56,55,12,-85,77,-39};
    int len=nums.size();
//    bubbleSort(nums);//冒泡排序
//    bubbleSortImprove(nums);//冒泡排序改进
//    cocktailSort(nums);//鸡尾酒排序
//    selectionSort(nums);//选择排序
//    insertionSort(nums);//插入排序
//    shellSort(nums);//希尔排序
//    mergeSort(nums, 0, len - 1);show(nums);//归并排序
//    heapSort(nums);//堆排序
//    quickSort(nums, 0, len - 1);show(nums);//快速排序
        randQuickSort(nums,0,len-1);show(nums);
//    countingSort(nums);//计数排序
//    radixSort(nums);//基数排序
//    bucketSort(nums);//桶排序
    return 0;
}