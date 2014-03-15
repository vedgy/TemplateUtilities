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

# ifndef TEMPLATE_UTILITIES_RESERVE_HPP
# define TEMPLATE_UTILITIES_RESERVE_HPP

# include <utility>
# include <type_traits>


namespace TemplateUtilities
{
template <class C, typename = void>
struct HasReserve
        : std::false_type
{};

template <class C>
struct HasReserve < C, typename std::enable_if <
        std::is_same <
decltype(std::declval<C>().reserve(std::declval<typename C::size_type>())),
         void
         >::value
         >::type >
         : std::true_type
         {};

/// @brief Calls c.reserve(n) if appropriate C::reserve() method exists.
/// Has no effect otherwise.
template <class C>
typename std::enable_if < ! HasReserve<C>::value >::type
reserve(C &, typename C::size_type)
{}
template <class C>
typename std::enable_if<HasReserve<C>::value>::type
reserve(C & c, typename C::size_type n)
{
    c.reserve(n);
}

}

# endif // TEMPLATE_UTILITIES_RESERVE_HPP
