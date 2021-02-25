#pragma once

#include <memory>

namespace Aquarius {

    template<typename T>
    using uniquePtr = std::unique_ptr<T>;

    template<typename T>
    using sharedPtr = std::shared_ptr<T>;

} // namespace Aquarius
