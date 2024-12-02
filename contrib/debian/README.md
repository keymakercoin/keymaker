
Debian
====================
This directory contains files used to package keymakerd/keymaker-qt
for Debian-based Linux systems. If you compile keymakerd/keymaker-qt yourself, there are some useful files here.

## keymaker: URI support ##


keymaker-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install keymaker-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your keymaker-qt binary to `/usr/bin`
and the `../../share/pixmaps/keymaker128.png` to `/usr/share/pixmaps`

keymaker-qt.protocol (KDE)

