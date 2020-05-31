#include <iostream>
#include <string>

#include <cmath>
#include <limits>

using namespace std;
#include <cstdlib>
#include <sstream>

#include <fstream>
#include <locale.h>
#include <vector>
int outof;
int score;
int current;
class Book {

private:
    string isbn;
    string name;
    string category;
    string writer;
    string publisher;
    int first_pub_date;
    int page_count;

public:
// Constructors
    Book() : isbn("") {}

    Book(const string isbn, const string name, const string category, const string writer, const string publisher,
         int first_pub_date, int page_count) : isbn(isbn), name(name), category(category), writer(writer),
                                                             publisher(publisher), first_pub_date(first_pub_date),
                                                             page_count(page_count) {}
// Getters and setters
    const string &getIsbn() const {
        return isbn;
    }

    void setIsbn(const string &isbn) {
        Book::isbn = isbn;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Book::name = name;
    }

    const string &getCategory() const {
        return category;
    }

    void setCategory(const string &category) {
        Book::category = category;
    }

    const string &getWriter() const {
        return writer;
    }

    void setWriter(const string &writer) {
        Book::writer = writer;
    }

    const string &getPublisher() const {
        return publisher;
    }

    void setPublisher(const string &publisher) {
        Book::publisher = publisher;
    }

    int getFirst_pub_date() const {
        return first_pub_date;
    }

    void setFirst_pub_date(int first_pub_date) {
        Book::first_pub_date = first_pub_date;
    }

    int getPage_count() const {
        return page_count;
    }

    void setPage_count(int page_count) {
        Book::page_count = page_count;
    }

};
void SetPoints(int points) {
    current = points;
}

void Describe(const std::string& test, int points, bool critical = false) {
    outof += points;
    score += points;
    cout << test << " (" << points << ")" << endl;
    SetPoints(points);
}

template <class T>
void AssertEqual(const T& a, const T& b) {
    if (a != b) {
        cout << "Failed" << endl;
        cout << "Expected: " << b << endl;
        cout << "Output: " << a << endl;
        score -= current;
        SetPoints(0);
    }
}

void Assert(bool cond) {
    if (!cond) {
        cout << "Failed" << endl;
        score -= current;
        SetPoints(0);
    }
}

vector<string> split(string line, char delim) {
    vector<string> result;
    stringstream s_stream(line); //create string stream from the string
    while(s_stream.good()) {
        string substr;
        getline(s_stream, substr, delim); //get first string delimited by comma
        result.push_back(substr);
    }
    //for(int i = 0; i<result.size(); i++) {    //print all splitted strings
    //    cout << result.at(i) << endl;
    //}
    return result;
}

vector<Book> readInput(string inputPath, char delim) {
    vector<Book> books;
    setlocale(LC_ALL, "Turkish");

    ifstream infile;
    string line;
    int lineNo = 0;

    infile.open(inputPath.c_str());
    getline(infile, line);
    while (getline(infile, line)) {
        lineNo++;
        vector<string> args = split(line, delim);
        if (args.size() == 7) {
            int pub_date = atoi(args[5].c_str());//stoi(args[5]);
            int page_cnt = atoi(args[6].c_str());//stoi(args[6]);
            Book book(args[0], args[1], args[2], args[3], args[4], pub_date ,page_cnt);
            books.push_back(book);
        }
        else {
            cout << "Not enough arguments to create a book object! at line no: " << lineNo << endl;
        }


    }
    infile.close();
    return books;
}

const int Primes[] = { 353, 431, 521, 631, 761, 919,
                       1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591,
                       17519, 21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437,
                       187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897, 1162687, 1395263,
                       1674319, 2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369, 9270769, 14000839};

#define A 54059
#define B 76963
#define C 86969
unsigned UniversalHash(const std::string data, int size) {
    unsigned h = 31 /* also prime */;
    for (int i = 0; i < size; ++i) {
        h = (h * A) ^ (data[i] * B);
    }
    return h;
}

int Hash(std::string key) {
    return (UniversalHash(key, key.length()) & 0x7FFFFFFF);
}

template<class T, int N>
static int length(const T (&arr)[N]) {
    return N;
}

static bool isPrime(int num) {
    if ((num & 1) != 0) {
        int limit = static_cast<int>(std::sqrt(num));
        for (int divisor = 3; divisor <= limit; divisor += 2) {
            if ((num % divisor) == 0)
                return false;
        }
        return true;
    }
    return (num == 2);}

int NextCapacity(int from) {
    if (from > Primes[length(Primes) - 1]) {
        for (int i = (from | 1); i < std::numeric_limits<int>::max(); i += 2) {
            if (isPrime(i) && ((i - 1) % 101 != 0))
                return i;
        }

        return from;
    }

    for (int i = 0; i < length(Primes); ++i) {
        if (Primes[i] > from) {
            return Primes[i];
        }
    }

    return -1; }





template <class T>
class HashTable {
    struct Entry {
        std::string Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[3];
    };

    int _capacity; // INDICATES THE SIZE OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // HASH TABLE
    double _probes;
    double loadfactor();
    bool insert_helper(std::string key, Bucket &given);
    
    
    // You can define private methods and variables

public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    HashTable(const HashTable<T>& rhs);
    HashTable<T>& operator=(const HashTable<T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE.
    // IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(std::string key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
    // HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.
    void Delete(std::string key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()
    T Get(std::string key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
    void Resize(int newCapacity);
    
    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH
    double getAvgSuccessfulProbe();
    
    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH
    double getAvgUnsuccessfulProbe();

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const;
    int Size() const;
};

template <class T>
double HashTable<T>::loadfactor(){
    if(_capacity) return (double) _size/(3*_capacity);
    else return (double) 0;
}

template <class T>
bool HashTable<T>::insert_helper(std::string key, Bucket &given){
    for(int i=0;i<3;i++){
        if(given.entries[i].Key==key && given.entries[i].Deleted==false &&given.entries[i].Active==true) return true;
    }
    return false;
}

template <class T>
HashTable<T>::HashTable() {
_table=NULL;
_capacity=0;
_size=0;
_probes=0;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& rhs) {
// TODO: COPY CONSTRUCTOR
_capacity=rhs._capacity;
    if(_capacity){   _table= new Bucket[_capacity]; //bucketlara allocation yapiyor
    for(int i=0; i<_capacity; i++){
        for(int j=0; j<3; j++) {  //entries are copied
        _table[i].entries[j].Key=rhs._table[i].entries[j].Key;
        _table[i].entries[j].Value=rhs._table[i].entries[j].Value;
        _table[i].entries[j].Active=rhs._table[i].entries[j].Active;
        _table[i].entries[j].Deleted=rhs._table[i].entries[j].Deleted;}
    }}
    _size=rhs._size;
    _probes=rhs._probes;
}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& rhs) {
if(_table) delete [] _table;    //original table is deallocated
if(rhs._capacity){
_table= new Bucket[rhs._capacity];
_capacity=rhs._capacity;
_probes=rhs._probes;
_size=rhs._size;
for(int i=0; i<rhs._capacity; i++){
        for(int j=0; j<3; j++){  //rhs entries are copied
               _table[i].entries[j].Key=rhs._table[i].entries[j].Key;
               _table[i].entries[j].Value=rhs._table[i].entries[j].Value;
               _table[i].entries[j].Active=rhs._table[i].entries[j].Active;
               _table[i].entries[j].Deleted=rhs._table[i].entries[j].Deleted;}
}}
else{
    _table=NULL;
    _capacity=0;
    _probes=0;
    _size=0;
}
return *this;}

template <class T>
HashTable<T>::~HashTable() {
    delete [] _table;
    _table=NULL;
    _probes=0;
    _size=0;
    _capacity=0;
}

template <class T>
void HashTable<T>::Insert(std::string key, const T& value) {
// TODO: IMPLEMENT THIS FUNCTION.
// INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
// IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
// THE ALREADY EXISTING ONE. IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
// RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    int i=1;
    if(_capacity==0 || loadfactor()>0.5){
            int newcap=NextCapacity(_capacity);
            Resize(newcap);
        }
    int hashvalue=Hash(key);
    hashvalue%=_capacity;
    _probes++;
    while( !(insert_helper(key,_table[hashvalue])) && (_table[hashvalue].entries[0].Active)  && (_table[hashvalue].entries[1].Active) && (_table[hashvalue].entries[2].Active)){
        hashvalue = (hashvalue + i*i) % _capacity;
        i++;
        _probes++;}
    if((insert_helper(key,_table[hashvalue]))==true){   //son gelinen bucketta aynisindan active var
        for(int i=0; i<3; i++){
            if((_table[hashvalue].entries[i].Key==key) && (_table[hashvalue].entries[i].Deleted==false)) {_table[hashvalue].entries[i].Value=value;}} //update identical key
        }
    else{            //bos entry bulunmus
     for(int i=0 ; i<3; i++){
        if(_table[hashvalue].entries[i].Active==false){ //deleted ya da bos nokta bulmus
            _table[hashvalue].entries[i].Key=key;
            _table[hashvalue].entries[i].Value=value;
            _table[hashvalue].entries[i].Active=true;
            _table[hashvalue].entries[i].Deleted=false;
            _size++;
            break; } //sadece bir boslugu doldur
        }
    }
}

template <class T>
void HashTable<T>::Delete(std::string key) {
// TODO: IMPLEMENT THIS FUNCTION.
// DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
// IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
// HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.
if(_capacity){
    bool flag=false;
    int i=1;
    int hashvalue=Hash(key);
    hashvalue%=_capacity;
    while( (_table[hashvalue].entries[0].Active==true) && (_table[hashvalue].entries[1].Active==true) && (_table[hashvalue].entries[2].Active==true)){
        if(flag==true) break;
        for(int j=0; j<3; j++){
            if(_table[hashvalue].entries[j].Key==key && _table[hashvalue].entries[j].Active==true){
             _table[hashvalue].entries[j].Deleted=true;
             _table[hashvalue].entries[j].Active=false;
             _size--;
             flag=true;
             break;}}
        hashvalue = (hashvalue + i*i) % _capacity;
        i++;}
        
if(flag==false){for(int j=0; j<3; j++){
     if(_table[hashvalue].entries[j].Active==false) break;
     else if(_table[hashvalue].entries[j].Key==key && _table[hashvalue].entries[j].Active==true){
             _table[hashvalue].entries[j].Deleted=true;
             _table[hashvalue].entries[j].Active=false;
             _size--;
             break;}}
}
}}

template <class T>
T HashTable<T>::Get(std::string key) const {
// TODO: IMPLEMENT THIS FUNCTION. IT SHOULD RETURN THE VALUE THAT
// IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
// IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()
if(_capacity){
    int i=1;
    int hashvalue=Hash(key);
    hashvalue%=_capacity;
    while( (_table[hashvalue].entries[0].Active==true) && (_table[hashvalue].entries[1].Active==true) && (_table[hashvalue].entries[2].Active==true)){
        for(int j=0; j<3; j++) {if(_table[hashvalue].entries[j].Key==key && _table[hashvalue].entries[j].Active==true) return _table[hashvalue].entries[j].Value;}
        hashvalue = (hashvalue + i*i) % _capacity;
        i++;}
    for(int j=0; j<3; j++){
        if(_table[hashvalue].entries[j].Active==false) break;
        else if(_table[hashvalue].entries[j].Key==key && _table[hashvalue].entries[j].Active==true) return _table[hashvalue].entries[j].Value;}
return T();}
else return T();
}

template <class T>
void HashTable<T>::Resize(int newCapacity) {
// TODO: IMPLEMENT THIS FUNCTION. AFTER THIS FUNCTION IS EXECUTED
// THE TABLE CAPACITY MUST BE EQUAL TO newCapacity AND ALL THE
// EXISTING ITEMS MUST BE REHASHED ACCORDING TO THIS NEW CAPACITY.
// WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
if(_capacity){
    HashTable<T> temp;
    temp._capacity=_capacity;
    temp._size=_size;
    temp._probes=_probes;
    temp._table= new Bucket[_capacity]; //bucketlara allocation yapiyor
    for(int i=0; i<temp._capacity; i++){
        for(int j=0; j<3; j++) {      //the table is copied to the temp
        temp._table[i].entries[j].Key=_table[i].entries[j].Key;
        temp._table[i].entries[j].Value=_table[i].entries[j].Value;
        temp._table[i].entries[j].Active=_table[i].entries[j].Active;
        temp._table[i].entries[j].Deleted=_table[i].entries[j].Deleted;}
    }
    delete [] _table;    //original table is deallocated
    _table= new Bucket[newCapacity];
    _probes=0;
    _size=0;
    _capacity=newCapacity;
    for(int i=0; i<temp._capacity; i++){
        for(int j=0; j<3; j++) {  //ex entries are hashed back
             if(temp._table[i].entries[j].Active==true) //sadece deleted olanlar rehash edilecekmis
             Insert(temp._table[i].entries[j].Key, temp._table[i].entries[j].Value);}
    }
    delete [] temp._table;  //temp is deallocated to prevent leaks
    temp._table=NULL;}
else {
    _table= new Bucket[newCapacity];
    _capacity=newCapacity;}
}


template <class T>
double HashTable<T>::getAvgSuccessfulProbe() {
// TODO: IMPLEMENT THIS FUNCTION.
// RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH
  return ((double) _probes/_size);

}

template <class T>
double HashTable<T>::getAvgUnsuccessfulProbe() {
// TODO: IMPLEMENT THIS FUNCTION.
// RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH
double total = 0;
for (int i = 0; i< _capacity; i++){
    if(_table[i].entries[0].Active==false || _table[i].entries[1].Active==false || _table[i].entries[2].Active==false) {
        total++;
        continue;}
    else{
        total++;
        int q=1;
        while(_table[(i+q*q)%_capacity].entries[0].Active==true && _table[(i+q*q)%_capacity].entries[1].Active==true  && _table[(i+q*q)%_capacity].entries[2].Active==true){
        q++;
        total++;}
    }
    total++;}
        
return (double)total/_capacity;

}

template <class T>
int HashTable<T>::Capacity() const {
    return _capacity;
}

template <class T>
int HashTable<T>::Size() const {
    return _size;
}

int main() {
   
      
    
        cout << NextCapacity(761) << endl;
    return 0;
}
