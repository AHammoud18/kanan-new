#pragma once

#include <cstdint>

namespace kanan {
    class FunctionHook {
    public:
        FunctionHook() = delete;
        FunctionHook(const FunctionHook& other) = delete;
        FunctionHook(FunctionHook&& other) = delete;
        FunctionHook(uintptr_t target, uintptr_t destination);
        virtual ~FunctionHook();

        // Called automatically by the destructor, but you can call it explicitly
        // if you need to remove the hook.
        bool remove();

        auto getOriginal() const {
            return m_original;
        }

        auto isValid() const {
            return m_original != 0;
        }

        FunctionHook& operator=(const FunctionHook& other) = delete;
        FunctionHook& operator=(FunctionHook&& other) = delete;

    private:
        uintptr_t m_target;
        uintptr_t m_destination;
        uintptr_t m_original;
    };
}