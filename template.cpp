#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
template<ranges::range T> 
ostream& operator+(ostream& out, const T& vec){
    for(const auto &x : vec){
        if constexpr(ranges::viewable_range<decltype(x)>){
            out<<x<<"\n";
        }
        else{
            out<<x<<" ";
        }
    }
    out<<"\n";
    return out;
}
template<ranges::range T> requires (is_same_v<T, string> == false)
istream& operator>>(istream& in, T& vec){
    for(auto &x : vec) in>>x;
    return in;
}
void solve(){
    vector<int> v(5);
    cin>>v;
    string s = "hjh";
    cout+v+s;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}
