/****************************************************************************
 ObjectPool class is used to create enemy and bullet lists.
 During the game, many enemies and bullets needs to be created.
 To not create new entity object each time; entities are saved in the pool after they leave the scene.
 When we need to show new entities, we send the entities from pool and save memory.
 ****************************************************************************/

#pragma once
#include <list>

template <typename T, int TAG>
class ObjectPool {
public:
	ObjectPool() { }

	// If there is an entitiy in the pool; return it otherwise return a new entity.
	T* getEntity() {
		if (_objectPool.size() <= 0) {
			return new T(TAG);
		}
		T* first = _objectPool.front();
		_objectPool.pop_front();
		return first;
	}

	// Add entity to pool.
	// This way we save the created entities after they leave the scene.
	// This we do not create hundreds of entities for the whole game and keep 
	void addObjectToPool(T* obj) {
		_objectPool.push_back(obj);
	}

	// Delete all entities from the pool 
	// TODO Use it on game destroy
	void destroy() {
		typename std::list<T*>::iterator it;
		for (it = _objectPool.begin(); it != _objectPool.end(); ++it) {
			delete* it;
		}
	}

protected:
	std::list<T*> _objectPool;
};

