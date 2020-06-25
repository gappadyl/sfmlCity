#include "LinkedPathList.h"
LinkedPathList::LinkedPathList()
{
	head = NULL; 
}

LinkedPathList::LinkedPathList(sf::Vector2i data)
{
	head = new Path(data); 
}

LinkedPathList::~LinkedPathList()
{
	if (size() == 1)
	{
		delete head; 
	}
	else
	{//i think this should delete each node
		for (int x = 0; x < size(); x++)
		{
			Path* cur = head; 

			while (cur->next != NULL)
			{
				cur = cur->next; 
			}

			delete cur; 
		}

		delete head; 
	}
}

int LinkedPathList::size()
{
	int count = 0; 

	Path* cur = head; 

	while (cur != NULL)
	{
		count++; 
		cur = cur->next; 
	}

	return count; 
}

void LinkedPathList::add(sf::Vector2i data)
{
	Path* cur = head; 
	if (cur == NULL)
	{
		head = new Path(data); 
	}
	else
	{

		while (cur->next != NULL)
		{
			cur = cur->next;
		}

		cur->next = new Path(data);
	}
}

void LinkedPathList::remove()
{
	Path* cur = head; 
	while (cur->next->next != NULL)
	{
		cur = cur->next; 
	}
	cur->next = cur->next->next; 
}

void LinkedPathList::remove(int index)
{
	Path* cur = head; 

	for (int x = 0; x < index-1; x++)
	{
		cur = cur->next; 
	}

	cur->next = cur->next->next; 
}

void LinkedPathList::reverse()
{
	// Initialize current, previous and 
		// next pointers 
	Path* current = head;
	Path* prev = NULL, * next = NULL;

	while (current != NULL) {
		// Store next 
		next = current->next;

		// Reverse current node's pointer 
		current->next = prev;

		// Move pointers one position ahead. 
		prev = current;
		current = next;
	}

	head = prev;

}
void LinkedPathList::printPath()
{
	Path* cur = head;
	while (cur != NULL)
	{
		std::cout << "x: " << cur->data.x << " y: " << cur->data.y << std::endl; 
		cur = cur->next; 
	}
}