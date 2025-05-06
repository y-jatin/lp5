#include<iostream>
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
void seqMax(vector<int>&arr){
    double start=omp_get_wtime();
    int mx=arr[0];
    for(auto &it:arr){
        mx=max(mx,it);
    }
    double end=omp_get_wtime();
    cout<<"Sequential time "<<(end-start)<<" maximum "<<mx<<endl;
}
void parallelMax(vector<int>&arr){
    double start=omp_get_wtime();
    int mx=arr[0];
#pragma omp parallel reduction(max:mx)
    for(auto &it:arr){
        mx=max(mx,it);
    }
    double end=omp_get_wtime();
    cout<<"Parallel time "<<(end-start)<<" maximum "<<mx<<endl;
}
void seqMin(vector<int>&arr){
    double start=omp_get_wtime();
    int mx=arr[0];
    for(auto &it:arr){
        mx=min(mx,it);
    }
    double end=omp_get_wtime();
    cout<<"Sequential time "<<(end-start)<<" minimum "<<mx<<endl;
}
void parallelMin(vector<int>&arr){
    double start=omp_get_wtime();
    int mx=arr[0];
#pragma omp parallel reduction(min:mx)
    for(auto &it:arr){
        mx=min(mx,it);
    }
    double end=omp_get_wtime();
    cout<<"Parallel time "<<(end-start)<<" minimum "<<mx<<endl;
}
void seqsum(vector<int>&arr){
    long long sum=0;
    double start=omp_get_wtime();
     for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    double end=omp_get_wtime();
    cout<<"Sum sequential "<<(end-start)<<" sum "<<sum<<endl;

}
void parSum(vector<int>&arr){
    long long sum=0;
    double start=omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
     for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    double end=omp_get_wtime();
    cout<<"Sum parallel "<<(end-start)<<" sum "<<sum<<endl;
    

}
void seqAvg(vector<int>&arr){
    long long sum=0;
    double start=omp_get_wtime();
    for(auto &it:arr){
        sum+=it;
    }
    double end=omp_get_wtime();
    cout<<"Avg Sequential "<<(end-start)<<" avg "<<(sum/arr.size())<<endl;

}

void parAvg(vector<int>&arr){
    long long sum=0;
    double start=omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
    for(auto &it:arr){
        sum+=it;
    }
    double end=omp_get_wtime();
    cout<<"Avg parallel "<<(end-start)<<" avg "<<(sum/arr.size())<<endl;

}
int main(){
    cout<<"#pragma omp parallel for (+:sum and max:mx)use syntax correctly";
    int n=1000000;
    vector<int> arr={1,2,3,4,5};
    for(int i=0;i<n;i++){
        arr.push_back(rand()%10000);
    }
    cout<<"Sequential maximum "<<endl;
    seqMax(arr);

    cout<<"Parallel maximum "<<endl;
    parallelMax(arr);

    cout<<"Sequential minimum "<<endl;
    seqMin(arr);

    cout<<"Parallel minimum "<<endl;
    parallelMin(arr);

    cout<<"Sequential Sum "<<endl;
    seqsum(arr);

    cout<<"Parallel Sum "<<endl;
    parSum(arr);

    cout<<"Sequential Avg "<<endl;
    seqAvg(arr);

    cout<<"Parallel Avg "<<endl;
    parAvg(arr);
    
}
