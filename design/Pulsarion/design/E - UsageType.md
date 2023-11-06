# Overview
An enum that stores the usage type of elements

# Enum Variants
- Static - never changes, the renderer will not check for changes ever
- Nearly Static - almost never changes, the renderer will store the data as static, but changes are checked
- Dynamic - changes frequently, the renderer will store it in a way that is easy to change
- Streamed - changes (almost) every frame, the renderer will not store a copy of the data, but instead stream it.