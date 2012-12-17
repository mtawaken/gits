/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  2.2
 *
 *        Version:  1.0
 *        Created:  2012年12月08日 10时06分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include <iostream>
#include "node.h"
using namespace std;
Node* findNthToTail(int n,Node*head){
    Node*a,*b;
    a=b=head;
    int i;
    for(i=0;i<n&&b;i++){
        b=b->getNext();
    }
    if(i!=n)
        return NULL;
    while(b){
        a=a->getNext();
        b=b->getNext();
    }
    return a;
}
int main(){
    Node* head=new Node(0);
    head->appendToTail(1);
    head->appendToTail(2);
    head->appendToTail(3);
    head->appendToTail(4);
    head->appendToTail(5);
    head->appendToTail(6);
    head->printAll();
    Node*p=findNthToTail(3,head);
    cout<<p->getData()<<endl;
    Node::destroyList(head);
    return 0;
}
