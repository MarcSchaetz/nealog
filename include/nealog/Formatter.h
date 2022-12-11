#pragma once

#include "fmt/compile.h"
#include <fmt/core.h>
#include <utility>


#define nlFormat(msg, ...) nealog::Formatter().format(msg, __VA_ARGS__)

namespace nealog
{




    class FormatterBase
    {
      protected:
        FormatterBase() = default;
    };

    /*
     * The formatter is a wrapper around the Fmt library
     */
    class Formatter : public FormatterBase
    {
      public:
        template <typename... TArg>
        auto format(const std::string_view& msg, TArg&&... args) -> std::string
        {
            return fmt::format(msg, std::forward<TArg>(args)...);
        }
    };



} // namespace nealog
  //
#ifdef NEALOG_HEADERONLY
#include "nealog_impl/FormatterImpl.h"
#endif // NEALOG_HEADERONLY
