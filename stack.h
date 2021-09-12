#pragma once
#include "itemType.h"
namespace stack
{
	class Stack
	{
	private:
		struct Node
		{
			ItemType* data;
			Node* next;
		};

		Node* top; //points to top of the stack

	public:
		Stack() : top(nullptr) {}
		~Stack();
		bool isEmpty();
		void makeEmpty();
		void push(ItemType& item);
		ItemType& pop();
	};
}
