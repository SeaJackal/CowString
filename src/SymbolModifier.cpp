module CowString;

import std;

namespace sea_jackal
{

CowString::SymbolModifier::SymbolModifier(CowString &cow_str,
                                          std::size_t index) noexcept
    : cow_str_(&cow_str), index_(index)
{
}

CowString::SymbolModifier::operator char() const noexcept
{
    return cow_str_->data_[index_];
}

CowString::SymbolModifier &CowString::SymbolModifier::operator=(char symbol)
{
    if (*cow_str_->ref_counter_ > 1)
    {
        cow_str_->Detach();
    }
    cow_str_->data_[index_] = symbol;
    return *this;
}

} // namespace sea_jackal
