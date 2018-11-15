# TODO

- Change build system to Cmake [DONE]
	- Move files outside of folders in src and include [DONE]
	- Create CMakeLists.txt with include folder and src folder [DONE]
- Update interfaces to return and require data types for each parts of the program rather than use static variables
	- File
	- Stack
		- Datum stack
		- Character stack
	- Vartable
	- Change state functions to require file, datum stack, char stack, and vartable
- Separate code into executables and libraries
	- Split Uppercase "Modules" and "Program" to separate libraries
