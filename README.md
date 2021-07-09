# TextBased_Shell_Utility
 A simple menu that allows a user to pick an item that will execute that command.


 The shell will read a single key "command" entered by the user,
 Followed by a file or directory number
 (or [optionally]) partial file name with “name completion”
 and it will output some system information on the terminal,
 or run a program (by means of systems calls).

# The commands it will implement:
 Edit – opens a text editor with a file.
 Run - runs an executable program. You should handle parameters.
 Change – changes working directory.
 Sort – sorts listing by either size or date (prompt user)

 Prev, and Next Operations so that the menu fits on one screen.
 Store names in an array, Only one pass through directory.