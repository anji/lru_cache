#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

#define CACHE_SIZE 10

class LRU_cache {
private:
    int size;
    unordered_map<int, pair<int, list<int>::iterator> > KVmap;
    list<int> key;

public:
  LRU_cache(int s) {
    size = s;
  }

  void put(int k, int v) {
    auto loc= KVmap.find(k);

    if(loc == KVmap.end() ) {
      key.push_front(k);
      KVmap[k] = {v, key.begin()};

      if(KVmap.size() > size) {
        KVmap.erase(key.back());
        key.pop_back();
      }
    }

    else {
      key.erase(loc->second.second);
      key.push_front(k);
      KVmap[k] = {v, key.begin()};
    }
  }

  bool get(int k, int &v) {
    auto loc = KVmap.find(k);
    if(loc == KVmap.end() ) {
      return false;
    }
    key.erase(loc->second.second);
    key.push_front(k);
    KVmap[k] = {loc->second.first, key.begin()};
    v = loc->second.first;
    return true;
  }

  void display() {
  	list<int>::iterator it;
  	for(it = key.begin(); it != key.end(); it++) {
  		cout << "(" << *it << "," << KVmap[*it].first << ") , ";
  	}
  	cout << endl;
  }

};

int main() {
  LRU_cache lr(CACHE_SIZE);

  //pushing elemnts to cache
  for(int i=0; i<CACHE_SIZE+2; i++) {
  	lr.put(i,i*i);
  }


  lr.display();

  lr.put(CACHE_SIZE/2, (CACHE_SIZE*CACHE_SIZE)/4 );
  lr.display();


  return 0;

}
