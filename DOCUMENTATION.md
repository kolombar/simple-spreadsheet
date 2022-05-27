# Spreadsheet

The application provides a simple spreadsheet that is both displayed and controlled from terminal. There are two supported modes - command mode and interactive mode. In command mode the user modifies the spreadsheet by calling commands with specific arguments. In interactive mode the user can navigate through the spreadsheet using keyboard controls w/a/s/d and then modify the currently selected cell. Cells can store text as well as mathematical expressions. Every expression has to start with an equality sign `=` in order to be recognized as an expression. Basic mathematical operators `+`, `-`, `*`, `/` are supported. Expressions can also contain these functions: `abs`, `log`, `sin`, `cos`. Moreover, references to other cells are supported, e.g. `=A1 * 2` means that we take a value of a cell in the first row and the first column and multiply it by 2. If cyclic references are detected, error is reported and the new value is not set. Spreadsheet can be saved to a file or loaded from a file. Two supported file formats are TSV and CSV.

Supported commands:

- `SET "<cell>" "<expr>"` sets cell's value to the given expression
- `DEL "<cell>"` deletes cell's value
- `SHOW` prints values of all cells (math expressions are not evaluated)
- `SHOW "<cell>"` prints value of the given cell (math expressions are not evaluated)
- `PRINT` prints values of all cells (math expressions are evaluated)
- `PRINT "<cell>"` prints value of the given cell (math expressions are evaluated)
- `SAVE "<fileformat>" "<filepath>"` saves current spreadsheet to the specified file (supported formats are TSV and CSV, TSV is the default)
- `LOAD "<fileformat>" "<filepath>"` loads spreadsheet from the specified file (supported formats are TSV and CSV, TSV is the default)
- `EDIT` switches to interactive mode
- `EXIT` exits the program
- `HELP` prints help