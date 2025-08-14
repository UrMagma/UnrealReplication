#pragma once

#include <cstdint>
#include <vector>

class FArchive;

/**
 * @brief Base class for a replicated property.
 * This allows storing properties of different types in a single container.
 */
class FRepPropertyBase
{
public:
    virtual ~FRepPropertyBase() = default;
    virtual void Serialize(FArchive& Ar) = 0;
    virtual bool IsDirty() const = 0;
    virtual void ClearDirty() = 0;
};

/**
 * @brief A template class for a replicated property.
 * It wraps a value and tracks whether it has been changed.
 * @tparam T The type of the value to be replicated.
 */
template <typename T>
class FRepProperty : public FRepPropertyBase
{
public:
    FRepProperty() : Value(), bIsDirty(true) {}
    FRepProperty(const T& InValue) : Value(InValue), bIsDirty(true) {}

    // Overload the assignment operator to set the dirty flag.
    FRepProperty<T>& operator=(const T& InValue)
    {
        if (Value != InValue)
        {
            Value = InValue;
            bIsDirty = true;
        }
        return *this;
    }

    // Allow implicit conversion to the underlying type for easy access.
    operator T() const { return Value; }

    // Serialize the property's value into an archive.
    virtual void Serialize(FArchive& Ar) override
    {
        Ar << Value;
    }

    // Check if the property has been changed since the last update.
    virtual bool IsDirty() const override
    {
        return bIsDirty;
    }

    // Clear the dirty flag.
    virtual void ClearDirty() override
    {
        bIsDirty = false;
    }

private:
    T Value;
    bool bIsDirty;
};
