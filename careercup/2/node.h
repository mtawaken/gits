/*
 * =====================================================================================
 *
 *       Filename:  node.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月08日 10时10分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */
#include<iostream>
using namespace std;
class Node{
    private:
        Node* next;
        int data;
    public:
        Node(int d):data(d),next(NULL){}
        Node*getNext(){
            return next;
        }
        int getData(){
            return data;
        }
        Node*appendToTail(Node&node){
            Node*p=this;
            while(p->next!=NULL){
                p = p->next;
            }
            p->next = &node;
            return this;
        }
        Node*appendToTail(int d){
            Node*newNode = new Node(d);
            return appendToTail(*newNode);
        }
        void setNext(Node*node){
            this->next = node;
        }
        void setData(int data){
            this->data = data;
        }
        void printAll(){
            Node*p = this;
            while(p){
                cout<<p->getData()<<' ';
                p = p->getNext();
            }
            cout<<endl;
        }
        static void destroyList(Node*head){
            Node* p = head->next;
            if(p){
                destroyList(p);
            }
            delete head;            
        }
};

