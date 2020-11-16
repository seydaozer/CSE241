package HW8_171044023;

/**
 * @author Seyda Ozer
 *
 */
public abstract class GTUContainer<T> {
	
	/**
	 * Returns whether the container is empty.
	 * This function does not modify the container in any way.
	 * @return True if the container size is 0, false otherwise.
	 */
	public abstract boolean empty();
	
	/**
	 * Returns the number of elements in the container.
	 * @return The number of elements in the container.
	 */
	public abstract int size();
	
	/**
	 * Returns the maximum number of elements that the container can hold.
	 * @return The maximum number of elements a container can hold as content.
	 */
	public abstract int max_size();
	
	/**
	 * Extends the container by inserting new elements,
	 * effectively increasing the container size by the number of elements inserted.
	 * @param element value to be copied (or moved) to the inserted elements.
	 * @throws IllegalArgumentException throws exception if the element already exists in the array.
	 */
	public abstract void insert(T element) throws IllegalArgumentException;
	
	/**
	 * Removes from the container a single element.
	 * @param element value of the element to be removed from the container
	 */
	public abstract void erase(T element);
	
	/**
	 * Removes all elements from the container (which are destroyed), leaving the container with a size of 0.
	 */
	public abstract void clear();
	
	/**
	 * This method returns an iterator pointing the beginning of the container.
	 * @return returns an iterator pointing to beginning.
	 */
	public abstract GTUIterator<T> iterator();
	
	/**
	 * Returns true if this collection contains the specified element.
	 * @param element the value to be check.
	 * @return returns true if the element exists in the container.
	 */
	public abstract boolean contains(Object element);
	
	/**
	 * This method returns the array of the container.
	 * @return returns the array of the container.
	 */
	public abstract T [] getContainer();

}
