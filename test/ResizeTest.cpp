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

# include <TemplateUtilities/Resize.hpp>

# include <CommonUtilities/Testing.hpp>

# include <QObject>
# include <QTest>

# include <utility>
# include <array>
# include <iterator>
# include <iostream>


namespace TemplateUtilities
{
namespace
{
template <class Container>
void assertSize(const Container & container, int size);

template <class Container>
void assertValue(const Container & container, int position,
                 typename Container::value_type value);

template <class Container>
struct TestDefaultInit {
    void operator()() const;
};

template <class Container>
struct TestValueInit {
    void operator()() const;
};

template <class Container>
struct TestCorrectValues {
    void operator()() const;
};

}

class ResizeTest: public QObject
{
    Q_OBJECT
private slots:
    void defaultInit();
    void valueInit();
    void correctValues();
};


namespace
{
template <class Container>
void assertSize(const Container & container, const int size)
{
    const int resultingSize = static_cast<int>(
                                  std::distance(std::begin(container),
                                          std::end(container)));
    if (resultingSize != size) {
        CommonUtilities::Testing::printForType<Container>(true);
        std::cout << "resulting size after resizing to " << size
                  << " was " << resultingSize << '.' << std::endl;
        QFAIL("");
    }
}

template <class Container>
void assertValue(const Container & container, const int position,
                 const typename Container::value_type value)
{
    const auto atPosition = * std::next(std::begin(container), position);
# ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wfloat-equal"
# endif
    if (atPosition != value) {
# ifdef __clang__
# pragma clang diagnostic pop
# endif
        CommonUtilities::Testing::printForType<Container>(true);
        std::cout << "resizing resulted in incorrect value." << std::endl;
        CommonUtilities::Testing::print("position", position,
                                        "expected_value", value,
                                        "actual_value", atPosition);
        QFAIL("");
    }
}


template <class Container>
void TestDefaultInit<Container>::operator()() const
{
    Container container;
    assertSize(container, 0);
    const int biggerSize = 100, smallerSize = 5;
    resize(container, biggerSize);
    assertSize(container, biggerSize);
    resize(container, smallerSize);
    assertSize(container, smallerSize);
}

template <class Container>
void TestValueInit<Container>::operator()() const
{
    Container container;
    assertSize(container, 0);

    /// WARNING: be careful with changing constants -
    /// test logic depends on values!
    constexpr int a = 44, b = 11, c = 55;
    resize(container, a, {1});
    assertSize(container, a);
    assertValue(container, a - 1, {1});

    resize(container, b, typename Container::value_type());
    assertSize(container, b);
    assertValue(container, b - 1, {1});

    resize(container, c, {0});
    assertSize(container, c);
    assertValue(container, c - 1, {0});
}

template <class Container>
void TestCorrectValues<Container>::operator()() const
{
    /// WARNING: be careful with changing numbers -
    /// test logic depends on values!
    constexpr std::array<std::pair<int, typename Container::value_type>, 5>
    config = {{
            { 222, 57 }, { 600, 2 }, { 10, 99 }, { 0, 5 }, { 5, 0 }
        }
    };
    Container container;
    assertSize(container, 0);

    using SizeType = typename Container::size_type;

    int prevSize = 0;
    for (const auto & p : config) {
        resize(container, static_cast<SizeType>(p.first), p.second);
        assertSize(container, p.first);
        if (p.first > prevSize)
            assertValue(container, p.first - 1, p.second);
        else if (p.first != 0)
            assertValue(container, p.first - 1, config[0].second);
        prevSize = p.first;
    }

    const int a = prevSize + 11, b = prevSize + 2;
    resize(container, static_cast<SizeType>(a));
    assertSize(container, a);
    assertValue(container, a - 1, 0);
    resize(container, static_cast<SizeType>(b));
    assertSize(container, b);
    assertValue(container, b - 1, 0);
}

}

void ResizeTest::defaultInit()
{
    TestUtilities::rotateResizableDefaultInitContainers<TestDefaultInit>();
}

void ResizeTest::valueInit()
{
    TestUtilities::rotateResizableContainers<TestValueInit>();
}

void ResizeTest::correctValues()
{
    TestUtilities::rotateNumericalResizableContainers<TestCorrectValues>();
}

}


QTEST_MAIN(TemplateUtilities::ResizeTest)


# include "ResizeTest.moc"
