export module CowString:String;

import std;

namespace sea_jackal
{

export class CowString final
{
public:
    class SymbolModifier;

    explicit CowString(std::string_view value);
    CowString(const CowString &other) noexcept;
    CowString &operator=(const CowString &other) noexcept;
    ~CowString() noexcept;

    [[nodiscard]] operator std::string() const;

    [[nodiscard]] CowString DeepCopy() const;

    SymbolModifier operator[](std::size_t index) noexcept;

private:
    void Detach();

    char *data_;
    std::size_t *ref_counter_;
    std::size_t size_ = 0;
};

} // namespace sea_jackal
