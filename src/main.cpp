#include "PCH.h" // Include Precompiled Header first

namespace Hooks
{
    // Function specifically for patching the strength cap CMOV instruction
    void InstallStrengthCapPatch()
    {
        // --- Configuration ---
        // Offset of the CMOV instruction (0F 4F D8) from the Oblivion.exe base address.
        // Example: If Ghidra shows base 140000000 and instruction at 14684a835,
        // the offset is 14684a835 - 140000000 = 0x684a835.
        constexpr REL::Offset instructionOffset(0x684a835);

        // Size of the CMOV instruction (0F 4F D8 is 3 bytes)
        constexpr size_t instructionSize = 3;

        // Get the relocation object (calculates the address in memory)
        REL::Relocation<std::uintptr_t> target(instructionOffset);

        // Write NOP instructions (0x90) over the original instruction bytes
        // This effectively disables the conditional move that caps strength at 100.
        target.write_fill(REL::NOP, instructionSize);
    }

    // Main function to install all hooks/patches
    void Install()
    {
        // Call the specific patch function(s)
        InstallStrengthCapPatch();

    }

}

namespace // Anonymous namespace for local functions
{
    // OBSE Message Listener
    void MessageHandler(OBSE::MessagingInterface::Message* a_msg)
    {
        switch (a_msg->type) {
            // kPostLoad is sent after OBSE and all plugins are loaded,
            // making it a safe time to apply patches.
            case OBSE::MessagingInterface::kPostLoad:
                Hooks::Install();
                break;
            default:
                break;
        }
    }
}

// OBSE Plugin Entry Point (used by CommonLibOB64's rule)
OBSE_PLUGIN_LOAD(OBSE::LoadInterface* a_obse)
{
    OBSE::Init(a_obse);

    // Get the OBSE messaging interface and register our listener
    auto* messaging = OBSE::GetMessagingInterface();
    if (messaging) {
        messaging->RegisterListener(MessageHandler);
    } else {
        return false;
    }

    return true;
}
