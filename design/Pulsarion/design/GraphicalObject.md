# Overview
A object representing an object that is renderable, and is the only object the renderer will allow for in world elements. This contains the mesh data and unique data for each instance.

# Requirements
- [x] Represent both 2D and 3D graphical objects
- [ ] Storage of a mesh pointer, which is used to determine the mesh while rendering, and other optimizations such as instancing and batching.
- [x] Storage of basic universal data
	- [x] transform data (translation, rotation, scaling) as a simple struct, which can be accessed for publicly and changed
- [x] Storage of a Material pointer, used to determine the Shader and other uniform data.
- [ ] Storage of other custom data, which can be different and updated dynamically for every instance.
	- [ ] Make sure the handling of this data is done in a way that can be updated easily and at runtime
- [ ] A function to convert the non mesh data to a map of UniformDescriptor and UniformData.
- [ ] A function to get the uniform descriptor of the GraphicalObject, should be fast and cached as it is called frequently to determine a shader
	- [ ] Cache and regenerate descriptors when the size of the custom data array changes.
- [ ] Rendering options for the object (wireframe, no cull, etc...). Should cache the rendering option using a cascading approach for the texture and the GraphicalObject.
- [ ] A function internally to check for changes in the mesh and update the internal state, typically called at the beginning or end of each frame, maximum once per frame.
- [ ] Storage of internal metadata used by the renderer, which can be updated by the renderer.
- [ ] A function to get the transform as a StrictModifiable
# Template Arguments
[[Dimension_t]] - the dimensions of the Graphical Object, can be 2 or 3

# Variables
[[Util Modifiable]]\<[[Transform]]> - The transform data, which is wrapped in a Modifiable to allow for efficient caching.
std::shared_ptr\<[[Material]]> - The material data, which is a shared pointer pointing to a material

# Functions
