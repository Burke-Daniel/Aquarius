#pragma once

#include <memory>


namespace Aquarius {
    
    using timeDelta_t = float;

    template<typename T>
    using uniquePtr = std::unique_ptr<T>;

    template<typename T>
    using sharedPtr = std::shared_ptr<T>;

} // namespace Aquarius
