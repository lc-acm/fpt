# fpt
the OFFICIAL version of Jeff Ely's Freshman's Programming Toolkit

## What is this?

In CS 171 (Computer Science I) and CS 377/477 (Graphics/Advanced Graphics), there is at least a portion which requires use of Jeff Ely's "Freshman's Programming Toolkit (fpt)." FPT is a graphics library which uses X11 to allow C-based graphical function on most operating systems. 

There have been several different versions of FPT floating around on GitHub for quite some time now, and the Lewis & Clark ACM Student Chapter has decided to curate one for easy installation.

## How do I install this?

If you are using a Mac, read both sections. If you are using a Linux system, skip to "Installing FPT." If you are using Windows, you may need to install a Linux virtual machine and then follow the Linux instructions.

### Installing X11

MacOS used to include X11, but stopped doing so in the mid 2010s. Luckily, there is an open-source project called XQuartz which maintains a Mac-compatible build of X11.

Go to [https://www.xquartz.org/](https://www.xquartz.org/), and download the `.DMG` image for the latest version of XQuartz. When it finishes downloading install it and verify the installation by launching the `XQuartz` app.

### Installing FPT

1. Open a terminal window. If you've just installed XQuartz, make sure to open a new window rather than reusing one you might already have open. XQuartz changes do not propagate until you open a new terminal window.
2. Obtain this copy of FPT. We recommend using the command `git clone https://github.com/lc-acm/fpt`.
3. Navigate to FPT. If you've used the `git clone` command, you should be able to simply `cd fpt`.
4. Decide where you'd like FPT to be installed. For Macs, we recommend `/Users/<yourusername>/fpt` and for Linux users we recommend `/home/<yourusername>/fpt`. You are free to install it anywhere else, of course, but make sure it's somewhere you have permissions to create files and directories.
5. Make FPT. This is accomplished by running the command `./make_FPT <path-to-the-place-you-want-fpt-installed>`. You will see several warning messages. This is fine, ignore them.
6. Verify FPT. Run `which acom` and you should see something like `/usr/local/bin/acom`.
7. You're done! Now, you should be able to run any of the included examples by compiling with `acom <example>`, and running `./a.out`. The examples are in the `<path to this directory>/fpt/Examples/` directory.
8. Feel free to delete the directory containing this document and the `make_FPT` script. The script has created a new copy of the library.

If you find that you need help, feel free to reach out to <lcacmchapter@gmail.com> or stop by CSpace.
