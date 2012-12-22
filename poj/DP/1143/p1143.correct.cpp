/*
 * =====================================================================================
 *
 *       Filename:  p1143.correct.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月22日 12时57分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
short d[1<<20];//-1:undone;0:false:1:true
int encode(bool* nums){
    int state = 0;
    for(int i=20;i>0;i--){
        if(nums[i]==1){
            state += 1<<(20-i);
        }
    }
    return state;
}
void decode(int state,bool* nums){
    nums[0]=0;
    for(int i=20;i>0;i--){
        if(state%2==1){
            nums[i]=1;
        }else{
            nums[i]=0;
        }
        state = state>>1;
    }
}
int change(int state,int pos){
    bool nums[21];
    decode(state,nums);
    for(int i=pos;i<=20;i+=pos){
        nums[i]=0;
        for(int j=2;j+i<=20;j++){
            if(nums[j]==0){
               nums[j+i]=0;
            }
        }
    }
    return encode(nums);
}
bool work(int state){
    if(d[state]>-1)
        return d[state];
    bool nums[21];
    decode(state,nums);
    int orig_state = state;
    int new_state;
    bool flag=false;
    for(int i=0;i<21;i++){
        if(nums[i]!=0){
            new_state = change(orig_state,i);
            if(work(new_state)==false){
                flag = true;
                break;
            }
        }
    }
    d[state]=flag;
    return d[state];
}
int main(){
    bool nums[21];
    int n,tmp,times;
    cin>>n;
    vector<int> v;
    times=1;
    while(n!=0){
        memset(nums,0,sizeof(nums));
        memset(d,-1,sizeof(d));
        v.clear();
        for(int i=0;i<n;i++){
            cin>>tmp;
            nums[tmp]=1;
        }
        int orig_state = encode(nums);
        int new_state;
        for(int i=0;i<21;i++){
            if(nums[i]!=0){
                new_state = change(orig_state,i);
                if(work(new_state)==false){
                    v.push_back(i);
                }
            }
        }
        cout<<"Test Case #"<<times<<endl;
        if(v.empty()){
            cout<<"There's no winning move."<<endl;
        }else{
            cout<<"The winning moves are:";
            for(int i=0;i<v.size();i++){
                cout<<" "<<v[i];
            }
            cout<<endl;
        }
        cout<<endl;
        times++;
        cin>>n;
    }
    
    return 0;
}
