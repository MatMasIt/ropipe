
# Ropipe

![License](https://img.shields.io/github/license/MatMasIt/ropipe)
![c](https://img.shields.io/badge/language-C-blue)

> Convert Roman numbers to integers and vice-versa in pipes.

## What is ropipe?

Ropipe converts base-10 integers to Roman numbers and vice versa, reading from stdin and printing to stdout. It is designed to be used primarily in pipes. By default, it converts integers to Roman numbers.

## Options

- `-r`: Roman to integer conversion. Integer to Roman is the default behavior.
- `-h`: Display help message and exit.
- `-s`: Fail silently, with no output on invalid input.
- `-q`: Accept quirky Roman numerals like IIII for IV.
- `-k`: Don't quit on invalid input; continue processing subsequent inputs.


You can use the options concatenated, like `-rsk` or individually, like `-r -s -k`.


## Installation

1. Clone this repository:
   ```sh
   git clone https://github.com/MatMasIt/ropipe.git
   cd ropipe
   ```

2. Compile and install:

   ```sh
   sudo make install
   ```

   or

   ```sh
   doas make install
   ```

   The program is compiled during installation. You may review the script and the program before proceeding.

## Examples

Once installed, you can use `ropipe` in your shell commands. Below are some examples:

---

**Example 1:**

```sh
ropipe < arabic.txt
```

**Result:**

```
I
X
CXXIII
CCCXXI
```

---

**Example 2:**

```sh
ropipe -r < roman.txt
```

**Result:**

```
4
5
7
1200
```

## Manpage

A manpage is installed alongside the program. You can access it by running:

```sh
man ropipe
```

## Updates

There is no automatic update system currently implemented. Please visit [ropipe GitHub repository](https://github.com/MatMasIt/ropipe) regularly to check for updates. To update, download the latest version and re-run the installer.

Nontheless, it's not a program that one would expect to change often, so manual updates should be rare.

## Make commands

- `make`: compile ropipe
- `make install`: install ropipe
- `make uninstall`: uninstall ropipe
