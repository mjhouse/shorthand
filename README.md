#Shorthand.h

####Flag
creates a flag object that holds two character arrays, one defined by the program, and one from argv[]. The
"check" function returns true on const characters that are in both strings, and can be used to build a flag 
handler.
  * shorthand::flag FLAG(char const *flaglist, char *inputlist)
    1. int FLAG.check(char c):
      - returns true if char 'c' is in both input list and flag list
    2. int FLAG.valid_input();
      - returns true if all characters in input_list are in flag_list

####File
Allows the creation of a file object that can load text files into a linked list, 
manipulate lines as strings, and save the modified text again.
  * shorthand::file FILE()
    1. int FILE.load(char *s)
      - loads a file line by line into list from location "s"
    2. int FILE.save(char *s)
      - saves list into file at path "s"
    3. int FILE.print()
      - prints each line in list with line number
    4. int FILE.insert(int i, string s)
      - inserts new line consisting of string "s" at line "i"
    5. int FILE.remove(int i)
      - removes line at line number "i"
    6. string FILE.line(int i)
      - returns string from line "i"
