# Usage

Need [syringe](https://github.com/Multfinite/Syringe) for injection. The last one can be taken from ares.

`Syringe.exe --mix-list %filepath%`

- `filepath` it is path to file with mix definition.

Mix definition file is just a file, where 1 line = 1 mix file. No empty in file allowed. All mixes will be loaded BEFORE any other mixes. First entry will overwrite next entries. **Path of mix file is relative to gamemd.exe** - you are noticed.