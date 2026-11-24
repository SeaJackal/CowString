#include <gtest/gtest.h>

import std;
import CowString;

namespace sea_jackal
{
namespace
{

TEST(CowStringTest, ConstructsFromStringView)
{
    CowString value("hello");
    EXPECT_EQ(static_cast<std::string>(value), "hello");
}

TEST(CowStringTest, ConstructsFromEmptyStringView)
{
    CowString value("");
    EXPECT_EQ(static_cast<std::string>(value), "");
}

TEST(CowStringTest, ConvertedStringOwnsItsContents)
{
    CowString value("hello");
    std::string result = value;
    result[0] = 'j';
    EXPECT_EQ(static_cast<std::string>(value), "hello");
    value[4] = '!';
    EXPECT_EQ(result, "jello");
    EXPECT_EQ(static_cast<std::string>(value), "hell!");
}

TEST(CowStringTest, OwnsItsInput)
{
    std::string input = "hello";
    CowString value(input);
    input[0] = 'j';
    EXPECT_EQ(static_cast<std::string>(value), "hello");
}

TEST(CowStringTest, EmptyStringCanBeCopied)
{
    CowString empty("");
    auto copy = empty;
    auto deep_copy = empty.DeepCopy();
    EXPECT_EQ(static_cast<std::string>(copy), "");
    EXPECT_EQ(static_cast<std::string>(deep_copy), "");
}

TEST(CowStringTest, ModifiesFirstAndLastCharacters)
{
    CowString value("hello");
    value[0] = 'H';
    value[4] = '!';
    EXPECT_EQ(static_cast<std::string>(value), "Hell!");
}

TEST(CowStringTest, CopyConstructionKeepsMutationsIndependent)
{
    CowString original("hello");
    auto copy = original;
    copy[0] = 'j';
    EXPECT_EQ(static_cast<std::string>(original), "hello");
    EXPECT_EQ(static_cast<std::string>(copy), "jello");
    original[4] = '!';
    EXPECT_EQ(static_cast<std::string>(original), "hell!");
    EXPECT_EQ(static_cast<std::string>(copy), "jello");
}

TEST(CowStringTest, MultipleCopiesRemainIndependent)
{
    CowString original("abc");
    auto first = original;
    auto second = first;
    first[0] = 'x';
    second[1] = 'y';
    EXPECT_EQ(static_cast<std::string>(original), "abc");
    EXPECT_EQ(static_cast<std::string>(first), "xbc");
    EXPECT_EQ(static_cast<std::string>(second), "ayc");
}

TEST(CowStringTest, DeepCopyPreservesContentsAndIsIndependent)
{
    CowString original("hello");
    const auto &source = original;
    auto copy = source.DeepCopy();
    EXPECT_EQ(static_cast<std::string>(copy), "hello");
    original[0] = 'j';
    copy[4] = '!';
    EXPECT_EQ(static_cast<std::string>(original), "jello");
    EXPECT_EQ(static_cast<std::string>(copy), "hell!");
}

TEST(CowStringTest, CopyOutlivesOriginal)
{
    auto copy = [] {
        CowString original("hello");
        auto result = original;
        return result;
    }();
    EXPECT_EQ(static_cast<std::string>(copy), "hello");
    copy[0] = 'j';
    EXPECT_EQ(static_cast<std::string>(copy), "jello");
}

TEST(CowStringTest, AssigmentLeftAssociative)
{
    CowString original("abc");
    (original[0] = 'x') = 'y';
    EXPECT_EQ(static_cast<std::string>(original), "ybc");
}

} // namespace
} // namespace sea_jackal
