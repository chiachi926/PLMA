//
//  main.cpp
//  HW1
//
//  Created by Corrine Lai on 2023/3/21.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void insertion(int arr[], int n){
    int i, key, j;
    for (i = 1; i < n; i++)//從第二個數字作為key值開始比較
    {
        key = arr[i];//把值存到key裡面，交換時不會遺失
        j = i - 1;//arr[j]會在arr[i]左邊一個
        while (j >= 0 && arr[j] > key) //取得key值左邊的位置，開始與其比較，直到j<0，或者key>arr[j]
        {
            arr[j + 1] = arr[j];//arr[j]的值會取代arr[j+1]的值
            j = j - 1;//j箭頭往左移，換下一個數跟key比
        }
        arr[j + 1] = key;//j比key值小，所以把key值放到j的右邊
    }
    
}

void quick(int arr[], int left, int right){
    if(left < right){
        int i = left;
        int j = right + 1;//因為從最右邊開始-1，要先+1才能從最右邊開始比
        int pivot = arr[left];//最左邊為樞紐
        do{
            do i++; while(arr[i] < pivot);//從樞紐右邊（第二個）開始i++比到arr[i]大於樞紐
            do j--; while(arr[j] > pivot);//從最右邊開始j--比到arr[j]小於樞紐
            if(i < j) swap(arr[i], arr[j]);//i<j時（arr[i]在arr[j]左邊時），arr[i],arr[j]互換
        }while(i < j);
        swap(arr[left], arr[j]);//arr[j]比樞紐小，樞紐跟arr[j]互換，讓樞紐的左邊都比樞紐小，樞紐的右邊都比樞紐大
        quick(arr, left, j-1);//遞回到比樞紐小的數值做排列
        quick(arr, j+1, right);//遞回到比樞紐大的數值做排列
    }
}

void merge(int low, int mid, int high,int arr[]) {
    if (low >= high) return;
    int l = low, r = mid + 1, k = 0, size = high - low + 1;
    int sorted[size];//建立一個暫時的串列放完成排序的數字
    while (l <= mid and r <= high)//arr[l]跟arr[r]邊比較邊排序，放到暫時的array裡
        if(arr[l] < arr[r]) {//若左邊串列最左邊的數字比右邊串列最左邊的數字小
            sorted[k++] = arr[l++];//將左邊串列最左邊的數字移到暫時串列裡
        } else {//若右邊串列最左邊的數字比左邊串列最左邊的數字小
            sorted[k++] = arr[r++];//將右邊串列最左邊的數字移到暫時串列裡
        }
    //把剩下的數值放到暫時的array裡
    while (l <= mid)//右邊串列沒有數值時，將左邊串列剩下的數值放到暫時串列裡
        sorted[k++] = arr[l++];
    while (r <= high)//左邊串列沒有數值時，將右邊串列剩下的數值放到暫時串列裡
        sorted[k++] = arr[r++];
    //從暫時的array移到原本的array
    for (k = 0; k < size; k++)
        arr[k + low] = sorted[k];
}

void mergeSort(int arr[], int start, int end){
    if(start < end){
        int mid = start + (end - start) / 2;//將串列左右分半
        mergeSort(arr, start, mid);//分一半後左邊的繼續分半，到剩一個時再進行比較排列
        mergeSort(arr, mid + 1, end);//分一半後右邊的繼續分半，到剩一個時再進行比較排列
        merge(start, mid, end, arr);//比較排列合併
    }
}
void CheckArray(int* arr, int n) {
    for(int i = 0; i < n-1; i++)
        if(arr[i + 1]<arr[i]) {
            cout << "Error!";
            return ;
        }
    cout << "right";
}
int main(){
    srand(time_t(NULL));

    int n;
    cout << "Please give me how much number you need?" << endl;
    cin >> n;
    int array [n];
    int mthd = 0;

    for(int r = 0; r < n; r++){
        unsigned random = rand();
        unsigned rndm = rand();
        array [r] = ((random + rndm) % 50000) + 1;
    }
    cout << "choose a sorting method:\n 1)insertion sort\n 2)quick sort\n 3)merge sort" << endl;
    cin >> mthd;
    while(mthd < 1 || mthd > 3) {//小於1、大於3時，顯示錯誤
        cout << "Method error! enter it again!" << endl;
        cin >> mthd;
    }
    clock_t start = clock();
    if(mthd == 1)
        insertion(array, n);
    if(mthd == 2)
        quick(array, 0, n-1);
    if(mthd == 3)
        mergeSort(array, 0, n-1);
    clock_t end = clock();
    for(int i = 0; i < n; i++) //印出array裡的數
        ((i + 1)%10)==0 ? cout << array[i] << endl : cout << array[i]<<"\t";
    CheckArray(array,n);
    cout << endl << double(end-start)/CLOCKS_PER_SEC << endl;
    return 0;
}
