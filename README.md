# Ropipe
> Convert roman numbers to integers and vice-versa in pipes
## What is ropipe?
Ropipe converts decimal integers to roman numbers and vice versa, reading from stdin and printing to stdout, it is meant to primarily be used in pipes.
Default is integer to roman.
## Options 
* -r : Roman to integer. Integer to roman is the default.
## Installation
    1. Clone this repository
    2. `cd` into it
    3. run
    ```sh
    sudo bash install.sh
    ```
    (The program is compiled at this time, you may check the script and the program out beforehand)
## Examples
Once installed, you can find sample files in the project dir.
```sh
ropipe < arabic.txt
```
```sh
ropipe -r < roman.txt
```
## Manpage

A manpage is installed alongside the program, try running `man ropipe`

## Updates

There is no automatic update system as of yet, you are advised to regularly visit https://github.com/MatMasIt/ropipe, download and re-run the installer in order to get updates