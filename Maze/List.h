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
		while (node) //node != nullptr과 같은 조건식
		{

			Node<T>* deleteNode = node; //temp를 만들어줘야 node가 next로 넘어갈수있다.
			node = node->next;
			delete deleteNode;
		}
	}


	Node<T>* GetNode(int index) //인덱스의 노드를 가져오는 메소드
	{

		Node<T>* node = _head->next;

		if (node == _tail) //리스트 안에 노드가 없을 수도 있죠
			return nullptr;

		for (int i = 0; i < index; i++)
		{
			if (node->next == _tail)
				return nullptr; //dummy를 달라고 할땐 주면 안되죠.
			node = node->next;
		}
		return node;

	}

	//					[node] 이 자리에 낑겨서 insert 해줄것
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

		return nextNode; //필요할지도 모르니 삭제한 거 다음 노드를 그냥 넘겨주자.
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
		Node<T>* node = new Node<T>(data);//새로 넣을 노드
		//더미가 있을 때의 장점은 head, tail을 계속 수정해주지 않아도 된다는것
		Node<T>* nextNode = _head->next; // nextNode를 로컬로 만들어두고
		_head->next = node;
		node->prev = _head;

		node->next = nextNode; //nextNode랑 결합
		nextNode->prev = node;

		return node; //혹시 필요할지도 모르니 방금 넣은 노드 뱉어줌.
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

