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

# ifndef TEMPLATE_UTILITIES_TEST_UTILITIES_HPP
# define TEMPLATE_UTILITIES_TEST_UTILITIES_HPP

# define QSTRING_HAS_SIZE_TYPE QT_VERSION >= 0x050000

# include <QList>
# include <QLinkedList>
# include <QVector>
# include <QStack>
# include <QQueue>
# include <QMap>
# include <QMultiMap>

# if QSTRING_HAS_SIZE_TYPE
# include <QString>
# endif

# include <array>
# include <vector>
# include <deque>
# include <forward_list>
# include <list>
# include <set>
# include <map>
# include <unordered_set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <string>
# include <iostream>
# include <typeinfo>


namespace TemplateUtilities
{
namespace TestUtilities
{
template <template<class> class F, template<class> class Container>
void rotateNumericalElementTypes()
{
    F<Container<int>>()();
    F<Container<long long>>()();
    F<Container<unsigned short>>()();
    F<Container<unsigned long>>()();
    F<Container<double>>()();
    F<Container<long double>>()();
}

template <template<class> class F, template<class> class Container>
void rotateElementTypes()
{
    rotateNumericalElementTypes<F, Container>();
    F<Container<bool>>()();
    F<Container<char>>()();
    F<Container<signed char>>()();
    F<Container<std::string>>()();
}

template <typename T> using Array5 = std::array<T, 5>;
template <typename T> using Vector = std::vector<T>;
template <typename T> using Deque = std::deque<T>;
template <typename T> using ForwardList = std::forward_list<T>;
template <typename T> using List = std::list<T>;
template <typename T> using Set = std::set<T>;
template <typename T> using Multiset = std::multiset<T>;
template <typename T> using Map = std::map<T, T>;
template <typename T> using Multimap = std::multimap<T, std::string>;
template <typename T> using UnorderedSet = std::unordered_set<T>;
template <typename T> using UnorderedMultiset = std::unordered_multiset<T>;
template <typename T> using UnorderedMap = std::unordered_map<int, T>;
template <typename T> using UnorederedMultimap =
    std::unordered_multimap<T, char>;
template <typename T> using Stack = std::stack<T>;
template <typename T> using Queue = std::queue<T, Vector<T>>;
template <typename T> using TQMap = QMap<T, T>;
template <typename T> using TQMultiMap = QMultiMap<double, T>;


template <template<class> class F>
void rotateContainersWithCapacity()
{
    rotateElementTypes<F, Vector>();
    F<std::string>()();
    rotateElementTypes<F, QVector>();
}

template <template<class> class F>
void rotateContainersWithMaxLoadFactor()
{
    rotateElementTypes<F, UnorderedSet>();
    rotateElementTypes<F, UnorderedMultiset>();
    rotateElementTypes<F, UnorderedMap>();
    rotateElementTypes<F, UnorederedMultimap>();
}

template <template<class> class F>
void rotateResizableContainers()
{
    rotateContainersWithCapacity<F>();
    rotateElementTypes<F, Deque>();
    rotateElementTypes<F, ForwardList>();
    rotateElementTypes<F, List>();
    rotateElementTypes<F, QList>();
    rotateElementTypes<F, QLinkedList>();
    rotateElementTypes<F, QStack>();
    rotateElementTypes<F, QQueue>();
}

template <template<class> class F>
void rotateResizableDefaultInitContainers()
{
    rotateResizableContainers<F>();
# if QSTRING_HAS_SIZE_TYPE
    F<QString>()();
# endif
}

template <template<class> class F>
void rotateNumericalResizableContainers()
{
    rotateNumericalElementTypes<F, Vector>();
    rotateNumericalElementTypes<F, QVector>();
    rotateNumericalElementTypes<F, Deque>();
    rotateNumericalElementTypes<F, ForwardList>();
    rotateNumericalElementTypes<F, List>();
    rotateNumericalElementTypes<F, QList>();
    rotateNumericalElementTypes<F, QLinkedList>();
    rotateNumericalElementTypes<F, QStack>();
    rotateNumericalElementTypes<F, QQueue>();
}

template <template<class> class F>
void rotateAllContainers()
{
    rotateResizableDefaultInitContainers<F>();
    rotateContainersWithMaxLoadFactor<F>();
    rotateElementTypes<F, Array5>();
    rotateElementTypes<F, Set>();
    rotateElementTypes<F, Multiset>();
    rotateElementTypes<F, Map>();
    rotateElementTypes<F, Multimap>();
    rotateElementTypes<F, Stack>();
    rotateElementTypes<F, Queue>();
    rotateElementTypes<F, TQMap>();
    rotateElementTypes<F, TQMultiMap>();
}

}

}

# endif // TEMPLATE_UTILITIES_TEST_UTILITIES_HPP
