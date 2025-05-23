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
#include <valuetypes.hpp>

#include <limits>

/*
    IntValue
*/
FloatValue IntValue::toFloat() const noexcept {
    return { static_cast<f32>(value) };
}

CoordValue IntValue::toCoord() const noexcept {
    return { value % 16, value / 16, rotation };
}

/*
    RangeValue
*/
ObjectValue RangeValue::toObject() const {
    ObjectValue object;
    bool increment = from <= to;
    for (i32 i = from; increment ? i <= to : i >= to; increment ? ++i : --i)
        object.value.push_back({ i, rotation });
    object.rotation = rotation == Rotation::Default ? Rotation::N : rotation;
    object.update();
    return object;
}

/*
    CoordValue
*/
IntValue CoordValue::toInt() const noexcept {
    return { y.value * 16 + x.value, rotation };
}

/*
    FloatValue
*/
IntValue FloatValue::toInt() const noexcept {
    return { static_cast<i32>(value) };
}

/*
    ObjectValue
*/
ArrayValue<IntValue> ObjectValue::toArray() const {
    ArrayValue<IntValue> array;
    for (auto i : value)
        array.value.push_back(i);
    array.update();
    return array;
}

void ObjectValue::update(bool sort) {
    if (sort) {
        std::sort(value.begin(), value.end());
        value.erase(std::unique(value.begin(), value.end()), value.end());
    }

    last.value  = static_cast<i32>(value.size()) - 1;
    count.value = static_cast<i32>(value.size());

    for (auto& val : value)
        val.rotation = rotation;

    /*
        object's anchor after rotations:

        N - lowest index from first row
        V - highest index from first row
        H - lowest index from last row
        R - highest index from first column
        VH - highest index from last row
        VR - highest index from last column
        HR - lowest index from first column
        VHR - lowest index from last column
    */
    if (!value.empty()) {
        IntValue* result = nullptr;
        if (rotation == Rotation::Default || rotation == Rotation::N)
            result = &value.front();
        else if (rotation == Rotation::VH || rotation == Rotation::XY)
            result = &value.back();
        else if (rotation == Rotation::V || rotation == Rotation::X) {
            result = &value.front();
            for (auto& index : value) {
                if (index.value / 16 > result->value / 16)
                    break;
                result = &index;
            }
        }
        else if (rotation == Rotation::H || rotation == Rotation::Y) {
            result = &value.back();
            for (auto it = value.rbegin(); it != value.rend(); ++it) {
                if (it->value / 16 < result->value / 16)
                    break;
                result = &(*it);
            }
        }
        else if (rotation == Rotation::R) {
            i32 first_col = std::numeric_limits<i32>::max();
            for (auto index : value)
                if (index.value % 16 < first_col)
                    first_col = index.value % 16;

            for (auto it = value.rbegin(); it != value.rend(); ++it) {
                if (it->value % 16 == first_col) {
                    result = &(*it);
                    break;
                }
            }
        }
        else if (rotation == Rotation::VR || rotation == Rotation::XR) {
            i32 last_col = std::numeric_limits<i32>::min();
            for (auto index : value)
                if (index.value % 16 > last_col)
                    last_col = index.value % 16;

            for (auto it = value.rbegin(); it != value.rend(); ++it) {
                if (it->value % 16 == last_col) {
                    result = &(*it);
                    break;
                }
            }
        }
        else if (rotation == Rotation::HR || rotation == Rotation::YR) {
            i32 first_col = std::numeric_limits<i32>::max();
            for (auto index : value)
                if (index.value % 16 < first_col)
                    first_col = index.value % 16;

            for (auto it = value.begin(); it != value.end(); ++it) {
                if (it->value % 16 == first_col) {
                    result = &(*it);
                    break;
                }
            }
        }
        else {
            i32 last_col = std::numeric_limits<i32>::min();
            for (auto index : value)
                if (index.value % 16 > last_col)
                    last_col = index.value % 16;

            for (auto it = value.begin(); it != value.end(); ++it) {
                if (it->value % 16 == last_col) {
                    result = &(*it);
                    break;
                }
            }
        }
        anchor = result->toCoord();
    }
}
