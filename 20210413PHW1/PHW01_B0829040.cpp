#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

void Insert(int e, int*a, int i){
    a[0] = e;
    while(e<a[i]){
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}

void InsertionSort(int*a, int n){
    for (int j = 2; j <= n; j++){
        int temp = a[j];
        Insert(temp, a, j - 1);
    }
}

void Adjust(int*a, int root, int n){
    int e = a[root];
    int j;
    for (j = 2 * root; j <= n; j*=2){
        if(j<n&&a[j]<a[j+1]){
            j++;
        }
        if(e>=a[j]){
            break;
        }
        a[j / 2] = a[j];
    }
    a[j / 2] = e;
}

void HeapSort(int*a, int n){
    for (int i = n / 2; i >= 1; i--){
        Adjust(a, i, n);
    }
    for (int i= n - 1; i >= 1; i--){
        swap(a[1], a[i + 1]);
        Adjust(a, 1, i);
    }
}

void Merge(int*initList, int*mergedList ,int l, int m, int n){
    int i1, iResult, i2;
    for (i1 = l, iResult = l, i2 = m + 1;
        i1 <= m && i2 <= n;
        iResult++){
        if(initList[i1]<=initList[i2]){
            mergedList[iResult] = initList[i1];
            i1++;
        }
        else{
            mergedList[iResult] = initList[i2];
            i2++;
        }
    }
    copy(initList + i1, initList + m + 1, mergedList + iResult);//
    copy(initList + i2, initList + n + 1, mergedList + iResult);//
}

void MergePass(int*initList, int*resultList, int n, int s){
    int i;
    for (i = 1; i <= n - 2 * s + 1; i+=2*s){
        Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);
    }

    if((i+s-1)<n){//
        Merge(initList, resultList, i, i + s - 1, n);
    }
    else{//
        copy(initList + i, initList + n + 1, resultList + i);
    }
}

void MergeSort(int*a, int n){
    int *tempList = new int[n + 1];
    for (int l = 1; l < n; l*=2){
        MergePass(a, tempList, n, l);
        l *= 2;
        MergePass(tempList, a, n, l);
    }
    delete[] tempList;
}

void PrintArray(int*a){
    for (int i = 1; i <= 10; i++){//
        cout << " " << a[i];
    }
    cout << endl;
}

void CopyArray(int*b, int *x){
     for (int i = 1; i <= 10; i++){//
        x[i] = b[i];
    }
}

int main(){
    clock_t start_time, end_time;
    double total_time;
    srand(time(NULL));
    int b[11];//
    int *x = new int[11];//
    for (int i = 1; i <= 10;i++){//
        b[i] =(((rand() % 50000) + 1)*((rand() % 100) + 1)) % 50000 + 1;
    }
    cout << "orginal: "; PrintArray(b);

    int c;
    while(cin >> c){
        if(c==0)break;
        switch(c){
        case 1:
            CopyArray(b, x);
            cout << "Insertion Sort" << endl;
            start_time = clock();
            InsertionSort(x, 10);//
            end_time = clock();
            cout << "sorted: "; PrintArray(x);
            total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            cout << total_time << endl;
            break;

        case 2:
            CopyArray(b, x);
            cout << "Heap Sort" << endl;
            start_time = clock();
            HeapSort(x, 10);//
            end_time = clock();
            cout << "sorted: "; PrintArray(x);
            total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            cout << total_time << endl;
            break;

        case 3:
            CopyArray(b, x);
            cout << "Merge Sort" << endl;
            start_time = clock();
            MergeSort(x, 10);//
            end_time = clock();
            cout << "sorted: "; PrintArray(x);
            total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            cout << total_time << endl;
            break;
        }      
    }
    delete[] x;
}