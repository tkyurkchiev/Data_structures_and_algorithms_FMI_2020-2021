#pragma once
#include <functional>
#include <vector> 

template<class KeyType, class ValueType, class HashFunc =  std::hash<KeyType>>
class HashTable
{
	virtual void free();
	void copyFrom(const HashTable<KeyType, ValueType, HashFunc>& other);

protected:
	struct Pair
	{
		Pair(const KeyType& key, const ValueType& value) : key(key), value(value){}
		KeyType key;
		ValueType value;
	};

	HashFunc hasher;

	int capacity = 1;
	std::vector<Pair*> data;

public:
	HashTable();
	HashTable(const HashTable& other);
	const HashTable& operator=(const HashTable& other);
	virtual ~HashTable();

	virtual void put(KeyType key, ValueType value) = 0;
	virtual const ValueType& get(KeyType key) = 0;
	virtual bool remove(KeyType key) = 0;
};

template<class KeyType, class ValueType, class HashFunc>
HashTable<KeyType, ValueType, HashFunc>::HashTable() : data(32), capacity(32)
{}

template<class KeyType, class ValueType, class HashFunc>
HashTable<KeyType, ValueType, HashFunc>::~HashTable()
{
	free();
}

template<class KeyType, class ValueType, class HashFunc>
HashTable<KeyType, ValueType, HashFunc>::HashTable(const HashTable& other)
{
	copyFrom(other);
}

template<class KeyType, class ValueType, class HashFunc>
void HashTable<KeyType, ValueType, HashFunc>::free()
{
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] != nullptr)
			delete data[i];
	}
}

template<class KeyType, class ValueType, class HashFunc>
const HashTable<KeyType, ValueType, HashFunc>& HashTable<KeyType, ValueType, HashFunc>::operator=(const HashTable<KeyType, ValueType, HashFunc>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class KeyType, class ValueType, class HashFunc>
void HashTable<KeyType, ValueType, HashFunc>::copyFrom(const HashTable<KeyType, ValueType, HashFunc>& other)
{
	capacity = other.capacity;
	data.resize(capacity);
	for (int i = 0; i < other.data.size(); i++)
	{
		if (other.data[i] != nullptr)
			data[i] = new Pair(*other.data[i]);
	}
}