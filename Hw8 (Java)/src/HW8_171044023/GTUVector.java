package HW8_171044023;

import java.lang.reflect.Array;

/**
 * @author Seyda Ozer
 *
 */
public class GTUVector<T> extends GTUContainer<T> {

	/**
	 * The value is the number of capacity of the vector.
	 */
	private int capacity;
	/**
	 * The value is the number of used of the vector.
	 */
	private int used;
	/**
	 * This value is true if the vector is empty.
	 */
	private boolean _empty = true;
	/**
	 * The array of vector
	 */
	private T [] vector;
	
	/**
     * Type of the elements in the vector
     */
	private Class<T[]> type;
	
	
	/**
	 * GTUVector Constructor
	 * @param object the type of the array that needs to be created.
	 */
	public GTUVector(Class<T[]> object) {
		type = object;
		capacity = 10;
		used = 0;
		vector = object.cast(Array.newInstance(object.getComponentType(), capacity));
	}
	
	/**
	 * Returns whether the vector container is empty.
	 * This function does not modify the vector container in any way.
	 * @return True if the vector container size is 0, false otherwise.
	 */
	@Override
	public boolean empty() {
		return _empty;
	}

	/**
	 * Returns the number of elements in the vector container.
	 * @return The number of elements in the vector container.
	 */
	@Override
	public int size() {
		return used;
	}

	/**
	 * Returns the maximum number of elements that the vector container can hold.
	 * @return The maximum number of elements a vector container can hold as content.
	 */
	@Override
	public int max_size() {
		return capacity;
	}

	/**
	 * Extends the vector container by inserting new elements,
	 * effectively increasing the vector container size by the number of elements inserted.
	 * @param element value to be copied (or moved) to the inserted elements.
	 */
	
	@Override
	public void insert(T element) {
		if(used == 0)	_empty = false;
		if(used >= capacity) {

			T [] temp = type.cast(Array.newInstance(type.getComponentType(), capacity));
				
			for(int i=0; i<used; i++)
				temp[i] = vector[i];
			
			capacity += capacity;
			vector = type.cast(Array.newInstance(type.getComponentType(), capacity));
				
			for(int i=0; i<used; i++)
				vector[i] = temp[i];
		}
		vector[used] = element;
		used++;
	}

	/**
	 * Removes from the vector container a single element.
	 * @param element value of the element to be removed from the vector container.
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
				vector[i] = vector[i+1];
			used--;
		}
		
		if(used == 0)	_empty = true;
	}

	/**
	 * Removes all elements from the vector container (which are destroyed), leaving the vector container with a size of 0.
	 */
	@Override
	public void clear() {
		used = 0;
		_empty = true;
	}

	/**
	 * This method returns an iterator pointing the beginning of the vector container.
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
	 * @return returns true if the element exists in the vector container.
	 */
	@Override
	public boolean contains(Object element) {
		boolean flag = false;
		GTUIterator<T> iter = this.iterator();
		if(vector[0] == element)	flag = true;
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
	 * This method returns the array of the vector container.
	 * @return returns the array of the vector container.
	 */
	@Override
	public T [] getContainer() {
		return vector;
	}

	
}
