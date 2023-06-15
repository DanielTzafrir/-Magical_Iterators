#include "MagicalContainer.hpp"

namespace ariel {
	
	bool MagicalContainer::isPrime(int number) {
		if (number < 2) {
			return false;
		}
		for (int i = 2; i <= sqrt(number); ++i) {
			if (number % i == 0) {
				return false;
			}
		}
		return true;
	}
	
	void MagicalContainer::addElement(int element) {
		elements.push_back(element);
		sort(elements.begin(), elements.end());
		primePointers.clear();
        	for (vector<int>::size_type i = 0; i< elements.size(); i++) {
		        if (isPrime(elements[i])) {
		        	primePointers.push_back(&elements[i]);
		        }
            	}	
	}
	
	void MagicalContainer::removeElement(int element) {
		auto it = find(elements.begin(), elements.end(), element); // Find the iterator to the element
		if (it == elements.end()) {
			throw runtime_error("Element is not in the container!");
		}
		elements.erase(it);
		auto pointerIt = find(primePointers.begin(), primePointers.end(), &(*it));
		if (pointerIt != primePointers.end()) {
			primePointers.erase(pointerIt);
		}
    	}	
    	
    	vector<int>::size_type MagicalContainer::size() const {
		return elements.size();
	}
}
