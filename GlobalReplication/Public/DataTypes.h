#pragma once

#include <string>
#include <vector>
#include <cstdint>

class FArchive;

/**
 * @brief A serializable string class, similar to Unreal Engine's FString.
 * Wraps std::string for convenience.
 */
class FString
{
public:
    FString() = default;
    FString(const char* InStr) : Data(InStr) {}
    FString(const std::string& InStr) : Data(InStr) {}

    const char* c_str() const { return Data.c_str(); }
    const std::string& ToString() const { return Data; }
    bool operator!=(const FString& Other) const { return Data != Other.Data; }
    bool operator==(const FString& Other) const { return Data == Other.Data; }

    void Serialize(FArchive& Ar);

private:
    std::string Data;
};

/**
 * @brief A serializable dynamic array, similar to Unreal Engine's TArray.
 * Wraps std::vector for convenience.
 * @tparam T The type of elements in the array.
 */
template <typename T>
class TArray
{
public:
    TArray() = default;

    T& operator[](int32_t Index) { return Data[Index]; }
    const T& operator[](int32_t Index) const { return Data[Index]; }
    void push_back(const T& Element) { Data.push_back(Element); }
    void push_back(T&& Element) { Data.push_back(std::move(Element)); }
    size_t size() const { return Data.size(); }
    bool empty() const { return Data.empty(); }
    T* data() { return Data.data(); }
    const T* data() const { return Data.data(); }
    void clear() { Data.clear(); }
    void resize(size_t NewSize) { Data.resize(NewSize); }
    bool operator!=(const TArray<T>& Other) const { return Data != Other.Data; }
    bool operator==(const TArray<T>& Other) const { return Data == Other.Data; }

    void Serialize(FArchive& Ar);

    // Provide access to iterators for range-based for loops
    typename std::vector<T>::iterator begin() { return Data.begin(); }
    typename std::vector<T>::iterator end() { return Data.end(); }
    typename std::vector<T>::const_iterator begin() const { return Data.begin(); }
    typename std::vector<T>::const_iterator end() const { return Data.end(); }

private:
    std::vector<T> Data;
};
