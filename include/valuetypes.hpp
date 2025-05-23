///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2020-2025 Aerll - aerlldev@gmail.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright noticeand this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
#ifndef RPP_VALUETYPES_HPP
#define RPP_VALUETYPES_HPP

#include <enums.hpp>
#include <token.hpp>

#include <algorithm>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

class Value;

class BoolValue;
class IntValue;
class RangeValue;
class CoordValue;
class FloatValue;
class StringValue;
class ObjectValue;
template <typename T>
class ArrayValue;

using ptr_value = std::unique_ptr<Value>;

class Value {
public:
    virtual ~Value() = default;

    virtual ValueType type() const noexcept = 0;
    virtual ptr_value clone() const         = 0;
    virtual ptr_value makeNew() const       = 0;
    virtual void reset()                    = 0;

    virtual std::string str() const = 0;

public:
    template <typename T>
    constexpr T as() noexcept {
        return static_cast<T>(this);
    }
};

class BoolValue final : public Value {
public:
    ~BoolValue() = default;

    BoolValue() noexcept
        : value(false) {}

    BoolValue(bool value) noexcept
        : value(value) {}

    friend bool operator==(const BoolValue& lhs, const BoolValue& rhs) {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const BoolValue& lhs, const BoolValue& rhs) {
        return !(lhs == rhs);
    }

    ValueType type() const noexcept final {
        return ValueType::Bool;
    }

    ptr_value clone() const final {
        return std::make_unique<BoolValue>(*this);
    }

    ptr_value makeNew() const final {
        return std::make_unique<BoolValue>();
    }

    void reset() final {
        value = false;
    }

    std::string str() const final {
        return value ? "true" : "false";
    }

public:
    bool value;
};

class IntValue final : public Value {
public:
    ~IntValue() = default;

    IntValue() noexcept
        : value(0)
        , rotation(Rotation::Default) {}

    IntValue(i32 value, Rotation rotation = Rotation::Default) noexcept
        : value(value)
        , rotation(rotation) {}

    friend IntValue operator+(const IntValue& lhs, const IntValue& rhs) {
        return { lhs.value + rhs.value };
    }

    friend IntValue operator-(const IntValue& lhs, const IntValue& rhs) {
        return { lhs.value - rhs.value };
    }

    friend IntValue operator*(const IntValue& lhs, const IntValue& rhs) {
        return { lhs.value * rhs.value };
    }

    friend IntValue operator/(const IntValue& lhs, const IntValue& rhs) {
        return { lhs.value / rhs.value };
    }

    friend bool operator==(const IntValue& lhs, const IntValue& rhs) {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const IntValue& lhs, const IntValue& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const IntValue& lhs, const IntValue& rhs) {
        return lhs.value < rhs.value;
    }

    friend bool operator<=(const IntValue& lhs, const IntValue& rhs) {
        return lhs.value <= rhs.value;
    }

    friend bool operator>(const IntValue& lhs, const IntValue& rhs) {
        return lhs.value > rhs.value;
    }

    friend bool operator>=(const IntValue& lhs, const IntValue& rhs) {
        return lhs.value >= rhs.value;
    }

    ValueType type() const noexcept final {
        return ValueType::Int;
    }

    ptr_value clone() const final {
        return std::make_unique<IntValue>(*this);
    }

    ptr_value makeNew() const final {
        return std::make_unique<IntValue>();
    }

    void reset() final {
        value    = 0;
        rotation = Rotation::Default;
    }

    std::string str() const final {
        std::string result = std::to_string(value);
        if (rotation != Rotation::Default)
            result += "." + Token::rotationToString(rotation);
        return result;
    }

    FloatValue toFloat() const noexcept;
    CoordValue toCoord() const noexcept;

public:
    i32 value;
    Rotation rotation;
};

class RangeValue final : public Value {
public:
    ~RangeValue() = default;

    RangeValue() noexcept
        : from(0)
        , to(0)
        , rotation(Rotation::Default) {}

    RangeValue(i32 from, i32 to, Rotation rotation = Rotation::Default) noexcept
        : from(from)
        , to(to)
        , rotation(rotation) {}

    friend bool operator==(const RangeValue& lhs, const RangeValue& rhs) {
        return lhs.from == rhs.from && lhs.to == rhs.to;
    }

    friend bool operator!=(const RangeValue& lhs, const RangeValue& rhs) {
        return !(lhs == rhs);
    }

    ValueType type() const noexcept final {
        return ValueType::Range;
    }

    ptr_value clone() const final {
        return std::make_unique<RangeValue>(*this);
    }

    ptr_value makeNew() const final {
        return std::make_unique<RangeValue>();
    }

    void reset() final {
        from     = 0;
        to       = 0;
        rotation = Rotation::Default;
    }

    std::string str() const final {
        std::string result = std::to_string(from) + "_" + std::to_string(to);
        if (rotation != Rotation::Default)
            result += "." + Token::rotationToString(rotation);
        return result;
    }

    ObjectValue toObject() const;

public:
    i32 from;
    i32 to;
    Rotation rotation;
};

class CoordValue final : public Value {
public:
    ~CoordValue() = default;

    CoordValue() noexcept
        : x(0)
        , y(0)
        , rotation(Rotation::Default) {}

    CoordValue(i32 x, i32 y, Rotation rotation = Rotation::Default) noexcept
        : x(x)
        , y(y)
        , rotation(rotation) {}

    friend bool operator==(const CoordValue& lhs, const CoordValue& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    friend bool operator!=(const CoordValue& lhs, const CoordValue& rhs) {
        return !(lhs == rhs);
    }

    ValueType type() const noexcept final {
        return ValueType::Coord;
    }

    ptr_value clone() const final {
        return std::make_unique<CoordValue>(*this);
    }

    ptr_value makeNew() const final {
        return std::make_unique<CoordValue>();
    }

    void reset() final {
        x        = {};
        y        = {};
        rotation = Rotation::Default;
    }

    std::string str() const final {
        std::string result = "[" + std::to_string(x.value) + ", " + std::to_string(y.value) + "]";
        if (rotation != Rotation::Default)
            result += "." + Token::rotationToString(rotation);
        return result;
    }

    IntValue toInt() const noexcept;

public:
    IntValue x;
    IntValue y;
    Rotation rotation;
};

class FloatValue final : public Value {
public:
    ~FloatValue() = default;

    FloatValue() noexcept
        : value(0.0f) {}

    FloatValue(f32 value) noexcept
        : value(value) {}

    friend FloatValue operator+(const FloatValue& lhs, const FloatValue& rhs) {
        return { lhs.value + rhs.value };
    }

    friend FloatValue operator-(const FloatValue& lhs, const FloatValue& rhs) {
        return { lhs.value - rhs.value };
    }

    friend FloatValue operator*(const FloatValue& lhs, const FloatValue& rhs) {
        return { lhs.value * rhs.value };
    }

    friend FloatValue operator/(const FloatValue& lhs, const FloatValue& rhs) {
        return { lhs.value / rhs.value };
    }

    friend bool operator==(const FloatValue& lhs, const FloatValue& rhs) {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const FloatValue& lhs, const FloatValue& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const FloatValue& lhs, const FloatValue& rhs) {
        return lhs.value < rhs.value;
    }

    friend bool operator<=(const FloatValue& lhs, const FloatValue& rhs) {
        return lhs.value <= rhs.value;
    }

    friend bool operator>(const FloatValue& lhs, const FloatValue& rhs) {
        return lhs.value > rhs.value;
    }

    friend bool operator>=(const FloatValue& lhs, const FloatValue& rhs) {
        return lhs.value >= rhs.value;
    }

    ValueType type() const noexcept final {
        return ValueType::Float;
    }

    ptr_value clone() const final {
        return std::make_unique<FloatValue>(*this);
    }

    ptr_value makeNew() const final {
        return std::make_unique<FloatValue>();
    }

    void reset() final {
        value = 0.0f;
    }

    std::string str() const final {
        return std::to_string(value);
    }

    IntValue toInt() const noexcept;

public:
    f32 value;
};

class StringValue final : public Value {
public:
    ~StringValue() = default;

    StringValue() = default;

    StringValue(const std::string& value)
        : value(value) {}

    StringValue(std::string&& value)
        : value(std::move(value)) {}

    friend bool operator==(const StringValue& lhs, const StringValue& rhs) {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const StringValue& lhs, const StringValue& rhs) {
        return !(lhs == rhs);
    }

    friend StringValue operator+(const StringValue& lhs, const StringValue& rhs) {
        return { lhs.value + rhs.value };
    }

    ValueType type() const noexcept final {
        return ValueType::String;
    }

    ptr_value clone() const final {
        return std::make_unique<StringValue>(*this);
    }

    ptr_value makeNew() const final {
        return std::make_unique<StringValue>();
    }

    void reset() final {
        value = {};
    }

    std::string str() const final {
        return value;
    }

public:
    std::string value;
};

class Container : public Value {
public:
    virtual ~Container() = default;

    Container() noexcept
        : last(-1)
        , count(0) {}

    virtual Value* at(usize index) = 0;

public:
    IntValue last;
    IntValue count;
};

class ObjectValue final : public Container {
public:
    ~ObjectValue() = default;

    ObjectValue()
        : Container()
        , value()
        , rotation(Rotation::N)
        , anchor() {}

    ObjectValue(const std::vector<IntValue>& value, Rotation rotation = Rotation::N)
        : value(value)
        , rotation(rotation)
        , anchor() {
        update();
    }

    ObjectValue(std::vector<IntValue>&& value, Rotation rotation = Rotation::N) noexcept
        : value(std::move(value))
        , rotation(rotation)
        , anchor() {
        update();
    }

    friend bool operator==(const ObjectValue& lhs, const ObjectValue& rhs) {
        return lhs.value == rhs.value && lhs.rotation == rhs.rotation;
    }

    friend bool operator!=(const ObjectValue& lhs, const ObjectValue& rhs) {
        return !(lhs == rhs);
    }

    ValueType type() const noexcept final {
        return ValueType::Object;
    }

    ptr_value clone() const final {
        return std::make_unique<ObjectValue>(*this);
    }

    ptr_value makeNew() const final {
        return std::make_unique<ObjectValue>();
    }

    void reset() final {
        value.clear();
        rotation    = Rotation::N;
        anchor      = {};
        last.value  = -1;
        count.value = 0;
    }

    Value* at(usize index) final {
        return &value[index];
    }

    std::string str() const final {
        std::string result = "{";
        i32 int_anchor = anchor.toInt().value;
        for (usize i = 0; i < value.size(); ++i) {
            result += std::to_string(value[i].value);
            if (value[i].value == int_anchor)
                result += "*";
            if (i != value.size() - 1)
                result += ", ";
        }
        result += "}";
        if (rotation != Rotation::Default)
            result += "." + Token::rotationToString(rotation);
        return result;
    }

    ArrayValue<IntValue> toArray() const;

    void update(bool sort = true);

public:
    std::vector<IntValue> value;
    Rotation rotation;
    CoordValue anchor;
};

class Array : public Container {
public:
    virtual ~Array() = default;

    virtual void unique() = 0;
};

template <typename T>
class ArrayValue final : public Array {
    constexpr ValueType subtype() const noexcept {
        if constexpr (std::is_same_v<T, BoolValue>)
            return ValueType::Bool;
        else if constexpr (std::is_same_v<T, IntValue>)
            return ValueType::Int;
        else if constexpr (std::is_same_v<T, RangeValue>)
            return ValueType::Range;
        else if constexpr (std::is_same_v<T, CoordValue>)
            return ValueType::Coord;
        else if constexpr (std::is_same_v<T, FloatValue>)
            return ValueType::Float;
        else if constexpr (std::is_same_v<T, StringValue>)
            return ValueType::String;
        else
            return ValueType::Object;
    }

public:
    ~ArrayValue() = default;

    ArrayValue()
        : Array()
        , value() {}

    ArrayValue(const std::vector<T>& value)
        : value(value) {
        update();
    }

    ArrayValue(std::vector<T>&& value)
        : value(std::move(value)) {
        update();
    }

    friend bool operator==(const ArrayValue& lhs, const ArrayValue& rhs) {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const ArrayValue& lhs, const ArrayValue& rhs) {
        return !(lhs == rhs);
    }

    ValueType type() const noexcept final {
        return ValueType::Array | subtype();
    }

    ptr_value clone() const final {
        return std::make_unique<ArrayValue<T>>(*this);
    }

    ptr_value makeNew() const final {
        return std::make_unique<ArrayValue<T>>();
    }

    void reset() final {
        value.clear();
        last.value  = -1;
        count.value = 0;
    }

    Value* at(usize index) final {
        return &value[index];
    }

    ObjectValue toObject() const {
        ObjectValue object;
        for (const auto& i : value)
            object.value.push_back(i);
        object.update();
        return object;
    }

    bool has(const T& val) const {
        return std::find(value.rbegin(), value.rend(), val) != value.rend();
    }

    void push(ArrayValue<T>* values) {
        value.insert(value.end(), values->value.begin(), values->value.end());
        update();
    }

    void unique() final {
        value.erase(util::removeDuplicates(value.begin(), value.end()), value.end());
        update();
    }

    std::string str() const final {
        std::string result = "{";
        for (usize i = 0; i < value.size(); ++i) {
            result += value[i].str();
            if (i != value.size() - 1)
                result += ", ";
        }
        result += "}";
        return result;
    }

    i32 find(ArrayValue<T>* values) const {
        i32 index = static_cast<i32>(
            std::distance(value.begin(), std::search(value.begin(), value.end(), values->value.begin(), values->value.end()))
        );
        return index != count.value ? index : -1;
    }

    void update() {
        last.value  = static_cast<i32>(value.size()) - 1;
        count.value = static_cast<i32>(value.size());
    }

public:
    std::vector<T> value;
};

#endif // RPP_VALUETYPES_HPP
