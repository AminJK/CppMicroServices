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

#include "cppmicroservices/LDAPFilter.h"

#include "cppmicroservices/Bundle.h"
#include "cppmicroservices/ServiceReference.h"

#include "LDAPExpr.h"
#include "Properties.h"
#include "PropsCheck.h"
#include "ServiceReferenceBasePrivate.h"

#include <stdexcept>

namespace cppmicroservices {

class LDAPFilterData
{
public:
  LDAPFilterData()
    : ldapExpr()
  {
  }

  LDAPFilterData(const std::string& filter)
    : ldapExpr(filter)
  {
  }

  LDAPFilterData(const LDAPFilterData&) = default;

  LDAPExpr ldapExpr;
};

LDAPFilter::LDAPFilter()
  : d(nullptr)
{
}

LDAPFilter::LDAPFilter(const std::string& filter)
  : d(nullptr)
{
  try {
    d = std::make_shared<LDAPFilterData>(filter);
  } catch (const std::exception& e) {
    throw std::invalid_argument(e.what());
  }
}

LDAPFilter::LDAPFilter(const LDAPFilter&) = default;

LDAPFilter::~LDAPFilter() = default;

LDAPFilter::operator bool() const
{
  return d != nullptr;
}

bool LDAPFilter::Match(const ServiceReferenceBase& reference) const
{
  return ((d) ? d->ldapExpr.Evaluate(reference.d.load()->GetProperties(), false)
              : false);
}

// This function has been modified to call the LDAPExpr::Evaluate() function which takes
// an AnyMap rather than a PropertiesHandle to optimize the code. Constructing a Properties
// object is much slower (requiring a copy) than simply using the AnyMap directly.
bool LDAPFilter::Match(const Bundle& bundle) const
{
  if (d) {
    const auto& headers = bundle.GetHeaders();

    if (headers.GetType() != AnyMap::UNORDERED_MAP_CASEINSENSITIVE_KEYS) {
      props_check::ValidateAnyMap(headers);
    }

    return d->ldapExpr.Evaluate(headers, false);
  } else {
    return false;
  }
}

// This function has been modified to call the LDAPExpr::Evaluate() function which takes
// an AnyMap rather than a PropertiesHandle to optimize the code. Constructing a Properties
// object is much slower (requiring a copy) than simply using the AnyMap directly.
bool LDAPFilter::Match(const AnyMap& dictionary) const
{
  if (d) {
    if (dictionary.GetType() != AnyMap::UNORDERED_MAP_CASEINSENSITIVE_KEYS) {
      props_check::ValidateAnyMap(dictionary);
    }

    return d->ldapExpr.Evaluate(dictionary, false);
  } else {
    return false;
  }
}

// This function has been modified to call the LDAPExpr::Evaluate() function which takes
// an AnyMap rather than a PropertiesHandle to optimize the code. Constructing a Properties
// object is much slower (requiring a copy) than simply using the AnyMap directly.
bool LDAPFilter::MatchCase(const AnyMap& dictionary) const
{
  if (d) {
    if (dictionary.GetType() != AnyMap::UNORDERED_MAP_CASEINSENSITIVE_KEYS) {
      props_check::ValidateAnyMap(dictionary);
    }

    return d->ldapExpr.Evaluate(dictionary, true);
  } else {
    return false;
  }
}

std::string LDAPFilter::ToString() const
{
  return ((d) ? d->ldapExpr.ToString() : std::string());
}

bool LDAPFilter::operator==(const LDAPFilter& other) const
{
  return (this->ToString() == other.ToString());
}

LDAPFilter& LDAPFilter::operator=(const LDAPFilter& filter) = default;

std::ostream& operator<<(std::ostream& os, const LDAPFilter& filter)
{
  return os << filter.ToString();
}
}
