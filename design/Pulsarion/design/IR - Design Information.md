# Notation Used
## Filenames
- `_t` suffix - Typedef, the file will provide context and the data type of the typedef
- `E - ` prefix - Enum, the file should be an enum
- `S - ` prefix - Struct, the file should be a struct

## Sections in a design file
- Name / Title - the name / title of the design file is the class / struct / enum name
- Overview - information about what the file is designed to do, implementation detail is not required
- Requirements - A checklist of requirements that the final / prototype implementation should follow
- Template Variables (Optional) - Describing each template variable, the valid values, and what they are used for / represent
- Functions (Optional) - Describe each function in the class / struct
	- Name of the function
		- Params - Parameters of the function, with information for each one
		- Returns - The return of the function, with information for what the return is
		- Info - Information about the function, what it is suppose to do
		- Details - Detailed implementation information, could be in English or code, or even an algorithm to use.
- Variables (Optional)- Describe all of the variables, their types, their names, and what they represent and do 
- Enum Variants (Only for Enums) - describe all of the variants for the enum
	- Name - the name of the variant
	- Value - the value of the variant
	- Info - what the variant of the enum represents
- Usage
	- What are the usage of the this function
	- What can be modified