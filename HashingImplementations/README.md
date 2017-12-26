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
		Runs a spell check program, using the constructed hash table on a short document

	make run2 	
		Runs a spell check program, using the constructed hash table on a large document. 
