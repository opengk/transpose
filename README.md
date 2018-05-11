# Transpose

As a first git deposit, I wrote this little program capable of transforming any terminal output vertically, i.e. the horizontal text is translated vertically.

### Prerequisites

You will need:
* a terminal
* a c compiler

It runs in a terminal as a command line program.
It is a c file, it can therefore be compiled on any system (I guess). On linux use can gcc.

### Warning

No special warning unless I have to improve the code to make it work with big files.
However, the aim is to output small texts in a terminal window and therefore converting big amount of text does not really make sense.

### Installing

The file can be compiled with gcc on linux by running the following command:

```
gcc -Wall src/transpose.c -o transpose
```

Then you can use ./transpose [FILE] to run the program. It can of course be moved to /usr/local/bin  for example or any other path to simply use 'transpose' without './' as a prefix.

### Use

Syntax is the following:

```
transpose [FILE]
```

You can also pipe into transpose like:
```
cat [FILE] | transpose
```

Or simply run the following to enter some text and end with Enter and EOF signal (CTRL-D):
```
transpose
```

## Author

* **Guillaume Koehl** - [opengk](https://github.com/opengk)

## License

* This project is licensed under the GNU GPL version 3 - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

* Kernighan and Ritchie's Learning C
* Linux 'coreutils' programs
