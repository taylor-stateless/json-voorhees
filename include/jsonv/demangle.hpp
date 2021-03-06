/** \file jsonv/demangle.hpp
 *
 *  Copyright (c) 2015 by Travis Gockel. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it under the terms of the Apache License
 *  as published by the Apache Software Foundation, either version 2 of the License, or (at your option) any later
 *  version.
 *
 *  \author Travis Gockel (travis@gockelhut.com)
**/
#ifndef __JSONV_DEMANGLE_HPP_INCLUDED__
#define __JSONV_DEMANGLE_HPP_INCLUDED__

#include <jsonv/config.hpp>
#include <jsonv/string_view.hpp>

#include <functional>
#include <string>

namespace jsonv
{

/** \addtogroup Serialization
 *  \{
**/

/** Convert the input \a source from a mangled type into a human-friendly version. This is used by \c formats (and the
 *  associated serialization functions) to give more user-friendly names in type errors.
 *
 *  \see demangle_function
 *  \see set_demangle_function
**/
JSONV_PUBLIC std::string demangle(string_view source);

/** Type of function used in setting a custom demangler.
 *
 *  \see demangle
 *  \see set_demangle_function
**/
using demangle_function = std::function<std::string (string_view source)>;

/** Sets the global demangle function. This controls the behavior of \c demangle -- the provided \a func will be called
 *  by \c demangle.
 *
 *  \see demangle
**/
JSONV_PUBLIC void set_demangle_function(demangle_function func);

/** Resets the demangle function to the default.
 *
 *  \see set_demangle_function
**/
JSONV_PUBLIC void reset_demangle_function();

/** Get the demangled type name of the current exception. This is meant to be called from `catch (...)` blocks to
 *  attempt to get more information about the exception type when it doesn't derive from a known entity.
 *
 *  \returns The demangled type name of the current exception or "unknown" if this cannot be discovered. Failure to
 *   discover is not an error -- this can happen if the exception is foreign to C++ (it does not have a
 *   \c std::type_info implementation) or if discovery is not known for this platform.
**/
JSONV_PUBLIC std::string current_exception_type_name();

/** \} **/

}

#endif/*__JSONV_DEMANGLE_HPP_INCLUDED__*/
