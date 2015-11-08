# shorthand

##FLAG class:
		allows the creation of shorthand::flag objects that compare character strings (user input) against character strings 
		that define available flags. f.check() is used to check for the presence of characters in both strings.
			##shorthand::flag f(char* flags, char* input)
				*flag.valid_input():				returns true if all input characters are in flag list
				*flag.check('c'):				returns true if char 'c' is in both input and flag list

##FILE class:
		allows creation of shorthand::file objects.
			###shorthand::file f();
				*file.load(char* p): 			loads the file at path "p" line-by-line into a linked list
				*file.save(char* p): 			saves the linked list to path "p"
				*file.print(): 					prints each line preceded by line num (0-n)
				*file.insert(int i, char* s): 	inserts "s" at line number "i", moves following lines down
				*file.remove(int i):				removes line at line number "i", moves following lines up
		
