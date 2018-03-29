#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
#include <assert.h>
using namespace std;

int get_digit (unsigned long long num, int r)
{
	// cout << "num= " << bitset<64> (num) << endl;
	// cout << "num >> 8*r= " << bitset<8> (num>> 8*r) << endl;
	return ((num >> (8*r)) & 255);
}

/* создаем массив = количеству элементов (n)
заполняем его последними битами с помощью get_digit
создаем массив на 255 элементов
делаем как в countSort_v2:
	сначала пробегаем по всему массиву и записываем сколько раз какое число встретилось
	затем немного меняем его, чтобы этот массив содержал позицию начала данного числа
	создаем ещё один массив равный (n)
	бежим с конца по массиву и закидываем числа из изначалного массива
*/

void countSort (unsigned long long* arr, int size)
{
	for (int i = 0; i < sizeof(unsigned long long); ++i){
		int* data = new int [size];
		for (int j = 0; j < size; ++j)
			data[j] = get_digit(arr[j],i);
        int minV = data[0];
        int maxV = data[0];
        for (int j = 0; j < size; ++j){
            minV = min(minV, data[j]);
            maxV = max(maxV, data[j]);
        }
        int valuesCount = maxV - minV + 1;

        int* valuesData = new int[valuesCount];
        memset(valuesData, 0, valuesCount*sizeof(int));
        for (int j = 0; j < size; ++j) {
            valuesData[data[j] - minV]++;
        }
        for (int j = 1; j < valuesCount; ++j) {
            valuesData[j] += valuesData[j-1];
        }
        unsigned long long* tempData = new unsigned long long[size];

        for (int j = size-1; j >= 0; --j){
            int value = data[j] - minV;
            valuesData[value]--;
            tempData[valuesData[value]] = arr[j];
        }
        memcpy(arr, tempData,size*sizeof(unsigned long long));
        delete [] data;
        delete [] tempData;
        delete [] valuesData;
//        for (int i = 0; i < size; ++i) {
//            cout << arr[i] << ' ';
//        }
//        cout << endl;
	}
}
//18446744073709551614
int main (int argc, char *argv[]){
    int n = 0;
    cin >> n;
    unsigned long long* arr = new unsigned long long[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
//    for (int i = 0; i < n; ++i) {
//        cout << arr[i] << ' ';
//    }
//    cout << endl;
    countSort(arr,n);

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;
//	 unsigned long long n2;
//	 cin >> n2;
//	 cout << bitset<8>(get_digit(n2, 0))<<endl;
//     cout << bitset<8>(get_digit(n2, 1))<<endl;
//     cout << bitset<8>(get_digit(n2, 2))<<endl;
//      cout << bitset<8>(get_digit(n2, 3))<<endl;
//    cout << bitset<8>(get_digit(n2, 4))<<endl;
//    cout << bitset<8>(get_digit(n2, 5))<<endl;
//    cout << bitset<8>(get_digit(n2, 6))<<endl;
//    cout << bitset<8>(get_digit(n2, 7))<<endl;
//	unsigned int c = 132;
//	cout << int(c) << endl;
    delete [] arr;


	return 0;
}