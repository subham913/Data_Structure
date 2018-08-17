#include<bits/stdc++.h>
using namespace std;

int maximum;
string s;
vector< pair<int,string> > words[1000];
void hashing(string word){
    int val1=0;
    int val;
    double val2,frac_part,int_part;
    string str1;
    str1="*";
    for(int j=0;j<word.size();j++){
        val1=val1+int(word[j])-96;
    }
    val2=val1*0.61803339887;
    frac_part=modf(val2,&int_part);
    frac_part=1000*frac_part;
    val2=modf(frac_part,&int_part);
    val=int_part;
    int flag=0;
    int i;
    for(i=0;i<words[val].size();i++){
        if(words[val][i].second==word){
            flag=1;
            break;
        }
    }
    if(flag==1){
        words[val][i].first+=1;
        if(maximum<words[val][i].first){
            maximum=words[val][i].first;
            s=word;
        }
    }
    else{
        
        words[val].push_back(make_pair(1,word));
        if(maximum<1){
            s=word;
        }
    }
}
int main(){
    int q;
    maximum=0;
    cin>>q;
    for(int i=0;i<q;i++){
        string word;
        cin>>word;
        hashing(word);
    }
    cout<<s;
}