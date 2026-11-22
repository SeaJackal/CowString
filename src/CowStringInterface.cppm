export module CowString:String;

import std;

namespace sea_jackal
{

export class CowString
{
public:
    class SymbolModifier;

    explicit CowString(std::string_view value);
    CowString(const CowString &other);
    CowString &operator=(const CowString &other);
    ~CowString() noexcept;

    [[nodiscard]] operator std::string() const;

    [[nodiscard]] CowString DeepCopy() const;

    SymbolModifier operator[](std::size_t index);

private:
    void Detach();

    char *data_;
    std::size_t *ref_counter_;
    std::size_t size_ = 0;
};

} // namespace sea_jackal
