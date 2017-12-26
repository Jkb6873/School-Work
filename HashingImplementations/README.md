Simple Hashing implementations.

Compile with:

	make all

Clean with:

	make clean

Run Tests:

	make run1linear 	
		Runs a hash implementation test using linear probing.
		Calculates the amount of collisions and other statistics. 

	make run1quadratic 	
		Runs a hash implementation test using quadratic probing.
		Calculates the amount of collisions and other statistics.

	make run1double 	
		Runs a hash implementation test using double hashing.
		Calculates the amount of collisions and other statistics. 

	make run2short 	
		Runs a spell check program, on a short document, 
		using the constructed hash table as a dictionary.

	make run2 	
		Runs a spell check program, on a large document, 
		using the constructed hash table as a dictionary.
