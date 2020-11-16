package HW8_171044023;

import java.util.NoSuchElementException;

/**
 * @author Seyda Ozer
 *
 */
public class GTUIterator<T> {
	/**
	 * The array of the iterator.
	 */
	private T [] p;
	/**
	 * The index of array the iterator.
	 */
	private int index = 0;
	/**
	 * The value of size of the iterator array.
	 */
	private int size;
	
	/**
	 * GTUIterator Constructor
	 * @param container the array in the Container
	 */
	public GTUIterator(T [] container) {
		p = container;
		setSize(container.length);
	}
	
	/**
	 * GTUIterator Constructor
	 * @param object the object of GtuContainer
	 */
	public GTUIterator(GTUContainer<T> object) {
		size = object.size();
		p = object.getContainer();
	}
	
	/**
	 * Returns true if the iteration has more elements.
	 * @return true if the iteration has more elements
	 */
	public boolean hasNext() {
		try {
			next();
			return true;
		}
		catch(NoSuchElementException e) {
			return false;
		}
	}
	
	/**
	 * Returns the next element in the iteration.
	 * @return the next element in the iteration
	 * @throws NoSuchElementException - if the iteration has no more elements
	 */
	public T next() throws NoSuchElementException{
		if( index+1 >= size )
			throw new NoSuchElementException("This container has no more element.");
		else {
			index++;
			return p[index];
		}
	}
	
	/**
	 * Removes from the underlying collection the last element returned by this iterator.
	 */
	public void remove() {
		size = size - 1;
	}
	
	/**
	 * This method pushes iterator to the previous address.
	 */
	public void previous() {
		if(index > 0)
			index--;
	}
	
	/**
	 * This method sets the index of the iterator array.
	 * @param newIndex the value of the index.
	 */
	public void setIndex(int newIndex) {
		index = newIndex;
	}
	
	/**
	 * This method gets the index of the iterator array.
	 * @return index the value of the index.
	 */
	public int getIndex() {
		return index;
	}

	/**
	 * This method gets the size of iterator array.
	 * @return the size
	 */
	public int getSize() {
		return size;
	}

	/**
	 * This method sets the size of iterator array.
	 * @param theSize the size to set
	 */
	public void setSize(int theSize) {
		size = theSize;
	}
	
	/**
	 * This method returns string representation of GTUIterator object.
	 *@return string of representation of GTUIterator object
	 */
	public String toString() {
		String s = "";
		for(int i=0; i<size; i++) {
			s += p[i] + " ";
		}
		return s;
	}
}
