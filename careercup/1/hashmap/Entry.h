class Entry {
public:
	int hash, key, value;
	Entry* next;
	Entry(int hash, int key, int value) :
			hash(hash), key(key), value(value), next(NULL) {
	}
	Entry(int hash, int key, int value, Entry* next) :
			hash(hash), key(key), value(value), next(next) {
	}
};
