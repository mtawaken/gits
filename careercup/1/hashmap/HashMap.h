#include<stdio.h>
#include"Entry.h"
class HashMap {
private:
	static const int DEFAULT_INITCAPACITY = 32;
	static const float DEFAULT_LOADFACTOR = 0.75f;
	static const int MAX_CAPACITY = 1 << 30;
	Entry** table;
	float loadFactor;
	int threshold;
	int capacity;
	int size;
public:
	HashMap() {
		capacity = DEFAULT_INITCAPACITY;
		loadFactor = DEFAULT_LOADFACTOR;
		threshold = this->capacity * this->loadFactor;
		size = 0;
		table = new Entry*[this->capacity];
	}
	HashMap(int initCapacity, int loadFactor) {
		this->capacity = initCapacity <= 0 ? DEFAULT_INITCAPACITY : 1;
		if (this->capacity != DEFAULT_INITCAPACITY) {
			while (this->capacity < initCapacity) {
				this->capacity = this->capacity << 1;
			}
		}
		this->loadFactor = loadFactor <= 0 ? DEFAULT_LOADFACTOR : loadFactor;
		threshold = this->capacity * this->loadFactor;
		size = 0;
		table = new Entry*[this->capacity];
	}
	int hash(int key) {
		unsigned int h = 0;
		h ^= key;
		h ^= (h >> 20) ^ (h >> 12);
		return h ^ (h >> 7) ^ (h >> 4);
	}
	int indexFor(int h) {
		return h & (this->capacity - 1);
	}
	void resize() {
		if (this->capacity == MAX_CAPACITY) {
			threshold = 0x7fffffff;
		} else {
			int newCapacity = this->capacity * 2;
			Entry** newTable = new Entry*[newCapacity];
			for (int i = 0; i < this->capacity; i++) {
				for (Entry* e = table[i]; e != NULL;) {
					Entry* n = e->next;
					int h = hash(e->key);
					int index = h & (newCapacity - 1);
					e->next = newTable[index];
					e->hash = h;
					newTable[index] = e;
					e = n;
				}
			}
			delete table;
			table = newTable;
			this->capacity = newCapacity;
			threshold = capacity * loadFactor;
		}
	}
	void addEntry(int index, int h, int key, int value) {
		size++;
		if (size >= threshold) {
			resize();
			index = indexFor(h);
		}
		Entry* old = table[index];
		table[index] = new Entry(h, key, value, old);
	}
	int put(int key, int value) {
		int h = hash(key);
		int index = indexFor(h);
		for (Entry* e = table[index]; e != NULL; e = e->next) {
			if (e->hash == h && e->key == key) {
				int oldValue = e->value;
				e->value = value;
				return oldValue;
			}
		}
		addEntry(index, h, key, value);
		return value;
	}
	int get(int key) {
		int h = hash(key);
		int index = indexFor(h);
		for (Entry* e = table[index]; e != NULL; e = e->next) {
			if (e->hash == h && e->key == key) {
				return e->value;
			}
		}
		return 0;
	}
};
