/*
 * VMap.h
 *
 *  Created on: Dec 14, 2018
 *      Author: hvr1hc
 */

#ifndef SOURCE_VMAP_H_
#define SOURCE_VMAP_H_

#include <map>
#include <mutex>
using namespace std;

template <typename X, typename Y>
class VMap {

public:
	VMap() 			{}
	virtual ~VMap() {}

	int insert_(const X& key, const Y& value){
		lock_guard<std::mutex> lock(_mtx);
		_Content.insert(std::pair<X, Y>(key, value));
		return 0;
	}

	bool find_(const X& key, Y& value){
		lock_guard<std::mutex> lock(_mtx);
		auto it = _Content.find(key);
		if(it != _Content.end()){
			value = it->second;
			return true;
		}
		return false;
	}

	bool delete_(const X& key){
		lock_guard<std::mutex> lock(_mtx);
		_Content.erase(key);
		return true;
	}

protected:
	map<X, Y> 	_Content;
	mutex 		_mtx;
};

#endif /* SOURCE_VMAP_H_ */
