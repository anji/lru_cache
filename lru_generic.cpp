#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

#define CACHE_SIZE 10

template <typename K, typename V>
class LRU_cache {
private:
    int size;
    unordered_map<K, pair<V,typename list<K>::iterator> > KVmap;
    list<K> key_list;

public:
  LRU_cache(int s) {
    size = s;
  }

  void put(K key, V val) {
    auto loc= KVmap.find(key);

    if(loc == KVmap.end() ) {
      key_list.push_front(key);
      KVmap[key] = {val, key_list.begin()};

      if(KVmap.size() > size) {
        KVmap.erase(key_list.back());
        key_list.pop_back();
      }
    }

    else {
      key_list.erase(loc->second.second);
      key_list.push_front(key);
      KVmap[key] = {val, key_list.begin()};
    }
  }

  bool get(K key, V &val) {
    auto loc = KVmap.find(key);
    if(loc == KVmap.end() ) {
      return false;
    }
    key_list.erase(loc->second.second);
    key_list.push_front(key);
    KVmap[key] = {loc->second.first, key_list.begin()};
    val = loc->second.first;
    return true;
  }

  void display() {
  	typename list<K>::iterator it;
  	for(it = key_list.begin(); it != key_list.end(); it++) {
  		cout << "(" << *it << "," << KVmap[*it].first << ") , ";
  	}
  	cout << endl;
  }

};

int main() {
  LRU_cache<int,string> lr(CACHE_SIZE);
  string s;
  bool res;

  //pushing elemnts to cache
  lr.put(1, "one");
  lr.put(2, "two");
  lr.put(3,"three");
  lr.put(4,"four");
  lr.put(5,"five");
  lr.put(6,"six");
  lr.put(7,"seven");
  lr.put(8,"eight");
  lr.put(9,"nine");
  lr.put(10,"ten");
  lr.display();

  lr.put(20,"twenty");
  lr.display();

  lr.put(3, "three");
  lr.display();

  res = lr.get(4 , s);
  if(res)
    cout << s << endl;
  else
    cout << "Not found in cache" << endl;

  return 0;

}
