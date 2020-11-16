package HW8_171044023;

import java.util.Scanner;

/**
 * @author Seyda Ozer
 *
 */
public class Test {

	/**
	 * This main method of this application.
	 * @param args array of string arguments.
	 */
	public static void main(String[] args) {
		System.out.println("Please select a type ");
		System.out.println("1- Vector ");
		System.out.println("2- Set ");
		
		Scanner input = new Scanner(System.in);
		int choice = input.nextInt();

		System.out.println();
		
		if(choice == 1) { //GTUVECTOR
			GTUContainer<Character> v1 = new GTUVector(Character[].class);
			
			System.out.println("--------------------------------------------------------------------");
			if( v1.empty() )	System.out.println("This vector is empty.");
			else	System.out.println("This vector is not empty. Vector's size: " + v1.size() + ", and its maximum size: " + v1.max_size());
			System.out.println("--------------------------------------------------------------------");
			
			GTUIterator<Character> iter;
			v1.insert('a');
			v1.insert('b');
			v1.insert('c');
			v1.insert('d');
			v1.insert('a');
			iter = v1.iterator();
			System.out.println(iter);
			
			System.out.println("--------------------------------------------------------------------");
			if( v1.empty() )	System.out.println("This vector is empty.");
			else	System.out.println("This vector is not empty. Vector's size: " + v1.size() + ", and its maximum size: " + v1.max_size());
			System.out.println("--------------------------------------------------------------------");
			
			System.out.println("the value of the element to be deleted: 'c'");
			v1.erase('c');
			iter = v1.iterator();
			System.out.println(iter);
			System.out.println("--------------------------------------------------------------------");
			System.out.println("the value of the element to be search: 'c'");
			if(v1.contains('c'))
				System.out.println("This element exists in the vector.");
			else
				System.out.println("This element does not exist in the vector.");
			System.out.println("------------------------------------------");
			System.out.println("the value of the element to be search: 'b'");
			if(v1.contains('b'))
				System.out.println("This element exists in the vector.");
			else
				System.out.println("This element does not exist in the vector.");
			System.out.println("--------------------------------------------------------------------");
			
			iter = v1.iterator();
			System.out.println(iter);
			System.out.println("Remove a element from the iterator.");
			iter.remove();
			System.out.println(iter);
			System.out.println("--------------------------------------------------------------------");
			
			System.out.println("Remove all elements from the vector.");
			v1.clear();
			if( v1.empty() )	System.out.println("This vector is empty.");
			else	System.out.println("This vector is not empty. Vector's size: " + v1.size() + ", and its maximum size: " + v1.max_size());
			System.out.println("--------------------------------------------------------------------");
			
		}// END TESTING GTUVECTOR
		
		else if(choice == 2) { //GTUSET
			GTUContainer<Integer> s1 = new GTUSet(Integer[].class);
			
			System.out.println("---------------------------------------------------------------------------------");
			if( s1.empty() )	System.out.println("This set is empty.");
			else	System.out.println("This set is not empty. Set's size: " + s1.size() + ", and its maximum size: " + s1.max_size());
			System.out.println("---------------------------------------------------------------------------------");
			
			try {
				GTUIterator<Integer> it;
				s1.insert(1);
				s1.insert(2);
				s1.insert(3);
				s1.insert(4);
				it = s1.iterator();
				System.out.println(it);
				s1.insert(1);
				it = s1.iterator();
				System.out.println(it);
			}
			catch(IllegalArgumentException e) {
				System.out.println(e);
			}
			
			GTUIterator<Integer> iter;
			iter = s1.iterator();
			System.out.println(iter);
			
			System.out.println("---------------------------------------------------------------------------------");
			if( s1.empty() )	System.out.println("This set is empty.");
			else	System.out.println("This set is not empty. Set's size: " + s1.size() + ", and its maximum size: " + s1.max_size());
			System.out.println("---------------------------------------------------------------------------------");
			
			System.out.println("the value of the element to be deleted: 2");
			s1.erase(2);
			iter = s1.iterator();
			System.out.println(iter);
			System.out.println("---------------------------------------------------------------------------------");
			System.out.println("the value of the element to be search: 2");
			if(s1.contains(2))
				System.out.println("This element exists in the set.");
			else
				System.out.println("This element does not exist in the set.");
			System.out.println("------------------------------------------");
			System.out.println("the value of the element to be search: 1");
			if(s1.contains(1))
				System.out.println("This element exists in the set.");
			else
				System.out.println("This element does not exist in the set.");
			System.out.println("---------------------------------------------------------------------------------");
			
			iter = s1.iterator();
			System.out.println(iter);
			System.out.println("Remove a element from the iterator.");
			iter.remove();
			System.out.println(iter);
			System.out.println("---------------------------------------------------------------------------------");
			
			System.out.println("Remove all elements from the set.");
			s1.clear();
			if( s1.empty() )	System.out.println("This set is empty.");
			else	System.out.println("This set is not empty. Set's size: " + s1.size() + ", and its maximum size: " + s1.max_size());
			System.out.println("---------------------------------------------------------------------------------");
			
		}// END TESTING GTUSET
	}

}
