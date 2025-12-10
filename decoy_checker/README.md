# Decoy Checker

The proposed solution came up during our project at AGH university of Krakoów. Main goal was to check if the user authenticated using valid credential or decoy. This might not be the best way to check those, and it will not work on seperate systems like said in the paper. However it gives some kind of isolation between two apps.

The program checks if there was a change in file `/var/tmp/check_decoy.txt` (by default, but can be changed). After the change occured, the program reads the value and checks if it's a valid one. Based on the result it prints to console whether it's a decoy or real password.

To compile and run the program:

```bash
gcc -o decoyChecker decoyChecker.c
./decoyChecker
```

## Troubleshooting

When segmentation fault appears, make sure that the file has those permissions:

```bash
chmod 666 /var/tmp/check_decoy.txt
chown root:root /var/tmp/check_decoy.txt
```
