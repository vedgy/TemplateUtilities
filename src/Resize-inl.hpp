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

# ifndef TEMPLATE_UTILITIES_RESIZE_INL_HPP
# define TEMPLATE_UTILITIES_RESIZE_INL_HPP

# include <TemplateUtilities/Reserve.hpp>

# include <utility>
# include <type_traits>
# include <iterator>


namespace TemplateUtilities
{
template <class C, typename = void>
struct HasResizeDefaultInit
        : std::false_type
{};

template <class C>
struct HasResizeDefaultInit < C, typename std::enable_if <
        std::is_same <
decltype(std::declval<C>().resize(std::declval<typename C::size_type>())),
         void
         >::value
         >::type >
         : std::true_type
         {};


template <class C, typename = void>
struct HasResizeValueInit
        : std::false_type
{};

template <class C>
struct HasResizeValueInit < C, typename std::enable_if <
        std::is_same <
decltype(std::declval<C>().resize(std::declval<typename C::size_type>(),
                                  std::declval<typename C::value_type>())),
                                      void
                                      >::value
                                      >::type >
                                      : std::true_type
                                      {};


/// @brief Resizes collection c to size n by reserving and calling pushBack(c)
/// n times OR, if c.size() >= n, by erasing items from the end of c.
/// @tparam C Must have appropriate size(), erase() methods and iterators.
template <class C, class PushBack>
void customResize(C & c, typename C::size_type n, PushBack pushBack)
{
    typename C::size_type size = c.size();
    if (size < n) {
        reserve<C>(c, n);
        do {
            pushBack(c);
            ++size;
        }
        while (size < n);
    }
    else
        c.erase(std::next(c.begin(), n), c.end());
}

}

# endif // TEMPLATE_UTILITIES_RESIZE_INL_HPP
