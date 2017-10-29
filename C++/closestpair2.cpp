#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

// Returns a sorted vector of two sorted input vectors
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

// Sorts a vector in n log n time in increasing order
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

// Calculates Euclidean distance between two input points in an x-y plane
template<class T, class U>
double euclidean(const tuple<T,U>& a, const tuple<T,U>& b) {
    return pow(pow(get<0>(a)-get<0>(b),2)+pow(get<1>(a)-get<1>(b),2),0.5);
}

// Calculates the closest pair of points within +/- delta in an x dimension sorted vector
template<class T, class U>
vector<tuple<T,U>> closestsplitpair(const vector<tuple<T,U>>& P, const vector<tuple<T,U>>& Y, double delta) {
    // number of elements in tuple
    // tuple_size<decltype(tuple<T,U>)>::value
    // Largest x value in input vector X is the last value in Pl
    double X_bar = get<0>(P.begin() + P.size() / 2);
    
    // Create a subset Ys of the coordinates of Y that are within X_bar x +/- delta
    vector<tuple<T,U>> Ys;
    for(auto i : Y) {
        if(abs(X_bar - ((double)get<0>)(i)) <= delta)
            Ys.push_back(i);
    }
    
    // Compute distance between all values of Ys up to 7 points after (geometrically proven as correct)
    double min = delta;
    vector<tuple<T,U>> ret(Ys.begin(), Ys.begin() + 1);
    for(auto i : Ys) {
        for(auto iter = Ys.begin(); iter != Ys.end(); ++iter) {
            // Check if 7 elements have been compared
            auto num = distance(Ys.begin(), iter);
            if(num > 7)
                break;
            if(euclidean(i, *iter) < delta) {
                min = euclidean(i, *iter);
                ret = vector<tuple<T,U>>(i, *iter);
            }
        cout << "i(" << num << "): " << i << endl;  
        } 
    }
    return ret;
}

// Returns the pair of input tuples with the smallest distance between them
template<class T, class U>
vector<tuple<T,U>> smallestpair(const tuple<T,U>& a, const tuple<T,U>& b, const tuple<T,U>& c = NULL) {
    if(c == NULL)
        return vector<tuple<T,U>> { a, b };
    else {
        double min = min(euclidean(a, b), euclidean(a, c), euclidean(b, c));
        if(min == euclidean(a, b))
            return vector<tuple<T,U>> { a, b };
        if(min == euclidean(a, c))
            return vector<tuple<T,U>> { a, c };
        if(min == euclidean(b, c))
            return vector<tuple<T,U>> { b, c };
    }
}

// Returns closest pair in a vector of tuples containing x and y coordinates
template <class T, class U>
vector<tuple<T,U>> closestpair(vector<tuple<T,U>> P, vector<tuple<T,U>> X, vector<tuple<T,U>> Y) {
    if(P.size() <= 3) {
        if(P.size() == 2)
            return smallestpair(P[0], P[1]);
        if(P.size() == 3)
            return smallestpair(P[0], P[1], P[2]);
    }
    else {
        // X = sorted array by x-coordinate, Y = sorted array by y-coordinate
        vector<tuple<T,U>> Pl, Pr, Xl, Xr, Yl, Yr, X_out, Y_out, XY_out;
        Pl = vector<tuple<T,U>>(P.begin(), P.begin() + P.size() / 2);
        Pr = vector<tuple<T,U>>(P.begin() + P.size() / 2, P.begin() + P.size());
        Xl = Yl = Pl;
        Xr = Yr = Pr;
        sort(begin(Yl), end(Yl), [](tuple<T,U> const &t1, tuple<T,U> const &t2) { return get<1>(t1) < get<1>(t2); });
        sort(begin(Yr), end(Yr), [](tuple<T,U> const &t1, tuple<T,U> const &t2) { return get<1>(t1) < get<1>(t2); });
        
        X_out = closestpair(Pl, Xl, Yl);
        Y_out = closestpair(Pr, Xr, Yr);
        double delta = min(euclidean(X_out[0], X_out[1]), euclidean(Y_out[0], Y_out[1]));
        
        XY_out = closestsplitpair(P, Y, delta);
        delta = min(euclidean(X_out[0], X_out[1]), euclidean(Y_out[0], Y_out[1]), euclidean(XY_out[0], XY_out[1]));
        if(delta == euclidean(X_out[0], X_out[1]))
            return X_out;
        if(delta == euclidean(Y_out[0], Y_out[1]))
            return Y_out;
        if(delta == euclidean(XY_out[0], XY_out[1]))
            return XY_out;
    }

    return NULL;
}

int main() {
    vector<long int> test = { 2, 8, 1, 7, 5, 3, 6 };
    vector<long int> result = mergesort(test);

    for(auto i : result)
        cout << i << ", ";
    
    cout << endl;
    cout << "Euclidean distance: " << euclidean(tuple<double, double> (1.0,1.0), tuple<double, double> (2.0,2.0)) << endl;

    vector<tuple<double, double>> tuples = { make_tuple(1.0 , 1.0), make_tuple(3.0, 3.0), make_tuple(3.0, 11.0), make_tuple(8.0, 8.0) };
    vector<tuple<double, double>> tuplesX, tuplesY;
    sort(begin(tuples), end(tuples), [](tuple<double, double> const &t1, tuple<double, double> const &t2) { return get<0>(t1) < get<0>(t2); });
    tuplesX = tuples;
    sort(begin(tuples), end(tuples), [](tuple<double, double> const &t1, tuple<double, double> const &t2) { return get<1>(t1) < get<1>(t2); });
    tuplesY = tuples;
    vector<tuple<double, double>> resultantpair = closestpair(tuples, tuplesX, tuplesY);    
    cout << "Euclidean distance result: " << euclidean(resultantpair[0], resultantpair[1]) << endl;

	return 0;
}
