#include <MinHook.h>

#include "FunctionHook.hpp"

using namespace std;

namespace kanan {
    bool g_isMinHookInitialized{ false };

    FunctionHook::FunctionHook(uintptr_t target, uintptr_t destination)
        : m_target{ 0 },
        m_destination{ 0 },
        m_original{ 0 }
    {
        // Initialize MinHook if it hasn't been already.
        if (!g_isMinHookInitialized && MH_Initialize() == MH_OK) {
            g_isMinHookInitialized = true;
        }

        // Create and enable the hook, only setting our member variables if it was
        // successful.
        uintptr_t original{ 0 };

        if (MH_CreateHook((LPVOID)target, (LPVOID)destination, (LPVOID*)&original) == MH_OK &&
            MH_EnableHook((LPVOID)target) == MH_OK)
        {
            m_target = target;
            m_destination = destination;
            m_original = original;
        }
    }

    FunctionHook::~FunctionHook() {
        remove();
    }

    bool FunctionHook::remove() {
        // Don't try to remove invalid hooks.
        if (m_original == 0) {
            return true;
        }

        // Disable then remove the hook.
        if (MH_DisableHook((LPVOID)m_target) != MH_OK ||
            MH_RemoveHook((LPVOID)m_target) != MH_OK) {
            return false;
        }

        // Invalidate the members.
        m_target = 0;
        m_destination = 0;
        m_original = 0;

        return true;
    }
}
