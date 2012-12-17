/*
 * =====================================================================================
 *
 *       Filename:  work.cpp
 *
 *    Description:  MEIZI
 *
 *        Version:  1.0
 *        Created:  2012年11月03日 20时04分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<fstream>
#include<iostream>
using namespace std;
int main(){
    ifstream infile;
    infile.open("binary");
    if(infile){
        cout<<"open success!"<<endl;
        ofstream outfile;
        outfile.open("binaryout",ofstream::out);
        if(!outfile){
            cout<<"open write file failure"<<endl;
            return 0;
        }else{
            cout<<"open outfile success!"<<endl;
        }
        char in,out,tmp;
        int count=0;
        int totalInterator = 0;
        out=0;
        while(true){
            cout<<"totalInterator:"<<totalInterator<<endl;
            totalInterator++;
            in = infile.get();
            if(!infile.good()){
                break;
            }
            if(in==10){
                continue;
            }
            tmp = ((in-'0')<<(7-count));
            out = out | tmp;
            count++;
            if(count==8){
                count=0;
                outfile.put(out);
                outfile.flush();
                out=0;
            }
        }
        outfile.flush();
        outfile.close();
        infile.close();
        cout<<"done"<<endl;

    }else{
        cout<<"open error!"<<endl;
    }
    return 0;
}
