# Digital-electronics-2
# H1
## H2
### H3
*italics*
**bold**
## List - unordered and ordered
- item 1
- item 2
- item 3
1. item A
2. item B
3. item C
## Link
The link to this repository: [link](https://github.com/xhorna16/Digital-electronics-2)
## Table
First Header | Second Header
------------ | -------------
Content from cell 1 | Content from cell 2
Content in the first column | Content in the second column
## C code example
```c
#define LED_GREEN   PB5 // AVR pin where green LED is connected
#define SHORT_DELAY 250 // Delay in milliseconds
#ifndef F_CPU           // Preprocessor directive allows for conditional
                        // compilation. The #ifndef means "if not defined".
# define F_CPU 16000000 // CPU frequency in Hz required for delay
#endif                  // The #ifndef directive must be closed by #endif
```c
