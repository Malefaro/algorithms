#include <iostream>
#include <assert.h>

#define STARTSIZE 10
using namespace std;

class train {
public:
    int time_in;
    int time_out;
};

template <class T>
class Heap {
public:
    Heap() : buf(nullptr), bufSize(STARTSIZE), size(0) {}
    Heap(int size = 1);
    Heap(T* arr, int size);
    ~Heap();
    int GetMax() const; // просто посмотреть  O(1)
    int ExtractMax(); // извлекает O(logN)
    void Add(int value); // O(log(N))
    bool IsEmpty() const;
    void printHeap();
private:
    T* buf;
    int bufSize;
    int size;
    void siftup(int index);
    void siftdown(int index);
};

template <class T>
Heap<T>::Heap(int size) : bufSize(size), size(0)
{
    buf = new T[size];
}

template <class T>
Heap<T>::~Heap() { delete [] buf; }

template <class T>
void Heap<T>::siftup(int index)
{
    assert(index >= 0 && index < bufSize);
    while (index > 0){
        int parent = (index-1)/2;
        if (buf[index] <= buf[parent])
            return;
        swap(buf[index], buf[parent]);
        index = parent;
    }
}
template <class T>
void Heap<T>::siftdown(int index)
{
   // assert(index >= 0 && index < bufSize);
    while(index < size){
        int max = index;
        int left = 2*index + 1;
        int right = 2*index + 2;
        if (left < size && buf[left] > buf[index])
            max = left;
        if (right < size && buf[right] > buf[max])
            max = right;
        if (max != index){
            swap(buf[index], buf[max]);
            index = max;
        } else return;
    }
}
template <class T>
Heap<T>::Heap(T *arr, int s)
{
    assert(arr && s > 0);
    size = s;
    bufSize = s*2;
    buf = new T[bufSize];

    for (int i = 0; i < s; ++i)
        buf[i] = arr[i];
    int i = 1;
    while (i < s)
        i *= 2;
    while ( i > 0 ) {
        for (int k = (i - 1) / 4; k < (i/2 - 1); ++k) {
            siftdown(k);
        }
        i /= 2;
    }
}
template <class T>
void Heap<T>::printHeap()
{
    for (int i = 0; i < size; ++i)
        cout << buf[i] << ' ';
    cout << endl;
}

template <class T>
int Heap<T>::GetMax() const
{
    return buf[0];
}

template <class T>
void Heap<T>::Add(int value)
{
    buf[size] = value;
    ++size;
    if (size == bufSize){
        bufSize *= 2;
        T* tmp = new T[bufSize];
        for (int i = 0; i< size; ++i)
            tmp[i] = buf[i];
        delete [] buf;
        buf = tmp;
    }
    siftup(size-1);
}

template <class T>
bool Heap<T>::IsEmpty() const
{
    return size == 0;
}

template <class T>
int Heap<T>::ExtractMax()
{
    assert( !IsEmpty() );
    int max = buf[0];
    buf[0] = buf[size--];
    if ( !IsEmpty() )
        siftdown(0);
    return max;
}

int main() {
    //int mas[10] = {16, 11,6, 10,5,9,8,1,2,4};
    int mas[10] = {1,2,4,10,5,6,8,11,9,16};
    Heap<int> h(mas,10);
    h.printHeap();
//    for (int i = 0; i < 12; ++i){
//        h.Add(i);
//    }
    h.printHeap();
    h.ExtractMax();
    h.printHeap();
    return 0;
}