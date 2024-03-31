#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Node
{
public:
	Node(T data) : data(data), prev(nullptr), next(nullptr) { }
public:	
	T data;
	Node* prev;
	Node* next;
};

template<typename T>
class List
{
public:
	List()
	{
		_head = new Node<T>(0);
		_tail = new Node<T>(0);
		_head->next = _tail;
		_tail->prev = _head;
	}

	~List()
	{
		Node<T>* node = _head;
		while (node) //node != nullptr�� ���� ���ǽ�
		{

			Node<T>* deleteNode = node; //temp�� �������� node�� next�� �Ѿ���ִ�.
			node = node->next;
			delete deleteNode;
		}
	}


	Node<T>* GetNode(int index) //�ε����� ��带 �������� �޼ҵ�
	{

		Node<T>* node = _head->next;

		if (node == _tail) //����Ʈ �ȿ� ��尡 ���� ���� ����
			return nullptr;

		for (int i = 0; i < index; i++)
		{
			if (node->next == _tail)
				return nullptr; //dummy�� �޶�� �Ҷ� �ָ� �ȵ���.
			node = node->next;
		}
		return node;

	}

	//					[node] �� �ڸ��� ���ܼ� insert ���ٰ�
	//	[dummy][prevNode]<->[posNode][2][3][dummy]
	//	[head]								[tail]
	void Insert(Node<T>* posNode, T data)
	{
		Node<T>* node = new Node<T>(data);
		Node<T>* prevNode = posNode->prev;
		
		prevNode->next = node;
		node->prev = prevNode;

		posNode->prev = node;
		node->next = posNode;
	}
	
	Node<T>* Remove(Node<T>* node)
	{
		Node* prevNode = node->prev;
		Node* nextNode = node->next;

		(prevNode)->next = node->next;
		(nextNode)->prev = node->prev;

		delete node;

		return nextNode; //�ʿ������� �𸣴� ������ �� ���� ��带 �׳� �Ѱ�����.
	}

	void Print()
	{
		Node<T>* node = _head->next;
		while (node != _tail)
		{
			cout<< node->data << " ";
			node = node->next;
		}
		cout << endl;
	}



	//	[dummy]<->[node]<->[nextNode][2][3][dummy]
	//	[head]								[tail]
	Node<T>* AddAtHead(T data)
	{
		Node<T>* node = new Node<T>(data);//���� ���� ���
		//���̰� ���� ���� ������ head, tail�� ��� ���������� �ʾƵ� �ȴٴ°�
		Node<T>* nextNode = _head->next; // nextNode�� ���÷� �����ΰ�
		_head->next = node;
		node->prev = _head;

		node->next = nextNode; //nextNode�� ����
		nextNode->prev = node;

		return node; //Ȥ�� �ʿ������� �𸣴� ��� ���� ��� �����.
	}

	Node* AddAtTail(T data)
	{
		Node<T>* node = new Node<T>(data);
		Node<T>* prevNode = _tail->prev;

		node->prev = prevNode;
		prevNode->next = node;

		node->next = _tail;
		_tail->prev = node;

		return node;
	}

private:
	Node<T>* _head = nullptr;
	Node<T>* _tail = nullptr;
};

