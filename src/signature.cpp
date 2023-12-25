///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2020-2023 Aerll - aerlldev@gmail.com
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
#include <signature.hpp>
#include <token.hpp>

/*
    Signature
*/
bool Signature::isSame(const Signature& call) const {
    return m_types == call.m_types;
}

bool Signature::isConvertible(const Signature& call) const {
    uint32_t i = 0;
    uint32_t j = 0;

    if (m_types.size() != call.m_types.size())
        return false;

    for (; i < m_types.size(); ++i) {
        if (j == call.m_types.size())
            break;

        for (; j < call.m_types.size(); ++j) {
            if (call.m_types[j] == m_types[i])
                ++j;
            else if (Token::isConvertible(call.m_types[j], m_types[i]))
                ++j;
            break;
        }
    }
    return i == m_types.size() && j == call.m_types.size();
}

bool Signature::isVariadicConvertible(const Signature& call) const {
    uint32_t i = 0;
    uint32_t j = 0;

    for (; i < m_types.size(); ++i) {
        if (j == call.m_types.size())
            break;

        for (; j < call.m_types.size(); ++j) {
            if ((call.m_types[j] == m_types[i]) || (Token::isConvertible(call.m_types[j], m_types[i])) || (Token::isVariadic(call.m_types[j], m_types[i]))) {} // skip
            else
                break;
        }
    }
    return i == m_types.size() && j == call.m_types.size();
}

bool Signature::isVariadic() const {
    return m_types.size() == 1 && Token::isArray(m_types.front());
}
