# HexTools
Just a simple hex editing lib for cpp.
## How to use
To use HexTools.h, just download the file, put it into your c++ project and link it in the start of the main file.
## Documentation
### HexByte
A struct that contains the data for a hex byte.
#### Constructors
Unsigned char copy constructor, unsigned int copy constructor, char copy constructor, int copy constructor, and HexByte copy constructor
##### Example
HexTools::HexByte = 81;
#### Functions
None
### HexData
A struct that can load files into hex and save hex into files, while also allowing you to edit the hex.
