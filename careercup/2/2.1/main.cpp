/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  2.1
 *
 *        Version:  1.0
 *        Created:  2012年12月07日 21时06分12秒
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
Node*removeDuplicates(Node&head){
    int*check=new int[100];
    Node*p=head.getNext();
    Node*previous=&head;
    check[head.getData()]=1;
    while(p){
        if(check[p->getData()]!=0){
            previous->setNext(p->getNext());
            delete p;
            p = previous->getNext();
        }else{
            check[p->getData()]=1;
            previous=p;
            p = p->getNext();
        }        
    }
    return &head;
}
int main(){
    Node head(0);
    head.appendToTail(1);
    head.appendToTail(2);
    head.appendToTail(3);
    head.appendToTail(5);
    head.appendToTail(2);
    head.appendToTail(3);
    head.appendToTail(2);
    head.appendToTail(6);
    head.printAll();
    Node* p = removeDuplicates(head);
    p->printAll();
    return 0;
}
