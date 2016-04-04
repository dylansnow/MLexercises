#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

template <class T>
vector<T> merge(vector<T> a, vector<T> b) {
    vector<T> c;
    // Compare values until an array has had all its elements appended to the sorted result
    while(a.size() >= 1 && b.size() >= 1) {
        if (a[0] > b[0]) {
            c.push_back(b[0]);
            b.erase(b.begin());
        }
        else {
            c.push_back(a[0]);
            a.erase(a.begin());
        }
    }
    
    // Append remaining elements from sorted input arrays
    while(a.size() >= 1) {
        c.push_back(a[0]);
        a.erase(a.begin());
    }
    while(b.size() >= 1) {
        c.push_back(b[0]);
        b.erase(b.begin());
    }
    
    return c;
}

template <class T>
vector<T> mergesort(vector<T> a) {
    if (a.size() == 1)
        return a;
    
    // Assign first and second half of input arrays ready for sorting
    vector<T> l1 = vector<T>(a.begin(), a.begin() + a.size() / 2);
    vector<T> l2 = vector<T>(a.begin() + a.size() / 2, a.begin() + a.size());    


    l1 = mergesort(l1);
    l2 = mergesort(l2);
    
    return merge(l1, l2);
}

template<class T, class U>
double euclideandistance(tuple<T,U> a, tuple<T,U> b) {
    return pow(pow(get<0>(a)-get<0>(b),2)+pow(get<1>(a)-get<1>(b),2),0.5);
}

template<class T, class U>
tuple<T,U> closestsplitpair(vector<tuple<T,U>> a, vector<tuple<T,U>> b, double delta) {
    // number of elements in tuple
    // tuple_size<decltype(tuple<T,U>)>::value
    return NULL;
}

template <class T, class U>
tuple<T,U> closestpair(vector<tuple<T,U>> a) {
    return NULL;
}

int main() {
    vector<long int> test = { 2, 8, 1, 7, 5, 3, 6 };
    vector<long int> result = mergesort(test);

    for(auto i : result)
        cout << i << ", ";
    
    cout << endl;

    cout << "Euclidean distance: " << euclideandistance(tuple<double, double> (1.0,1.0),
        tuple<double, double> (2.0,2.0));
	return 0;
}
