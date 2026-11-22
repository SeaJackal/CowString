export module CowString:SymbolModifier;

import std;
import :String;

namespace sea_jackal
{

class CowString::SymbolModifier
{
public:
    SymbolModifier(CowString &cow_str, std::size_t index);

    operator char() const;

    SymbolModifier &operator=(char symbol);

private:
    CowString *cow_str_;
    std::size_t index_;
};

} // namespace sea_jackal
