#include<bits/stdc++.h>
using namespace std;
#define ll long long int
vector<ll> st[1<<18];

vector<ll> merge(vector<ll> &a,vector<ll> &b){
	ll i=0,j=0;
	vector<ll> val;

	while(i<a.size() && j<b.size()){
		if(a[i]<b[j]){
			val.push_back(a[i++]);
		}
		else{
			val.push_back(b[j++]);
		}
	}

	while(i<a.size()){
		val.push_back(a[i++]);
	}

	while(j<b.size()){
		val.push_back(b[j++]);
	}

	return val;
}


void build(ll index,ll left,ll right,vector<ll> &val){
	if(left==right){
		st[index].push_back(val[left]);
		return;
	}
	ll mid=(left+right)/2;
	build(2*index,left,min(mid,right),val);
	build(2*index+1,max(left,mid+1),right,val);
	st[index]=merge(st[2*index],st[2*index+1]);
}

ll query(ll index,ll left,ll right,ll a,ll b,ll &k){
	if(left> right){
		return 0;
	}
	if(left==a && right==b){
		return st[index].end()-upper_bound(st[index].begin(),st[index].end(),k);
	}

	ll mid=(left+right)/2;

	if(b<=mid){
		return query(2*index,left,mid,a,b,k);
	}
	else if(a>mid){
		return query(2*index+1,mid+1,right,a,b,k);
	}
	else{
		return query(2*index,left,min(mid,right),a,min(b,mid),k) + query(2*index+1,max(left,mid+1),right,max(a,mid+1),b,k);
	}
}

int main(){
	ll n;
	cin>>n;
	vector<ll> val(n+1);
	for(int i=1;i<=n;i++){
		cin>>val[i];
	}

	build(1,1,n,val);

	ll q;
	cin>>q;
	while(q--){
		ll a,b,k;
		cin>>a>>b>>k;

		cout<<query(1,1,n,a,b,k)<<endl;
	}

	return 0;
}
