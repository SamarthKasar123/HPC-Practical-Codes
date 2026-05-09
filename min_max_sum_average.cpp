#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main() {

    int n;

    cout<<"Enter number of elements: ";
    cin>>n;

    vector<int> arr(n);

    for(int i=0;i<n;i++) {
        cin>>arr[i];
    }

    int sum = 0;

    int minimum = arr[0];
    int maximum = arr[0];

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++) {
        sum += arr[i];
    }

    #pragma omp parallel for reduction(min:minimum)
    for(int i=0;i<n;i++) {

        if(arr[i] < minimum) {
            minimum = arr[i];
        }
    }

    #pragma omp parallel for reduction(max:maximum)
    for(int i=0;i<n;i++) {

        if(arr[i] > maximum) {
            maximum = arr[i];
        }
    }

    double average = (double)sum / n;

    double end = omp_get_wtime();

    cout<<"Sum = "<<sum<<endl;

    cout<<"Minimum = "<<minimum<<endl;

    cout<<"Maximum = "<<maximum<<endl;

    cout<<"Average = "<<average<<endl;

    cout<<"Execution Time = "<<end-start<<endl;

    return 0;
}
