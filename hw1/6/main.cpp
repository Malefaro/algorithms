#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

template <class T>
void printArr(T* arr,int l, int r)
{
    for (int i = 0; i< (r-l+1); ++i)
        cout << arr[i] << ' ';
    cout << endl;
}

template <class T>
int get_pivot(T* arr,int l, int r){
    T left = arr[l];
    T right = arr[r];
    T mid = arr[(r+l)/2];
    int pivot = (left <= right && left >= mid || left >= right && left <= mid) ?
            l : ((mid <= left && mid >= right || mid >= left && mid <= right) ? (r+l)/2 : r);//((right < left && right > mid)? right)
    return pivot;
}


template <class T>
int partition( T* arr, int l, int r)
{
    swap(arr[get_pivot<T>(arr,l,r)] , arr[r]);
    int i = l;
    int j = l;
    while (j < r)
    {
        if (arr[j] < arr[r]) {
            swap(arr[i], arr[j]);
            ++i;
        }
        ++j;
    }
    swap(arr[i],arr[r]);
    return i;
}

template <class T>
const T& kStatDC(T* arr, int size, int k){
    int l = 0;
    int r = size - 1;

    int p = partition(arr, l, r);
    //printArr(arr,0, size-1);
    while(p != k){
        if(k < p)
            r = p - 1;
        else
            l = p + 1;
        p = partition(arr, l, r);
        //printArr(arr,0,size-1);
    }
    return arr[p];
}


//struct test{
//    test(int m[], int size, int result) : size(size), result(result){
//        mas = new int[size];
//        for (int i = 0; i < size; ++i)
//            mas[i] = m[i];
//    }
//    ~test(){ delete [] mas; }
//    int* mas;
//    int size;
//    int result;
//};
//
//struct t{
//    int m[2] = {1,2};
//};
//
//struct Tests {
//    Tests(){
//        mas= new int*[10];
//        mas[0] = test( []()->int*{int mas[] = {1,2,3,4,5,6,7,8,9};
//            int* m;return m;}, 9,5);
//    }
//    ~Tests(){ delete [] mas; }
//    int** mas;
//    int mas1[9] = {1,2,3,4,5,6,7,8,9};
//    int result1 = 5;
//
//};

int main() {
//    int mas[] = {4,4,2,1,11,6,8,3,2};
//    //int mas[] = {4,4,4,4,2,1,4};
//    int pivot = get_pivot(mas, 4, sizeof(mas)/sizeof(int)-1);
//    cout << pivot << endl;
    int size, k;
    cin >>size >> k;
    int* arr = new int[size];
    for(int i = 0; i < size; i++)
        cin >> arr[i];

    int kElem = kStatDC(arr, size, k);
    cout << kElem << endl;

    delete[] arr;
    return 0;
}