#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

template<size_t capacity>
class LRU{
public:
	bool lookup(int isbn,int* price){
		auto it = cache_.find(isbn);
		if(it==cache_.cend()){
			return false;
		}
		*price = it->second.second;
		moveToFront(isbn,it);
		return true;
	}
	void insert(int isbn,int price){
		auto it = cache_.find(isbn);
		if(it!=cache_.end()){
			moveToFront(isbn,it);
		}else{
			if(cache_.size()==capacity){
				cache_.erase(data_.back());
				data_.pop_back();
			}
			data_.emplace_front(isbn);
			cache_[isbn]={data_.begin(),price};
		}
	}
	bool erase(int isbn){
		auto it = cache_.find(isbn);
		if(it==cache_.end())
			return false;
		data_.erase(it->second.first);
		cache_.erase(it);
		return true;
	}
private:
	typedef unordered_map<int,pair<list<int>::iterator,int>> Table;
	Table cache_;
	list<int> data_;
	void moveToFront(int isbn,Table::iterator& it){
		data_.erase(it->second.first);
		data_.emplace_front(isbn);
		it->second.first = data_.begin();
	}
};

int main(){

}