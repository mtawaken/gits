/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  2.3 *
 *
 *        Version:  1.0
 *        Created:  2012年12月08日 10时43分19秒
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
bool removeNode(Node*p){
    if(!p||!p->getNext())
        return false;
    Node*next = p->getNext();
    p->setData(next->getData());
    p->setNext(next->getNext());
    delete next;
}
int main(){
    Node*head=new Node(0);
    head->appendToTail(1);
    head->appendToTail(2);
    head->appendToTail(3);
    head->appendToTail(4);
    head->appendToTail(5);
    head->printAll();
    Node*p=head->getNext()->getNext()->getNext();//3
    removeNode(p);
    head->printAll();
    return 0;
}
