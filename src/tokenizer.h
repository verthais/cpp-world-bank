#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string_view>
#include <string>

class Tokenizer
{
public:
    Tokenizer(const std::string& source);

    class Iterator
    {
    public:
        Iterator(const std::string& string);

        Iterator& operator++();
        std::string_view operator*() const;
        bool operator!=(const Iterator& other) const;

    private:
        void step();

    private:
        size_t m_index{0};
        size_t m_step{0};
        std::string_view m_sv;
    };

    Iterator begin() const noexcept;
    Iterator end() const noexcept;

private:
    std::string m_string;
};

#endif // TOKENIZER_H