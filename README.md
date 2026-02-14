## how to install & set
1. clone cirrus: ``` https://github.com/wrouruy/cirrus.git && cd cirrus ```
2. compile it: ``` gcc main.c -o cirrus ```
3. make compiled file global(linux): ``` sudo ln -s "$(pwd)/cirrus" /usr/bin ```

## all flags
| command       | description         |
|---------------|---------------------|
| --help,    -h | print help          |
| --version, -v | print version       |
| --repo        | open repo on github |
| -S            | compile to asm      |