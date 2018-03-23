#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа).
Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени.
Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно.
Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
Требуется определить минимальное число показов рекламы.
*/


template<class T> // для дефолтных типов таких как инт можно не задавать функцию сравнения
bool IsLessDefault (const T& l, const T& r){
    return l < r;
}

template<class T, class Compare>
void merge(T* a1, int l1, T* a2, int l2, T*& c, Compare cmp )
{
    if (a2 == nullptr || l2 <= 0) {
        c[0] = a1[0];
        return;
    }
    int i = 0;
    int j = 0;
    int k = 0;
    while (i != l1 && j != l2){
        if ( cmp(a1[i], a2[j]) ){
            c[k++] = a1[i++];
        } else { c[k++] = a2[j++]; }
    }
    if (i == l1)
        while (j != l2)
            c[k++] = a2[j++];
    else
        while (i != l1)
            c[k++] = a1[i++];
};

template<class T, class Compare>
void mergeSort(T* arr, int l, int r,Compare cmp)
{
    if (r == l)
        return;
    if (r - l == 1){
        if(arr[r] < arr[l])
            swap(arr[r],arr[l]);
        return;
    }
    int i = 1;


    while (i < r-l+1){
        int k =0;
        while( k < (r-l + 1) / i ) {
            int size = 2 * i +i*k < (r-l+1) ? 2*i : (r-i*k +1);
            T *c = new T[size];
            merge(arr + i * (k), i, arr + i * (k+1), (i * (k+1)) < r ? i : (r - i * (k+1)+1), c, cmp);
            k+=2;
            memcpy(arr+i*(k-2), c, sizeof(T) * 2 * i);
            delete[] c;
        }
        i *= 2;
    }
}; // i * (k++) < r ? k : r - i * (k)
//arr + i * (k), i, arr + ( (i * (k+1)) < r ? (k+1) : (r - i * (k+1)) ), i, c, cmp

template<class T>
class IsLess{
public:
    bool operator () (const T& l, const T& r) {return l < r;}
private:

};

int main() {
    int mas1[] = {11,2,5,6,3,8,7,1};
    int mas2[3] = {2,4,7};
//    int mas1[1] = {2};
//    int mas2[1] = {1};
//    int* c = new int[2];
//    merge<int>(mas1, 1, mas2, 1, c, IsLess<int>() );
//    for (int i = 0; i<2; ++i)
//        cout << c[i] << ' ';
//    delete [] c;
//    mergeSort(mas1,0,3, IsLess<int>());
//    for (int i = 0; i<4; ++i)
//        cout << mas1[i] << ' ';
    mergeSort<int>(mas1,0,7,IsLess<int>());
    for (int i = 0; i<8; ++i)
        cout << mas1[i] << ' ';
    return 0;
}