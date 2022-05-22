#pragma once
#include <utility>
#include "vector"
#include <queue>
#include <stack>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "string"
using namespace std;

namespace ariel{
    template<typename T=string>
    class OrgChart {

    private:
        struct Node {
            T data;
            vector<Node *> children;

            explicit Node(T d) : data(d) {}
        };

        enum Order {
            level_order,
            reversed_order,
            preorder
        };

        Node *root = nullptr;

//        return the node with the current data,throw exception if it does not exist.
        Node *find_node(T data) {

            stack<Node *> s;
            s.push(root);

            while (!s.empty()) {
                Node *curr = s.top();
                if (curr->data == data) {
                    return curr;
                }
                s.pop();
                for (auto a: curr->children) {
                    s.push(a);
                }
            }
            throw invalid_argument("\nthe first element is not exist in the tree.");
        }

//        return the most left son for the start in reverse level order.
        static Node *find_left(Node *root) {
            Node *tmp = root;
            while (!tmp->children.empty()) {
                tmp = tmp->children.at(0);
            }
            return tmp;
        }

//        return a string for pretty printing the tree.
        static string pretty_print_tree(Node *tree, string indent, bool last) {
            string string;
            string += indent + "+-" + tree->data + "\n";
            if (last) {
                indent += "   ";
            } else {
                indent += "|  ";
            }
            for (unsigned long i = 0; i < tree->children.size(); i++) {
                string += pretty_print_tree(tree->children.at(i), indent, i == tree->children.size() - 1);
            }
            return string;
        }

    public:


        OrgChart()=default;
        OrgChart(OrgChart<T> &other){
            this->root=other.root;
        }
        OrgChart &operator=(OrgChart<T> other){
            this->root=other.root;
            other.root= nullptr;
        }

        OrgChart(OrgChart<T> &&other) noexcept {
            this->root=other.root;
            other.root= nullptr;
        }
        OrgChart &operator=(OrgChart<T> &&other)noexcept{
            this->root=other.root;
            other.root= nullptr;
        }
        ~OrgChart(){

            if(root!= nullptr){
                stack<Node*> stack;
                queue<Node*>queue;
                queue.push(root);
                Node* tmp= nullptr;

                while (!queue.empty()){
                    tmp=queue.front();
                    stack.push(tmp);
                    queue.pop();
                    for (auto it = tmp->children.rbegin(); it != tmp->children.rend(); ++it){
                        queue.push(*it);
                    }
                }
                while (!stack.empty()){
                    tmp=stack.top();
                    stack.pop();
                    delete tmp;
                }
            }

        }
//        add new root to the tree or replace if it exists.
        OrgChart& add_root(T new_root){
            if(root== nullptr){
                root=new Node(new_root);
            } else{
                root->data=new_root;
            }
            return *this;
        }
//        add child to exist node,throw exception if it does not exist.
        OrgChart& add_sub(T parent_data,T child_data){
            if(root== nullptr){
                throw invalid_argument("\ncant add sub before root.");
            }
            Node* parent= find_node(parent_data);
            Node* child=new Node(child_data);
            parent->children.push_back(child);
            return *this;
        }

        friend std::ostream& operator<< (std::ostream& output, const OrgChart& org){
            return output<<pretty_print_tree(org.root,"", true);;
        }

        class iterator{
        private:
            Node* curr;
            Order order;
            queue<Node*>queue;
            stack<Node*>stack;

        public:
            iterator(Node* ptr,Order order):curr(ptr),order(order){
                if (ptr== nullptr){
                    throw invalid_argument("\nthe tree is empty.");
                }
//                initial the stack and queue for first loop.
                stack.push(nullptr);
                queue.push(nullptr);

                if(order==reversed_order&&ptr!= nullptr){
                    stack.pop();
                    queue.pop();
                    queue.push(ptr);
                    while (!queue.empty()){
                        Node* tmp=queue.front();
                        stack.push(tmp);
                        queue.pop();
                        for (auto it = tmp->children.rbegin(); it != tmp->children.rend(); ++it){
                            queue.push(*it);
                        }
                    }
                    curr=stack.top();
                    stack.pop();
                }

            }
            explicit iterator(Node* ptr= nullptr):curr(ptr){}
            T& operator*() const {
                return curr->data;
            }

            T* operator->() const {
                return &(curr->data);
            }

            void next_level_order(){
                if(queue.empty()){
                    curr= nullptr;
                }
                else if(queue.front()== nullptr){
                    queue.pop();
                    for (auto a:curr->children)
                    {
                        queue.push(a);
                    }
                    if(queue.empty()){
                        curr= nullptr;
                        return;
                    }
                    curr=queue.front();
                    queue.pop();
                    for (auto a:curr->children)
                    {
                        queue.push(a);
                    }
                }
                else{
                    curr=queue.front();
                    queue.pop();
                    for (auto a:curr->children)
                    {
                        queue.push(a);
                    }
                }
            }
            void next_reversed_order(){
                if(stack.empty()){
                    curr= nullptr;
                }
                else{
                    curr=stack.top();
                    stack.pop();
                }

            }

            void next_preorder(){
                if(stack.empty()){
                    curr= nullptr;
                }
                else if(stack.top()== nullptr){
                    stack.pop();
                    for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it)
                    {
                        stack.push(*it);
                    }
                    if(stack.empty()){
                        curr= nullptr;
                        return;
                    }
                    curr=stack.top();
                    stack.pop();
                    for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it)
                    {
                        stack.push(*it);
                    }
                }
                else{
                    curr=stack.top();
                    stack.pop();
                    for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it)
                    {
                        stack.push(*it);
                    }
                }
            }
            iterator& operator++() {
//                increase the iterator by it order.
                if (curr != nullptr) {

                    switch (order) {
                        case level_order:
                            next_level_order();
                            break;

                        case reversed_order:
                            next_reversed_order();
                            break;

                        case preorder:
                            next_preorder();
                            break;
                    }
                }
                return *this;
            }
            bool operator!=(const iterator& it) const {
                return curr != it.curr;
            }

        };
        iterator begin_level_order() {return iterator(root,level_order); }

        iterator end_level_order() {
            if (root== nullptr){
                throw invalid_argument("\nthe tree is empty.");
            }
            return iterator(); }

        iterator begin_reverse_order() { return iterator(root, reversed_order); }

        iterator reverse_order() {
            if (root== nullptr){
                throw invalid_argument("\nthe tree is empty.");
            }
            return iterator(); }

        iterator begin_preorder() { return iterator(root,preorder); }

        iterator end_preorder() {
            if (root== nullptr){
                throw invalid_argument("\nthe tree is empty.");
            }
            return iterator(); }

        iterator begin() { return begin_level_order(); }

        iterator end() { return end_level_order(); }


    };
}
