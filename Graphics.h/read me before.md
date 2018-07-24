### How to integrate GRAPHICS.H with CODE BLOCKS

  1. Copy graphics.h and winbgim.h files in include folder of your compiler directory
  2. Copy libbgi.a to lib folder of your compiler directory
  3. In code::blocks open Settings >> Compiler and debugger >>linker settings
  4. click Add button  in link libraries part and browse and select libbgi.a file
  5. In right part (ie. other linker options) paste commands
  "-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32"
  6. click Ok
