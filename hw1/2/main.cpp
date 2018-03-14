#include <iostream>
#include <algorithm>
using namespace std;

/*Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. 
Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], 
ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000.*/

int binarySearch( const int* mas, int elem, int start, int end)  // находит индекс ближайшего по значению элемента
{
    if (start == end && mas[start] == elem)
        return 0;
    int first = start;
    int last = end;
    while( first < last ) {
        int mid = ( first + last ) / 2;
        if( mas[mid] < elem )
            first = mid + 1;
        else
            last = mid;
    }
    if (first == start)
        return start;
    else
    {
        return ( abs(mas[first]-elem) < abs(mas[first-1]-elem) ) ? first : (first-1); // возвращаем индекс ближайшего по значению числа
    }
}


/*Поиск: сначала выполняется приближенный поиск элемента в массиве(по степеням двойки) И затем бинарным поиском в оставшемся массиве
 * ищет наиболее "похожий" элемент*/
int search(const int* mas, int elem, int size){
    int current = 1;
    while (current < size && mas[current] < elem){
        current *= 2;
    }
    // теперь элемент находится между current/2 и current
    // if (current > size-1) // если current Больше размера массива
    //     current = size-1;
    return binarySearch(mas, elem, current/2, current > (size - 1) ? (size-1) : current);

}

void readMas(int* mas, int size){
    for (int i = 0; i < size; ++i){
        cin >> mas[i];
    }
}

void printMas(int* mas, int size){
    for (int i = 0; i < size; ++i){
        cout << mas[i]<< ' ';
    }
    cout << endl;
}



int main() {
    int n = 0;
    int m = 0;
    //cout << "enter A size" << endl;
    cin >> n;
    int* A = new int[n];
    //cout << "enter A" << endl;
    readMas(A,n);
    //cout << "enter B size" << endl;
    cin >> m;
    int* B = new int[m];
    //cout << "enter B" << endl;
    readMas(B,m);
    sort(A,A+n);
    for (int i = 0; i < m; ++i){
        cout << search(A, B[i], n) << ' ' << endl;
    }
    cout << endl;
    delete [] A;
    delete [] B;
    return 0;
}

/*
7
0 10 20 30 60 90 100
4
8 20 100 62
 */