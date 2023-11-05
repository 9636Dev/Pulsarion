# Overview
A concept to only allow float types, float and double.

# Data Type
concept FloatType_t = std::is_same_v<T, float> || std::is_same_v<T, double>;