/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  2.4
 *
 *        Version:  1.0
 *        Created:  2012年12月08日 10时51分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<iostream>
#include"node.h"
using namespace std;
Node*getSum(Node*s1,Node*s2){
    Node*sum=NULL;
    Node*n1,*n2;
    n1=s1;
    n2=s2;
    int addition,res;
    addition=0;
    res=0;
    while(n1||n2){
        res=0;
        if(n1!=NULL){
            res+=n1->getData();
            n1=n1->getNext();
        }
        if(n2!=NULL){
            res+=n2->getData();
            n2=n2->getNext();
        }
        res+=addition;
        if(res>9){
            res-=10; 
            addition=1;
        }else{
            addition=0;
        }
        if(!sum){
            sum = new Node(res);
        }else{
            sum->appendToTail(res);
        }
    }
    if(addition!=0) {
        sum->appendToTail(addition);
    }
    return sum;
}
int main(){
    Node*head=new Node(3);
    head->appendToTail(1);
    head->appendToTail(5);
    head->printAll();
    Node*head2=new Node(5);
    head2->appendToTail(9);
    head2->appendToTail(4);
    head2->appendToTail(9);
    head2->printAll();
    Node*sum=getSum(head,head2);
    sum->printAll();
    Node::destroyList(head);
    Node::destroyList(head2);
    Node::destroyList(sum);
    return 0;
}
