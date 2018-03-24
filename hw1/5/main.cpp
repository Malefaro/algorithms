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
        if ( cmp(arr[r], arr[l]) )
            swap(arr[r],arr[l]);
        return;
    }
    int i = 1;


    while (i < r-l+1){
        int k =0;
        while( k < (r-l + 1) / i ) {
            //int size = 2 * i +i*k < (r-l+1) ? 2*i : (r-i*k +1);
            int size1 = i*k+i < (r-l+1) ? i : (r-i*k);
            size1 = size1 > 0 ? size1 : 0;
            int size2 = i*k+2*i < (r-l+1) ? i : (r - i*k - i + 1);
            if (size1 < i)
                size2 = 0;
            int size = size1+size2;
            T *c = new T[size];
            //merge(arr + i * (k), i, arr + i * (k+1), (i * (k+1)) < r ? i : (r - i * (k+1)+1), c, cmp);
            merge(arr + size1 * (k), size1, arr + size1 * (k+1), size2, c, cmp);
            k+=2;
            memcpy(arr+i*(k-2), c, sizeof(T) * size);
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

class Client {
public:
    Client(): time_in(0), time_out(0) {}
    int time_in;
    int time_out;
    Client& operator = (const Client& other){
        this->time_in = other.time_in;
        this->time_out = other.time_out;
    }

    friend std::ostream& operator << (std::ostream& os, Client const& obj){
        return os << obj.time_in << ' ' << obj.time_out << " ; ";
    }
};

bool IsLessClient (const Client& obj1,const Client& obj){
    if (obj1.time_out < obj.time_out)
        return true;
    if (obj1.time_out == obj.time_out)
        return obj1.time_in > obj.time_in;
    else return false;
}

template<class T>
int printArr(const T* arr , int size){
    for (int i = 0; i<size; ++i)
        cout << arr[i] << ' ';
}

int min_Ads(Client* cls, int count){
    mergeSort(cls,0, count-1, IsLessClient);
    printArr(cls,count);
    int minAds = 0;
    int t1=0, t2=0;
    for (int i = 0; i < count; ++i) {
        if ( cls[i].time_in == t2) {
            ++minAds;
            t1 = t2;
            t2 = cls[i].time_out;
        }
        else if(cls[i].time_in < t2 && cls[i].time_in > t1){
            ++minAds;
            t1 = t2;
            t2 = cls[i].time_out;
        }

        else if(cls[i].time_in <= t1) ;
        else {
            minAds += 2;
            t1 = cls[i].time_out -1;
            t2 = cls[i].time_out;
        }
        while (i+1 < count && cls[i].time_out == cls[i+1].time_out)
            ++i;

    }
    return minAds;
}



int main() {
//    int mas1[] = {11,2,5,6,3,8,7,1};
//    int mas2[3] = {2,4,7};
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
//    mergeSort<int>(mas1,0,7,IsLess<int>() );
//    for (int i = 0; i<8; ++i)
//        cout << mas1[i] << ' ';

    int count = 0;

    cin >> count;
    if (count <= 0)
        return 0;
    Client* cls = new Client[count];
    for (int i = 0; i < count; ++i) {
        cin >> cls[i].time_in >> cls[i].time_out;
    }


    cout << min_Ads(cls,count) << endl;
    delete [] cls;
    return 0;
}

/*
4
1 25
3 10
9 10
9 14
2

5
1 10
10 12
1 10
1 10
23 24
5

5
1 5
5 8
1 8
3 10
6 13
4


5
1 5
5 8
1 8
3 10
5 13
3
*/

/*10
1 10
1 10
2 10
3 10
4 10
2 10
1 11
9 10
10 12
11 13
*/

/*
15
1 10
2 10
3 10
7 10
4 10
2 10
3 10
9 10
10 16
11 16
2 16
4 20
3 11
22 26
15 16
 */

/*18
1 10
2 10
3 10
4 10
5 10
6 10
7 10
1 11
2 11
3 11
4 11
5 11
6 7
7 8
9 10
2 10
3 22
22 25
 7*/