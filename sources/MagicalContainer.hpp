#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

namespace ariel {
class MagicalContainer {
private:
	vector<int> elements;
	vector<int*> primePointers;
	bool isPrime(int number);
public:
	void addElement(int element);

	void removeElement(int element);

	vector<int>::size_type size() const;

	// Iterator classes
	class AscendingIterator {
	private:
		MagicalContainer& container;
		size_t currentIndex;

	public:
		// Constructor
		AscendingIterator(MagicalContainer& cont, size_t index = 0): container(cont), currentIndex(index) {}
		
		// Copy Constructor
		AscendingIterator(const AscendingIterator& other): container(other.container), currentIndex(other.currentIndex) {}
		
		// Move Constructor
		AscendingIterator(AscendingIterator&& other) noexcept : container(other.container), currentIndex(other.currentIndex) {
                	other.currentIndex = 0;
		}
		
		// Default Destructor
            	~AscendingIterator() = default;
		
		AscendingIterator& operator=(AscendingIterator&& other) noexcept{
			{ 
				container = other.container;
				currentIndex = other.currentIndex;
				return *this;
			}
		}
			
		AscendingIterator& operator=(const AscendingIterator& other)
		{
			if (&container != &other.container)
			{
				throw runtime_error("Not the same AscendingIterator");
			}
			container = other.container;
			currentIndex = other.currentIndex;
			return *this;
		}

		bool operator==(const AscendingIterator& other) const {
			return currentIndex == other.currentIndex;
		}

		bool operator!=(const AscendingIterator& other) const {
			return !(*this == other);
		}

		bool operator>(const AscendingIterator& other) const {
			return currentIndex > other.currentIndex;
		}

		bool operator<(const AscendingIterator& other) const {
			return currentIndex < other.currentIndex;
		}

		int operator*() const {
			return container.elements[currentIndex];
		}

		AscendingIterator& operator++() {
			if (currentIndex > container.elements.size() - 1) {
               		throw runtime_error("Is out of bounds");
               	}
                	++currentIndex;
                	return *this;
		}
			
		AscendingIterator begin() {
                	return AscendingIterator(container);
            	}

		
		AscendingIterator end() {
    			AscendingIterator itr(*this);
    			itr.currentIndex = container.size(); 
    			return itr;
		}	

	};

	class SideCrossIterator {
	private:
		MagicalContainer& container;
		size_t forwardIndex;
		size_t backwardIndex;
		bool forward;

	public:
		SideCrossIterator(MagicalContainer& cont): container(cont), forwardIndex(0), backwardIndex(container.size() - 1), forward(true) {}

		SideCrossIterator(const SideCrossIterator& other): container(other.container), forwardIndex(other.forwardIndex), backwardIndex(other.backwardIndex), forward(other.forward) {}

		SideCrossIterator(SideCrossIterator&& other) noexcept: container(other.container), forwardIndex(other.forwardIndex), backwardIndex(other.backwardIndex), forward(other.forward) {
                	other.forwardIndex = 0;
                	other.backwardIndex = 0;
            	}
            	
            	~SideCrossIterator() = default;
            	
		SideCrossIterator& operator=(const SideCrossIterator& other) {
			if (&container != &other.container)
                	{
                    		throw runtime_error("Not the same SideCrossIterator");
                	}
			container = other.container;
			forwardIndex = other.forwardIndex;
			backwardIndex = other.backwardIndex;
			forward = other.forward;

			return *this;
		}
		SideCrossIterator& operator=(SideCrossIterator&& other)noexcept {
                	container = other.container;
                	forwardIndex = other.forwardIndex;
                	backwardIndex = other.backwardIndex;
                	forward = other.forward;
                	return *this;
            	}
            
		bool operator==(const SideCrossIterator& other) const {
			return forwardIndex == other.forwardIndex && backwardIndex == other.backwardIndex;
		}

		bool operator!=(const SideCrossIterator& other) const {
			return !(*this == other);
		}

		bool operator>(const SideCrossIterator& other) const {

		        return (!(other<*this) && other!=*this );
		}

		bool operator<(const SideCrossIterator& other) const {
		        return (forwardIndex < other.forwardIndex && backwardIndex < other.backwardIndex) || (forwardIndex < other.forwardIndex && other.forward) || (forward && backwardIndex < other.backwardIndex);
		}

		vector<int>::value_type operator*() const {
			if (forward) {
				return container.elements[forwardIndex];
			}
				return container.elements[backwardIndex];
		}

		SideCrossIterator& operator++() {
			if(forwardIndex == container.size()/2+container.size()%2 && backwardIndex == container.size()/2-(1-container.size()%2)) {
                    		throw runtime_error("Out of bounds");
                	}
                	if (forward) {
                    		++forwardIndex;

                	} else {
                    		--backwardIndex;

                	}
               	forward = !forward;
                	return *this;
            	}
		
		SideCrossIterator begin() {
                	return SideCrossIterator(container);
            	}

		SideCrossIterator end() {
                	SideCrossIterator itr(container);
                	itr.forwardIndex = container.size()/2+container.size()%2;
                	itr.backwardIndex = container.size()/2-(1-container.size()%2);
                	return itr;
            	}
	};

	class PrimeIterator {
	private:
		MagicalContainer& container;
		size_t currentIndex;

	public:
		PrimeIterator(MagicalContainer& cont): container(cont), currentIndex(0) {}

		PrimeIterator(const PrimeIterator& other): container(other.container), currentIndex(other.currentIndex) {}
		
		PrimeIterator(PrimeIterator&& other) noexcept: container(other.container), currentIndex(other.currentIndex) {
                	other.currentIndex = 0;
            	}
           
            	~PrimeIterator() = default;
            	
            	PrimeIterator& operator=( PrimeIterator&& other) noexcept{
                	container = other.container;
                	currentIndex = other.currentIndex;
                	return *this;
            	}
            	
		PrimeIterator& operator=(const PrimeIterator& other) {
			if (&container != &other.container) {
                    		throw runtime_error("Not the same PrimeIterator");
                	}
                	container = other.container;
                	currentIndex = other.currentIndex;

                	return *this;
		}

		bool operator==(const PrimeIterator& other) const {
			return currentIndex == other.currentIndex;
		}

		bool operator!=(const PrimeIterator& other) const {
			return currentIndex != other.currentIndex;
		}

		bool operator>(const PrimeIterator& other) const {
		 	return currentIndex > other.currentIndex;
		}

		bool operator<(const PrimeIterator& other) const {
			return currentIndex < other.currentIndex;
		}

		int operator*() const {
			return *container.primePointers[currentIndex];
		}

		PrimeIterator& operator++() {
			if (currentIndex >= container.primePointers.size()) {
                    		throw runtime_error("Out of bounds");
                	}
                	if (currentIndex < container.primePointers.size()) {
                    		++currentIndex;
                	}
                	return *this;
		}

		PrimeIterator begin() {
                	PrimeIterator itr(container);
                	return itr;
            	}

            	PrimeIterator end() {
                	PrimeIterator itr(container);
                	itr.currentIndex = container.primePointers.size();
                	return itr;
            	}
	};
};
}
