/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  2.5
 *
 *        Version:  1.0
 *        Created:  2012年12月08日 11时23分24秒
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
/*
 *racing and calculations(speed v vs. speed 2v)
 */
Node* getCHead(Node*node){
    Node*fast,*slow;
    fast=node;
    slow=node;
    int counter=0;
    int total = 1000;
    while(counter!=1&&(total--)>0){
        if(fast!=NULL){
            fast=fast->getNext();
        }else{
            total=0;
            break;
        }
        if(fast!=NULL){
            fast = fast->getNext();
        }else{
            total=0;
            break;
        }
        slow=slow->getNext();
        if(fast==slow)
            counter++;
    }    
    if(total>0){
        slow = node;
        while(fast!=slow){
            slow = slow->getNext();
            fast = fast->getNext();
        }
        return fast;
    }else{
        return NULL;
    }
}
int main(){
    Node* head = new Node(0);
    head->appendToTail(1);
    head->appendToTail(2);
    head->appendToTail(3);
    head->appendToTail(4);
    head->appendToTail(5);
    Node*two=head->getNext()->getNext();
    Node*five=two->getNext()->getNext()->getNext();
    five->setNext(two);
    Node*cHead = getCHead(head);
    if(cHead){
        cout<<cHead->getData()<<endl;
    }else{
        cout<<"NULL"<<endl;
    }
    return 0;
}
