module;
#include <cassert>

module CowString;

import std;

namespace sea_jackal
{

CowString::CowString(std::string_view value)
    : data_(nullptr), ref_counter_(nullptr), size_(value.size())
{
    try
    {
        data_ = new char[value.size()];
        ref_counter_ = new std::size_t;
    }
    catch (...)
    {
        delete ref_counter_;
        delete[] data_;
        throw;
    }
    *ref_counter_ = 1;
    std::copy_n(value.data(), size_, data_);
}

CowString::CowString(const CowString &other) noexcept
    : data_(other.data_), ref_counter_(other.ref_counter_), size_(other.size_)
{
    (*other.ref_counter_)++;
}

CowString &CowString::operator=(const CowString &other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    Destroy();
    data_ = other.data_;
    ref_counter_ = other.ref_counter_;
    size_ = other.size_;
    (*ref_counter_)++;
    return *this;
}

CowString::~CowString() noexcept { Destroy(); }

CowString::operator std::string() const
{
    return size_ != 0 ? std::string(data_, size_) : std::string{};
}

CowString CowString::DeepCopy() const
{
    return CowString(size_ != 0 ? std::string_view(data_, size_)
                                : std::string_view{});
}

CowString::SymbolModifier CowString::operator[](std::size_t index) noexcept
{
    assert(index < size_);
    return {*this, index};
}

void CowString::Detach()
{
    auto new_string = DeepCopy();
    *this = new_string;
}

void CowString::Destroy()
{
    (*ref_counter_)--;
    if (*ref_counter_ == 0)
    {
        delete ref_counter_;
        delete[] data_;
    }
}

} // namespace sea_jackal
