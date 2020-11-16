package HW8_171044023;

import java.lang.reflect.Array;

/**
 * @author Seyda Ozer
 *
 */
public class GTUSet<T> extends GTUContainer<T> {

	/**
	 * The value is the number of capacity of the set.
	 */
	private int capacity;
	/**
	 * The value is the number of used of the set.
	 */
	private int used;
	/**
	 * This value is true if the set is empty.
	 */
	private boolean _empty = true;
	/**
	 * The array of set
	 */
	private T [] set;
	/**
     * Type of the elements in the set
     */
	private Class<T[]> type;
	
	/**
	 * GTUSet Constructor
	 * @param object the type of the array that needs to be created.
	 */
	public GTUSet(Class<T[]> object) {
		type = object;
		capacity = 10;
		used = 0;
		set = object.cast(Array.newInstance(object.getComponentType(), capacity));
	}
	
	/**
	 * Returns whether the set container is empty.
	 * This function does not modify the set container in any way.
	 * @return True if the set container size is 0, false otherwise.
	 */
	@Override
	public boolean empty() {
		return _empty;
	}

	/**
	 * Returns the number of elements in the set container.
	 * @return The number of elements in the set container.
	 */
	@Override
	public int size() {
		return used;
	}

	/**
	 * Returns the maximum number of elements that the set container can hold.
	 * @return The maximum number of elements a set container can hold as content.
	 */
	@Override
	public int max_size() {
		return capacity;
	}

	/**
	 * Extends the set container by inserting new elements,
	 * effectively increasing the set container size by the number of elements inserted.
	 * @param element value to be copied (or moved) to the inserted elements.
	 * @throws IllegalArgumentException throws exception if the element already exists in the array.
	 */
	@Override
	public void insert(T element) throws IllegalArgumentException {
		if(contains(element) == true)
			throw new IllegalArgumentException("This element (" + element + ") is added already to the set.");
		else {
			if(used == 0)	_empty = false;
			if(used >= capacity) {
				T [] temp = type.cast(Array.newInstance(type.getComponentType(), capacity));
				
				for(int i=0; i<used; i++)
					temp[i] = set[i];
				
				capacity += capacity;
				set = type.cast(Array.newInstance(type.getComponentType(), capacity));;
				
				for(int i=0; i<used; i++)
					set[i] = temp[i];
			}
			set[used] = element;
			used++;
		}
	}

	/**
	 * Removes from the set container a single element.
	 * @param element value of the element to be removed from the set container.
	 */
	@Override
	public void erase(T element) {
		boolean isInSet = false;
		GTUIterator<T> iter = this.iterator();
		
		while(iter.hasNext()) {
			iter.previous();
			if( element == iter.next() ) {
				isInSet = true;
				break;
			}
		}
		if(isInSet == true) {
			for(int i=iter.getIndex(); i<used-1; i++) 
				set[i] = set[i+1];
			used--;
		}
		if(used == 0)	_empty = true;
	}

	/**
	 * Removes all elements from the set container (which are destroyed), leaving the set container with a size of 0.
	 */
	@Override
	public void clear() {
		used = 0;
		_empty = true;
	}

	/**
	 * This method returns an iterator pointing the beginning of the set container.
	 * @return returns an iterator pointing to beginning.
	 */
	@Override
	public GTUIterator<T> iterator() {
		GTUIterator<T> iter = new GTUIterator<T>(this);
		return iter;
	}
	
	/**
	 * Returns true if this collection contains the specified element.
	 * @param element the value to be check.
	 * @return returns true if the element exists in the container.
	 */
	@Override
	public boolean contains(Object element) {
		boolean flag = false;
		GTUIterator<T> iter = this.iterator();
		if(set[0] == element)	flag = true;
		else{
			while(iter.hasNext()) {
				iter.previous();
				if( iter.next() == element )
					flag = true;
			}
		}
		return flag;
	}

	/**
	 * This method returns the array of the set container.
	 * @return returns the array of the set container.
	 */
	@Override
	public T [] getContainer() {
		return set;
	}
	
}
