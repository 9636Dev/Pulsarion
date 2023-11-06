# Overview
A structure to store generic transform data, used for the Graphical Object.

# Requirements
 - [ ] 2D and 3D versions
 - [ ] Storage of translation glm::vec
 - [ ] Storage of scale glm::vec
 - [ ] Storage of rotation glm::vec
 - [ ] Function to get the transform as a matrix of dimension + 1 by dimension + 1
	 - [ ] Should cache the matrix result as calculations will require matrix multiplication
 - [ ] Specialized constructors for 2D and 3D versions, as 2D rotation is 1 value, and 3D is 3
 - [ ] Functions to get const references for the data types
	 - [ ] Translation
	 - [ ] Rotation
	 - [ ] Scale
 - [ ] Generated typedefs for vector and matrix types
 - [ ] Functions on specialized template functions
	 - [ ] Get Translation X, ...
	 - [ ] Get Rotation X, ...
	 - [ ] Get Scale X, ...

# Template Arguments
[[Dimension_t]] - represents the dimensions of the transform

# Template specialization typedefs

- VecType - The vector type,  should contained in a struct called Transform trait with explicit specializations for the template arguments
- MatType =The matrix type, same as VecType