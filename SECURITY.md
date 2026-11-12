# Security policy

## Supported versions

Only the latest published AliceFracturedMinds release is supported.

## Network warning

The UDP relay (`AliceCoopServer.exe`) is designed for localhost, a trusted LAN,
or a trusted VPN such as Radmin VPN. It has no authentication, encryption,
identity verification, or protection against hostile packets. Do not
port-forward it to the public Internet and do not run it on an untrusted network.

## Reporting a vulnerability

Do not publish exploitable network or file-handling vulnerabilities in a public
issue. Use GitHub's private vulnerability reporting when it is enabled, or
contact the repository owner through their GitHub profile.

Do not attach saves, crash dumps, or logs containing personal paths, IP
addresses or access tokens to a public report without redacting them first.
