module;
#include <cassert>
#include <iterator>

module CowString;

import std;

namespace sea_jackal
{

CowString::CowString(std::string_view value)
    : data_(new char[value.size()]),
      ref_counter_(new std::size_t),
      size_(value.size())
{
    *ref_counter_ = 1;
    std::copy_n(value.data(), size_, data_);
}

CowString::CowString(const CowString &other)
    : data_(other.data_), ref_counter_(other.ref_counter_), size_(other.size_)
{
    (*other.ref_counter_)++;
}

CowString &CowString::operator=(const CowString &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->~CowString();
    data_ = other.data_;
    ref_counter_ = other.ref_counter_;
    size_ = other.size_;
    (*ref_counter_)++;
    return *this;
}

CowString::~CowString() noexcept
{
    (*ref_counter_)--;
    if (*ref_counter_ == 0)
    {
        delete ref_counter_;
        delete[] data_;
    }
}

CowString::operator std::string() const
{
    return size_ != 0 ? std::string(data_, size_) : std::string{};
}

CowString CowString::DeepCopy() const
{
    return CowString(size_ != 0 ? std::string_view(data_, size_)
                                : std::string_view{});
}

CowString::SymbolModifier CowString::operator[](std::size_t index)
{
    assert(index < size_);
    return {*this, index};
}

void CowString::Detach()
{
    auto new_string = DeepCopy();
    *this = new_string;
}

} // namespace sea_jackal
