# ibwm - a TINY window manager

The name says it all. ibwm is a window manager (calling it that is a stretch) written in **110 lines of C**. It is pretty much the smallest window manager you can get with X11.
I made this to learn some stuff about X11. Use it if you want, or use it as a starting point for your own WM.

### Running

Compile with:

`gcc src/main.c -o ibwm -lX11`


Make sure you have xterm installed. 

Add this to your `.xinitrc`:

```
# ~/.xinitrc
xterm &
exec ibwm # replace with the path to where you have the ibwm executable stored
```

OR

Run startx with no .xinitrc file, then, run ibwm from the terminal in there. 

Then run `startx`. You could alternatively run it as an overlay over your current WM. 

