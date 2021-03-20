
#include<bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define ll int
//input 2-d array
ll c[1000][1000];
//generating input
void inputGenerator(ll n,ll m){
    for(ll i=0;i<n;i++)
        for(ll j=0;j<m;j++)
            c[i][j]=rand();
}
//applying merge sort
void sort(ll array[],ll l,ll r){
    ll m=(r-l)/2+l;
    if(l!=r){
        sort(array,l,m);
        sort(array,m+1,r);
    }
    ll size1=m-l+1,size2=r-m,left[size1],right[size2],i,j;
    for(i=0;i<size1;i++)
        left[i]=array[l+i];
    for(i=0;i<size2;i++)
        right[i]=array[m+1+i];
    i=0,j=0;
    for(ll curr=l;curr<=r;curr++){
        if(i==size1)
            array[curr]=right[j],j++;
        else if(j==size2)
            array[curr]=left[i],i++;
        else{
            if(left[i]<=right[j])
                array[curr]=left[i],i++;
            else
                array[curr]=right[j],j++;
        }
    }
}
//for debugging
void print(ll n,ll m){
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++)
            cout<<c[i][j]<<" ";
        cout<<"\n";
    }
}
int main(){
    srand(time(0));
    ll n,m,i,j,ans=INT_MAX;
    cout<<"NO. OF ROWS:";
    cin>>n;
    cout<<"\nNO. OF COLOUMNS:";
    cin>>m;
    cout<<"\nHERE IS THE RANDOM GENERATED ARRAY(2-D)\n";
    inputGenerator(n,m);
    for(i=0;i<n;i++)
        sort(c[i],0,m-1);
    //for debugging
    //print(n,m);
    auto start = high_resolution_clock::now();
    for(i=0;i<n-1;i++){
        for(j=0;j<m;j++){
            ll lo=0,hi=m,mid,index=m;
            //applying upperbound(using binary search- which is divide and conquer alogrithm)
            while(hi>=lo){
                mid=(hi+lo)/2;
                //checking the weather the c[i+1][mid] can be a upperbound or not
                if(c[i+1][mid]>c[i][j]){
                    index=mid;
                    hi=mid-1;
                }
                else
                    lo=mid+1;
            }
            if(index!=m)
                ans=min(ans,abs(c[i+1][index]-c[i][j]));
            // checking that answer with just less than element c[i][j]
            if(index!=0)
                ans=min(ans,abs(c[i+1][index-1]-c[i][j]));
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<"Minimum Possible absolute difference between two elements taken from the consecutive row:";
    cout<<ans<<"\n";
    cout<<"total time taken ";
    cout<<duration.count()<<"\n";
}
