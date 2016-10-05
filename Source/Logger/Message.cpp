#include "Precompiled.hpp"
#include "Message.hpp"
#include "Sink.hpp"
using namespace Logger;

Message::Message() :
    std::ostream(&m_text),
    m_source(),
    m_line(0)
{
}

Message::Message(Message&& other) :
    std::ostream(&m_text)
{
    m_text = std::move(other.m_text);
    m_source = std::move(other.m_source);

    m_line = other.m_line;
    other.m_line = 0;
}

Message::~Message()
{
}

Message& Message::SetText(const char* text)
{
    if(text != nullptr)
    {
        m_text.str(text);
    }
    else
    {
        m_text.str("");
    }

    return *this;
}

Message& Message::SetSource(const char* source)
{
    // Store constant string before processing it.
    m_source = source;

    // Truncate the source file path.
    if(!m_source.empty())
    {
        // Normalize source path separators.
        std::replace(m_source.begin(), m_source.end(), '\\', '/');

        // Get the source directory path.
        std::string sourceDir = Build::GetSourceDir();

        if(sourceDir.empty())
        {
            // Workaround in case source directory isn't specified.
            sourceDir = "Source/";
        }

        // Remove base path to source directory.
        auto it = std::search(m_source.begin(), m_source.end(), sourceDir.begin(), sourceDir.end(),
            [](char a, char b)
            {
                // Ignore character case.
                return std::toupper(a) == std::toupper(b);
            }
        );

        if(it != m_source.end())
        {
            m_source.erase(m_source.begin(), it + sourceDir.size());
        }

        // Workaround for the first letter being lower case on Visual C++ compiler.
        // Happenes whenever __FILE__ macro is used inside an inlined function.
        if(!m_source.empty())
        {
            m_source[0] = std::toupper(m_source[0]);
        }
    }

    return *this;
}

Message& Message::SetLine(int line)
{
    Assert(line > 0, "Attempted to set an invalid source line!");

    m_line = line;
    return *this;
}

std::string Message::GetText() const
{
    return m_text.str();
}

std::string Message::GetSource() const
{
    return m_source;
}

int Message::GetLine() const
{
    return m_line;
}

bool Message::IsEmpty() const
{
    return m_text.str().empty();
}

ScopedMessage::ScopedMessage(Logger::Sink* sink) :
    m_sink(sink)
{
    Assert(sink != nullptr, "Attempted to create a scoped message with no sink!");
}

ScopedMessage::ScopedMessage(ScopedMessage&& other)
{
    m_sink = other.m_sink;
    other.m_sink = nullptr;
}

ScopedMessage::~ScopedMessage()
{
    if(m_sink != nullptr)
    {
        m_sink->Write(*this);
    }
}
