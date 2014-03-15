/*
 This file is part of vedgTools/TemplateUtilities.
 Copyright (C) 2014 Igor Kushnir <igorkuo AT Google mail>

 vedgTools/TemplateUtilities is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 vedgTools/TemplateUtilities is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with
 vedgTools/TemplateUtilities.  If not, see <http://www.gnu.org/licenses/>.
*/

# ifndef TEMPLATE_UTILITIES_RESIZE_HPP
# define TEMPLATE_UTILITIES_RESIZE_HPP

# include "../../src/Resize-inl.hpp"


namespace TemplateUtilities
{
/// @brief Resizes collection c to size n either by calling c.resize(n) if
/// available, or manually. Manual resizing is performed by reserving and
/// pushing back n default-constructed elements OR, if c.size() >= n,
/// by erasing items from the end of c.
/// @tparam C Must have appropriate resize() method or
/// { size(), push_back(), erase() methods and iterators }.
template <class C>
typename std::enable_if < ! HasResizeDefaultInit<C>::value >::type
resize(C & c, typename C::size_type n)
{
    customResize<C>(c, n, [](C & c) { c.push_back(typename C::value_type()); });
}
template <class C>
typename std::enable_if<HasResizeDefaultInit<C>::value>::type
resize(C & c, typename C::size_type n)
{
    c.resize(n);
}


/// @brief Similar to resize(c, n), but calls c.resize(n, value) instead of
/// c.resize(n) OR pushes back value, not default-constructed element, n times.
template <class C>
typename std::enable_if < ! HasResizeValueInit<C>::value >::type
resize(C & c, typename C::size_type n, const typename C::value_type & value)
{
    customResize<C>(c, n, [& value](C & c) { c.push_back(value); });
}
template <class C>
typename std::enable_if<HasResizeValueInit<C>::value>::type
resize(C & c, typename C::size_type n, const typename C::value_type & value)
{
    c.resize(n, value);
}

}

# endif // TEMPLATE_UTILITIES_RESIZE_HPP
