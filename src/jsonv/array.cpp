/** \file
 *  
 *  Copyright (c) 2012 by Travis Gockel. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it under the terms of the Apache License
 *  as published by the Apache Software Foundation, either version 2 of the License, or (at your option) any later
 *  version.
 *
 *  \author Travis Gockel (travis@gockelhut.com)
**/
#include <jsonv/array.hpp>

#include "detail.hpp"

#include <algorithm>
#include <ostream>

namespace jsonv
{

value array()
{
    value x;
    x._data.array = new detail::array_impl;
    x._kind = kind::array;
    return x;
}

value array(std::initializer_list<value> source)
{
    value x = array();
    x.assign(source);
    return x;
}

namespace detail
{

value::size_type array_impl::size() const
{
    return _values.size();
}

bool array_impl::empty() const
{
    return _values.empty();
}

}

value::array_iterator value::begin_array()
{
    check_type(kind::array, get_kind());
    return array_iterator(this, 0);
}

value::const_array_iterator value::begin_array() const
{
    check_type(kind::array, get_kind());
    return const_array_iterator(this, 0);
}

value::array_iterator value::end_array()
{
    check_type(kind::array, get_kind());
    return array_iterator(this, _data.array->_values.size());
}

value::const_array_iterator value::end_array() const
{
    check_type(kind::array, get_kind());
    return const_array_iterator(this, _data.array->_values.size());
}

value::array_view value::as_array()
{
    return array_view(begin_array(), end_array());
}

value::const_array_view value::as_array() const
{
    return const_array_view(begin_array(), end_array());
}

value& value::operator[](size_type idx)
{
    check_type(kind::array, get_kind());
    return _data.array->_values[idx];
}

const value& value::operator[](size_type idx) const
{
    check_type(kind::array, get_kind());
    return _data.array->_values[idx];
}

value& value::at(size_type idx)
{
    check_type(kind::array, get_kind());
    return _data.array->_values.at(idx);
}

const value& value::at(size_type idx) const
{
    check_type(kind::array, get_kind());
    return _data.array->_values.at(idx);
}

void value::push_back(value item)
{
    check_type(kind::array, get_kind());
    _data.array->_values.emplace_back(std::move(item));
}

void value::pop_back()
{
    check_type(kind::array, get_kind());
    if (_data.array->_values.empty())
        throw std::logic_error("Cannot pop from empty array");
    _data.array->_values.pop_back();
}

void value::push_front(value item)
{
    check_type(kind::array, get_kind());
    _data.array->_values.emplace_front(std::move(item));
}

void value::pop_front()
{
    check_type(kind::array, get_kind());
    if (_data.array->_values.empty())
        throw std::logic_error("Cannot pop from empty array");
    _data.array->_values.pop_front();
}

void value::assign(size_type count, const value& val)
{
    check_type(kind::array, get_kind());
    _data.array->_values.assign(count, val);
}

void value::assign(std::initializer_list<value> items)
{
    check_type(kind::array, get_kind());
    _data.array->_values.assign(std::move(items));
}

void value::resize(size_type count, const value& val)
{
    check_type(kind::array, get_kind());
    _data.array->_values.resize(count, val);
}

value::array_iterator value::erase(const_array_iterator position)
{
    check_type(kind::array, get_kind());
    difference_type dist(position - begin_array());
    _data.array->_values.erase(_data.array->_values.begin() + dist);
    return array_iterator(this, static_cast<size_type>(dist));
}

value::array_iterator value::erase(const_array_iterator first, const_array_iterator last)
{
    difference_type fdist(first - begin_array());
    difference_type ldist(last  - begin_array());
    _data.array->_values.erase(_data.array->_values.begin() + fdist,
                               _data.array->_values.begin() + ldist
                              );
    return array_iterator(this, static_cast<size_type>(fdist));
}

namespace detail
{

int array_impl::compare(const array_impl& other) const
{
    auto self_iter = _values.begin();
    auto othr_iter = other._values.begin();
    for (; self_iter != _values.end() && othr_iter != other._values.end(); ++self_iter, ++othr_iter)
        if (int cmp = self_iter->compare(*othr_iter))
            return cmp;
    return self_iter == _values.end() ? othr_iter == other._values.end() ? 0 : -1 : 1;
}

bool array_impl::operator==(const array_impl& other) const
{
    if (this == &other)
        return true;
    if (_values.size() != other._values.size())
        return false;
    
    return std::equal(begin(_values), end(_values), begin(other._values));
}

bool array_impl::operator!=(const array_impl& other) const
{
    return !operator==(other);
}

}
}