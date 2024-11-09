#include <iostream>

template<class T>
struct Node
{
    Node* next;
    T data;

    Node(const T& value, Node<T>* n=nullptr) : data(value), next(n){};
};

template<class T>
void print(Node<T>* list)
{
    Node<T>* head = list;
    while (head)
    {
        std::cout << head->data;
        if(head->next){
            std::cout << "->";
        }
        head = head->next;
    }
};

template <class T>
void free(Node<T>* list){
    Node<T>* head = list;
    while(head){
        Node<T>* curr = head;
        head=head->next;
        delete curr;
    }
}

template<class T>
Node<T>* getMid(Node<T>* list){
    Node<T>* slow = list;
    Node<T>* fast = list->next;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
};

template <class T>
// tuk rabotim s referecniq, inache ako sa kopiq, sled skoupa - ne sme promenili nishto!
void push_back(Node<T>*& head, Node<T>*& tail, Node<T>* value)
{
    if(!head){
        head = tail = value;
    }
    else{
        tail->next = value;
        tail = tail->next;
    }
}

template<class T>
Node<T>* merge(Node<T>* first, Node<T>* second){
    Node<T>* resultHead = nullptr;
    Node<T>* resultTail = nullptr;

    while(first && second){
        if(first->data <= second->data){
                push_back(resultHead,resultTail,first);
                first = first->next;
        }
        else{
            push_back(resultHead,resultTail,second);
            second = second->next;
        }
    }

    while(first){
        push_back(resultHead,resultTail,first);
        first=first->next;
    }

    while(second){
        push_back(resultHead,resultTail,second);
        second = second->next;
    }

    return resultHead;
};

template<class T>
Node<T>* mergeSort(Node<T>* list)
{
    if(!list || !list->next){
        return list;
    }

    Node<T>* mid = getMid<T>(list);
    Node<T>* left = list;
    Node<T>* right = mid->next;
    // vajno e za razdelqneto na dvata spisuka na dve polovini
    mid->next = nullptr;

    left = mergeSort<T>(left);
    right = mergeSort<T>(right);

    return merge<T>(left,right);
};


int main(){
    Node<int>* list = new Node<int>(5, new Node<int>(4, new Node<int>(22, new Node<int>(42, new Node(2)))));
    
    Node<int>* result = mergeSort(list);

    print(result);
    free(result);
}