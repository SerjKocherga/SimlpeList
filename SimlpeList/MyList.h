#pragma once

template <class T>
class MyList {

public:


	MyList() {

		head = nullptr;
		tail = nullptr;
		listSize = 0;
	}

	~MyList() { clear(); }

	void push_back(const T data) {

		if (head == nullptr) { head = new Node<T>(data); tail = head; }
		else { tail = tail->pNext = new Node<T>(data, tail->pNext, tail); }
		listSize++;
	}

	void push_front(const T data) {

		if (head == nullptr) { head = new Node<T>(data); tail = head; }
		else { head = head->pPrev = new Node<T>(data, head, head->pPrev); }
		listSize++;
	}



	void insert(const T data, size_t index) {

		if (index == 0) { push_front(data); }
		else if (index == listSize - 1) { push_back(data); }
		else if (index <= listSize / 2) { headInsert(data, index); }
		else if (index >= listSize / 2) { tailInsert(data, index); }
	}

	void pop_front() {

		Node<T> *temp = head;
		head = head->pNext;
		delete temp;
		listSize--;
	}

	void pop_back() {

		Node<T> *temp = tail;
		tail = tail->pPrev;
		delete temp;
		listSize--;
	}

	void erase(size_t index) {

		if (index == 0) { pop_front(); }
		else if (index == listSize - 1) { pop_back(); }
		else if (index <= listSize / 2) { headErase(index); }
		else if (index >= listSize / 2) { tailErase(index); }
	}

	int GetSize() { return listSize; }

	void clear() { while (listSize) pop_front(); }

	T& operator[](const size_t index) {

		if (index <= listSize / 2) {

			size_t Size(0);
			Node<T> *current = this->head;
			while (current->pNext != nullptr) {

				if (Size == index) { return current->data; break; }
				current = current->pNext;
				Size++;
			}
		}
		if (index >= listSize / 2) {

			size_t Size(listSize - 1);
			Node<T> *current = this->tail;
			while (current->pPrev != nullptr) {

				if (Size == index) { return current->data; break; }
				current = current->pPrev;
				Size--;
			}
		}
	}

private:

	template <class T>
	class Node {

	public:

		Node(T data = T(), Node* pNext = nullptr, Node *pPrev = nullptr) {

			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}

		T data;
		Node *pNext;
		Node *pPrev;
	};

	Node<T> *head;
	Node<T> *tail;
	size_t listSize;

	void headInsert(const T data, size_t index) {

		Node<T> *hprevorious = this->head;
		for (size_t i = 0; i < index - 1; ++i)
			hprevorious = hprevorious->pNext;
		Node<T> *hnext = this->head;
		for (size_t i = 0; i < index + 1; ++i)
			hnext = hnext->pNext;
		hnext->pPrev = hprevorious->pNext = new Node<T>(data, hprevorious->pNext, hprevorious);
		listSize++;
	}

	void tailInsert(const T data, size_t index) {

		Node<T> *tprevorious = this->tail;
		for (size_t i = listSize - 1; i > index - 1; --i)
			tprevorious = tprevorious->pPrev;
		Node<T> *tnext = this->tail;
		for (size_t i = listSize - 1; i > index + 1; --i)
			tnext = tnext->pPrev;
		tnext->pPrev = tprevorious->pNext = new Node<T>(data, tprevorious->pNext, tprevorious);
		listSize++;
	}

	void headErase(size_t index) {

		Node<T> *hprevorious = this->head;
		for (size_t i = 0; i < index - 1; ++i)
			hprevorious = hprevorious->pNext;
		Node<T> *hnext = this->head;
		for (size_t i = 0; i < index + 1; ++i)
			hnext = hnext->pNext;
		Node<T> *toDelete = hprevorious->pNext;
		hprevorious->pNext = toDelete->pNext;
		hnext->pPrev = toDelete->pPrev;
		delete toDelete;
		listSize--;
	}

	void tailErase(size_t index) {

		Node<T> *tprevorious = this->tail;
		for (size_t i = listSize - 1; i > index - 1; --i)
			tprevorious = tprevorious->pPrev;
		Node<T> *tnext = this->tail;
		for (size_t i = listSize - 1; i > index + 1; --i)
			tnext = tnext->pPrev;
		Node<T> *toDelete = tprevorious->pNext;
		tprevorious->pNext = toDelete->pNext;
		tnext->pPrev = toDelete->pPrev;
		delete toDelete;
		listSize--;
	}
};

