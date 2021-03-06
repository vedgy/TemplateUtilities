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

# include "TestUtilities.hpp"

# include <TemplateUtilities/Reserve.hpp>

# include <CommonUtilities/Testing.hpp>

# include <QObject>
# include <QTest>

# include <cstdint>
# include <cmath>
# include <functional>
# include <random>
# include <chrono>
# include <iostream>


namespace TemplateUtilities
{
namespace
{
std::mt19937 & randomEngine()
{
    static std::mt19937 e(
        static_cast<std::uint_fast32_t>(
            std::chrono::system_clock::now().time_since_epoch().count()));
    return e;
}

using UniformDistribution = std::uniform_int_distribution<int>;

namespace TestAllStatic
{
inline UniformDistribution & reserveCount()
{
    static UniformDistribution u(0, 1000);
    return u;
}

}

namespace SpecializedTestStatic
{
inline UniformDistribution & startSize()
{
    static UniformDistribution u(0, 1000);
    return u;
}

inline UniformDistribution & multiplier()
{
    static UniformDistribution u(0, 10);
    return u;
}

}

template <class Container>
void equalContainers(const Container & lhs, const Container & rhs);

template <class Container, class Init, class Capacity>
void testCapacity(Init init, Capacity capacity);


template <class Container>
struct TestAll {
    void operator()() const;
};

template <class Container>
struct TestCapacity {
    void operator()() const;
};

template <class Container>
struct TestMaxLoadFactor {
    void operator()() const;
};

}

class ReserveTest: public QObject
{
    Q_OBJECT
private slots:
    void allContainers();
    void containersWithCapacity();
    void containersWithMaxLoadFactor();
};


namespace
{
template <class Container>
void equalContainers(const Container & lhs, const Container & rhs)
{
    if (lhs != rhs) {
        CommonUtilities::Testing::printForType<Container>(true);
        std::cout << "reserving changed container." << std::endl;
        QFAIL("");
    }
}

template <class Container, class Init, class Capacity>
void testCapacity(Init init, Capacity capacity)
{
    typedef typename Container::size_type SizeType;
    Container container = init(static_cast<SizeType>(
                                   SpecializedTestStatic::startSize()(
                                       randomEngine())));
    const Container copy = container;

    const SizeType newCapacity =
        capacity(container) *
        static_cast<SizeType>(
            SpecializedTestStatic::multiplier()(randomEngine()));
    reserve(container, newCapacity);

    equalContainers(container, copy);
    if (capacity(container) < newCapacity) {
        CommonUtilities::Testing::printForType<Container>(true);
        std::cout << "capacity after reserving " << newCapacity
                  << " is insufficient (" << capacity(container) << ")."
                  << std::endl;
        QFAIL("");
    }
}


template <class Container>
void TestAll<Container>::operator()() const
{
    Container container {}, copy = container;
    reserve(container, static_cast<typename Container::size_type>(
                TestAllStatic::reserveCount()(randomEngine())));
    equalContainers(container, copy);
}

template <class Container>
void TestCapacity<Container>::operator()() const
{
    testCapacity<Container>(
    [](typename Container::size_type size) {
        return Container(size, typename Container::value_type {'\0'});
    },
    std::bind(& Container::capacity, std::placeholders::_1));
}

template <class Container>
void TestMaxLoadFactor<Container>::operator()() const
{
    testCapacity<Container>(
    [](typename Container::size_type size) {
        return Container(size);
    },
    [](const Container & c) {
        return (typename Container::size_type)
               std::ceil(c.bucket_count() * c.max_load_factor());
    });
}

}

void ReserveTest::allContainers()
{
    TestUtilities::rotateAllContainers<TestAll>();
}

void ReserveTest::containersWithCapacity()
{
    TestUtilities::rotateContainersWithCapacity<TestCapacity>();
}

void ReserveTest::containersWithMaxLoadFactor()
{
    TestUtilities::rotateContainersWithMaxLoadFactor<TestMaxLoadFactor>();
}

}


QTEST_MAIN(TemplateUtilities::ReserveTest)


# include "ReserveTest.moc"
