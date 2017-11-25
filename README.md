# Scout

A simple Network scanner for GNU/Linux used as frontend for many network scanning tools like: nmap, nbtscan, smbclient, etc.. This is work in progress. Features:

+ Host discover with SMB protocol
+ SMB unprotected shares scanner
+ Host information gathering

![Image](../master/doc/scout.png?raw=true)

## Requirements:

All requirements can be installed with apt in debian-like systems:

```
sudo apt install \
nbtscan \
smbclient \
qt5-default \
libqtwebkit-dev \
libqt5webkit5-dev \
qtpositioning5-dev \
geoip-bin
```

Optional, for more actualized database (heavy download!)

```
geoip-database-contrib
```

## Compiling

```
cd release-build
./configure.sh
make
./Scout
```

## Compiling with QtCreator

Open project file, and press build button xD

## Development

This project uses the *Qt libraries* for c++. In order to develop scout you will need the packages specified in requirements section and optionally *qtcreator* package. QtCreator is the default IDE provided by Qt. Make sure you are using Qt5 in QtCreator. PRs are welcome!

