# Overview
Represents one type of material in the graphics engine

# Requirements
- [ ] Store the type of the material, if it is static, dynamic (changes, but not every frame), stream (changes basically every frame)
- [ ] Store diffuse fill color information
- [ ] Store optional texture information
- [ ] Stores whether or not it has any transparent part
- [ ] Store rarely used material attributes in a map
	- [ ] Generate and cache bitmap of the attributes, which is used to determine shaders to use