#include "tokenizer.h"

Tokenizer::Tokenizer(const std::string& source)
    : m_string{source}
{}

Tokenizer::Iterator::Iterator(const std::string& string)
    : m_sv{string}
{
    step();
}

Tokenizer::Iterator&
Tokenizer::Iterator::operator++()
{
    m_index += m_step;
    step();
    return *this;
}

std::string_view
Tokenizer::Iterator::operator*() const
{
    return m_sv.substr(m_index, m_step);
}

bool
Tokenizer::Iterator::operator!=(const Iterator& other) const
{
    return m_index < other.m_sv.size();
}

void
Tokenizer::Iterator::step()
{
    if(m_index >= m_sv.size()) return;

    if ('"' == m_sv.at(m_index))
    {
        m_index = m_sv.find("\"", m_index);
        m_step = m_sv.find("\"", m_index + 1) - m_index + 1;
    }
    else if (']' == m_sv.at(m_index)
        || '}' == m_sv.at(m_index)
        || '[' == m_sv.at(m_index)
        || '{' == m_sv.at(m_index))
    {
        m_step = 1;
    }
    else if (' ' == m_sv.at(m_index)
        || '\n' == m_sv.at(m_index)
        || ',' == m_sv.at(m_index)
        || ':' == m_sv.at(m_index))
    {
        ++m_index;
        step();
    }
    else
    {
        size_t pos = m_index;
        while( pos < m_sv.size()
            && ' ' != m_sv.at(pos)
            && '}' != m_sv.at(pos)
            && ']' != m_sv.at(pos)
            && ',' != m_sv.at(pos))
        {
            ++pos;
        }
        m_step = pos - m_index;
    }
}

Tokenizer::Iterator
Tokenizer::begin() const noexcept
{
    return {m_string};
}

Tokenizer::Iterator
Tokenizer::end() const noexcept
{
    return {m_string};
}