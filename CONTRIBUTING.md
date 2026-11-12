# Contributing

AliceFracturedMinds is experimental reverse-engineering and compatibility work.
Small, focused changes with reproducible test cases are preferred.

1. Open an issue describing the map, checkpoint, host/client order and the exact
   observed behavior.
2. Build the `Release|x86` configuration with Visual Studio 2022 or newer
   (MSVC v143 toolset).
3. Keep protocol compatibility when practical. A breaking protocol change must
   update `src/Coop/Protocol.hpp` and the changelog together.
4. Do not commit game files, saves, crash dumps, private IP addresses, tokens,
   logs or proprietary assets.
5. Submit source changes under GPL-2.0 and keep the upstream notices.

See [docs/DEVELOPMENT.md](docs/DEVELOPMENT.md) for build details.
