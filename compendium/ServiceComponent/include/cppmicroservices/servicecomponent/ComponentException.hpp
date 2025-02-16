/*=============================================================================

  Library: CppMicroServices

  Copyright (c) The CppMicroServices developers. See the COPYRIGHT
  file at the top-level directory of this distribution and at
  https://github.com/CppMicroServices/CppMicroServices/COPYRIGHT .

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  =============================================================================*/

#ifndef ComponentException_hpp
#define ComponentException_hpp

#include <stdexcept>
#include <string>

#include <cppmicroservices/servicecomponent/ServiceComponentExport.h>

namespace cppmicroservices {
namespace service {
namespace component {

/**
 \defgroup gr_componentexception ComponentException
 \brief Groups ComponentException class related symbols.
 */

#ifdef _MSC_VER
// C4275 can be ignored in Visual C++ if you are deriving from a type in the C++ Standard Library
#  pragma warning(push)
#  pragma warning(disable : 4275)
#endif
/**
 * \ingroup gr_componentexception
 *
 * Exception which may be thrown by Service Component Runtime.
 */
class US_ServiceComponent_EXPORT ComponentException final : public std::runtime_error
{
public:
  /**
   * Construct a new ComponentException with the specified message.
   *
   * @param message The message for the exception.
   */
  explicit ComponentException(const std::string& message);
  explicit ComponentException(const char* message);

  virtual ~ComponentException() noexcept;
};
#ifdef _MSC_VER
#  pragma warning(pop)
#endif
}
}
}

#endif /* ComponentException_hpp */
