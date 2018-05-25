#include <iostream>
#include <string>
#include <vector>
using namespace std;


#define DefaultSize 8
#define MaxAlpha 0.75

template <class T>
class Hash1
{
public:
    Hash1(const T& data1, int tableSize)
    {
        string data = data1;
        hash = 0;
        for (int i = 0; i < data.size(); ++i) {
            hash = (hash * 127 + data[i]) % tableSize;
        }
    }

    operator size_t() const
    {
        return hash;
    }

    int operator ()(const T& data, int tableSize) {
        int hash = 0;
        for (int i = 0; i < data.size(); ++i) {
            hash = (hash * 127 + data[i]) % tableSize;
        }
        return hash;
    }

private:
    size_t hash;
};


template <class T>
class Hash2
{
public:
    Hash2(const T& data1, int tableSize)
    {
        string data = data1;
        hash = 0;
        for (int i = 0; i < data.size(); ++i){
            hash = (hash*37 + data[i]) % tableSize;
        }
        hash = (hash*2+1) % tableSize;
    }
    operator size_t() const
    {
        return hash;
    }
    int operator ()(const T& data, int tableSize) {
        int hash = 0;
        for (int i = 0; i < data.size(); ++i){
            hash = (hash*37 + data[i]) % tableSize;
        }
        return (hash*2+1) % tableSize;
    }
private:
    size_t hash;
};



template <class T, class FirstHash = Hash1<T>, class SecondHash = Hash2<T> >
class HashTable{
private:
//    class Node {
//    public:
//        Node(const T& data): Data(data), IsDel(false) {}
//        T Data;
//        bool IsDel;
//    };
    T DelVal;
    T NilVal;
public:
    HashTable() : _tableSize(DefaultSize) , _size(0), _table(_tableSize, NilVal){}
    HashTable(T del, T nil) : _tableSize(DefaultSize) , _size(0), _table(_tableSize, NilVal), DelVal(del), NilVal(nil){}
    ~HashTable() = default;

    bool Has(const T& data);
    bool Add(const T& data);
    bool Delete(const T& data);
    void show(){
        for (const auto& object : _table){
            if ( object != NilVal && object != DelVal)
                cout << object << " ";
        }
        cout << endl;
    }

private:
    size_t _tableSize; // максимальный размер таблицы
    size_t _size; // сколько элементов лежит
    vector<T> _table;
    void growTable();
};

template <class T, class FirstHash, class SecondHash >
bool HashTable<T, FirstHash, SecondHash>::Has(const T &data) {
    size_t h1 = FirstHash(data, _tableSize);
    size_t h2 = SecondHash(data, _tableSize);
    size_t i = 0;
    while(_table[h1] != NilVal && i < _tableSize){
        if(_table[h1] == data && _table[h1] != DelVal)
            return true;
        h1 = (h1+h2)% _tableSize;
        ++i;
    }
    return false;
}

template <class T, class FirstHash, class SecondHash>
bool HashTable<T, FirstHash, SecondHash>::Add(const T &data) {
    if ((double)_size / (double)_tableSize >= MaxAlpha)
        growTable();
    size_t h1 = FirstHash(data, _tableSize);
    size_t h2 = SecondHash(data, _tableSize);
    size_t i = 0;
    long deletedIndex = -1;
    while ( _table[h1] != NilVal && i < _tableSize){
        if ( _table[h1] == data && _table[h1] != DelVal)
            return false;

        if (_table[h1] == DelVal && deletedIndex < 0)
            deletedIndex = h1;

        h1 = (h1 + h2) % _tableSize;
        ++i;
    }

    if (deletedIndex >=0 ){
        _table[deletedIndex] = data;
        //_table[deletedIndex]->IsDel = false;

    } else{
        _table[h1] = data;
    }
    ++_size;
    return true;
}

template <class T, class FirstHash , class SecondHash>
bool HashTable<T, FirstHash, SecondHash>::Delete(const T &data) {
    size_t h1 = FirstHash(data, _tableSize);
    size_t h2 = SecondHash(data, _tableSize);
    size_t i = 0;
    while(_table[h1] != NilVal && i < _tableSize){
        if (_table[h1] == data && _table[h1] != DelVal ){
            _table[h1] = DelVal;
            --_size;

            return true;
        }
        h1 = (h1+h2)% _tableSize;
        ++i;
    }
    return false;
}

template <class T, class FirstHash, class SecondHash>
void HashTable<T, FirstHash, SecondHash>::growTable() {
    vector<T> buf = _table;
    _tableSize *= 2;
    _table.clear();
    _table.resize(_tableSize, nullptr);
    for (const auto& object : buf){
        if ( object != NilVal && object != DelVal)
            Add(object);
    }

}


class Test
{
public:
    friend  istream& operator >> (istream & is, Test & obj){
        is >> obj.name >> obj.age;
        return is;
    }
    bool operator == (const Test& other){
        return (name == other.name && age == other.age);
    }
    operator string() const {return name;}
    string name;
    int age;
};

//class test_hash1{
//public:
//    test_hash1(const Test& obj, int tableSize)
//    {
//        string data = obj.name;
//        hash = 0;
//        for (int i = 0; i < data.size(); ++i) {
//            hash = (hash * 127 + data[i]) % tableSize;
//        }
//    }
//
//    operator int() const
//    {
//        return hash;
//    }
//private:
//    int hash;
//};
//
//class test_hash2{
//public:
//    test_hash2(const Test& obj, int tableSize)
//    {
//        string data = obj.name;
//        hash = 0;
//        for (int i = 0; i < data.size(); ++i){
//            hash = (hash*37 + data[i]) % tableSize;
//        }
//        hash = (hash*2+1) % tableSize;
//    }
//
//    operator int() const
//    {
//        return hash;
//    }
//
//private:
//    int hash;
//};

int main() {
//    const string& (*ptr)(const string& ) = &defaultHFunc<string>;
//    HashTable<string, const string& (*)(const string&)> h;
//    h.test("asd", defaultHFunc<string>);
//    abra<A> aqw;

    HashTable<string> table("DEL", "NIL");
    char operation;
    string word;
    while(cin >> operation >> word) {
        if ( operation == '+')
            cout << (table.Add(word) ? "OK" : "FAIL") << endl;
        if ( operation == '-')
            cout << (table.Delete(word) ? "OK" : "FAIL") << endl;
        if ( operation == '?')
            cout << (table.Has(word) ? "OK" : "FAIL") << endl;
        if ( operation == '[')
            table.show();
    }
    return 0;
}

/*
 + a
 + b
 + q
 + w
 + e + r + t + y + u + i + o + p + aa + s + d + f + g + h + j + k + l + z + x + c + v + bb + n + m

  - a
 - b
 - q
 - w
 - e - r - t - y - u - i - o - p - aa - s - d - f - g - h - j - k - l - z - x - c - v - bb - n - m

  ? a
 ? b
 ? q
 ? w
 ? e ? r ? t ? y ? u ? i ? o ? p ? aa ? s ? d ? f ? g ? h ? j ? k ? l ? z ? x ? c ? v ? bb ? n ? m

 + a + b + c + aa + bb
 ? aa ? bb


 +a
OK
+a
FAIL
+a
FAIL
+a
FAIL
?a
OK
-a
OK
?a
FAIL
+a
OK
?a
OK
-a
OK
-a

 */