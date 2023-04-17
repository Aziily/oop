# Vector

## Orgnization

`bin` - the binary file

`src` - source code

`temp` - code compile temp

`obj` - the object file

## Quick Start

For windows(x86) user, just run `run.bat` in the terminal.

While for macOS(arm) user, the `run.sh` should be correct, while there will be one error that means the `ld` is not included in arm64, so it cannot work.

I guess this is because the difference between the instructions of x86 and arm, so if your PC is arm64, maybe you cannot use this too.

> The possible reason is the usage of stdexcept, maybe you can change it by yourself.
