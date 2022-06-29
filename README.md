```
                                       /$$     /$$           /$$      
                                      | $$    |__/          | $$      
                                     /$$$$$$   /$$  /$$$$$$$| $$$$$$$ 
                                    |_  $$_/  | $$ /$$_____/| $$__  $$
                                      | $$    | $$|  $$$$$$ | $$  \ $$
                                      | $$ /$$| $$ \____  $$| $$  | $$
                                      |  $$$$/| $$ /$$$$$$$/| $$  | $$
                                       \___/  |__/|_______/ |__/  |__/   v1.0
```

# To-do List
- [ ] Implementing `tfetch`
- [ ] Testing: Command Pipelines
- [ ] Testing: Advanced Scanning
- [ ] Testing: Error Handling
- [ ] Testing: Built-in Commands

# Known Issues
## Command Pipelines
- `echo Hello, World! > message.txt` returns with `-tish: syntax error: invalid filename` error
- Pipes ( `|` ) do not work
- Input Redirection (`<`) does not work