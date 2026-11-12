# Third-party notices

AliceFracturedMinds includes or builds on the following projects. Copyright
remains with the respective authors.

| Component | Use | License |
| --- | --- | --- |
| [Alice Co-op](https://github.com/docwitson/Alice-Madness-Returns-Co-op) | The co-op mod this project is forked from | GPL-2.0 |
| [MadnessPatch](https://github.com/Wemino/MadnessPatch) | Base injection DLL, fixes and build foundation | GPL-2.0 |
| [Dear ImGui](https://github.com/ocornut/imgui) 1.92.8 | In-game menu and overlays | MIT |
| [SafetyHook](https://github.com/cursey/safetyhook) | Runtime hooks | Boost Software License 1.0 |
| [Zydis](https://github.com/zyantific/zydis) | Disassembly support bundled with SafetyHook | MIT |
| [SDL](https://github.com/libsdl-org/SDL) 3.4.12 | Controller support inherited from MadnessPatch | zlib |
| [mINI](https://github.com/metayeti/mINI) 0.9.18 | INI parsing | MIT |

The vendored source files keep their original copyright and license headers.
Redistribution notices are collected in [`third_party/licenses`](third_party/licenses)
and included in release archives. SDL's complete license text also remains in
[`include/SDL3/SDL_copying.h`](include/SDL3/SDL_copying.h).

The Unreal Engine 3 SDK declarations in `include/SDK` are inherited from the
MadnessPatch source tree and are used only to interoperate with the installed
game. They contain no retail game assets or executable game build.

Release binaries depend on the Microsoft Visual C++ runtime (x86), which is not
bundled; install the Microsoft Visual C++ Redistributable when required.
