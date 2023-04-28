#pragma once

#include "fmt/compile.h"
#include "nealog/Severity.h"
#include <algorithm>
#include <fmt/core.h>
#include <memory>
#include <utility>


#define nlFormat(msg, ...) nealog::Formatter().format(msg, __VA_ARGS__)

namespace nealog
{

    /*!
     * The formatter is a wrapper around the Fmt library
     */
    class Formatter
    {
      public:
        Formatter() = default;

        template <typename... TArg>
        auto format(const std::string_view& msg, TArg&&... args) -> std::string
        {
            return fmt::format(msg, std::forward<TArg>(args)...);
        }
    };



    constexpr const char* MESSAGE_SUBSTITUTOR         = "%(msg)";
    constexpr const char* NAME_SUBSTITUTOR            = "%(name)";
    constexpr const char* SEVERITY_NAME_SUBSTITUTOR   = "%(levelname)";
    constexpr const char* SEVERITY_NUMBER_SUBSTITUTOR = "%(levelno)";

    /*!
     * The PatternFormatter can be used to extend the message with specific
     * keywords that expand to different informations.
     *
     * The keywords used are a subset of the ones used in the Formatter
     * of Pythons standard logging library.
     */
    class PatternFormatter : public Formatter
    {
        using Formatter::format;

      public:
        PatternFormatter(const std::string_view& pattern);


        /*!
         *  If pattern_ is unset the message is returned as the normal Formatter formats it.
         */
        template <typename... TArg>
        auto format(const std::string_view& msg, TArg&&... args) -> std::string
        {
            std::string messageToFormat{msg};

            if (!pattern_.empty())
            {
                messageToFormat = wrapMessageWithPattern(msg);
            }

            return Formatter::format(messageToFormat, std::forward<TArg>(args)...);
        }

        auto getPattern() const -> const std::string&;

        auto setLoggerInfo(std::string_view name, Severity severity) -> void;

      private:
        auto wrapMessageWithPattern(const std::string_view& msg) -> std::string;
        /*!
         * Replaces the `substitutor` in a `pattern` with the `substitutee`.
         * The pattern will be changed.
         */
        auto replaceSubstitutor(const char* substitutor, std::string& pattern, std::string_view substitutee) -> void;

      private:
        std::string pattern_{};
        std::string loggerName_{};
        Severity severity_{};
    };


} // namespace nealog
  //
#ifdef NEALOG_HEADERONLY
#include "nealog_impl/FormatterImpl.h"
#endif // NEALOG_HEADERONLY
