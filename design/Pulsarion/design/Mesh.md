# Overview
Used to store vertex information and indices information

# Requirements
- [x] Type - Static, Dynamic, Streamed
- [x] Storage of vertex positions
- [ ] Storage of indices
- [ ] Storage of texture coordinates
- [ ] Storage of normals
- [ ] Optional storage of binormals / tangents -  used to add detail to the mesh
- [ ] Optional storage of bone weights and bone indices
- [ ] A function to return an AABB for culling, regenerate cached AABB when data changes. 
- [ ] A function to return a bitmap number used to determine shaders
- [ ] A function to create a backend
- [ ] A function to delete the backend (free GPU VRAM)
- [ ] A function to check if a backend is created
- [ ] A function to get or create a backend

# Template Arguments
VertexType -  float or double
IndicesType - short, unsigned short, int, unsigned int 
# Variables
[[E - UsageType ]] - the usage type of the mesh
std::vector\<VertexType> -  the vertices of the mesh
std::vector\<IndicesType> - the indices of the mesh


# Functions