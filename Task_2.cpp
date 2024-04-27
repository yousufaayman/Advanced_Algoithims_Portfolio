#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *nextNode;
    Node *prevNode;
    Node(int data) : data(data), nextNode(nullptr), prevNode(nullptr) {}
};

class LinkedList
{
public:
    Node *head;
    Node *tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    void insertEnd(int data)
    {
        Node *newNode = new Node(data);
        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->nextNode = newNode;
            newNode->prevNode = tail;
            tail = newNode;
        }
    }

    void Traverse()
    {
        cout << "Linked List:\n";
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->nextNode;
        }
        cout << endl;
    }

    Node *lastNode(Node *node)
    {
        while (node && node->nextNode)
        {
            node = node->nextNode;
        }
        return node;
    }

    void quickSort(Node *l, Node *h)
    {
        tail = lastNode(head);
        quickSortHelper(l, h);
    };

    void quickSortHelper(Node *l, Node *h)
    {
        if (h != nullptr && l != h && l != h->nextNode)
        {
            Node *p = partition(l, h);
            quickSortHelper(l, p->prevNode);
            quickSortHelper(p->nextNode, h);
        }
    };

    Node *partition(Node *l, Node *h)
    {
        int x = h->data;
        Node *i = l->prevNode;
        for (Node *j = l; j != h; j = j->nextNode)
        {
            if (j->data <= x)
            {
                i = (i == nullptr) ? l : i->nextNode;
                swap(i->data, j->data);
            }
        }
        i = (i == nullptr) ? l : i->nextNode;
        swap(i->data, h->data);
        return i;
    };
};

int main()
{
    LinkedList linkedList;
    linkedList.insertEnd(102);
    linkedList.insertEnd(5);
    linkedList.insertEnd(46);
    linkedList.insertEnd(32);
    linkedList.insertEnd(9);
    linkedList.insertEnd(69);
    linkedList.insertEnd(23);
    linkedList.insertEnd(65);

    cout << "Original Linked List: ";
    linkedList.Traverse();

    linkedList.quickSort(linkedList.head, linkedList.tail);

    cout << "Sorted: ";
    linkedList.Traverse();

    return 0;
}