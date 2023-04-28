#pragma once

#include "nealog/Severity.h"
#ifndef NEALOG_HEADERONLY
#include "nealog/Formatter.h"
#endif // !NEALOG_HEADERONLY

#include <string>

namespace nealog
{
    NL_INLINE PatternFormatter::PatternFormatter(const std::string_view& pattern) : pattern_{pattern}
    {
    }



    NL_INLINE auto PatternFormatter::setLoggerInfo(std::string_view name, Severity severity) -> void
    {
        loggerName_ = name;
        severity_   = severity;
    }



    NL_INLINE auto PatternFormatter::wrapMessageWithPattern(const std::string_view& msg) -> std::string
    {
        std::string copiedPattern{pattern_};

        replaceSubstitutor(MESSAGE_SUBSTITUTOR, copiedPattern, msg);
        replaceSubstitutor(NAME_SUBSTITUTOR, copiedPattern, loggerName_);
        replaceSubstitutor(SEVERITY_NUMBER_SUBSTITUTOR, copiedPattern, std::to_string((int)severity_));
        replaceSubstitutor(SEVERITY_NAME_SUBSTITUTOR, copiedPattern, severityToString(severity_));

        return copiedPattern;
    }



    NL_INLINE auto PatternFormatter::replaceSubstitutor(const char* substitutor, std::string& pattern,
                                                        std::string_view substitutee) -> void
    {
        size_t position = pattern.find(substitutor);

        while (position != std::string::npos)
        {
            pattern.replace(position, strlen(substitutor), substitutee);
            position = pattern.find(substitutor);
        }
    }



    NL_INLINE auto PatternFormatter::getPattern() const -> const std::string&
    {
        return pattern_;
    }

} // namespace nealog
