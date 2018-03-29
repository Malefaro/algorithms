#include <iostream>
#include <bitset>
using namespace std;

int get_digit (unsigned long long num, int r)
{
	// cout << "num= " << bitset<64> (num) << endl;
	// cout << "num >> 8*r= " << bitset<8> (num>> 8*r) << endl;
	return (num >> 8*r) & 255;
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

int countSort (unsigned long long* arr, int size)
{
	for (int i = 0, i < 8; ++i){
		char* data = new char [size];
		for (int j = 0; j < size; ++j)
			data[j] = get_digit(arr[j],i);
		 
	}
}

int main (int argc, char *argv[]){
	// int n = 0;
	// cin >> n;
	// unsigned long long* arr = new unsigned long long[n];
	// for (int i = 0; i < n; ++i) {
	// 	cin >> arr[i];
	// }
	// for (int i = 0; i < n; ++i) {
	// 	cout << arr[i] << ' ';
	// }
	// cout << endl;
	// unsigned long long n;
	// cin >> n;
	// cout << bitset<8>(get_digit(n, 0))<<endl;
	unsigned char c = 132;
	cout << int(c) << endl;
	return 0;
}	