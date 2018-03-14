#include <iostream>
using namespace std;

#define STEP 10 // константа задающая минимальный размер bufSize при котором его можно ресайзить в случае малой заполниности

//3_1. Реализовать очередь с динамическим зацикленным буфером.

class CQueue {
public:
    CQueue() : bufSize( 1 ), head( 0 ), tail( 0 ) {
        buf = new int [bufSize];
    }

    CQueue( int size ) : bufSize( size ), head( 0 ), tail( 0 ) {
        buf = new int[bufSize];
    }

    ~CQueue() { delete[] buf; }

    bool IsEmpty() const { return head == tail; }

/*

ПЕРЕДЕЛАТЬ GET_SIZE()!!

*/
    int get_size() const // возвращает реальное количество элементов лежащих в массиве
    {
        int i = 0;
        while ( (head + i)% bufSize != tail ) {
            ++i;
        }
        return i;
    }
    void Push( int a )
    {
        if ( ( tail + 1 ) % bufSize != head ) {
            buf[tail] = a;
            tail = (tail + 1) % bufSize;
        } else { // буффер закончился расширяем его
            int* tmp = new int[bufSize*2];
            int i = 0;
            for (i = 0; i < bufSize; ++i){
                tmp[i] = buf[(head+i) % bufSize];
            }
            delete [] buf;
            buf = tmp;
            bufSize *= 2;
            head = 0;
            tail = i;
            buf[tail-1] = a; // -1 т.к. после выхода из цикла for счетчик был наперед увеличен.
            tail = (tail) % bufSize;
        }
    }

    int Pop()
    {
        if ( head == tail )
            return -1;
        int result = buf[head];
        head = ( head + 1 ) % bufSize;
//        if (bufSize > STEP && get_size() < bufSize/4 ){ // если массив относительно пустой уменьшим его.
//            int* tmp = new int[bufSize/2];
//            int i = 0;
//            for (i = 0; i < get_size(); ++i){
//                tmp[i] = buf[(head+i) % bufSize];
//            }
//            delete [] buf;
//            buf = tmp;
//            bufSize /= 2;
//            head = 0;
//            tail = i;
//            tail = (tail) % bufSize;
//        }
        return result;
    }
private:
    int* buf;
    int bufSize;
    int head;
    int tail;
};



int main()
{
    int count = 0;
    cin >> count;
    if ( count < 0 )
        return -1;
    CQueue q1;
    for( int i = 0; i < count; ++i ) {
        int c = 0;
        int val = 0;
        cin >> c >> val;
        switch( c ) {
            case 2:
                if( q1.IsEmpty() && val != -1 || !q1.IsEmpty() && q1.Pop() != val ) {
                    cout << "NO";
                    return 0;
                }
                break;
            case 3:
                q1.Push( val );
                break;
            default:
                return -1;
        }
    }
    cout << "YES";
    return 0;
}

/*
13
3 1
3 1
3 1
3 2
3 3
3 4
3 5
3 11
2 1
2 1
2 11
2 5
2 2
 */