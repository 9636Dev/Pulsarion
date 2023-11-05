# Overview
A utility class that wraps a data and a boolean, which can be set to dirty and read. Useful for computations dependent on the changes of others which are computationally expensive

# Requirements
- [ ] A boolean storing the dirty flag
- [ ] A method to set the dirty flag
- [ ] A method to read the dirty flag
- [ ] A method to reset the dirty flag
- [ ] A implicit conversion to the underlying data type
- [ ] A constructor used to construct the underlying data type in place
- [ ] A static method to move an existing object into the Modifiable
- [ ] A method to get a T&, which will call the Set Dirty function, as all functions requiring a T& will be assumed to change it
- [ ] A method to get const T&, which doesn't call the Dirty function
- [ ] Storage of an underlying T type, should only be constructed in place or moved in, therefore resulting it to always to valid when Modifiable is valid

# Template Arguments
- T - A type representing the underlying data type
