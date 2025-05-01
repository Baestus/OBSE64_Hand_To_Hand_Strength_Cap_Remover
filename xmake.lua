-- set xmake version (use version from example or newer)
set_xmakever("2.9.4") -- Or your installed version if >= 2.8.2

-- include commonlibob64's xmake config from the lib directory
includes("lib/commonlibob64")

-- set project details
set_project("StrengthCapRemover") 
set_version("1.0.0")             
set_license("GNU")               -- Choose your license

-- set defaults (usually fine as is)
set_arch("x64")
set_languages("c++23")
set_optimize("faster")
set_warnings("allextra", "error")
set_defaultmode("releasedbg") -- Build with release optimizations + debug info

-- enable link-time optimization (optional but good for release)
set_policy("build.optimization.lto", true)

-- add rules (keep these from the example)
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate") -- For VS project generation if used

-- setup the target DLL
target("StrengthCapRemover") -- Use the same name as set_project
    -- link against commonlibob64
    add_deps("commonlibob64")

    -- Apply the CommonLibOB64 plugin rule.
    -- This automatically sets defines, includes, links, entry points etc.
    add_rules("commonlibob64.plugin", {
        -- Provide necessary info for the rule
        name = "StrengthCapRemover", -- Match target/project name
        author = "jab",
        version = "1.0",            
    })

    -- add source files from the src directory
    add_files("src/**.cpp")
    add_headerfiles("src/**.h") -- Include headers too
    add_includedirs("src")      -- Allow includes relative to src (for PCH.h)
    set_pcxxheader("src/PCH.h") -- Specify precompiled header
